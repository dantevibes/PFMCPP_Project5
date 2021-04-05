#include "SubWoof.h"

SubWoof::SubWoof()
{
    cleanBassAmp.driveLevel = .5f;
    cleanBassAmp.toneLevel = 5;
    cleanBassAmp.outputLeveldB = -6.f;
}
SubWoof::~SubWoof()
{
    std::cout << "Closing SubWoof" << std::endl;
}

void SubWoof::bassBoom(int startFreq)
{
    steepLoPass.envAmount = 100;
    steepLoPass.resonance = 50;
    for(int i = startFreq; i > 0; --i)
    {
        steepLoPass.cutoffFreq = i;
    }
}

void SubWoof::gateToSignal(float inputSignal, float threshold)
{
    if(inputSignal > threshold)
        cleanBassAmp.outputLeveldB = 0.00;
    else
        cleanBassAmp.outputLeveldB = -60.00;

    std::cout << "cleanBass output level is " << cleanBassAmp.outputLeveldB << " dB" << std::endl;
}
