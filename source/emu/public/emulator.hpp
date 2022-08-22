#pragma once


class emulator {

public:
    emulator();
    void Boot();

    void Play();
    void Pause();

private:

    bool paused = false;

};
