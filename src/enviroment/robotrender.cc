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

    int success;
 
    robotshaderProgram = ShaderUtils::createShader(vertexShader, fragmentShader);

    glGenVertexArrays(1, &robotVAO);
    glGenBuffers(1, &robotVBO);
    glGenBuffers(1, &robotEBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(robotVAO);

    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    glBufferData(GL_ARRAY_BUFFER, robotVertices.size()*sizeof(float), &robotVertices[0], GL_STATIC_DRAW);

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

Robotrender::~Robotrender()
{

}






