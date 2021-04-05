#pragma once
#include "LeakedObjectDetector.h"
#include "Oscillator.h"

struct Filter
{
    Filter();
    ~Filter();

    int cutoffFreq;
    int resonance;
    char filterType;
    int envAmount;
    int wet;

    struct LFO
    {
        float frequency{1.f};
        int tempoMultiplier{1};
        char waveform{'S'};
        float waveformMorph{.5f};
        bool bpmSync{true};

        void changeWaveform(char nextWave);
        void changeTempoMultiplier(int newValue);
        void syncToOscillator(Oscillator syncTo, float warpAmount);
    };

    void changeType(char nextType);
    void switchInput(int newInput);
    void filterSweep(int startFreq, int endFreq, float sweepTimeInMillis);
    void getFilterType();

    JUCE_LEAK_DETECTOR(Filter)
};
