#include "logging.h"

#include <cstdarg>
#include <cstdio>

#include <SDL_error.h>

#define LOG_IMPLEMENTATION(category, ansi_escape_code) \
    void log_##category(const char* format, ...) \
    { \
        std::va_list args; \
        va_start(args, format); \
        std::fprintf(stderr, ansi_escape_code); \
        std::vfprintf(stderr, format, args); \
        std::fprintf(stderr, "\033[0m\n"); \
        va_end(args); \
    }

LOG_IMPLEMENTATION(error, "\033[1;31m")
LOG_IMPLEMENTATION(warning, "\033[1;33m")

void log_sdl_error()
{
    log_error("SDL error: %s", SDL_GetError());
}
