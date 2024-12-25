#ifndef SIMULATOR_APPLICATION_H
#define SIMULATOR_APPLICATION_H

struct CommandLineData;

class Application
{
public:
    Application(int argc, char* argv[]);

private:
    void parse_command_line_arguments(int argc, char* argv[], CommandLineData& command_line_data);
};

#endif // SIMULATOR_APPLICATION_H
