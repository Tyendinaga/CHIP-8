#pragma once

// External Libs
#include <portaudio.h>

class Buzzer
{

public:

    // Constructor
    Buzzer();

    // Destructor
    ~Buzzer();

    //
    static int GetSampleRate();
    static int GetBufferSize();

    void Start();
    void Stop();

private:

    static int GetAudio(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

    PaStream* Stream;
    PaStreamParameters Output;

};




