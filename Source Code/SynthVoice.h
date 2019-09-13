/*
  ==============================================================================

    SynthVoice.h
    Created: 29 Jul 2019 2:05:51am
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast <SynthSound*>(sound) != nullptr;
	}

	void setPitchBend(int pitchWheelPos)
	{
		if (pitchWheelPos > 8192)
		{
			// shifting up
			pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
		}
		else
		{
			// shifting down
			pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
		}
	}

	float pitchBendCents()
	{
		if (pitchBend >= 0.0f)
		{
			// shifting up
			return pitchBend* pitchBendRangeSemitones * 100;
		}
		else
		{
			// shifting down
			return pitchBend * pitchBendRangeSemitones * 100;
		}
	}

	float transposeCents()
	{
		return transpose * 100;
	}

	static double noteHz(int midiNoteNumber, double centsOffset)
	{
		double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		hertz *= std::pow(2.0, centsOffset / 1200);
		return hertz;
	}

	//=======================================================

	void getOscType(float* selection)
	{
		theWave = *selection;

	}

	void getOsc2Type(float* selection)
	{

		theWave2 = *selection;
	}

	void getLFOType(float* selection)
	{
		theWaveLFO = *selection;
	}
	//=======================================================
	
	double setLFORoute()
	{
		return LFOroute;
	}

	void getLFORoute(float* selection)
	{
		LFOroute = *selection;
	}

	double setLFOType()
	{
		double sampleLFO;

		switch (theWaveLFO)
		{
		case 0:
			sampleLFO = oscLFO.square(LFOrate);
			break;
		case 1:
			sampleLFO = oscLFO.saw(LFOrate);
			break;
		case 2:
			sampleLFO = oscLFO.sinewave(LFOrate);
			break;
		case 3:
			sampleLFO = oscLFO.triangle(LFOrate);
			break;
		default:
			sampleLFO = oscLFO.sinewave(LFOrate);
			break;
		}
		return sampleLFO * LFOamount;
	}


	double setOscType()

	{
		double sample1, sample2, modulatorLFO1=1, modulatorLFO2=1, modulatorLFO12=1,pwmod=1;
		float octaveMultiplier;
	
		if (LFOroute == 0)
		{
			if ((LFOrate && LFOamount) > 0)
			{
				modulatorLFO1 = setLFOType();
			}
			else
				modulatorLFO1 = 1;
		}
		else if (LFOroute == 1)
		{
			if ((LFOrate && LFOamount) > 0)
			{
				modulatorLFO2 = setLFOType();
			}
			else
				modulatorLFO2 = 1;
		}
		else if (LFOroute == 2)
		{
			if ((LFOrate && LFOamount) > 0)
			{
				modulatorLFO1 = modulatorLFO2 =setLFOType();
			}
			else
				modulatorLFO1 = modulatorLFO2 = 1;
		}
		else if (LFOroute == 3)
		{
			if ((LFOrate && LFOamount) > 0)
			{
				pwmod = setLFOType();
			}
			else
				pwmod = 1;
		}
		else
		{
			modulatorLFO1 = modulatorLFO2 = modulatorLFO12 = 1;
		}



		switch (theWave)
		{
		case 0:
			sample1 = osc1.square(frequency + detune1) * modulatorLFO1;
			break;
		case 1:
			sample1 = osc1.saw(frequency + detune1) * modulatorLFO1;
			break;
		case 2:
			sample1 = osc1.sinewave(frequency + detune1) * modulatorLFO1;
			break;
		case 3:
			sample1 = osc1.triangle(frequency + detune1) * modulatorLFO1;
			break;
		case 4:
			sample1 = osc1.pulse(frequency + detune1, pulseWidth * pwmod) * modulatorLFO1;
			break;
		default:
			sample1 = osc1.pulse(frequency + detune1, pulseWidth * pwmod) * modulatorLFO1;
			break;
		}

		if (osc2octave == -1)
		{
			octaveMultiplier = 0.5;
		}
		else if(osc2octave == 1)
		{
			octaveMultiplier = 2;
		}
		else
		{
			octaveMultiplier = 1;
		}

		switch (theWave2)
		{
		case 0:
			sample2 = osc2.square((frequency * octaveMultiplier) + detune2) * modulatorLFO2;
			break;
		case 1:
			sample2 = osc2.saw((frequency * octaveMultiplier) + detune2) * modulatorLFO2;
			break;
		case 2:
			sample2 = osc2.sinewave((frequency * octaveMultiplier) + detune2) * modulatorLFO2;
			break;
		case 3:
			sample2 = osc2.triangle((frequency * octaveMultiplier) + detune2) * modulatorLFO2;
			break;
		case 4:
			sample2 = osc2.pulse((frequency * octaveMultiplier) + detune2, (1-pulseWidth) * pwmod) * modulatorLFO2;
			break;
		default:
			sample2 = osc2.sinewave((frequency * octaveMultiplier) + detune2) * modulatorLFO2;
			break;
		}

		return osc1blend * sample1 + osc2blend * sample2;
	}

	//=======================================================

	void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
	{
		env1.setAttack(*attack);
		env1.setDecay(*decay);
		env1.setSustain(*sustain);
		env1.setRelease(*release);
	}

	//=======================================================

	double setEnvelope()
	{
		return env1.adsr(setOscType(), env1.trigger);
	}

	//=======================================================

	void getWillsParams(float* mGain, float* blend1,float *blend2, float* pb, float* octave2, float* fine1, float* fine2, float* trans, float* pwidth, float* amountLFO, float* rateLFO)
	{
		masterGain = *mGain;
		osc1blend = *blend1;
		osc2blend = *blend2;
		osc2octave = *octave2;
		pitchBendRangeSemitones = *pb;
		detune1 = *fine1;
		detune2 = *fine2;
		transpose = *trans;
		pulseWidth = *pwidth;
		LFOamount = *amountLFO;
		LFOrate = *rateLFO;
	}

	void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
	{
		filterChoice = *filterType;
		cutoff = *filterCutoff;
		resonance = *filterRes;
	}

	//=======================================================

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
	{
		noteNumber = midiNoteNumber;
		env1.trigger = 1;
		setPitchBend(currentPitchWheelPosition);
		frequency = noteHz(noteNumber, pitchBendCents() + transposeCents());
		level = velocity;
	}

	//=======================================================

	void stopNote(float velocity, bool allowTailOff) override
	{
		env1.trigger = 0;
		allowTailOff = true;

		if (velocity == 0)
			clearCurrentNote();
	}

	//=======================================================

	void pitchWheelMoved(int newPitchWheelValue) override
	{
		setPitchBend(newPitchWheelValue);
		frequency = noteHz(noteNumber, pitchBendCents() + transposeCents());
	}

	//=======================================================

	void controllerMoved(int controllerNumber, int newControllerValue) override
	{

	}

	//=======================================================

	void renderNextBlock(AudioBuffer <float>& outputBuffer, int startSample, int numSamples) override
	{
		for (int sample = 0; sample < numSamples; ++sample)
		{
			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			{
				outputBuffer.addSample(channel, startSample, setEnvelope() * masterGain);
			}
			++startSample;
		}
	}

	//=======================================================
private:
	double level;
	double frequency;
	int theWave, theWave2, theWaveLFO;
	float pulseWidth;

	float masterGain;
	float osc1blend;
	float osc2blend;

	int noteNumber;
	float pitchBend = 0.0f;
	float pitchBendRangeSemitones = 2.0f;

	float transpose = 0;
	float detune1;
	float detune2;
	float osc2octave;

	int filterChoice;
	float cutoff;
	float resonance;

	float LFOroute;
	float LFOamount;
	float LFOrate;

	maxiOsc osc1, osc2, oscLFO;
	maxiEnv env1;
};