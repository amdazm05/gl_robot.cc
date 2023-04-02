#ifndef _RBTINPUTHANDLER
#define _RBTINPUTHANDLER
#include <fileoperations/fileoperations.hpp>
#include "robotmodel/robotmodel.hpp"

class RobotInputHandler
{
    public:
        RobotInputHandler();
        std::vector<RobotState> && getRobotStatesFromFile(std::string && filename);
    private:
        FileOperations *Handle;
        std::vector<RobotState> stateVector;
        std::array<char,1<<32> stringBuffer;
        std::size_t sizeofBufferToRead;
};

#endif 