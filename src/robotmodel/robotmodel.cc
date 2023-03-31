#include <robotmodel/robotmodel.hpp>

DiffRobotModel::DiffRobotModel()
{

}

RobotModel::RobotState DiffRobotModel::updateSate(float velocity, float yawRate)
{   
    // This is the B matrix
    Xt.velxy=velocity;
    Xt.yawrate=yawRate;
    // Next State
    Xt.x =   Xt_prev.x   +  velocity  * std::cosh(Xt_prev.yaw)*delT;
    Xt.y =   Xt_prev.y   +  velocity  * std::sinh(Xt_prev.yaw)*delT;
    Xt.yaw = Xt_prev.yaw +  yawRate   * delT;

    //Time update to previous state
    Xt_prev.x = Xt.x;
    Xt_prev.y = Xt.y;
    Xt_prev.yaw = Xt.yaw;
    Xt_prev.velxy=velocity;
    Xt_prev.yawrate=yawRate;
    return Xt;
    
}