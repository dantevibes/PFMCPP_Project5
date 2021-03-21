#include "Oscillator.h"
#include "Filter.h"
#include "Amplifier.h"
#include "LeakedObjectDetector.h"
#pragma once

struct MonoSynth
{
    MonoSynth();
    ~MonoSynth();

    Oscillator leadWave;
    Oscillator syncWave;
    Filter briteHiPass;
    Amplifier powerAmp;

    void unisonFattener();
    bool arpeggiator(int noteOne, int noteTwo, int noteThree);
    

    JUCE_LEAK_DETECTOR(MonoSynth)
};
