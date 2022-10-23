#include <enviroment/robotrender.hpp>

Robotrender::Robotrender()
{
    //initialising the the vertices of the robot
    robotVertices = 
    {
        -0.1f, -0.1f, 0.0f,  // left 
        0.1f, -0.1f, 0.0f,  // right
        0.1f, 0.1f, 0.0f,  // top 
        -0.1f, 0.1f, 0.0f,  // left 
    };
    
    indices = 
    {  
        0, 1, 2,   // first triangle
        2, 3, 0    // second triangle
    };

    robotshaderProgram = ShaderUtils::createShader(vertexShader, fragmentShader);

    glGenVertexArrays(1, &robotVAO);
    glGenBuffers(1, &robotVBO);
    glGenBuffers(1, &robotEBO);
    glBindVertexArray(robotVAO);
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    glBufferData(GL_ARRAY_BUFFER, robotVertices.size()*sizeof(float), &robotVertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, robotEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(float), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

}

unsigned int Robotrender::getRobotShaderprogram()
{
    return  robotshaderProgram;
}

unsigned int Robotrender::getRobotVAO()
{
    return  robotVAO;
}

unsigned int Robotrender::getRobotVBO()
{
    return  robotVBO;
}

void Robotrender::moveRobotRender()
{

    const float fLoopDuration = 5.0f;
    const float fScale = 3.14159f * 2.0f / fLoopDuration;
    
    float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    
    fXOffset =  0.01f*0.5f;
    fYOffset =  0.01f*0.5f;

    for(int iVertex = 0; iVertex < robotVertices.size() ; iVertex += 3)
    {
        std::cout<<robotVertices.at(iVertex)<<" , "<<robotVertices.at(iVertex+1)<<std::endl;
        
        robotVertices.at(iVertex)+= fXOffset;
        robotVertices.at(iVertex+1) += fYOffset;
    }

    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, robotVertices.size()*sizeof(float), &robotVertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Robotrender::~Robotrender()
{

}






