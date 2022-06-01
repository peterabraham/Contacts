//
//  Queue.h
//  ContactsClient
//
//  Created by Peter on 25/04/22.
//

#ifndef _QUEUE_H
#define _QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class Queue
{
private:
    mutable std::mutex m_Mutex;
    std::queue<T> myDataQueue;
    std::condition_variable myCond;
    
public:
    Queue() = default;
    ~Queue() = default;
    
    Queue(const Queue& that)
    {
        std::lock_guard<std::mutex> lock(that.m_Mutex);
        myDataQueue = that.myDataQueue;
    }
    
    void push(T value)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        myDataQueue.push(value);
        
        myCond.notify_one();
    }
    
    T waited_pop()
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        myCond.wait(lock, [this] {return !myDataQueue.empty();});

        auto ret = myDataQueue.front();
        myDataQueue.pop();

        return ret;
    }
    
    bool try_pop(T& ret)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        if (myDataQueue.empty()) return false;
        
        ret = myDataQueue.front();
        myDataQueue.pop();
        
        return true;
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        return myDataQueue.empty();
    }
};

#endif
