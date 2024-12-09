#include <exception>

#include <SDL_main.h>

#include "logging.h"

int main(int argc, char* argv[])
{
    try
    {
    }
    catch (const std::exception& exception)
    {
        log_error(exception.what());
        return 1;
    }
    catch (...)
    {
        log_error("Unknown exception");
        return 1;
    }

    return 0;
}
