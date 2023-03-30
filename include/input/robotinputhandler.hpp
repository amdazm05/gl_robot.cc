#ifndef _RBTINPUTHANDLER
#define _RBTINPUTHANDLER
#include "fileoperations/fileoperations.hpp"
#include "robotmodel/robotmodel.hpp"

class RobotInputHandler
{
    public:
        RobotInputHandler();
        vector<RobotModel> && getRobotStatesFromFile();
    private:
        FileOperations *Handle;
};

#endif 