#include "Logger.h"
#include "simulator/Application.h" // TODO:

#include <SDL_main.h>

#include <exception>

int main(int argc, char* argv[])
{
    Logger& logger = Logger::get_instance();

    try
    {
        logger.attach_file("log.txt");
        logger.log_info(logger.separator);
        logger.log_info("Started new session");
        logger.log_info("Logger subsystem is initialized successfully");
        logger.log_info(logger.separator);

        Application application(argc, argv);
    }
    catch (const std::exception& exception)
    {
        logger.log_fatal(exception.what());
        return 1;
    }
    catch (...)
    {
        logger.log_fatal("Unknown exception");
        return 1;
    }

    return 0;
}
