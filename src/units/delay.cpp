#include "delay.h"
#include <cstring>


Delay::Delay(unsigned nSamples)
{
	write = 0;
	read = 0;
	bufferSize = 44100;
	this->nSamples = nSamples;
	buffer = new float[bufferSize];
	memset(buffer, 0, bufferSize * sizeof(float));
	updateDelayLength(nSamples);
}

Delay::~Delay()
{ 
	delete[] buffer;
	buffer = nullptr;
}


void Delay::updateDelayLength(unsigned nSamples)
{
	// delay length can't be longer than the delay buffer size.
	if (nSamples > bufferSize && nSamples >= 0)
	{
		return;
	}

	// we move the read pointer behind the write pointer
	// so that the samples can be read later
	// temporarily we assign this value to temp int because 
	// "read" is an unsigned int and the value might be negative
	int temp = write - nSamples;

	// make sure that the read pointer is in range of 0 - buffer size
	while (temp < 0) 
	{
		temp += bufferSize;
	}

	read = temp;
}

float Delay::getTap(unsigned offset)
{
	if (offset >= bufferSize)
	{
		return 0;
	}
	else
	{
		int index = write - offset;
		if (index < 0)
		{
			index += bufferSize;
		}
		return buffer[index];
	}
}

void Delay::processSample(float& sampleIn, float& sampleOut)
{
	if (write == read)
	{
		sampleOut = sampleIn;
		return;
	}
	sampleOut = buffer[read];
	buffer[write] = sampleIn; 
	shiftPointers(1);
}

void Delay::shiftPointers(int nSamples)
{
	read = (read + nSamples) % bufferSize;
	write = (write + nSamples) % bufferSize;
}

