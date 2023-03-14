cmake_minimum_required(VERSION 3.14.0)
project(mb-reverb)

set(vst3sdk_SOURCE_DIR D:/Programming/SDKs/VST_SDK/VST3_SDK)
add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
  
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(mb-reverb    
    src/ids.h
    src/processor.h
    src/processor.cpp
    src/controller.h
    src/controller.cpp
    src/entry.cpp
    src/units/delay.h
    src/units/delay.cpp
    src/units/unit.h
    src/units/unit.cpp
    src/units/allpass.h
    src/units/allpass.cpp
    src/units/my_reverb.h
    src/units/my_reverb.cpp
    src/units/lowpass1.h
    src/units/lowpass1.cpp
    src/units/cascade.h
    src/units/cascade.cpp
    src/units/gain.h
    src/units/gain.cpp
    src/units/interpolated_delay.cpp
    src/units/interpolated_delay.h
    src/units/modulated_interpolated_allpass.cpp
    src/units/modulated_interpolated_allpass.h
    src/generators/oscillator.h
    src/generators/oscillator.cpp
)

target_link_libraries(mb-reverb
	PRIVATE
		sdk
        vstgui_support
)

smtg_add_vst3_resource(mb-reverb "src/gui/.uidesc")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT mb-reverb)

