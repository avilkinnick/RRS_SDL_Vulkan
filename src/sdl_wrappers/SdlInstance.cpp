#include "sdl_wrappers/SdlInstance.h"

#include "Logger.h"

#include <SDL.h>
#include <SDL_stdinc.h>

#include <stdexcept>

SdlInstance::SdlInstance(Uint32 flags)
{
    if (SDL_Init(flags) < 0)
    {
        Logger::get_instance().log_sdl_error();
        throw std::runtime_error("Failed to initialize SDL library");
    }
}

SdlInstance::~SdlInstance()
{
    SDL_Quit();
}
