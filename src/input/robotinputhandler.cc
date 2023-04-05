#include "input/robotinputhandler.hpp"

RobotInputHandler::RobotInputHandler()
{
    // initialise the input handle
    FileOperations::init();
    Handle = FileOperations::getinstance().get();
    // Allocate 16kb for the vector initially 
    stateVector.reserve(1<<16);
}

std::vector<RobotState> && RobotInputHandler::getRobotStatesFromFile(std::string && filename)
{
    RobotState state;
    Handle->readfromfile(filename.c_str(),stringBuffer.data(),stringBuffer.size());
    std::string temp = std::string(stringBuffer.data());
    std::istringstream stream(temp);
    while(true)
    {
        stream >> state.velxy;
        std::getline(stream, temp, ',');
        stream >> state.yawrate;
        if(!std::getline(stream,temp))
        {
            break;
        }
    }
    return {};
}