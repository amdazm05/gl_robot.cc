#ifndef _ROBOT_MODEL
#define _ROBOT_MODEL
#include <boost/numeric/ublas/matrix.hpp>

class RobotModel
{
    public:
        struct RobotState
        {
            float x;
            float y;
            float yaw;
        };
        RobotState Xt_prev;
        RobotState Xt;
    public:
        virtual RobotState updateSate(float velocity, float yawRate)=0;
};

class DiffRobotModel : public RobotModel
{
    private:
        //Since it an identity we don't really need to do anything fancy 
        // but writing this here for completeness 
        // boost::numeric::ublas::identity_matrix<float> A;
        float delT = 0.01f;
        boost::numeric::ublas::matrix<float> B;
    public:
        DiffRobotModel();
        //  Returns the new state ?
        RobotState updateSate(float velocity, float yawRate);
};

#endif //_ROBOT_MODEL
