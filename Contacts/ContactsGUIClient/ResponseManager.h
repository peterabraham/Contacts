//
//  ResponseManager.h
//  ContactsClient
//
//  Created by Peter on 27/04/22.
//

#ifndef _RESPONSE_MANAGER_H
#define _RESPONSE_MANAGER_H

#include "Queue.h"
#include "Contact.h"
#include <string>
#include <functional>

using Callback = std::function<void(const std::vector<Contact>& contactList)>;

class ResponseManager
{
public:
    ResponseManager(Queue<std::string>& responseQueue);
    ~ResponseManager();

    inline void terminateApp() { m_AppTerminated = true; }
    inline void setGuiCallBack(Callback guiCallBack) { m_guiCallBack = guiCallBack; }

private:
    void reponseThread();

private:
    Queue<std::string>& m_responseQueue;
    Callback m_guiCallBack;
    bool m_AppTerminated = false;
};

#endif // _RESPONSE_MANAGER_H
