/*
  ==============================================================================

    Oscillator.cpp
    Created: 31 Jul 2019 9:02:47am
    Author:  Javor

  ==============================================================================
*/

#include "../../../Users/Javor/Documents/synthFramework/JuceLibraryCode/JuceHeader.h"
#include "C:\JUCE\extras\AudioPluginHost\Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameworkAudioProcessor& p) :
	processor(p)
{
	setSize(200, 200);

	oscMenu.addItem("Square", 1);
	oscMenu.addItem("Saw", 2);
	oscMenu.addItem("Sine", 3);
	oscMenu.addItem("Triangle", 4);
	oscMenu.addItem("Pulse", 5);

	oscMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&oscMenu);

	waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu);

	blendSlider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
	blendSlider1.setRange(0.0f, 1.0f);
	blendSlider1.setValue(1.0f);
	blendSlider1.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&blendSlider1);

	tuneSlider1.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	tuneSlider1.setRange(-1, 1, 1);
	tuneSlider1.setValue(0);
	tuneSlider1.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	addAndMakeVisible(&tuneSlider1);

	pwidthSlider1.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	pwidthSlider1.setRange(0, 1, 0.01);
	pwidthSlider1.setValue(0.5);
	pwidthSlider1.setTextBoxStyle(Slider::TextBoxRight, false, 35, 25);
	addAndMakeVisible(&pwidthSlider1);

	blendVal1 = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "blend1", blendSlider1);
	tuneVal1 = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "fine1", tuneSlider1);
	pwidthVal1 = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "pwidth", pwidthSlider1);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	//g.fillAll(Colours::transparentBlack);
	g.setColour(Colours::silver);
	g.drawText("VCO1", titleArea, Justification::centredTop);

	g.drawText("Gain", 27, 150, 50, 30, Justification::centredTop);
	g.drawText("Tune", 78, 112, 60, 40, Justification::centredTop);
	g.drawText("Pulse Width", 78, 70, 100, 60, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::silver);
	g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Oscillator::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);
	oscMenu.setBounds(area.removeFromTop(20));

	int sliderWidth = 25;
	int sliderHeight = 175;

	blendSlider1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	tuneSlider1.setBounds(80, 120, 80, 50);
	pwidthSlider1.setBounds(80, 80, 80, 40);
}