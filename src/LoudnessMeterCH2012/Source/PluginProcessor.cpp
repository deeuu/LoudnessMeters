/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../../loudnessCode/support/AuditoryTools.h"

//==============================================================================
LoudnessMeterAudioProcessor::LoudnessMeterAudioProcessor()
    : model(),
      inputSignalBank(),
      levelMeter (SPLMeter::SLOW, 2e-5),
      pluginInitialised (false),
      copyLoudnessValues (1),
      settingsFlag (OkToDoStuff),
      measurementChannel(0), measurementLevel (94.0),
      newCalibrationLevel (0.0)
{
    loudnessParameters.modelRate = 62.5;
    loudnessParameters.camSpacing = 0.5;
    loudnessParameters.compression = 0.2;
    loudnessParameters.filter = 0;
}

LoudnessMeterAudioProcessor::~LoudnessMeterAudioProcessor()
{
}

//==============================================================================
const String LoudnessMeterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int LoudnessMeterAudioProcessor::getNumParameters()
{
    return 0;
}

float LoudnessMeterAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void LoudnessMeterAudioProcessor::setParameter (int index, float newValue)
{
}

const String LoudnessMeterAudioProcessor::getParameterName (int index)
{
    return String();
}

const String LoudnessMeterAudioProcessor::getParameterText (int index)
{
    return String();
}

const String LoudnessMeterAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String LoudnessMeterAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool LoudnessMeterAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool LoudnessMeterAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool LoudnessMeterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LoudnessMeterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LoudnessMeterAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double LoudnessMeterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LoudnessMeterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LoudnessMeterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LoudnessMeterAudioProcessor::setCurrentProgram (int index)
{
}

const String LoudnessMeterAudioProcessor::getProgramName (int index)
{
    return String();
}

void LoudnessMeterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void LoudnessMeterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    fs = sampleRate;
    
    //Logger::outputDebugString ("prepareToPlay: numInputChannels:" + String (getNumInputChannels()) + "\n");
    
    if(!pluginInitialised)//Ardour hack
    {
        initialiseLoudness (loudnessParameters);
    }
}

void LoudnessMeterAudioProcessor::initialiseLoudness (const LoudnessParameters &newLoudnessParameters)
{
    loudnessParameters = newLoudnessParameters;
    
    /*
    * Model configuration
    */

    //limit to two channels (ears)
    numEars = 2;

    //set up an input buffer with a default hop size of 4ms
    //use something larger for debugging, e.g. 32ms
    hopSize = static_cast <int> (round (fs / loudnessParameters.modelRate));
    samplesNeeded = hopSize;
    writePos = 0;

    //loudness model configuration and initialisation
    inputSignalBank.initialize (numEars, 1, hopSize, (int) fs);
    model.configureModelParameters ("Faster");
    model.setPresentationDiotic (false); //required for left and right output
    model.setPeakSTLFollowerUsed (true);
    //set default params
    model.setRate (loudnessParameters.modelRate);
    model.setFilterSpacingInCams (loudnessParameters.camSpacing);
    model.setCompressionCriterionInCams (loudnessParameters.compression);
    model.setExcitationPatternInterpolated (false);

    switch (loudnessParameters.filter)
    {
        case 0 :
            model.setOuterEarFilter (loudness::OME::ANSIS342007_FREEFIELD);
            break;
        case 1 :
            model.setOuterEarFilter (loudness::OME::ANSIS342007_DIFFUSEFIELD);
            break;
        case 2 :
            model.setOuterEarFilter (loudness::OME::BD_DT990);
            break;
        case 3 :
            model.setOuterEarFilter (loudness::OME::NONE);
            break;
        default :
            model.setOuterEarFilter (loudness::OME::ANSIS342007_FREEFIELD);
    }

    //initialise the model
    model.initialize (inputSignalBank);

    //initialise level meter
    levelMeter.setNumBlocksToAverage ( static_cast <int> (8.0f * fs / hopSize));
    levelMeter.initialize (inputSignalBank);

    //initial calibration gains at unity
    calibrationGains[0] = 1.0;
    calibrationGains[1] = 1.0;
    newCalibrationLevel = 0.0;
    
    /*
    * Pointers to loudness measures
    */

    // STL
    const loudness::SignalBank* bank = &model.getOutput ("ShortTermLoudness");
    pointerToSTLLeft = bank -> getSingleSampleReadPointer (0, 0);
    pointerToSTLRight = bank -> getSingleSampleReadPointer (1, 0);

    // Peak STL
    bank = &model.getOutput ("PeakShortTermLoudness");
    pointerToPeakSTLLeft = bank -> getSingleSampleReadPointer (0, 0);
    pointerToPeakSTLRight = bank -> getSingleSampleReadPointer (1, 0);
    pointerToPeakSTLOverall = bank -> getSingleSampleReadPointer (2, 0);

    // LTL
    bank = &model.getOutput ("LongTermLoudness");
    pointerToLTLLeft = bank -> getSingleSampleReadPointer (0, 0);
    pointerToLTLRight = bank -> getSingleSampleReadPointer (1, 0);
    pointerToLTLOverall = bank -> getSingleSampleReadPointer (2, 0);

    // Specific loudness (loudness as a function of frequency)
    bank = &model.getOutput ("SpecificLoudness");
    pointerToSpecificLeft = bank -> getSingleSampleReadPointer (0, 0);
    pointerToSpecificRight = bank -> getSingleSampleReadPointer (1, 0);
    
    numAuditoryChannels = bank -> getNChannels();
    
    copyLoudnessValues.set (1);
    loudnessValues.leftSpecificLoudness.clear();
    loudnessValues.rightSpecificLoudness.clear();
    loudnessValues.centreFrequencies.clear();
    
    const loudness::Real* ptr = bank -> getCentreFreqsReadPointer(0);

    for (int i = 0; i < numAuditoryChannels; ++i)
    {
        loudnessValues.leftSpecificLoudness.add (0);
        loudnessValues.rightSpecificLoudness.add (0);
        loudnessValues.centreFrequencies.add (loudness::hertzToCam (ptr[i]));
    }

    pluginInitialised = true;
}

