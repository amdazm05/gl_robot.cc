#include<enviroment/robotwindow.hpp>
#include<enviroment/robotrender.hpp>

GLFWwindow* RobotWindow::robotwindow;
int RobotWindow::width;
int RobotWindow::height;        

RobotWindow::RobotWindow(int width, int height)
{
   
}

void RobotWindow::RenderWindow(int width, int height,RobotModel::RobotState &offsets)
{
    width = width;
    height = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    glfwMakeContextCurrent(robotwindow);
    if ( glewInit() != GLEW_OK)
        exit(EXIT_FAILURE); // or handle the error in a nicer way
    glfwGetFramebufferSize(robotwindow, &width, &height);  
    glViewport(0, 0, width, height);

    Robotrender robotrender;
   
    
    while(!glfwWindowShouldClose(robotwindow))
    {

        {
            std::lock_guard<std::mutex> lock(AppThreadsManger::_mtx);
            robotrender.moveRobotRender(offsets);
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(robotrender.getRobotBodyShaderprogram());
        glBindVertexArray(robotrender.getRobotVAO()[0]);
        glBindBuffer(GL_ARRAY_BUFFER, robotrender.getRobotVBO()[0]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glUseProgram(0);

        glUseProgram(robotrender.getRobotWheelShaderprogram());
        glBindVertexArray(robotrender.getRobotVAO()[1]);
        glBindBuffer(GL_ARRAY_BUFFER, robotrender.getRobotVBO()[1]);
        glEnableVertexAttribArray(0);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glUseProgram(0);


        glUseProgram(robotrender.getRobotWheelShaderprogram());
        glBindVertexArray(robotrender.getRobotVAO()[2]);
        glBindBuffer(GL_ARRAY_BUFFER, robotrender.getRobotVBO()[2]);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_POINTS, 0, robotrender.getNumberOfTrailingPoints());
        glUseProgram(0);


        glfwSwapBuffers(robotwindow);
        glfwPollEvents();
    }
}

RobotWindow::~RobotWindow()
{
    glfwTerminate();
}