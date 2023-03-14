#pragma once
#include "unit.h"

/**
 * A general class for any unit that contains a delay buffer.
 * Can be expanded into comb or all-pass filter.
 */
class InterpolatedDelay: public Unit
{
public:
	InterpolatedDelay(float delayLength);
	~InterpolatedDelay();
	void updateDelayLength(float delayLength);
	// get sample at the specified index in the buffer
	float getTap(unsigned index);
	virtual void processSample(float& sampleIn, float& sampleOut) override;
	
protected:
	// shift the read and write pointers while staying in the range of buffer size
	void shiftPointers(float shift);
	// delay length in samples
	float delayLength;
	unsigned bufferSize;
	float* buffer; /// buffer pointer
 	unsigned write; /// read and write positions in the buffer
	float read;
};
