#include "modulated_interpolated_allpass.h"
#include <cmath>

ModulatedInterpolatedAllpass::ModulatedInterpolatedAllpass(float depth, float frequency, float g, float delayLength) : InterpolatedDelay(delayLength)
{
	if (depth > delayLength)
	{
		depth = delayLength - 1;
	}
	this->centerDelayLength = delayLength;
	this->g = g;
	osc = Oscillator(frequency, depth);
};

void ModulatedInterpolatedAllpass::processSample(float& sampleIn, float& sampleOut)
{
	InterpolatedDelay::updateDelayLength(centerDelayLength + osc.getSineTick());
	long rpi = (long)floorl(read);
	long rpi1 = (rpi + 1) % bufferSize;
	float a = read - (float)rpi;
	sampleOut = a * buffer[rpi1] + (1 - a) * buffer[rpi] + sampleIn * g;
	buffer[write] = -g * sampleOut + sampleIn;
	shiftPointers(1);
}

void ModulatedInterpolatedAllpass::setCenterDelayLength(float centerDelayLength)
{
	this->centerDelayLength = centerDelayLength;
}

void ModulatedInterpolatedAllpass::setModulationDepth(float depth)
{
	this->osc.setAmplitude(depth);
}

void ModulatedInterpolatedAllpass::setModulationFrequency(float frequency)
{
	this->osc.setFrequency(frequency);
}
