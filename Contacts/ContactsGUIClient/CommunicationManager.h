#ifndef _COMMUNICATION_MANAGER_H_
#define _COMMUNICATION_MANAGER_H_

#include <string>
#include "Queue.h"

class CommunicationManager
{
public:
    CommunicationManager(Queue<std::string>& responseQueue);
    ~CommunicationManager();
    
    inline void addMessageToQueue(const std::string& message) { m_MessageQueue.push(message); }
    inline void terminateApp() { m_AppTerminated = true; }
    
private:
    void messagingThread();

private:
    Queue<std::string> m_MessageQueue;
    Queue<std::string>& m_ResponseQueue;
    bool m_AppTerminated = false;
    
};
#endif
