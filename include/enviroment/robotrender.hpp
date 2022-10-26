#ifndef _robotrender
#define _robotrender
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <enviroment/robotshader.h>
#include <robotmodel/robotmodel.hpp>
#include <utils/shaderutils.hpp>
#include <math.h>


class Robotrender
{   
    private:
        RobotModel * model;
        
        std::vector<unsigned int>  robotWheelindices;
        std::vector<unsigned int>  robotBodyindices ;
        std::vector<float> robotBodyVertices;
        std::vector<float> robotWheelVertices;
        //Initial offsets
        float fYOffset=0.0f;
        float fXOffset=0.0f;
        float fyaw=0.0f;

        unsigned int    robotVBO[2];
        unsigned int    robotVAO[2];
        unsigned int    robotEBO[2];
        
        unsigned int    robotBodyshaderProgram;
        unsigned int    robotWheelshaderProgram;
        
    public:
        Robotrender();
        unsigned int    getRobotBodyShaderprogram();
        unsigned int    getRobotWheelShaderprogram();
        unsigned int *  getRobotVAO();
        unsigned int *  getRobotVBO();
        void            moveRobotRender();
        ~Robotrender();
};


#endif //_robotrender