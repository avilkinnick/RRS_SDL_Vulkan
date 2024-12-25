#ifndef SIMULATOR_APPLICATION_H
#define SIMULATOR_APPLICATION_H

struct CommandLineData;
class MotionModel;

#include <memory>

class Application
{
public:
    Application(int argc, char* argv[]);
    ~Application();

private:
    int parse_command_line_arguments(int argc, char* argv[], CommandLineData& command_line_data);

private:
    std::unique_ptr<MotionModel> motion_model;
};

#endif // SIMULATOR_APPLICATION_H
