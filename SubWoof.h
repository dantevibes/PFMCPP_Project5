#pragma once
#include "Oscillator.h"
#include "Filter.h"
#include "Amplifier.h"
#include "LeakedObjectDetector.h"

struct SubWoof
{
    SubWoof();
    ~SubWoof();

    Oscillator subTone;
    Filter steepLoPass;
    Amplifier cleanBassAmp;

    void bassBoom(int startFreq);
    void gateToSignal(float inputSignal, float threshold);

    JUCE_LEAK_DETECTOR(SubWoof)
};
