/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

//==============================================================================
SynthFrameworkAudioProcessor::SynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	tree(*this, nullptr, "PARAMETERS",
		{
			std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
			std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(1.0f, 2000.0f), 1.0f),
			std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 1.0f), 0.8f),
			std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.1f, 5000.0f), 0.1f),

			std::make_unique<AudioParameterFloat>("filterType", "FilterType", NormalisableRange<float>(0.0f, 4.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("filterCutoff", "FilterCutoff", NormalisableRange<float>(20.0f, 10000.0f), 400.0f),
			std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", NormalisableRange<float>(1.0f, 5.0f), 1.0f),

			std::make_unique<AudioParameterFloat>("wavetype", "WaveType", NormalisableRange<float>(0.0f, 5.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("wavetype2", "WaveType2", NormalisableRange<float>(0.0f, 4.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("blend1", "Osc1Blend", NormalisableRange<float>(0.0f, 1.0f), 0.6f),
			std::make_unique<AudioParameterFloat>("blend2", "Osc2Blend", NormalisableRange<float>(0.0f, 1.0f), 0.6f),
			std::make_unique<AudioParameterFloat>("octave2", "Octave2", NormalisableRange<float>(-1.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("fine1", "Fine1", NormalisableRange<float>(-1.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("fine2", "Fine2", NormalisableRange<float>(-1.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("pwidth", "Pwidth", NormalisableRange<float>(0.0f, 1.0f), 0.5f),

			std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", NormalisableRange<float>(0.0f, 1.0f), 0.7f),
			std::make_unique<AudioParameterFloat>("pbrange", "PBRange", NormalisableRange<float>(1.0f, 12.0f), 1.0f),
			std::make_unique<AudioParameterFloat>("trans", "Trans", NormalisableRange<float>(-12, 12), 0),

			std::make_unique<AudioParameterFloat>("amountLFO", "AmountLFO", NormalisableRange<float>(0.0f, 1.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("rateLFO", "RateLFO", NormalisableRange<float>(0.0f, 6.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("wavetypeLFO", "WavetypeLFO", NormalisableRange<float>(0.0f, 3.0f), 0.0f),
			std::make_unique<AudioParameterFloat>("routetypeLFO", "RoutetypeLFO", NormalisableRange<float>(0.0f, 3.0f), 0.0f),
		})
#endif
{

	mySynth.clearVoices();

	for (int i = 0; i < 8; i++)
	{
		mySynth.addVoice(new SynthVoice());
	}

	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());
}

SynthFrameworkAudioProcessor::~SynthFrameworkAudioProcessor()
{
}

//==============================================================================
const String SynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

	dsp::ProcessSpec spec;
	spec.sampleRate = lastSampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getTotalNumOutputChannels();

	stateVariableFilter.reset();
	stateVariableFilter.prepare(spec);
	updateFilter();
}

void SynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthFrameworkAudioProcessor::updateFilter()
{
	int menuChoice = *tree.getRawParameterValue("filterType");
	int freq = *tree.getRawParameterValue("filterCutoff");
	int res = *tree.getRawParameterValue("filterRes");


	if (menuChoice == 0)
	{
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
	}

	if (menuChoice == 1)
	{
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
	}

	if (menuChoice == 2)
	{
		stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
		stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
	}
}

void SynthFrameworkAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	
	//get the voice and get the params needed to make the voice
	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{
		//if myVoice sucessfully casts as a SynthVoice*, get the voice and set the params
		if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
		{
			myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"),
				tree.getRawParameterValue("decay"),
				tree.getRawParameterValue("sustain"),
				tree.getRawParameterValue("release"));

			myVoice->getOscType(tree.getRawParameterValue("wavetype"));
			myVoice->getOsc2Type(tree.getRawParameterValue("wavetype2"));
			myVoice->getLFOType(tree.getRawParameterValue("wavetypeLFO"));
			myVoice->getLFORoute(tree.getRawParameterValue("routetypeLFO"));

			myVoice->getFilterParams(tree.getRawParameterValue("filterType"),
				tree.getRawParameterValue("filterCutoff"),
				tree.getRawParameterValue("filterRes"));

			myVoice->getWillsParams(tree.getRawParameterValue("mastergain"),
				tree.getRawParameterValue("blend1"),
				tree.getRawParameterValue("blend2"),
				tree.getRawParameterValue("pbrange"),
				tree.getRawParameterValue("octave2"),
				tree.getRawParameterValue("fine1"),
				tree.getRawParameterValue("fine2"),
				tree.getRawParameterValue("trans"),
				tree.getRawParameterValue("pwidth"),
				tree.getRawParameterValue("amountLFO"),
				tree.getRawParameterValue("rateLFO"));
		}
	}

	buffer.clear();
	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	updateFilter();
	dsp::AudioBlock<float> block(buffer);
	stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool SynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthFrameworkAudioProcessor::createEditor()
{
    return new SynthFrameworkAudioProcessorEditor (*this);
}

//==============================================================================
void SynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFrameworkAudioProcessor();
}
