#include "pch.h"
#include<future> //async
#include<iostream>
#include<coroutine>
#include<chrono>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;
using namespace Windows::UI::Core;
using namespace std::chrono;

template<typename Async>
auto resume_in_any_apartment(Async async)
{
    struct awaiter : std::suspend_always
    {
        awaiter(Async async_) : async(std::move(async_)) { }

        bool await_ready()
        {
            return async.Status() == Windows::Foundation::AsyncStatus::Completed;
        }

        bool await_suspend(std::coroutine_handle<> handle)
        {
            if (async.Status() != Windows::Foundation::AsyncStatus::Started) {
                return false;
            }
            async.Completed([handle](auto&&...) { handle(); });
            return true;
        }

        auto await_resume()
        {
            return async.GetResults();
        }
        
        Async async;//awaiter
    };
    return awaiter{ std::move(async) };
}



auto ensure_dispatcher_thread(CoreDispatcher dispatcher)
{
    struct awaiter : std::suspend_always
    {
        CoreDispatcher dispatcher;

        bool await_ready() { return dispatcher.HasThreadAccess(); }

        void await_suspend(
            std::coroutine_handle<> handle)
        {
            dispatcher.RunAsync(CoreDispatcherPriority::Normal,
                [handle] { handle(); });
        }
    };
    return awaiter{ {}, std::move(dispatcher) };
}

auto operator co_await(CoreDispatcher dispatcher)
{
    return ensure_dispatcher_thread(std::move(dispatcher));
}

//IAsyncAction Delay10Seconds()
//{
//    co_await 10s;
//    co_return;
//}

int main() {
    //co_await this.Dispatcher();
	return 0;
}