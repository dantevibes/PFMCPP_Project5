#include "Filter.h"

Filter::Filter()
{
    cutoffFreq = 20000;
    resonance = 10;
    filterType = 'N';
    envAmount = 50;
    wet = 127;
}
Filter::~Filter()
{
    std::cout << "Filt end freq is " << cutoffFreq << std::endl;
}

void Filter::changeType(char nextType)
{
    filterType = nextType;
}

void Filter::switchInput(int newInput)
{
    newInput += 1;
    if(newInput > 5) newInput = 0;
}

void Filter::filterSweep(int startFreq, int endFreq, float sweepTimeInMillis)
{
    cutoffFreq = startFreq;

    for(float f = 0.0f; f < sweepTimeInMillis; f += 0.5f)
    {
        if(startFreq > endFreq)
        {
            if( cutoffFreq > endFreq ) 
                --cutoffFreq;
        }
        else
        {
            if(cutoffFreq < endFreq) 
                ++cutoffFreq;
        }
        std::cout << "Cutoff sweep is at " << cutoffFreq << std::endl;
    } 

    std::cout << "Cutoff Freq is at " << cutoffFreq << std::endl;
}

void Filter::LFO::changeWaveform(char nextWave)
{
    waveform = nextWave;
}

void Filter::LFO::changeTempoMultiplier(int newValue)
{
    tempoMultiplier = newValue;
}

void Filter::LFO::syncToOscillator(Oscillator syncTo, float warpAmount)
{
    frequency = syncTo.lfoAmount;
    warpAmount = 30.3f;
}

void Filter::getFilterType()
{
    std::cout << "Filter is set to type " << this-> filterType << std::endl;
}