void LoudnessMeterAudioProcessor::setLoudnessParameters (const LoudnessParameters &newLoudnessParameters)
{
    while (! settingsFlag.compareAndSetBool (NotOkToDoStuff, OkToDoStuff))
    {
        Thread::sleep (10);
    }

    initialiseLoudness (newLoudnessParameters);
    settingsFlag.set (OkToDoStuff);
}

LoudnessParameters LoudnessMeterAudioProcessor::getLoudnessParameters()
{
    return loudnessParameters;
}

void LoudnessMeterAudioProcessor::releaseResources()
{
    if(pluginInitialised)
    {
        pluginInitialised = false;
    }
}

void LoudnessMeterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // analyse audio if settings aren't being changed
    if (settingsFlag.compareAndSetBool (NotOkToDoStuff, OkToDoStuff))
    {
        /*
         * Buffer -> SignalBank -> Model
         */

        int numSamples = buffer.getNumSamples();
        int numInputChannels = buffer.getNumChannels();
        int remainingSamples = numSamples;
        int readPos = 0;

        // deal with any samples in the input which will create full hop buffers for us
        while (remainingSamples >= samplesNeeded)
        {
            //fill the SignalBank to be processed
            for (int ear = 0; ear < numEars; ++ear)
            {
                const float* signalToCopy = buffer.getReadPointer (ear);
                inputSignalBank.copySamples (ear, 0, writePos, signalToCopy + readPos, samplesNeeded);

                //calibration
                inputSignalBank.scale (ear, calibrationGains[ear]);
            }

            //model process call
            model.process (inputSignalBank);

            //SPL meter process call
            if (startCalibrationMeasurement)
            {
                //levelMeter.reset(); //as can bias measurement
                levelMeter.setRunningSumActive(true);
                startCalibrationMeasurement = false;
            }
            else if(levelMeter.isAverageReady())
            {
                newCalibrationLevel = measurementLevel - 
                    levelMeter.getAverageLevel (measurementChannel);
                levelMeter.setAverageReady(false);
                calibrationMeasurementNew = true;
            }

            levelMeter.process (inputSignalBank);

            remainingSamples -= samplesNeeded;
            readPos += samplesNeeded;
            samplesNeeded = hopSize;
            writePos = 0;
        }

        // grab any samples we need to save for the next processBlock call
        if (remainingSamples != 0)
        {
            for (int ear = 0; ear < numEars; ++ear)
            {
                int idx = ear;
                if (numInputChannels == 1)
                    idx = 0;
                const float* signalToCopy = buffer.getReadPointer (ear);
                inputSignalBank.copySamples (ear, 0, writePos, signalToCopy + readPos, samplesNeeded);
            }

            samplesNeeded -= remainingSamples;
            writePos += remainingSamples;
        }

        /*
         * Output
         */
        
        tryAndCopyLoudnessValuesAfterProcessing(false);
        
        settingsFlag.set (OkToDoStuff);
    }
}

