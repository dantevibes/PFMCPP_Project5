#include <iostream>
/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only what you need to new projects
       you will learn how to write code that doesn't leak as well as how to refactor. 

 Destructors
        
 0) move all of your implementations of all functions to OUTSIDE of the class. 
 
 1) Copy 3 of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
 2) add destructors
        make the destructors do something like print out the name of the class.

 3) add 2 new UDTs that use only the types you copied above as member variables.

 4) add 2 member functions that use your member variables to each of these new UDTs

 5) Add constructors and destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 6) copy over your main() from the end of Project3 and get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 7) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
 
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 */

/*
 copied UDT 1:
 */
struct Oscillator
{
    Oscillator();
    ~Oscillator()
    {
        std::cout<< "Osc last phase is " << phaseIndex << std::endl;
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
    std::cout<< "Value of sample at " ;
    for (int bufferSample = 0; bufferSample < bufferSize; ++bufferSample)
    {
        std::cout<< bufferSample << " = " << nextSamp(frequency, bufferSample, waveform) << ", ";
    }
    std::cout<< "buffer write done" << std::endl;
}


/*
 copied UDT 2:
 */
struct Filter
{
    Filter();
    ~Filter()
    {
        std::cout<< "Filt end freq is " << cutoffFreq << std::endl;
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
        std::cout<< "Cutoff sweep is at " << cutoffFreq <<std::endl;
    } 

    std::cout<< "Cutoff Freq is at " << cutoffFreq << std::endl;
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
/*
 copied UDT 3:
 */
struct Amplifier
{
    Amplifier();
    ~Amplifier()
    {
        std::cout<< "Final amp level is " << outputLeveldB << std::endl;
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
    std::cout<< "OutputFilter's cutoff Freq is: " << outputFilter.cutoffFreq << std::endl;

    outputFilter.cutoffFreq = inputFilter.cutoffFreq;
    driveLevel += driveAmount;

    std::cout<< "outputFilter's cutoff Freq changed to: " << outputFilter.cutoffFreq << std::endl;
}

void Amplifier::changeWaveshaperMode(int nextMode)
{
    waveshaperType = nextMode;
}

void Amplifier::envelope(int aMils, int dMils, int sCutoff, int rMils)
{
    outputFilter.cutoffFreq = 0;
    int aDiv = 20000/aMils;
    std::cout<< "aDiv:" << aDiv <<std::endl;
    int dDiv = (20000-sCutoff)/dMils;
    std::cout<< "dDiv:" << dDiv <<std::endl;
    int rDiv = sCutoff/rMils; //problem when rounding to 0...change type
    std::cout<< "rDiv:" << rDiv <<std::endl;

    for( int i = 0 ; i < aMils ; ++i)
        outputFilter.cutoffFreq += aDiv;
    std::cout<< "Amplifier envelope attack complete" << std::endl;
    for( int i = 0 ; i < dMils ; ++i)
        outputFilter.cutoffFreq -= dDiv;
    std::cout<< "Amplifier envelope decay complete" <<std::endl;
    for( int i = 0 ; i < rMils ; ++i)
        outputFilter.cutoffFreq -= rDiv;
    std::cout<< "Amplifier envelope release complete" << std::endl;
    std::cout<< "Amplifier cutoff is at " << outputFilter.cutoffFreq << std::endl;
}
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
        std::cout<< "Amplifier level is "<< powerAmp.outputLeveldB<< ", Shutting down Monosynth"<< std::endl;
    }

    Oscillator leadWave;
    Oscillator syncWave;
    Filter briteHiPass;
    Amplifier powerAmp;

    void unisonFattener()
    {
        std::cout<<"MonoSynth's output before UnisonFattener: " << powerAmp.outputLeveldB * powerAmp.driveLevel <<std::endl;

        syncWave.syncOscillator(leadWave);
        leadWave.phaseIndex += .05f;
        syncWave.semitone = leadWave.semitone + 7;

        briteHiPass.cutoffFreq = 220;
        briteHiPass.resonance = 20;

        powerAmp.driveLevel = 3.f;
        powerAmp.toneLevel = 60;
        powerAmp.outputFilter.resonance = 40;

        std::cout<<"MonoSynth's output after UnisonFattener: " << powerAmp.outputLeveldB * powerAmp.driveLevel <<std::endl;
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



};

MonoSynth::MonoSynth()
{
    briteHiPass.filterType = 'H';
    briteHiPass.cutoffFreq = 500;
    leadWave.outputSignal(100,1);
}

/*
 new UDT 5:
 with 2 member functions
 */

struct SubWoof
{
    SubWoof();
    ~SubWoof()
    {
        std::cout<< "Closing SubWoof" << std::endl;
    }

    Oscillator subTone;
    Filter steepLoPass;
    Amplifier cleanBassAmp;

    void bassBoom(int startFreq);
    void gateToSignal(float inputSignal, float threshold);
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

    std::cout<< "cleanBass output level is " << cleanBassAmp.outputLeveldB << " dB" <<std::endl;
}

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
    std::cout << "good to go!" << std::endl;

    Oscillator bigSaw;
    bigSaw.semitone = 400;
    bigSaw.outputSignal(bigSaw.semitone, 10);

    Filter highPassButter;
    highPassButter.changeType('H');
    highPassButter.filterSweep(30, 220, 2.2f);

    Amplifier fatStackMcGee;
    fatStackMcGee.addFilteredDrive(1.2f, highPassButter);
    fatStackMcGee.envelope(20, 200, 400, 400);

    MonoSynth trailBlazer;
    SubWoof bumpin;
}
