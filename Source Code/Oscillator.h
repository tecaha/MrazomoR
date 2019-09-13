/*
  ==============================================================================

    Oscillator.h
    Created: 31 Jul 2019 9:02:47am
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../../../Users/Javor/Documents/synthFramework/JuceLibraryCode/JuceHeader.h"
#include "C:\Users\Javor\Documents\synthFramework\Source\PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(SynthFrameworkAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

private:
	ComboBox oscMenu;
	Slider blendSlider1;
	Slider tuneSlider1;
	Slider pwidthSlider1;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal1;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tuneVal1;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pwidthVal1;

	SynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