//==============================================================================
bool LoudnessMeterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* LoudnessMeterAudioProcessor::createEditor()
{
    return new LoudnessMeterAudioProcessorEditor (*this);
}

//==============================================================================
void LoudnessMeterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LoudnessMeterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// CALIBRATION METHODS
//==============================================================================
void LoudnessMeterAudioProcessor::calibrate(double leftLevel, double rightLevel)
{
    if (std::abs (leftLevel) < 20)
        calibrationGains[0] *= Decibels::decibelsToGain (leftLevel);
    else
        calibrationGains[0] = 1.0;
    if (std::abs (rightLevel) < 20)
        calibrationGains[1] *= Decibels::decibelsToGain (rightLevel);
    else
        calibrationGains[1] = 1.0;
}

void LoudnessMeterAudioProcessor::setMeasurementChannel (int channel)
{
    measurementChannel = channel;
}

void LoudnessMeterAudioProcessor::setMeasurementLevel (double level)
{
    measurementLevel = level;
}

void LoudnessMeterAudioProcessor::setStartCalibrationMeasurement (bool shouldStart)
{
    startCalibrationMeasurement = shouldStart;
}

int LoudnessMeterAudioProcessor::getMeasurementChannel() const
{
    return measurementChannel;
}

double LoudnessMeterAudioProcessor::getMeasurementLevel () const
{
    return measurementLevel;
}

double LoudnessMeterAudioProcessor::getNewCalibrationLevel () const
{
    return newCalibrationLevel;
}

bool LoudnessMeterAudioProcessor::isCalibrationMeasurementNew() const
{
    return calibrationMeasurementNew;
}

void LoudnessMeterAudioProcessor::setCalibrationMeasurementNew(bool isNew)
{
    calibrationMeasurementNew = isNew;
}

//==============================================================================
bool LoudnessMeterAudioProcessor::loudnessValuesReady()
{
    return (copyLoudnessValues.get() == 0);
}

void LoudnessMeterAudioProcessor::updateLoudnessValues()
{
    copyLoudnessValues.set (1);
}

LoudnessValues* LoudnessMeterAudioProcessor::getPointerToLoudnessValues()
{
    return &loudnessValues;
}

void LoudnessMeterAudioProcessor::tryAndCopyLoudnessValuesAfterProcessing (bool convertToPhons)
{
    if (copyLoudnessValues.get() == 1)
    {
        // STL, LTL features
        loudnessValues.leftSTL = *pointerToSTLLeft;
        loudnessValues.rightSTL = *pointerToSTLRight;
        loudnessValues.rightPeakSTL = *pointerToPeakSTLRight;
        loudnessValues.leftPeakSTL = *pointerToPeakSTLLeft;
        loudnessValues.overallPeakSTL = *pointerToPeakSTLOverall;
        loudnessValues.leftLTL = *pointerToLTLLeft;
        loudnessValues.rightLTL = *pointerToLTLRight;
        loudnessValues.overallLTL = *pointerToLTLOverall;

        // Specific loudness
        for (int i = 0; i < numAuditoryChannels; ++i)
        {
            loudnessValues.leftSpecificLoudness.set (i, pointerToSpecificLeft [i]);
            loudnessValues.rightSpecificLoudness.set (i, pointerToSpecificRight [i]);
        }

        // Level
        loudnessValues.averageSPL = levelMeter.getLevel();
                
        copyLoudnessValues.set (0);
    }
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LoudnessMeterAudioProcessor();
}