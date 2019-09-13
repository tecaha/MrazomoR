/*
  ==============================================================================

    Oscillator2.cpp
    Created: 31 Jul 2019 5:01:57pm
    Author:  Javor

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator2.h"

//==============================================================================
Oscillator2::Oscillator2(SynthFrameworkAudioProcessor& p) :
	processor(p)
{
	setSize(200, 200);

	osc2Menu.addItem("Square", 1);
	osc2Menu.addItem("Saw", 2);
	osc2Menu.addItem("Sine", 3);
	osc2Menu.addItem("Triangle", 4);
	osc2Menu.addItem("Pulse", 5);
	osc2Menu.setJustificationType(Justification::centred);
	addAndMakeVisible(&osc2Menu);

	waveSelection2 = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype2", osc2Menu);

	blendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	blendSlider.setRange(0.0f, 1.0f);
	blendSlider.setValue(1.0f);
	blendSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&blendSlider);

	octaveSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	octaveSlider.setRange(-1, 1, 1);
	octaveSlider.setValue(0);
	octaveSlider.setTextBoxStyle(Slider::TextBoxRight, false, 30, 20);
	addAndMakeVisible(&octaveSlider);

	tuneSlider2.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	tuneSlider2.setRange(-1, 1, 1);
	tuneSlider2.setValue(0);
	tuneSlider2.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	addAndMakeVisible(&tuneSlider2);

	blendVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "blend2", blendSlider);
	octaveVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "octave2", octaveSlider);
	tuneVal2 = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "fine2", tuneSlider2);

}

Oscillator2::~Oscillator2()
{
}

void Oscillator2::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	//g.fillAll(Colours::black);
	g.setColour(Colours::silver);
	g.drawText("VCO2", titleArea, Justification::centredTop);

	g.drawText("Gain", 27, 150, 50, 30, Justification::centredTop);
	g.drawText("Octave", 80, 70, 60, 40, Justification::centredTop);
	g.drawText("Tune", 78, 112, 60, 40, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::silver);
	g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Oscillator2::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);
	osc2Menu.setBounds(area.removeFromTop(20));

	int sliderWidth = 25;
	int sliderHeight = 175;

	blendSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	octaveSlider.setBounds(80, 80, 80, 30);
	tuneSlider2.setBounds(80, 120, 80, 50);
}
