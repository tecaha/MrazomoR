/*
  ==============================================================================

    OscillatorLFO.cpp
    Created: 8 Aug 2019 7:05:17pm
    Author:  Javor

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscillatorLFO.h"

//==============================================================================
OscillatorLFO::OscillatorLFO(SynthFrameworkAudioProcessor& p) :
	processor(p)
{
	setSize(200, 200);

	oscMenuLFO.addItem("Square", 1);
	oscMenuLFO.addItem("Saw", 2);
	oscMenuLFO.addItem("Sine", 3);
	oscMenuLFO.addItem("Triangle", 4);

	oscMenuLFO.setJustificationType(Justification::centred);
	addAndMakeVisible(&oscMenuLFO);

	routeMenuLFO.addItem("VCO1", 1);
	routeMenuLFO.addItem("VCO2", 2);
	routeMenuLFO.addItem("VCO1+2", 3);
	routeMenuLFO.addItem("PWM", 4);

	routeMenuLFO.setJustificationType(Justification::centred);
	addAndMakeVisible(&routeMenuLFO);

	routeLFOSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "routetypeLFO", routeMenuLFO);
	waveLFOSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetypeLFO", oscMenuLFO);

	amountSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	amountSlider.setRange(0.0f, 1.0f);
	amountSlider.setValue(1.0f);
	amountSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&amountSlider);

	rateSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	rateSlider.setRange(0.0, 6, 0.1);
	rateSlider.setValue(3);
	rateSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&rateSlider);

	amountVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "amountLFO", amountSlider);
	rateVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "rateLFO", rateSlider);
}

OscillatorLFO::~OscillatorLFO()
{
}

void OscillatorLFO::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::transparentBlack);
	g.setColour(Colours::silver);
	g.drawText("LFO", titleArea, Justification::centredTop);

	g.drawText("Amount", 35, 150, 50, 30, Justification::centredTop);
	g.drawText("Rate", 105, 150, 50, 30, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::silver);
	g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void OscillatorLFO::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);
	oscMenuLFO.setBounds(area.removeFromTop(20));
	area.removeFromTop(5);
	routeMenuLFO.setBounds(area.removeFromTop(20));

	int sliderWidth = 25;
	int sliderHeight = 175;

	amountSlider.setBounds(30, 100, 60, 60);
	rateSlider.setBounds(100, 100, 60, 60);
}
