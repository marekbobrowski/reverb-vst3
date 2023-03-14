#include "unit.h"

void Unit::processSample(float& sampleIn, float& sampleOut)
{
	// does no modification to the signal
	sampleOut = sampleIn;
}

void Unit::processStereoSample(float& sampleInLeft, float& sampleInRight, float& sampleOutLeft, float& sampleOutRight)
{
	// does no modification to the signal
	sampleOutLeft = sampleInLeft;
	sampleOutRight = sampleInRight;
}
