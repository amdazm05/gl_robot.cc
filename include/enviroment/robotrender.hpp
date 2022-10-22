#ifndef _robotrender
#define _robotrender
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <enviroment/robotshader.h>


class Robotrender
{   
    private:
        std::vector<float> robotVertices;
        unsigned int robotVBO;
        unsigned int robotVAO;
        unsigned int robotEBO;
        unsigned int indices[6] = 
        {  // note that we start from 0!
            0, 1, 2,   // first triangle
            2, 3, 0    // second triangle
        };

        unsigned int robotshaderProgram;
        unsigned int robotvertexProgram;
        unsigned int robotfragmentShader;
        
    public:
        Robotrender();
        unsigned int getRobotShaderprogram();
        unsigned int getRobotVAO();
        ~Robotrender();
};


#endif //_robotrender