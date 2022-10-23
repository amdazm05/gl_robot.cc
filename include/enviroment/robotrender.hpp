#ifndef _robotrender
#define _robotrender
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <enviroment/robotshader.h>
#include <utils/shaderutils.hpp>
#include <math.h>


class Robotrender
{   
    private:
        std::vector<float> robotVertices;
        unsigned int robotVBO;
        unsigned int robotVAO;
        unsigned int robotEBO;
        std::vector<unsigned int>  indices ;

        //Initial offsets
        float fYOffset=0.0f;
        float fXOffset=0.0f;

        unsigned int robotshaderProgram;
        unsigned int robotvertexProgram;
        unsigned int robotfragmentShader;
        
    public:
        Robotrender();
        unsigned int getRobotShaderprogram();
        unsigned int getRobotVAO();
        unsigned int getRobotVBO();
        void moveRobotRender();
        ~Robotrender();
};


#endif //_robotrender