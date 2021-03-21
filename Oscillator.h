#include "LeakedObjectDetector.h"
#pragma once

struct Oscillator
{
    Oscillator();
    ~Oscillator();

    int semitone;
    char waveform;
    float phaseIndex;
    float noiseLevel;
    float lfoAmount;

    float outputLFOSignal(char lfoChannel, float amplitudeLevel);
    void syncOscillator(Oscillator oscToSyncTo);
    int nextSamp(int freq, int phase, char whichWave);
    void outputSignal(int frequency, int bufferSize);
    void getSemitone();

    JUCE_LEAK_DETECTOR(Oscillator)
};
