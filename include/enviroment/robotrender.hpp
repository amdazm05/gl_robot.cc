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

#define PATH_LINES 1 

class Robotrender
{   
    private:
        RobotModel * model;
        // limit the number of points available on the screen to save memory
        uint16_t     max_trail_points = -1;
        
        std::vector<unsigned int>  robotWheelindices;
        std::vector<unsigned int>  robotBodyindices ;
        std::vector<float> robotBodyVertices;
        std::vector<float> robotWheelVertices;
        std::vector<float> trail_points;

        //Initial offsets
        float fYOffset=0.0f;
        float fXOffset=0.0f;

        std::pair<float,float> robotCenter={0.0f,0.0f};

        float fyaw=0.0f;
        unsigned int    robotVBO[3];
        unsigned int    robotVAO[3];
        unsigned int    robotEBO[3];
        
        unsigned int    robotBodyshaderProgram;
        unsigned int    robotWheelshaderProgram;
        
    public:
        Robotrender();
        unsigned int    getRobotBodyShaderprogram();
        unsigned int    getRobotWheelShaderprogram();
        unsigned int *  getRobotVAO();
        unsigned int *  getRobotVBO();
        void            moveRobotRender(RobotState & offsets);
        void            renderRobotPathLine();
        unsigned int    getNumberOfTrailingPoints();
        void            updateRobotPath();
        ~Robotrender();
};


#endif //_robotrender