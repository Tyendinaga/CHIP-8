#include "audio.hpp"

// Standard Libs
#include <iostream>
#include <stdio.h>
#include <math.h>

// External Libs
#include "portaudio.h"

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
    auto error = Pa_OpenStream(
            &Stream,
            nullptr,
            &Output,
            Buzzer::GetSampleRate(),
            Buzzer::GetBufferSize(),
            paClipOff,
            GetAudio,
            nullptr);

    std::cout << "Error Number: " << error << std::endl;
    std::cout << "Error Text: " << Pa_GetErrorText(error) << std::endl;

}

/**
 * Destructor
 *
 * Clean up any necessary resources
 */
Buzzer::~Buzzer()
{
    std::cout << "Killing Buzzer" << std::endl;

    // Shutdown Port Audio
    Pa_Terminate();
}

/**
 * Generate Sawtooth Pattern
 *
 * This function generates a simple Sawtooth pattern in a range of +- 0.5f. This is used to create the buzzer sound that
 * the CHIP-8 needs in order to emulate the systems buzzer component.
 */
int Buzzer::GetAudio(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{

    // The output buffer for Audio
    float *out = (float*)outputBuffer;

    float Input = 0.0f;

    for(unsigned long i=0; i<framesPerBuffer; i++ )
    {
        *out++ = Input;

        Input += 0.01f;

        if (Input >= 0.5f)
        {
            Input = -0.5f;
        }
    }

    // Keep Playing
    return paContinue;
}

/**
 * Start Buzzer
 */
void Buzzer::Start()
{
    auto Active = Pa_IsStreamActive(Stream);

    if (Active == 1) {
        return;
    }

    std::cout << "Starting Stream" << std::endl;
    Pa_StartStream(Stream);
}

/**
 * Buzzer Should Stop
 */
void Buzzer::Stop()
{
    auto Active = Pa_IsStreamActive(Stream);

    if (Active <= 0) {
        return;
    }

    std::cout << "Stopping Stream" << std::endl;
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