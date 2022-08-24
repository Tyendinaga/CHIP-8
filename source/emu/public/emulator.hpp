#pragma once

#include <string>

class emulator {

public:
    emulator();
    void Boot(std::string image);

    void Play();
    void Pause();

private:

    bool paused = false;

};
