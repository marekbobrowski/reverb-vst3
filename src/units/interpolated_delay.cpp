#include "interpolated_delay.h"
#include <cstring>
#include <cmath>


InterpolatedDelay::InterpolatedDelay(float delayLength)
{
	write = 0;
	read = 0;
	bufferSize = 44100;
	this->delayLength = delayLength;
	buffer = new float[bufferSize];
	memset(buffer, 0, bufferSize * sizeof(float));
	updateDelayLength(this->delayLength);
}

InterpolatedDelay::~InterpolatedDelay()
{ 
	delete[] buffer;
	buffer = nullptr;
}


void InterpolatedDelay::updateDelayLength(float delayLength)
{
	// delay length can't be longer than the delay buffer size.
	if (delayLength > bufferSize && delayLength >= 0)
	{
		return;
	}

	// we move the read pointer behind the write pointer
	// so that the samples can be read later
	float temp = (float)write - delayLength;

	// make sure that the read pointer is in range of 0 - buffer size
	while (temp < 0) 
	{
		temp += (float)bufferSize;
	}

	if (temp == bufferSize)
	{
		temp = 0;
	}

	read = temp;
}

float InterpolatedDelay::getTap(unsigned offset)
{
	if (offset >= bufferSize)
	{
		return 0;
	}
	else
	{
		int index = (int)(write - offset);
		if (index < 0)
		{
			index += bufferSize;
		}
		return buffer[index];
	}
}

void InterpolatedDelay::processSample(float& sampleIn, float& sampleOut)
{
	long rpi = (long)floorl(read);
	long rpi1 = (rpi + 1) % bufferSize;
	float a = read - (float)rpi;
	sampleOut = a * buffer[rpi1] + (1 - a) * buffer[rpi];
	buffer[write] = sampleIn; 

	shiftPointers(1);
}

void InterpolatedDelay::shiftPointers(float nSamples)
{
	read+=nSamples;
	write+=nSamples;
	if (write > bufferSize - 1)
	{
		write -= bufferSize;
	}
	if (read > bufferSize - 1)
	{
		read -= (float)bufferSize;
	}
}

