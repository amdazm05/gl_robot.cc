#include "threads/threads.hpp"

AppThreadsManger::AppThreadsManger()
{

}

AppThreadsManger::~AppThreadsManger()
{
    std::for_each(threadVector.begin(),threadVector.end(),[](std::thread & thd){ thd.join();});
}