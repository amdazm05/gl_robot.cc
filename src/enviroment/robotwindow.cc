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
    unsigned int VAO = robotrender.getRobotVAO();
    unsigned int shaderprog = robotrender.getRobotShaderprogram();
    
    // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glUseProgram(shaderprog);   
    while(!glfwWindowShouldClose(robotwindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Segmentation fault if incorrect type is used here
        glfwSwapBuffers(robotwindow);
        glfwPollEvents();
    }
}

RobotWindow::~RobotWindow()
{
    glfwTerminate();
}