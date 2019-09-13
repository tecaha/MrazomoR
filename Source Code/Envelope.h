/*
  ==============================================================================

    Envelope.h
    Created: 31 Jul 2019 11:42:26am
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(SynthFrameworkAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;



	SynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
