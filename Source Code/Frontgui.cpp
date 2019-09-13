/*
  ==============================================================================

    Frontgui.cpp
    Created: 31 Jul 2019 5:02:24pm
    Author:  Javor

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Frontgui.h"

//==============================================================================
Frontgui::Frontgui(SynthFrameworkAudioProcessor& p):
	processor(p)
{
	setSize(200, 200);

	mastergainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	mastergainSlider.setRange(0.0f, 1.0f);
	mastergainSlider.setValue(1.0f);
	mastergainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&mastergainSlider);

	pbrangeSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	pbrangeSlider.setRange(0, 12, 1);
	pbrangeSlider.setValue(12);
	pbrangeSlider.setTextBoxStyle(Slider::TextBoxRight, false, 35, 25);
	addAndMakeVisible(&pbrangeSlider);

	transposeSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	transposeSlider.setRange(0, 12, 1);
	transposeSlider.setValue(12);
	transposeSlider.setTextBoxStyle(Slider::TextBoxRight, false, 35, 25);
	addAndMakeVisible(&transposeSlider);

	mastergainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "mastergain", mastergainSlider);
	pbrangeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "pbrange", pbrangeSlider);
	transposeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "trans", transposeSlider);
}

Frontgui::~Frontgui()
{
}

void Frontgui::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	//g.fillAll(Colours::transparentBlack);
	g.setColour(Colours::silver);
	g.drawText("MAIN", titleArea, Justification::centredTop);

	g.drawText("Master", 53, 40, 40, 20, Justification::centredLeft);
	g.drawText("PB Range", 53, 90, 90, 20, Justification::centredLeft);
	g.drawText("Transpose", 53, 125, 90, 20, Justification::centredLeft);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::silver);
	g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Frontgui::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(50);

	int sliderWidth = 25;
	int sliderHeight = 25;

	mastergainSlider.setBounds(45, 20, 120, 100);
	pbrangeSlider.setBounds(45, 70, 120, 100);/*area.removeFromBottom(sliderHeight).removeFromTop(sliderHeight).withTrimmedTop(10));*/
	transposeSlider.setBounds(45, 105, 120, 100);
}
