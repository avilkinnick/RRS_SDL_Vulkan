#include <exception>

#include <SDL_main.h>

#include "Logger.h"

int main(int argc, char* argv[])
{
    auto& logger = Logger::get_instance();
    logger.attach_log("log.txt");

    try
    {
        logger.log_message(logger.separator);
        logger.log_message("Started new session");
        logger.log_message("Journal subsystem is initialized successfully");
        logger.log_message(logger.separator);
    }
    catch (const std::exception& exception)
    {
        logger.log_error(exception.what());
        return 1;
    }
    catch (...)
    {
        logger.log_error("Unknown exception");
        return 1;
    }

    return 0;
}
