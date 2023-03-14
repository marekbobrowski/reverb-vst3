#pragma once

class Oscillator
{
public:
	Oscillator();
	Oscillator(float frequency, float amplitude);
	float getSineTick();
	float getNoiseTick();
	void setAmplitude(float amplitude);
	void setFrequency(float frequency);
protected:
	float phase;
	float frequency;
	float amplitude;
};