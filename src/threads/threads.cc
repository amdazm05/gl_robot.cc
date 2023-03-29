#include "threads/threads.hpp"
std::mutex AppThreadsManger::_mtx;

AppThreadsManger::AppThreadsManger()
{

}

AppThreadsManger::~AppThreadsManger()
{
    std::for_each(threadVector.begin(),threadVector.end(),[](std::thread & thd){ thd.join();});
}