#pragma once
#include "delay.h"

// Schroder's comb filter
class Lowpass1 : public Delay
{
public:
	Lowpass1(float g1, float g2);
	void processSample(float& sampleIn, float& sampleOut) override;
	void updateGains(float g1, float g2);
	// feedback gain coefficient;
	float g1, g2;
};
