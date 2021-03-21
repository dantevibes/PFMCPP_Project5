struct OscillatorWrapper
{
    OscillatorWrapper(Oscillator* ptr) : ptrToOscillator( ptr ) {}
    ~OscillatorWrapper()
    {
        delete ptrToOscillator;
    }

    Oscillator* ptrToOscillator = nullptr;
};

struct FilterWrapper
{
    FilterWrapper(Filter* ptr) : ptrToFilter( ptr ) {}
    ~FilterWrapper()
    {
        delete ptrToFilter;
    }

    Filter* ptrToFilter = nullptr;
};

struct AmplifierWrapper
{
    AmplifierWrapper(Amplifier* ptr) : ptrToAmplifier( ptr ) {}
    ~AmplifierWrapper()
    {
        delete ptrToAmplifier;
    }

    Amplifier* ptrToAmplifier = nullptr;
};

struct MonoSynthWrapper
{
    MonoSynthWrapper(MonoSynth* ptr) : ptrToMonoSynth( ptr ) {}
    ~MonoSynthWrapper()
    {
        delete ptrToMonoSynth;
    }

    MonoSynth* ptrToMonoSynth = nullptr;
};

struct SubWoofWrapper
{
    SubWoofWrapper(SubWoof* ptr) : ptrToSubWoof( ptr ) {}
    ~SubWoofWrapper()
    {
        delete ptrToSubWoof;
    }

    SubWoof* ptrToSubWoof = nullptr;
};
