#include <robotmodel/robotmodel.hpp>

DiffRobotModel::DiffRobotModel()
{
    // Set A and B to the following sizes
    B.resize(3,2);
}

void DiffRobotModel::updateSate(float velocity, float yawRate)
{
    Xt_prev.x;
    Xt_prev.y;
}