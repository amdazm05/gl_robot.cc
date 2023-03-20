#include "enviroment/robotwindow.hpp"
#include "robotmodel/robotmodel.hpp"
#include "threads/threads.hpp"

void UpdateStates(DiffRobotModel & model,RobotModel::RobotState & offsets)
{
    while (1)
    {
        offsets = model.updateSate(-0.05f, 0.05f);
        sleep(1);
    }
}

int main(int argc, char **argv)
{
    DiffRobotModel model;
    RobotModel::RobotState offsets;
    int width = 640;
    int height = 640;

    AppThreadsManger threadManager;
    threadManager.addTaskInThread(std::move(UpdateStates),model,offsets);
    threadManager.addTaskInThread(std::move(RobotWindow::RenderWindow),width,height,offsets);

    return EXIT_SUCCESS;
}

// To launch a window with a box moving