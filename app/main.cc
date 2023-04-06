#include "enviroment/robotwindow.hpp"
#include "robotmodel/robotmodel.hpp"
#include "threads/threads.hpp"
#include "input/robotinputhandler.hpp"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h>
    #define sleep(x) _sleep(x)
#endif


void UpdateStates(DiffRobotModel & model,RobotState & offsets)
{
    RobotInputHandler IOHandle;
    std::vector<RobotState> statevector = IOHandle.getRobotStatesFromFile("state.txt");
    uint32_t i = 0;
    while (i<statevector.size())
    {
        {
            std::lock_guard<std::mutex> lock(AppThreadsManger::_mtx);
            offsets = model.updateSate(statevector.at(i).velxy, statevector.at(i).yawrate);
        }
        std::cout<<i<<std::endl;
        sleep(5);
        i++;
    }

    offsets = model.updateSate(0.0f, 0.0f);
    std::cout<<offsets.x<<offsets.y<<offsets.yaw<<std::endl;
}

int main(int argc, char **argv)
{
    
    DiffRobotModel model;
    RobotState offsets;
    int width = 640;
    int height = 640;

    AppThreadsManger threadManager;
    threadManager.addTaskInThread(std::move(RobotWindow::RenderWindow),width,height,offsets);
    threadManager.addTaskInThread(std::move(UpdateStates),model,offsets);

    return EXIT_SUCCESS;
}

// To launch a window with a box moving