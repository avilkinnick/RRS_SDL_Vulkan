#ifndef SIMULATOR_MOTION_MODEL_H
#define SIMULATOR_MOTION_MODEL_H

#include "simulator/TrainInitializeData.h"

#include <vector>

struct CommandLineData;

class MotionModel
{
public:
    void initialize(const CommandLineData& command_line_data);

private:
    void load_initialize_data(TrainInitializeData& initialize_data);

    void override_initialize_data_by_command_line(
        TrainInitializeData& initialize_data,
        const CommandLineData& command_line_data
    );

private:
    bool debug_print;
    std::vector<TrainInitializeData> train_initialize_datas;
};

#endif // SIMULATOR_MOTION_MODEL_H
