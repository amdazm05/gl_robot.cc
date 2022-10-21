#ifndef _ROBOT_WINDOW
#define _ROBOT_WINDOW
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class RobotWindow
{
    private:
        GLFWwindow* robotwindow;
    public: 
        //No standard constructor
        RobotWindow()=delete;

        //The constructor use this
        RobotWindow(int width, int height);
        ~RobotWindow();

};

#endif //_ROBOT_WINDOW