/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../../loudnessCode/models/DynamicLoudnessCH2012.h"
#include "../../loudnessCode/support/SignalBank.h"
#include "../../dsp/SPLMeter.h"
#include "../../GUI/LoudnessConfig.h"

//==============================================================================

class LoudnessMeterAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    LoudnessMeterAudioProcessor();
    ~LoudnessMeterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // info for GUI
    bool loudnessValuesReady();
    void updateLoudnessValues();
    LoudnessValues* getPointerToLoudnessValues();

    // loudness parameters
    void setLoudnessParameters (const LoudnessParameters &parameters);
    LoudnessParameters getLoudnessParameters();

    // Calibration
    void calibrate(double leftLevel, double rightLevel);
    void setMeasurementChannel (int channel);
    void setMeasurementLevel (double level);
    void setStartCalibrationMeasurement (bool shouldStart);
    void setCalibrationMeasurementNew (bool isNew);
    int getMeasurementChannel() const;
    double getMeasurementLevel () const;
    double getNewCalibrationLevel () const;
    bool isCalibrationMeasurementNew() const;

private:

    int hopSize, numEars;
    double fs;
    int samplesNeeded, writePos;
    bool pluginInitialised;

    // analysers
    AudioSampleBuffer analysisBuffer;
    loudness::SignalBank inputSignalBank;
    loudness::DynamicLoudnessCH2012 model;
    SPLMeter levelMeter;
    
    //calibration stuff
    int measurementChannel;
    double measurementLevel, newCalibrationLevel;
    double calibrationGains[2], averageGainSoFar;
    bool startCalibrationMeasurement, calibrationMeasurementNew;

    int numAuditoryChannels;

    // Pointers to loudness values 
    const loudness::Real* pointerToSTLLeft;
    const loudness::Real* pointerToSTLRight;
    const loudness::Real* pointerToPeakSTLLeft;
    const loudness::Real* pointerToPeakSTLRight;
    const loudness::Real* pointerToPeakSTLOverall;
    const loudness::Real* pointerToLTLLeft;
    const loudness::Real* pointerToLTLRight;
    const loudness::Real* pointerToLTLOverall;
    const loudness::Real* pointerToSpecificLeft;
    const loudness::Real* pointerToSpecificRight;
    
    // info for GUI
    Atomic <int> copyLoudnessValues;
    LoudnessValues loudnessValues;
    
    // loudness settings 
    LoudnessParameters loudnessParameters;
    void initialiseLoudness (const LoudnessParameters &newParameters);
    void tryAndCopyLoudnessValuesAfterProcessing (bool convertToPhons);
    
    // settings flags
    enum SettingsFlag
    {
        OkToDoStuff,
        NotOkToDoStuff
    };
    
    Atomic <SettingsFlag> settingsFlag;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoudnessMeterAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
