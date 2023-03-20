#include <enviroment/robotrender.hpp>

Robotrender::Robotrender()
{
    //initialising the the vertices of the robot
    
    robotBodyVertices = 
    {
        -0.1f, -0.1f, 0.0f,  // left 
        0.1f, -0.1f, 0.0f,  // right
        0.1f, 0.1f, 0.0f,  // top 
        -0.1f, 0.1f, 0.0f,  // left 
    };
    
    robotBodyindices = 
    {  
        0, 1, 2,   // first triangle
        2, 3, 0    // second triangle
    };

    robotWheelVertices = 
    {
        -0.05f,0.1f,0.0f,
        -0.05f,0.15f,0.0f,
         0.05f,0.15f,0.0f,
         0.05f,0.1f,0.0f,

        -0.05f,-0.1f,0.0f,
        -0.05f,-0.15f,0.0f,
         0.05f,-0.15f,0.0f,
         0.05f,-0.1f,0.0f
    };

    robotWheelindices =
    {
        0,1,2,
        2,0,3,
        4,5,6,
        6,4,7
    };
    
    robotBodyshaderProgram = ShaderUtils::createShader(vertexShader, fragmentShader);
    robotWheelshaderProgram = ShaderUtils::createShader(vertexShader, blackfragShader);

    //Render Robot body 
    glGenVertexArrays(1, &robotVAO[0]);
    glGenBuffers(1, &robotVBO[0]);
    glGenBuffers(1, &robotEBO[0]);
    glBindVertexArray(robotVAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, robotBodyVertices.size()*sizeof(float), &robotBodyVertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, robotEBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, robotBodyindices.size()*sizeof(float), &robotBodyindices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);


    //Render the Robot wheels
    glGenVertexArrays(1, &robotVAO[1]);
    glGenBuffers(1, &robotVBO[1]);
    glGenBuffers(1, &robotEBO[1]);
    glBindVertexArray(robotVAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, robotWheelVertices.size()*sizeof(float), &robotWheelVertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, robotEBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, robotWheelindices.size()*sizeof(float), &robotWheelindices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);  

}

unsigned int Robotrender::getRobotBodyShaderprogram()
{
    return  robotBodyshaderProgram;
}

unsigned int Robotrender::getRobotWheelShaderprogram()
{
    return  robotWheelshaderProgram;
}

unsigned int * Robotrender::getRobotVAO()
{
    return  robotVAO;
}

unsigned int * Robotrender::getRobotVBO()
{
    return  robotVBO;
}

void Robotrender::moveRobotRender(RobotModel::RobotState &offsets)
{
   
    fXOffset = offsets.x;
    fYOffset = offsets.y;
    fyaw = offsets.yaw;

    // For animating the render
    for(int iVertex = 0; iVertex < robotWheelVertices.size() ; iVertex += 3)
    {   
        robotWheelVertices.at(iVertex) = robotWheelVertices.at(iVertex)*cosf(fyaw)+robotWheelVertices.at(iVertex+1)*sinf(fyaw);
        robotWheelVertices.at(iVertex+1) = -robotWheelVertices.at(iVertex)*sinf(fyaw)+robotWheelVertices.at(iVertex+1)*cosf(fyaw);
        robotWheelVertices.at(iVertex)+= fXOffset;
        robotWheelVertices.at(iVertex+1) += fYOffset;

        if(iVertex < robotBodyVertices.size())
        {
            robotBodyVertices.at(iVertex) = robotBodyVertices.at(iVertex)*cosf(fyaw)+robotBodyVertices.at(iVertex+1)*sinf(fyaw);
            robotBodyVertices.at(iVertex+1) = -robotBodyVertices.at(iVertex)*sinf(fyaw)+robotBodyVertices.at(iVertex+1)*cosf(fyaw);
            robotBodyVertices.at(iVertex)+= fXOffset;
            robotBodyVertices.at(iVertex+1) += fYOffset;
        }
    }

    #if PATH_LINES == 1 
    if((trail_points.size()+3) < (1<<16))
    {
        trail_points.push_back(robotBodyVertices.at(0));
        trail_points.push_back(robotBodyVertices.at(1));
        renderRobotPathLine();
    }
    else
    {
        trail_points.clear();
    }
    #endif

    glBindBuffer(GL_ARRAY_BUFFER, robotVBO[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, robotBodyVertices.size()*sizeof(float), &robotBodyVertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, robotVBO[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, robotWheelVertices.size()*sizeof(float), &robotWheelVertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void  Robotrender::renderRobotPathLine()
{
    //Render the Robot wheels
    glGenVertexArrays(1, &robotVAO[2]);
    glGenBuffers(1, &robotVBO[2]);

    glBindVertexArray(robotVAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO[2]);
    glBufferData(GL_ARRAY_BUFFER, trail_points.size()*sizeof(float), &trail_points[0], GL_STATIC_DRAW);


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glEnable(GL_PROGRAM_POINT_SIZE);
}

void Robotrender::updateRobotPath()
{
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO[2]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, trail_points.size()*sizeof(float), &trail_points[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int Robotrender::getNumberOfTrailingPoints()
{
    return trail_points.size();
}

Robotrender::~Robotrender()
{

}






