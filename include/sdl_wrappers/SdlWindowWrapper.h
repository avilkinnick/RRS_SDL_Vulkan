#pragma once

#include <SDL_stdinc.h>

struct SDL_Window;

class SdlWindowWrapper
{
public:
    SdlWindowWrapper(const char* title, int x, int y, int width, int height, Uint32 flags);
    SdlWindowWrapper(const char* title, int width, int height, Uint32 flags);
    ~SdlWindowWrapper();

    operator SDL_Window*() { return window; }

private:
    SDL_Window* window;
};
