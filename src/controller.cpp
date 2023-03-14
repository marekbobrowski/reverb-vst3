#include "controller.h"
#include "ids.h"
#include "base/source/fstreamer.h"

using namespace Steinberg;

tresult PLUGIN_API Controller::initialize (FUnknown* context)
{
	tresult result = EditControllerEx1::initialize (context);

	if (result != kResultOk)
	{
		return result;
	}
	parameters.addParameter(STR16("dampening"), nullptr, 0, 0.005,
		Vst::ParameterInfo::kCanAutomate, Params::dampening, 0,
		STR16("dampening"));
	parameters.addParameter(STR16("decay"), nullptr, 0, 0.7,
		Vst::ParameterInfo::kCanAutomate, Params::decay, 0,
		STR16("decay"));
	parameters.addParameter(STR16("diffusion"), nullptr, 0, 1,
		Vst::ParameterInfo::kCanAutomate, Params::diffusion, 0,
		STR16("diffusion"));
	parameters.addParameter(STR16("dry"), nullptr, 0, 1,
		Vst::ParameterInfo::kCanAutomate, Params::dry, 0,
		STR16("dry"));
	parameters.addParameter(STR16("highcut"), nullptr, 0, 0.8,
		Vst::ParameterInfo::kCanAutomate, Params::highcut, 0,
		STR16("highcut"));
	parameters.addParameter(STR16("moddepth"), nullptr, 0, 0.5,
		Vst::ParameterInfo::kCanAutomate, Params::moddepth, 0,
		STR16("moddepth"));
	parameters.addParameter(STR16("modfreq"), nullptr, 0, 0.25,
		Vst::ParameterInfo::kCanAutomate, Params::modfreq, 0,
		STR16("modfreq"));
	parameters.addParameter(STR16("predelay"), nullptr, 0, 0,
		Vst::ParameterInfo::kCanAutomate, Params::predelay, 0,
		STR16("predelay"));
	parameters.addParameter(STR16("size"), nullptr, 0, 0.8,
		Vst::ParameterInfo::kCanAutomate, Params::size, 0,
		STR16("size"));
	parameters.addParameter(STR16("wet"), nullptr, 0, 0.3,
		Vst::ParameterInfo::kCanAutomate, Params::wet, 0,
		STR16("wet"));

	setKnobMode(Vst::KnobModes::kLinearMode);

	return kResultOk;
}

Steinberg::IPlugView* PLUGIN_API Controller::createView(const char* name)
{
	if (name && strcmp(name, "editor") == 0)
	{
		auto* view = new VSTGUI::VST3Editor(this, "view", ".uidesc");
		return view;
	}
	return nullptr;
}
