#include "audio.hpp"

// Standard Libs
#include <iostream>
#include <stdio.h>
#include <math.h>

// External Libs
#include <portaudio.h>

/**
 * Constructor
 *
 * Initialize Audio Nonsense
 */
Buzzer::Buzzer()
{
    //
    std::cout << "Initializing Buzzer" << std::endl;
    std::cout << "Sample Rate: " << GetSampleRate() << "hz" << std::endl;
    std::cout << "Buffer Size: " << GetBufferSize() << std::endl;

    // Initialize Port Audio
    Pa_Initialize();

    // Get Default Output Device
    Output.device = Pa_GetDefaultOutputDevice();

    /**
     * Validate Output Device
     */
    if (Output.device == paNoDevice) {
        std::cout << "Error: No default output device" << std::endl;
        return;
    }

    /**
     * Monaural Output
     *
     * There's not need for more than one channel.
     */
    Output.channelCount = 1;

    /**
     * 32 Bit floating point output
     *
     * Honestly this is probably more than necessary.
     */
    Output.sampleFormat = paFloat32;

    /**
     * Set Output Latency
     *
     * Seems to be set in seconds.
     */
    Output.suggestedLatency = Pa_GetDeviceInfo( Output.device )->defaultLowOutputLatency;

    /**
     * No idea what this is for.
     */
    Output.hostApiSpecificStreamInfo = nullptr;

    /**
     * Open Stream
     */
    Pa_OpenStream(
            &Stream,
            nullptr,
            &Output,
            Buzzer::GetSampleRate(),
            Buzzer::GetBufferSize(),
            paClipOff,
            GetAudio,
            nullptr);
}

/**
 * Destructor
 *
 * Clean up any necessary resources
 */
Buzzer::~Buzzer()
{
    //
    std::cout << "Killing Buzzer" << std::endl;

    // Close Stream
    Pa_CloseStream(Stream);

    // Shutdown Port Audio
    Pa_Terminate();
}

int Buzzer::GetAudio(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{

    // Needing for Math Stuff
    const double pi = 3.14159265;

    // The output buffer for Audio
    float *out = (float*)outputBuffer;

    //sin(0.0);

    //(float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );

    for(unsigned long i=0; i<framesPerBuffer; i++ )
    {
        *out++ = 0.3;
    }

    // Keep Playing
    return paContinue;
}

/**
 * Buzzer Should Start
 */
void Buzzer::Start()
{
    Pa_StartStream(Stream);
}

/**
 * Buzzer Should Stop
 */
void Buzzer::Stop()
{
    Pa_StopStream(Stream);
}

/**
 * Get Sample Rate
 *
 * Defaulting to 44100hz.
 */
int Buzzer::GetSampleRate()
{
    return 44100;
}

/**
 * Get Buffer Size
 *
 * Default to 128
 */
int Buzzer::GetBufferSize()
{
    return 128;
}