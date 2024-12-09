#include "sdl_wrappers/SdlInstance.h"

#include <stdexcept>

#include <SDL.h>
#include <SDL_stdinc.h>

#include "logging.h"

SdlInstance::SdlInstance(Uint32 flags)
{
    if (SDL_Init(flags) < 0)
    {
        log_sdl_error();
        throw std::runtime_error("Failed to initialize SDL library");
    }
}

SdlInstance::~SdlInstance()
{
    SDL_Quit();
}
