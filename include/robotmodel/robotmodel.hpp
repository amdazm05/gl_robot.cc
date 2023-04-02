#ifndef _ROBOT_MODEL
#define _ROBOT_MODEL
#include <cmath>

struct RobotState
{
    float x;
    float y;
    float yaw;
    float velxy;
    float yawrate;
};

class RobotModel
{
    public:
        RobotState Xt_prev;
        RobotState Xt;
    public:
        virtual RobotState updateSate(float velocity, float yawRate)=0;
};

class DiffRobotModel : public RobotModel
{
    private:
        float delT = 0.001f;
    public:
        DiffRobotModel();
        //  Returns the new state ?
        RobotState updateSate(float velocity, float yawRate);
};

#endif //_ROBOT_MODEL
