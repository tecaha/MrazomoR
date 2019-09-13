/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "..\..\..\..\..\..\JUCE\extras\AudioPluginHost\Oscillator.h"
#include "Oscillator2.h"
#include "Envelope.h"
#include "Filter.h"
#include "Frontgui.h"
#include "OscillatorLFO.h"

//==============================================================================
/**
*/
class SynthFrameworkAudioProcessorEditor : public AudioProcessorEditor
{
public:
    SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor&);
    ~SynthFrameworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    SynthFrameworkAudioProcessor& processor;

	Oscillator oscGui;
	Oscillator2 osc2Gui;
	Envelope envGui;
	Filter filterGui;
	Frontgui frontGui;
	OscillatorLFO oscLFOGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFrameworkAudioProcessorEditor)
};