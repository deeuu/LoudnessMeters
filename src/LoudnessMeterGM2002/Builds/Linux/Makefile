# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := /usr/local/lib/lxvst/

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ~/SDKs/VST3SDK -I ../../JuceLibraryCode -I ../../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -lfftw3 

  TARGET := LoudnessMeterGM2002.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := /usr/local/lib/lxvst/

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ~/SDKs/VST3SDK -I ../../JuceLibraryCode -I ../../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -O3
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -lfftw3 

  TARGET := LoudnessMeterGM2002.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/BarGraph_ac7ecd93.o \
  $(OBJDIR)/CalibrationScreen_d815dea8.o \
  $(OBJDIR)/Graduations_3a8dccb7.o \
  $(OBJDIR)/LoudnessValueDisplay_848865f2.o \
  $(OBJDIR)/MeterBallistics_2c779769.o \
  $(OBJDIR)/SettingsButton_785aca8d.o \
  $(OBJDIR)/SettingsScreen_4a1b36c7.o \
  $(OBJDIR)/StereoLoudnessBarGraph_f870bbb4.o \
  $(OBJDIR)/StereoSpecificLoudnessGraph_219a31ed.o \
  $(OBJDIR)/PluginEditor_94d4fb09.o \
  $(OBJDIR)/PluginProcessor_a059e380.o \
  $(OBJDIR)/SPLMeter_9543c14c.o \
  $(OBJDIR)/DynamicLoudnessGM2002_db005328.o \
  $(OBJDIR)/PeakFollower_22a7b244.o \
  $(OBJDIR)/ARAverager_b708694d.o \
  $(OBJDIR)/BinauralInhibitionMG2007_157fe669.o \
  $(OBJDIR)/Butter_dfc5e627.o \
  $(OBJDIR)/CompressSpectrum_3bcd1d7a.o \
  $(OBJDIR)/FastRoexBank_11dca12f.o \
  $(OBJDIR)/FIR_795a4312.o \
  $(OBJDIR)/FrameGenerator_92c270d.o \
  $(OBJDIR)/IIR_180cf4d5.o \
  $(OBJDIR)/InstantaneousLoudness_70fd01e2.o \
  $(OBJDIR)/PowerSpectrum_c9a7b5f9.o \
  $(OBJDIR)/RoexBankANSIS342007_5d1cc40d.o \
  $(OBJDIR)/SpecificLoudnessANSIS342007_84a2683e.o \
  $(OBJDIR)/WeightSpectrum_c7719810.o \
  $(OBJDIR)/Window_4a432417.o \
  $(OBJDIR)/AuditoryTools_55b43cab.o \
  $(OBJDIR)/FFT_9d08787f.o \
  $(OBJDIR)/Filter_99933a57.o \
  $(OBJDIR)/Model_da5a7bf4.o \
  $(OBJDIR)/Module_c2477b4b.o \
  $(OBJDIR)/SignalBank_80ff8e3.o \
  $(OBJDIR)/cnpy_9262e5e.o \
  $(OBJDIR)/Spline_78a3501e.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_d0bb57db.o \
  $(OBJDIR)/juce_audio_devices_14f021d9.o \
  $(OBJDIR)/juce_audio_formats_43716b79.o \
  $(OBJDIR)/juce_audio_processors_6f42693.o \
  $(OBJDIR)/juce_core_1fecf6bd.o \
  $(OBJDIR)/juce_cryptography_d2405b17.o \
  $(OBJDIR)/juce_data_structures_836f8eb9.o \
  $(OBJDIR)/juce_events_fc7bbcb1.o \
  $(OBJDIR)/juce_graphics_79a0db95.o \
  $(OBJDIR)/juce_gui_basics_bd727091.o \
  $(OBJDIR)/juce_gui_extra_b8299259.o \
  $(OBJDIR)/juce_opengl_bcc3e4dd.o \
  $(OBJDIR)/juce_PluginUtilities_de4792e5.o \
  $(OBJDIR)/juce_video_64701e79.o \
  $(OBJDIR)/juce_VST_Wrapper_34c122ee.o \
  $(OBJDIR)/juce_VST3_Wrapper_129e58ac.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking LoudnessMeter
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning LoudnessMeter
	@$(CLEANCMD)

