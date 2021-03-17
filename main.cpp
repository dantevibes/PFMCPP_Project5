/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 3) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 4) write the name of your class where it says "OwnerClass"
 
 5) write wrapper classes for each type similar to how it was shown in the video
 
 7) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 you can safely ignore any warnings about exit-time-destructors.
 if you would like to suppress them, add -Wno-exit-time-destructors to the .replit file 
   with the other warning suppression flags
 */
#include "LeakedObjectDetector.h"
/*
 copied UDT 1:
 */
struct Oscillator
{
    Oscillator();
    ~Oscillator()
    {
        std::cout << "Osc last phase is " << phaseIndex << std::endl;
    }

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

Oscillator::Oscillator()
{
    semitone  = 0;
    waveform = 'N';
    phaseIndex = 0.f;
    noiseLevel = -100.f;
    lfoAmount = 0.f;
}

float Oscillator::outputLFOSignal(char lfoWave, float amplitudeLevel)
{
    std::cout << "LFO Amnt before: " << lfoAmount << std::endl;

    for(int i = 0; i < 2; ++i )
    {
        waveform = lfoWave;
        amplitudeLevel = .75f * i;
    }

    return amplitudeLevel;
}

void Oscillator::syncOscillator(Oscillator oscToSyncTo)
{
    phaseIndex = oscToSyncTo.phaseIndex;
}

int Oscillator::nextSamp(int freq, int phase, char whichWave)
{
    int sampValue = 0;
    if(whichWave == 'N')
    {
        sampValue = freq * (100 - (phase % 200));
    }
    return sampValue;
}

void Oscillator::outputSignal(int frequency, int bufferSize)
{
    std::cout << "Value of sample at " ;
    for (int bufferSample = 0; bufferSample < bufferSize; ++bufferSample)
    {
        std::cout << bufferSample << " = " << nextSamp(frequency, bufferSample, waveform) << ", ";
    }
    std::cout << "buffer write done" << std::endl;
}

void Oscillator::getSemitone()
{
    std::cout << "Osc is set to semitone " << this->semitone << std::endl;
}


struct OscillatorWrapper
{
    OscillatorWrapper(Oscillator* ptr) : ptrToOscillator( ptr ) {}
    ~OscillatorWrapper()
    {
        delete ptrToOscillator;
    }

    Oscillator* ptrToOscillator = nullptr;
};



/*
 copied UDT 2:
 */
struct Filter
{
    Filter();
    ~Filter()
    {
        std::cout << "Filt end freq is " << cutoffFreq << std::endl;
    }

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

Filter::Filter()
{
    cutoffFreq = 20000;
    resonance = 10;
    filterType = 'N';
    envAmount = 50;
    wet = 127;
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


struct FilterWrapper
{
    FilterWrapper(Filter* ptr) : ptrToFilter( ptr ) {}
    ~FilterWrapper()
    {
        delete ptrToFilter;
    }

    Filter* ptrToFilter = nullptr;
};

/*
 copied UDT 3:
 */
struct Amplifier
{
    Amplifier();
    ~Amplifier()
    {
        std::cout << "Final amp level is " << outputLeveldB << std::endl;
    }

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


struct AmplifierWrapper
{
    AmplifierWrapper(Amplifier* ptr) : ptrToAmplifier( ptr ) {}
    ~AmplifierWrapper()
    {
        delete ptrToAmplifier;
    }

    Amplifier* ptrToAmplifier = nullptr;
};
/*
 new UDT 4:
 with 2 member functions
 */
struct MonoSynth
{
    MonoSynth();
    ~MonoSynth()
    {
        powerAmp.outputLeveldB = -60.f;
        std::cout << "Amplifier level is " << powerAmp.outputLeveldB << ", Shutting down Monosynth" << std::endl;
    }

    Oscillator leadWave;
    Oscillator syncWave;
    Filter briteHiPass;
    Amplifier powerAmp;

    void unisonFattener()
    {
        std::cout << "MonoSynth's output before UnisonFattener: " << powerAmp.outputLeveldB * powerAmp.driveLevel << std::endl;

        syncWave.syncOscillator(leadWave);
        leadWave.phaseIndex += .05f;
        syncWave.semitone = leadWave.semitone + 7;

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

    JUCE_LEAK_DETECTOR(MonoSynth)
};

MonoSynth::MonoSynth()
{
    briteHiPass.filterType = 'H';
    briteHiPass.cutoffFreq = 500;
    leadWave.outputSignal(100,1);
}


struct MonoSynthWrapper
{
    MonoSynthWrapper(MonoSynth* ptr) : ptrToMonoSynth( ptr ) {}
    ~MonoSynthWrapper()
    {
        delete ptrToMonoSynth;
    }

    MonoSynth* ptrToMonoSynth = nullptr;
};

/*
 new UDT 5:
 with 2 member functions
 */

struct SubWoof
{
    SubWoof();
    ~SubWoof()
    {
        std::cout << "Closing SubWoof" << std::endl;
    }

    Oscillator subTone;
    Filter steepLoPass;
    Amplifier cleanBassAmp;

    void bassBoom(int startFreq);
    void gateToSignal(float inputSignal, float threshold);

    JUCE_LEAK_DETECTOR(SubWoof)
};

SubWoof::SubWoof()
{
    cleanBassAmp.driveLevel = .5f;
    cleanBassAmp.toneLevel = 5;
    cleanBassAmp.outputLeveldB = -6.f;
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


struct SubWoofWrapper
{
    SubWoofWrapper(SubWoof* ptr) : ptrToSubWoof( ptr ) {}
    ~SubWoofWrapper()
    {
        delete ptrToSubWoof;
    }

    SubWoof* ptrToSubWoof = nullptr;
};
/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */
#include <iostream>
int main()
{

    OscillatorWrapper bigSaw( new Oscillator );
    bigSaw.ptrToOscillator->semitone = 400;
    //bigSaw.outputSignal(bigSaw.semitone, 10);
    std::cout << "Osc is set to semitone " << bigSaw.ptrToOscillator->semitone << std::endl;
    bigSaw.ptrToOscillator->getSemitone();


    FilterWrapper highPassButter( new Filter );
    highPassButter.ptrToFilter->changeType('H');
    //highPassButter.filterSweep(30, 220, 2.2f);
    std::cout << "Filter is set to type " << highPassButter.ptrToFilter->filterType << std::endl;
    highPassButter.ptrToFilter->getFilterType();


    AmplifierWrapper fatStackMcGee( new Amplifier );
    //fatStackMcGee.addFilteredDrive(1.2f, highPassButter);
    //fatStackMcGee.envelope(20, 200, 400, 400);
    std::cout << "Amplifier's overall loudness is " << fatStackMcGee.ptrToAmplifier->driveLevel * fatStackMcGee.ptrToAmplifier->toneLevel << std::endl;
    fatStackMcGee.ptrToAmplifier->getLoudness();

    std::cout << "good to go!" << std::endl;
    std::cout << std::endl;

    MonoSynthWrapper trailBlazer( new MonoSynth );
    SubWoofWrapper bumpin( new SubWoof );
}
