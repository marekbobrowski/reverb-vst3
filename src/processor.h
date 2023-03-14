#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "units/unit.h"
#include "units/my_reverb.h"


class Processor : public Steinberg::Vst::AudioEffect
{
public:
	Processor ();

	static Steinberg::FUnknown* createInstance (void*) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new Processor; 
	}

	// OVERRIDE DEFAULT VST PROCESSOR METHODS

	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;


	/**
	 * Handles any changes of plugin parameters.
	 */
	void handleParameterChange(Steinberg::Vst::ProcessData& data);

	/**
	 * Processes the sound signal buffer.
	 */
	void processBuffer(void** in, void** out, Steinberg::int32 numSamples);

	/**
	 * Handles the silence flags.
	 */
	void handleSilenceFlags(void** in, void** out, Steinberg::Vst::ProcessData& data);
		
protected:
	MyReverb* reverb;
};

