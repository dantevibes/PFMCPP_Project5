/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 The purpose of this project part is to show you how accessing member variables of objects INSIDE member functions is very similar to accessing member variables of objects OUTSIDE of member functions, via 'this->' and via the '.' operator.
 This project part will break the D.R.Y. rule, but that is fine for the purpose of this project part.
 
 
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some.
    You can copy some from your Project3's main() if needed.
 
 2) For each std::cout statement in main() that accessed member variables of your types or printed out the results of your member function calls,
        a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
        b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
        c) call that member function after your std::cout statement in main.
        d) you should see 2 (almost) identical messages in the program output for each member function you add:
            one for the std::cout line, and one for the member function's output
 
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
 example:
 */
#include <iostream>
namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo() { std::cout << "creating MyFoo" << std::endl; }
        ~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
		
		// 2a) the member function whose function body is almost identical to the std::cout statement in main.
        void memberFunc() 
		{ 
            // 2b) explicitly using 'this' inside this member function.
			std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
		}  
		
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
		
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
		
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.memberFunc();
        return 0;
    }
}


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
