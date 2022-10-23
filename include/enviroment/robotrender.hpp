#ifndef _robotrender
#define _robotrender
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <enviroment/robotshader.h>
#include <utils/shaderutils.hpp>


class Robotrender
{   
    private:
        std::vector<float> robotVertices;
        unsigned int robotVBO;
        unsigned int robotVAO;
        unsigned int robotEBO;
        std::vector<unsigned int>  indices ;

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