strip:
	@echo Stripping LoudnessMeter
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/BarGraph_ac7ecd93.o: ../../../GUI/BarGraph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BarGraph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CalibrationScreen_d815dea8.o: ../../../GUI/CalibrationScreen.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CalibrationScreen.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Graduations_3a8dccb7.o: ../../../GUI/Graduations.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Graduations.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessValueDisplay_848865f2.o: ../../../GUI/LoudnessValueDisplay.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessValueDisplay.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MeterBallistics_2c779769.o: ../../../GUI/MeterBallistics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MeterBallistics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SettingsButton_785aca8d.o: ../../../GUI/SettingsButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SettingsButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SettingsScreen_4a1b36c7.o: ../../../GUI/SettingsScreen.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SettingsScreen.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StereoLoudnessBarGraph_f870bbb4.o: ../../../GUI/StereoLoudnessBarGraph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StereoLoudnessBarGraph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StereoSpecificLoudnessGraph_219a31ed.o: ../../../GUI/StereoSpecificLoudnessGraph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StereoSpecificLoudnessGraph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginEditor_94d4fb09.o: ../../Source/PluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginProcessor_a059e380.o: ../../Source/PluginProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SPLMeter_9543c14c.o: ../../../dsp/SPLMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SPLMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DynamicLoudnessGM2002_db005328.o: ../../../loudnessCode/models/DynamicLoudnessGM2002.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DynamicLoudnessGM2002.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PeakFollower_22a7b244.o: ../../../loudnessCode/modules/PeakFollower.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PeakFollower.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ARAverager_b708694d.o: ../../../loudnessCode/modules/ARAverager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ARAverager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinauralInhibitionMG2007_157fe669.o: ../../../loudnessCode/modules/BinauralInhibitionMG2007.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinauralInhibitionMG2007.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Butter_dfc5e627.o: ../../../loudnessCode/modules/Butter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Butter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CompressSpectrum_3bcd1d7a.o: ../../../loudnessCode/modules/CompressSpectrum.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CompressSpectrum.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FastRoexBank_11dca12f.o: ../../../loudnessCode/modules/FastRoexBank.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FastRoexBank.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FIR_795a4312.o: ../../../loudnessCode/modules/FIR.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FIR.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FrameGenerator_92c270d.o: ../../../loudnessCode/modules/FrameGenerator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FrameGenerator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/IIR_180cf4d5.o: ../../../loudnessCode/modules/IIR.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling IIR.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InstantaneousLoudness_70fd01e2.o: ../../../loudnessCode/modules/InstantaneousLoudness.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InstantaneousLoudness.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PowerSpectrum_c9a7b5f9.o: ../../../loudnessCode/modules/PowerSpectrum.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PowerSpectrum.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RoexBankANSIS342007_5d1cc40d.o: ../../../loudnessCode/modules/RoexBankANSIS342007.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RoexBankANSIS342007.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SpecificLoudnessANSIS342007_84a2683e.o: ../../../loudnessCode/modules/SpecificLoudnessANSIS342007.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SpecificLoudnessANSIS342007.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/WeightSpectrum_c7719810.o: ../../../loudnessCode/modules/WeightSpectrum.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling WeightSpectrum.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Window_4a432417.o: ../../../loudnessCode/modules/Window.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Window.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AuditoryTools_55b43cab.o: ../../../loudnessCode/support/AuditoryTools.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AuditoryTools.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FFT_9d08787f.o: ../../../loudnessCode/support/FFT.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FFT.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Filter_99933a57.o: ../../../loudnessCode/support/Filter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Filter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Model_da5a7bf4.o: ../../../loudnessCode/support/Model.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Model.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Module_c2477b4b.o: ../../../loudnessCode/support/Module.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Module.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SignalBank_80ff8e3.o: ../../../loudnessCode/support/SignalBank.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SignalBank.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cnpy_9262e5e.o: ../../../loudnessCode/thirdParty/cnpy/cnpy.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cnpy.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Spline_78a3501e.o: ../../../loudnessCode/thirdParty/spline/Spline.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Spline.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_d0bb57db.o: ../../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_14f021d9.o: ../../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_43716b79.o: ../../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_6f42693.o: ../../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_1fecf6bd.o: ../../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_d2405b17.o: ../../../JuceLibraryCode/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_836f8eb9.o: ../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_fc7bbcb1.o: ../../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_79a0db95.o: ../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_bd727091.o: ../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_b8299259.o: ../../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_bcc3e4dd.o: ../../../JuceLibraryCode/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_de4792e5.o: ../../../JuceLibraryCode/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_64701e79.o: ../../../JuceLibraryCode/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_34c122ee.o: ../../../JuceLibraryCode/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_129e58ac.o: ../../../JuceLibraryCode/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
