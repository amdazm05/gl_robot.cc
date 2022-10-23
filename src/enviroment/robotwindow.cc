#include<enviroment/robotwindow.hpp>
#include<enviroment/robotrender.hpp>

RobotWindow::RobotWindow(int width, int height)
{
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
   
    
    glBindVertexArray(robotrender.getRobotVAO());
    while(!glfwWindowShouldClose(robotwindow))
    {
        robotrender.moveRobotRender();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(robotrender.getRobotShaderprogram());
        
        glBindBuffer(GL_ARRAY_BUFFER, robotrender.getRobotVBO());
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glDisableVertexAttribArray(0);
        glUseProgram(0);

        glfwSwapBuffers(robotwindow);
        glfwPollEvents();
    }
}

RobotWindow::~RobotWindow()
{
    glfwTerminate();
}