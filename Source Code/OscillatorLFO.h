/*
  ==============================================================================

    OscillatorLFO.h
    Created: 8 Aug 2019 7:05:17pm
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OscillatorLFO    : public Component
{
public:
    OscillatorLFO(SynthFrameworkAudioProcessor&);
    ~OscillatorLFO();

    void paint (Graphics&) override;
    void resized() override;

private:

	ComboBox oscMenuLFO;
	ComboBox routeMenuLFO;
	Slider amountSlider;
	Slider rateSlider;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> routeLFOSelection;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveLFOSelection;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> amountVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rateVal;

	SynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorLFO)
};
