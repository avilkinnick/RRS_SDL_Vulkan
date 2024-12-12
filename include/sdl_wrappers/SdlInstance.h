#ifndef SDL_WRAPPERS_SDL_INSTANCE_H
#define SDL_WRAPPERS_SDL_INSTANCE_H

#include <SDL_stdinc.h>

class SdlInstance
{
public:
    explicit SdlInstance(Uint32 flags);
    ~SdlInstance();
};

#endif // SDL_WRAPPERS_SDL_INSTANCE_H
