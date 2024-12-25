#ifndef SIMULATOR_APPLICATION_H
#define SIMULATOR_APPLICATION_H

struct CommandLineData;
class TrainModel;

#include <memory>

class Application
{
public:
    Application(int argc, char* argv[]);
    ~Application();

private:
    int parse_command_line_arguments(int argc, char* argv[], CommandLineData& command_line_data);

private:
    std::unique_ptr<TrainModel> train_model;
};

#endif // SIMULATOR_APPLICATION_H
