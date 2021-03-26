#include "LeakedObjectDetector.h"
#include "Oscillator.h"
#include "Filter.h"
#include "Amplifier.h"
#pragma once

struct MonoSynth
{
    Oscillator leadWave;
    Oscillator syncWave;
    Filter briteHiPass;
    Amplifier powerAmp;
    
    MonoSynth();
    ~MonoSynth();

    void unisonFattener();
    bool arpeggiator(int noteOne, int noteTwo, int noteThree);
    

    JUCE_LEAK_DETECTOR(MonoSynth)
};
