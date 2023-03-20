#include <iostream>
#include "enviroment/robotwindow.hpp"
#include "threads/threads.hpp"



int main(int argc, char **argv)
{
    AppThreadsManger threadManager;
    threadManager.addTaskInThread(std::move(RobotWindow::RenderWindow),480,480);
    return EXIT_SUCCESS;
}

// To launch a window with a box moving