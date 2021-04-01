#pragma once
#include "LeakedObjectDetector.h"
#include "Filter.h"

struct Filter;

struct Amplifier
{
    Amplifier();
    ~Amplifier();

    float driveLevel;
    int toneLevel;
    int waveshaperType;
    Filter outputFilter;
    float outputLeveldB;

    void divideSignalBy(float denominator);
    void addFilteredDrive(float driveAmount, Filter inputFilter);
    void changeWaveshaperMode(int nextMode);
    void envelope(int aMils, int dMils, int sCutoff, int rMils);
    void getLoudness();

    JUCE_LEAK_DETECTOR(Amplifier)
};
