#include "allpass.h"
#include <cmath>

Allpass::Allpass(float g, unsigned nSamples) : Delay(nSamples), g(g) {};

void Allpass::processSample(float& sampleIn, float& sampleOut)
{
	long rpi = (long)floorl(read);
	float a = read - (float)rpi;
	sampleOut = buffer[read] + sampleIn * g;
	buffer[write] = -g * sampleOut + sampleIn;
	shiftPointers(1);
}

