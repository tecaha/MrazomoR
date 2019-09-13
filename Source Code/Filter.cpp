/*
  ==============================================================================

    Filter.cpp
    Created: 31 Jul 2019 5:03:05pm
    Author:  Javor

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(SynthFrameworkAudioProcessor& p) :
processor(p)
{
	setSize(200, 200);

	filterMenu.addItem("Low Pass", 1);
	filterMenu.addItem("High Pass", 2);
	filterMenu.addItem("Band Pass", 3);
	filterMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterMenu);
	filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filterType", filterMenu);

	filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutoff.setRange(20.0, 10000.0);
	filterCutoff.setValue(400.0);
	filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterCutoff);
	filterVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutoff", filterCutoff);
	filterCutoff.setSkewFactorFromMidPoint(1000.0);

	filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterRes.setRange(1, 5);
	filterRes.setValue(1);
	filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterRes);
	resVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes", filterRes);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	//g.fillAll(Colours::black);
	g.setColour(Colours::silver);
	g.drawText("VCF", titleArea, Justification::centredTop);
	
	g.drawText("Cutoff", 35, 150, 50, 30, Justification::centredTop);
	g.drawText("Resonance", 90, 150, 80, 30, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::silver);
	g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Filter::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	filterMenu.setBounds(area.removeFromTop(20));
	filterCutoff.setBounds(30, 100, 60, 60);
	filterRes.setBounds(100, 100, 60, 60);
}
