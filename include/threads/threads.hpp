#ifndef _THREADS
#define _THREADS

#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class AppThreadsManger
{
    private:
        std::vector<std::thread> threadVector;
        std::condition_variable sync_condition;
        std::mutex mtx;
    public:
        AppThreadsManger();
        template<class Invokable,class...Args>
        void addTaskInThread(Invokable && invokableFunction,Args... arguements);
        ~AppThreadsManger();
};

template<class Invokable,class...Args>
void AppThreadsManger::addTaskInThread(Invokable && invokableFunction,Args... arguments)
{
    std::shared_ptr<std::packaged_task<typename std::result_of<Invokable(Args...)>::type()>> packedTaskPtr =  
    std::make_shared<std::packaged_task<typename std::result_of<Invokable(Args...)>::type()>>
        (
            std::bind(std::forward<Invokable>(invokableFunction),std::forward<Args>(arguments)...)
        );
    std::function<void()> voidInvokable = 

    [packedTaskPtr]()
    {
        (*packedTaskPtr)();
    };
    threadVector.emplace_back(std::move(voidInvokable));
}

#endif //_THREADS