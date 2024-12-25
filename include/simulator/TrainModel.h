#ifndef SIMULATOR_TRAIN_MODEL_H
#define SIMULATOR_TRAIN_MODEL_H

struct CommandLineData;
struct TrainModelInitializeData;

class TrainModel
{
public:
    void initialize(const CommandLineData& command_line_data);

private:
    void load_initialize_data(TrainModelInitializeData& initialize_data);

private:
    bool debug_print;
};

#endif // SIMULATOR_TRAIN_MODEL_H
