#pragma once

#include "interpolated_delay.h"
#include "../generators/oscillator.h"


class ModulatedInterpolatedAllpass : public InterpolatedDelay
{
public:
	ModulatedInterpolatedAllpass(float depth, float frequency, float g, float delayLength);
	virtual void processSample(float& sampleIn, float& sampleOut) override;
	void setCenterDelayLength(float centerDelayLength);
	void setModulationDepth(float depth);
	void setModulationFrequency(float frequency);
	float g;
protected:
	Oscillator osc;
	// delay time will move around this value
	float centerDelayLength;
};
