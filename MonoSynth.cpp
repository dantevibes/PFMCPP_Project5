#include "MonoSynth.h"


MonoSynth::MonoSynth()
{}

MonoSynth::~MonoSynth()
{
    powerAmp.outputLeveldB = -60.f;
    std::cout << "Amplifier level is " << powerAmp.outputLeveldB << ", Shutting down Monosynth" << std::endl;
}


void unisonFattener()
{
    std::cout << "MonoSynth's output before UnisonFattener: " << powerAmp.outputLeveldB * powerAmp.driveLevel << std::endl;

    syncWave.syncOscillator(leadWave);
    leadWave.phaseIndex += .05f;
    syncWave.semitone = leadWave.semitone + 7; //didnt go farther bec  still throwing error

    briteHiPass.cutoffFreq = 220;
    briteHiPass.resonance = 20;

    powerAmp.driveLevel = 3.f;
    powerAmp.toneLevel = 60;
    powerAmp.outputFilter.resonance = 40;

    std::cout << "MonoSynth's output after UnisonFattener: " << powerAmp.outputLeveldB * powerAmp.driveLevel << std::endl;
}

bool arpeggiator(int noteOne, int noteTwo, int noteThree)
{
    bool isArpDone = false;

    for( int step = 0; step < 16 ; ++step)
    {
        if(step % 4 == 0)
            leadWave.semitone = noteOne;
        if(step % 3 == 0)
            leadWave.semitone = noteTwo;
        if(step % 5 == 0)
            leadWave.semitone = noteThree;
    }
    isArpDone = true;
        
    return isArpDone;
}
