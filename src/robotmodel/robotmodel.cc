#include <robotmodel/robotmodel.hpp>

DiffRobotModel::DiffRobotModel()
{
    // Set A and B to the following sizes
    B.resize(3,2);
}

RobotModel::RobotState DiffRobotModel::updateSate(float velocity, float yawRate)
{   
    // This is the B matrix
    Xt.velxy=velocity;
    Xt.yawrate=yawRate;
    B(0,0)= cosf(Xt_prev.yaw)*delT;
    B(1,0)= sinf(Xt_prev.yaw)*delT;
    // Next State
    Xt.x =   Xt_prev.x   +  velocity  * B(0,0);
    Xt.y =   Xt_prev.y   +  velocity  * B(1,0);
    Xt.yaw = Xt_prev.yaw +  yawRate   * delT;

    //Time update to previous state
    Xt_prev.x = Xt.x;
    Xt_prev.y = Xt.y;
    Xt_prev.yaw = Xt.yaw;
    Xt_prev.velxy=velocity;
    Xt_prev.yawrate=yawRate;
    return Xt;
    
}