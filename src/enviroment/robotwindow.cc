#include<enviroment/robotwindow.hpp>

RobotWindow::RobotWindow(int width, int height)
{
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    robotwindow= glfwCreateWindow(width,height,"RobotWindow",nullptr,nullptr);
    if(!robotwindow)
    {
        // Terminate all windows 
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while(!glfwWindowShouldClose(robotwindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(robotwindow);
        glfwPollEvents();
    }
}

RobotWindow::~RobotWindow()
{
    glfwTerminate();
}