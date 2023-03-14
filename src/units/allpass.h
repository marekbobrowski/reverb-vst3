#pragma once
#include "delay.h"

// Moorer's all pass filter (the one with only 2 gains).
class Allpass : public Delay
{
public:
	Allpass(float g, unsigned nSamples);
	virtual void processSample(float& sampleIn, float& sampleOut) override;
	// feedback and feedforward gain coefficient;
	float g;
};
