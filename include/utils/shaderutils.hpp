#ifndef _SHADER_UTIL
#define _SHADER_UTIL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

//Important fucntions that are used as utility here
class ShaderUtils
{
    public:
    static unsigned int compileShader(unsigned int type, const std::string& shader);
    static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
};

#endif //_SHADER_UTIL