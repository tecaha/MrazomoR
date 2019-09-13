/*
  ==============================================================================

    SynthSound.h
    Created: 29 Jul 2019 2:05:42am
    Author:  Javor

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"



class SynthSound : public SynthesiserSound
{

public:
	bool appliesToNote(int midiNoteNumber) override
	{
		return true;
	}

	bool appliesToChannel(int midiNoteNumber) override
	{
		return true;
	}
};
