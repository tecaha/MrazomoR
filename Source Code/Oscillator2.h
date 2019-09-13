/*
  ==============================================================================

    Oscillator2.h
    Created: 31 Jul 2019 5:01:57pm
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Oscillator2    : public Component
{
public:
    Oscillator2(SynthFrameworkAudioProcessor&);
    ~Oscillator2();

    void paint (Graphics&) override;
    void resized() override;

private:
	ComboBox osc2Menu;
	Slider blendSlider;
	Slider octaveSlider;
	Slider tuneSlider2;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection2;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> octaveVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tuneVal2;

	SynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator2)
};
