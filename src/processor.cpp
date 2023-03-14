#include "processor.h"
#include "ids.h"
#include "units/allpass.h"
#include "units/my_reverb.h"
#include "units/lowpass1.h"
#include "units/modulated_interpolated_allpass.h"
#include "units/interpolated_delay.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h";
#include "pluginterfaces/vst/ivstprocesscontext.h"

using namespace Steinberg;

Processor::Processor()
{
	setControllerClass (kControllerUID);
}

tresult PLUGIN_API Processor::initialize (FUnknown* context)
{
	tresult result = AudioEffect::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

tresult PLUGIN_API Processor::setActive (TBool state)
{
	if (state)
	{
		reverb = new MyReverb();
	}
	return AudioEffect::setActive (state);
}


tresult PLUGIN_API Processor::process (Vst::ProcessData& data)
{
	if (data.numInputs == 0 || data.numOutputs == 0)
	{
		return kResultOk;
	}

	void** in = getChannelBuffersPointer(processSetup, *data.inputs);
	void** out = getChannelBuffersPointer(processSetup, *data.outputs);

	if (data.inputs[0].silenceFlags != 0)
	{
		handleSilenceFlags(in, out, data);
		return kResultOk;
	}

	handleParameterChange(data);

	if (data.numSamples > 0)
	{
		processBuffer(in, out, data.numSamples);
	}
	return kResultOk;
}


tresult PLUGIN_API Processor::canProcessSampleSize (int32 symbolicSampleSize)
{
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;
	return kResultFalse;
}

void Processor::handleParameterChange(Vst::ProcessData& data)
{
	// Read inputs parameter changes
	if (data.inputParameterChanges)
	{
		int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
		for (int32 index = 0; index < numParamsChanged; index++)
		{
			Vst::IParamValueQueue* paramQueue =
				data.inputParameterChanges->getParameterData(index);
			if (paramQueue)
			{
				Vst::ParamValue value;
				int32 sampleOffset;
				int32 numPoints = paramQueue->getPointCount();
				switch (paramQueue->getParameterId())
				{
				case Params::dampening:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setDampening(value);
					}
					break;
				case Params::decay:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setDecay(value);
					}
					break;
				case Params::diffusion:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setDiffusion(value);
					}
					break;
				case Params::dry:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setDry(value);
					}
					break;
				case Params::highcut:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setHighcut(value);
					}
					break;
				case Params::moddepth:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setModulationFrequency(value);
					}
					break;
				case Params::modfreq:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setModulationFrequency(value);
					}
					break;
				case Params::predelay:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setPredelay(value);
					}
					break;
				case Params::size:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setSize(value);
					}
					break;
				case Params::wet:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
						kResultTrue)
					{
						reverb->setWet(value);
					}
					break;


				}
			}
		}
	}
}



void Processor::handleSilenceFlags(void** in, void** out, Vst::ProcessData& data)
{
	uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
	data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

	for (int32 i = 0; i < data.inputs[0].numChannels; i++)
	{
		if (in[i] != out[i])
		{
			memset(out[i], 0, sampleFramesSize);
		}
	}
}

void Processor::processBuffer(void** in, void** out, int32 numSamples)
{
	float* inRight = (float*)in[0];
	float* outRight = (float*)out[0];
	float* inLeft = (float*)in[1];
	float* outLeft = (float*)out[1];

	for (int i = 0; i < numSamples; i++)
	{
		reverb->processStereoSample(inLeft[i], inRight[i], outLeft[i], outRight[i]);
	}
}
