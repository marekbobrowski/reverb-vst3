#pragma once

/**
 * A general class for any stereo processing unit.
 */
class Unit
{
public:
	virtual void processSample(float& sampleIn, float& sampleOut);
	virtual void processStereoSample(float& sampleInLeft, float& sampleInRight, float& sampleOutLeft, float& sampleOutRight);
};
