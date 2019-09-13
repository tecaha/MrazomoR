/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGui(p), osc2Gui(p), envGui(p), filterGui(p), frontGui(p), oscLFOGui(p)
{
	setSize(1600, 200);
	addAndMakeVisible(&oscGui);
	addAndMakeVisible(&osc2Gui);
	addAndMakeVisible(&envGui);
	addAndMakeVisible(&filterGui);
	addAndMakeVisible(&frontGui);
	addAndMakeVisible(&oscLFOGui);
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
	Image background = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
	g.drawImageAt(background, 0, 0);
}

void SynthFrameworkAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area = getLocalBounds();

	const int componentWidth = 200;
	const int componentHeight = 200;

	oscLFOGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	osc2Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	area.removeFromLeft(componentWidth).removeFromTop(componentHeight);
	area.removeFromLeft(componentWidth).removeFromTop(componentHeight);
	filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	frontGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}