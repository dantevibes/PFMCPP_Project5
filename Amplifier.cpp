#include "Amplifier.h"

Amplifier::Amplifier()
{
    driveLevel = 1.f;
    toneLevel = 50;
    waveshaperType = 0;

    outputFilter.cutoffFreq = 10000;
    outputFilter.resonance = 3;
    outputFilter.filterType = 'L';
    outputFilter.envAmount = 90;
    outputFilter.wet = 33;
    
    outputLeveldB = 1.f;
}
Amplifier::~Amplifier()
{
    std::cout << "Final amp level is " << outputLeveldB << std::endl;
}

void Amplifier::divideSignalBy(float denominator)
{
    outputLeveldB = outputLeveldB/denominator;
}

void Amplifier::addFilteredDrive(float driveAmount, Filter inputFilter)
{
    std::cout << "outputFilter's cutoff Freq is: " << outputFilter.cutoffFreq << std::endl;

    outputFilter.cutoffFreq = inputFilter.cutoffFreq;
    driveLevel += driveAmount;

    std::cout << "outputFilter's cutoff Freq changed to: " << outputFilter.cutoffFreq << std::endl;
}

void Amplifier::changeWaveshaperMode(int nextMode)
{
    waveshaperType = nextMode;
}

void Amplifier::envelope(int aMils, int dMils, int sCutoff, int rMils)
{
    outputFilter.cutoffFreq = 0;
    int aDiv = 20000/aMils;
    std::cout << "aDiv:" << aDiv << std::endl;
    int dDiv = (20000-sCutoff)/dMils;
    std::cout << "dDiv:" << dDiv << std::endl;
    int rDiv = sCutoff/rMils; //problem when rounding to 0...change type
    std::cout << "rDiv:" << rDiv << std::endl;

    for( int i = 0 ; i < aMils ; ++i)
        outputFilter.cutoffFreq += aDiv;
    std::cout << "Amplifier envelope attack complete" << std::endl;
    for( int i = 0 ; i < dMils ; ++i)
        outputFilter.cutoffFreq -= dDiv;
    std::cout << "Amplifier envelope decay complete" << std::endl;
    for( int i = 0 ; i < rMils ; ++i)
        outputFilter.cutoffFreq -= rDiv;
    std::cout << "Amplifier envelope release complete" << std::endl;
    std::cout << "Amplifier cutoff is at " << outputFilter.cutoffFreq << std::endl;
}

void Amplifier::getLoudness()
{
  std::cout << "Amplifier's overall loudness is " << this->driveLevel * this->toneLevel << std::endl;
}
