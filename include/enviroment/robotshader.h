#ifndef _ROBOT_SHADER
#define _ROBOT_SHADER

static std::string vertexShader = "#version 330 core\n"
    "layout (location = 0) in vec4 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = position;\n"
    "gl_PointSize = 3.0;\n"
    "}\n";

static std::string fragmentShader = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.1f, 0.2f, 1.0f);\n"
"}\n";

static std::string blackfragShader = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
"}\n";

#endif