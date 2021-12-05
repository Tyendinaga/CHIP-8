#include "audio.hpp"

// Standard Libs
#include <iostream>
#include <stdio.h>
#include <math.h>

// External Libs
#include <portaudio.h>

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData )
{
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    unsigned long i;

    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer;

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = data->sine[data->left_phase];  /* left */
        *out++ = data->sine[data->right_phase];  /* right */
        data->left_phase += 1;
        if( data->left_phase >= TABLE_SIZE ) data->left_phase -= TABLE_SIZE;
        data->right_phase += 3; /* higher pitch so we can distinguish left and right. */
        if( data->right_phase >= TABLE_SIZE ) data->right_phase -= TABLE_SIZE;
    }

    return paContinue;
}

/*
 * This routine is called by portaudio when playback is done.
 */
static void StreamFinished( void* userData )
{
    // Do Nothing
}

void testAudio()
{
    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;
    paTestData data;
    int i;

    printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);

    /* initialise sinusoidal wavetable */
    for( i=0; i<TABLE_SIZE; i++ )
    {
        data.sine[i] = (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
    }
    data.left_phase = data.right_phase = 0;

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto error;
    }
    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
            &stream,
            NULL, /* no input */
            &outputParameters,
            Buzzer::GetSampleRate(),
            Buzzer::GetBufferSize(),
            paClipOff,
            patestCallback,
            &data );
    if( err != paNoError ) goto error;

    sprintf( data.message, "No Message" );
    err = Pa_SetStreamFinishedCallback( stream, &StreamFinished );
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    //printf("Play for %d seconds.\n", NUM_SECONDS );
    Pa_Sleep( 128 );

    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    Pa_Terminate();
    //printf("Test finished.\n");

    //return err;
    error:
    Pa_Terminate();
    //fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    //fprintf( stderr, "Error number: %d\n", err );
    //fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    //return err;
}

/**
 * Constructor
 *
 * Initialize Audio Nonsense
 */
Buzzer::Buzzer()
{
    std::cout << "Initializing Buzzer" << std::endl;
    std::cout << "Sample Rate: " << GetSampleRate() << "hz" << std::endl;
    std::cout << "Buffer Size: " << GetBufferSize() << std::endl;
}

/**
 * Destructor
 *
 * Clean up any necessary resources
 */
Buzzer::~Buzzer()
{
    std::cout << "Killing Buzzer" << std::endl;
    //Pa_Terminate();
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