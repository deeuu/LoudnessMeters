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

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ~/SDKs/VST3SDK -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -lfftw3 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ~/SDKs/VST3SDK -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := LoudnessMeter.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ~/SDKs/VST3SDK -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -lfftw3 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ~/SDKs/VST3SDK -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := LoudnessMeter.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/DynamicLoudnessGM2002_db005328.o \
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
  $(OBJDIR)/StereoSpecificLoudnessGraph_5b2e71dc.o \
  $(OBJDIR)/BarGraph_df5e2e04.o \
  $(OBJDIR)/MeterBallistics_1bf105d8.o \
  $(OBJDIR)/StereoLoudnessBarGraph_2ac20265.o \
  $(OBJDIR)/PluginProcessor_a059e380.o \
  $(OBJDIR)/PluginEditor_94d4fb09.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_devices_a4c8a728.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_audio_processors_44a134a2.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_cryptography_25c7e826.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_opengl_c7e3506c.o \
  $(OBJDIR)/juce_PluginUtilities_e2e19a34.o \
  $(OBJDIR)/juce_video_184321c8.o \
  $(OBJDIR)/juce_VST_Wrapper_bb62e93d.o \
  $(OBJDIR)/juce_VST3_Wrapper_77e7c73b.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
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

$(OBJDIR)/DynamicLoudnessGM2002_db005328.o: ../../../loudnessCode/models/DynamicLoudnessGM2002.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DynamicLoudnessGM2002.cpp"
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

$(OBJDIR)/StereoSpecificLoudnessGraph_5b2e71dc.o: ../../Source/StereoSpecificLoudnessGraph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StereoSpecificLoudnessGraph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BarGraph_df5e2e04.o: ../../Source/BarGraph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BarGraph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MeterBallistics_1bf105d8.o: ../../Source/MeterBallistics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MeterBallistics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StereoLoudnessBarGraph_2ac20265.o: ../../Source/StereoLoudnessBarGraph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StereoLoudnessBarGraph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginProcessor_a059e380.o: ../../Source/PluginProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginEditor_94d4fb09.o: ../../Source/PluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a4c8a728.o: ../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: ../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_25c7e826.o: ../../JuceLibraryCode/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_c7e3506c.o: ../../JuceLibraryCode/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_e2e19a34.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_184321c8.o: ../../JuceLibraryCode/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_bb62e93d.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_77e7c73b.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
