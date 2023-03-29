#ifndef _ROBOT_WINDOW
#define _ROBOT_WINDOW
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <robotmodel/robotmodel.hpp>
#include "threads/threads.hpp"


class RobotWindow
{
    private:
        static GLFWwindow* robotwindow;
        static int width;
        static int height;
    public: 
        //No standard constructor
        RobotWindow()=delete;
        static void RenderWindow(int width, int height,RobotModel::RobotState & offsets);
        //The constructor use this
        RobotWindow(int width, int height);
        ~RobotWindow();

};

#endif //_ROBOT_WINDOW