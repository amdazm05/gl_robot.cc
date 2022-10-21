#include <enviroment/robotrender.hpp>

Robotrender::Robotrender()
{
    //initialising the the vertices of the robot
    robotVertices = 
    {
        0.2f,  0.2f, 0.0f,  // top right
        0.0f, -0.0f, 0.0f,  // bottom right
        -0.2f, -0.2f, 0.0f,  // bottom left
        // -0.2f,  0.2f, 0.0f   // top left 

    };
    
    
    int success;
    unsigned int EBO;
    robotvertexProgram = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(robotvertexProgram, 1, &vertexShaderSource, NULL);
    glCompileShader(robotvertexProgram);
    // check for shader compile errors
    char infoLog[512];
    glGetShaderiv(robotvertexProgram, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(robotvertexProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    robotfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(robotfragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(robotfragmentShader);
    // check for shader compile errors
    glGetShaderiv(robotfragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(robotfragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED " << infoLog << std::endl;
    }
    // link shaders
    robotshaderProgram = glCreateProgram();

    glAttachShader(robotshaderProgram, robotvertexProgram);
    glAttachShader(robotshaderProgram, robotshaderProgram);
    glLinkProgram(robotshaderProgram);
    // check for linking errors
    glGetProgramiv(robotshaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(robotshaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(robotvertexProgram);
    glDeleteShader(robotfragmentShader);

    glGenVertexArrays(1, &robotVAO);
    glGenBuffers(1, &robotVBO);
    // glGenBuffers(1, &robotEBO);
    glBindVertexArray(robotVAO);

    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    glBufferData(GL_ARRAY_BUFFER, robotVertices.size()*sizeof(float), &robotVertices[0], GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, robotEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLint vpAttr = glGetAttribLocation(robotshaderProgram, "vp");
    glVertexAttribPointer(vpAttr, 3, GL_FLOAT, GL_FALSE, 0, NULL);

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






