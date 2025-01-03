#include "sdl_wrappers/SdlWindowWrapper.h"

#include "Logger.h"

#include <SDL_stdinc.h>
#include <SDL_video.h>

#include <stdexcept>

SdlWindowWrapper::SdlWindowWrapper(const char* title, int x, int y, int width, int height, Uint32 flags)
    : window(SDL_CreateWindow(title, x, y, width, height, flags))
{
    if (!window)
    {
        Logger::get_instance().log_sdl_error();
        throw std::runtime_error("Failed to create SDL window");
    }
}

SdlWindowWrapper::SdlWindowWrapper(const char* title, int width, int height, Uint32 flags)
    :SdlWindowWrapper(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags)
{
}

SdlWindowWrapper::~SdlWindowWrapper()
{
    SDL_DestroyWindow(window);
}
