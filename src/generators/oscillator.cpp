#include "oscillator.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>



Oscillator::Oscillator()
{
	Oscillator(1, 1);
}

Oscillator::Oscillator(float frequency, float amplitude)
{
	phase = 0;
	this->frequency = frequency;
	this->amplitude = amplitude;
	srand(time(NULL));
}

float Oscillator::getSineTick()
{
	float tick = amplitude * sinf(phase);
	phase += (2 * M_PI * frequency) / 44100;
	if (phase > 2 * M_PI)
	{
		phase = phase - (2 * M_PI);
	}
	return tick;
}

float Oscillator::getNoiseTick()
{
	float random = (((float)rand() / (RAND_MAX)) - 0.5) * 2;
	return random * amplitude;
}

void Oscillator::setAmplitude(float amplitude)
{
	this->amplitude = amplitude;
}

void Oscillator::setFrequency(float frequency)
{
	this->frequency = frequency;
}


