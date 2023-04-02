#include "enviroment/robotwindow.hpp"
#include "robotmodel/robotmodel.hpp"
#include "threads/threads.hpp"


void UpdateStates(DiffRobotModel & model,RobotModel::RobotState & offsets)
{
    uint32_t i = 0;
    while (i<(5))
    {
        {
            std::lock_guard<std::mutex> lock(AppThreadsManger::_mtx);
            offsets = model.updateSate(0.2f, -0.7f);
        }
        std::cout<<i<<std::endl;
        sleep(2);
        i++;
    }

    offsets = model.updateSate(0.0f, 0.0f);
    std::cout<<offsets.x<<offsets.y<<offsets.yaw<<std::endl;
}

int main(int argc, char **argv)
{
    DiffRobotModel model;
    RobotModel::RobotState offsets;
    int width = 640;
    int height = 640;

    AppThreadsManger threadManager;
    threadManager.addTaskInThread(std::move(RobotWindow::RenderWindow),width,height,offsets);
    threadManager.addTaskInThread(std::move(UpdateStates),model,offsets);

    return EXIT_SUCCESS;
}

// To launch a window with a box moving