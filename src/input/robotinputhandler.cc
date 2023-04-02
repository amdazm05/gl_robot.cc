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
    //  Read a chunk of 16KB
    Handle->readfromfile(filename.c_str(),stringBuffer.data(),sizeofBufferToRead);
    //  process buffer chunks and extract words
    //  remove redundant buffer chunks
    return std::move(stateVector);
}