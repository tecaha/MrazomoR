/*
  ==============================================================================

    Frontgui.h
    Created: 31 Jul 2019 5:02:23pm
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Frontgui    : public Component
{
public:
    Frontgui(SynthFrameworkAudioProcessor&);
    ~Frontgui();

    void paint (Graphics&) override;
    void resized() override;

private:
	Slider mastergainSlider;
	Slider pbrangeSlider;
	Slider transposeSlider;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mastergainVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbrangeVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> transposeVal;

	SynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Frontgui)
};
