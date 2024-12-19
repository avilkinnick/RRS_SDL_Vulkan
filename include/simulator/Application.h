#ifndef SIMULATOR_APPLICATION_H
#define SIMULATOR_APPLICATION_H

class Application
{
public:
    Application(int argc, char* argv[]);

    int parse_command_line_arguments(int argc, char* argv[]);
};

#endif // SIMULATOR_APPLICATION_H
