/*
  ==============================================================================

    Filter.h
    Created: 31 Jul 2019 5:03:05pm
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(SynthFrameworkAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
	Slider filterCutoff;
	Slider filterRes;

	ComboBox filterMenu;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;

	SynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
