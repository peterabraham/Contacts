//
//  ContactsManager.h
//  ContactsClient
//
//  Created by Peter on 25/04/22.
//

#ifndef _CONTACTS_MANAGER_H
#define _CONTACTS_MANAGER_H

#include <string>
#include <memory>
#include <functional>
#include "Contact.h"
#include "Queue.h"
#include "CommunicationManager.h"
#include "ResponseManager.h"

class ContactsManager
{
public:
    ContactsManager();
    ~ContactsManager();

    void createContact(const Contact& newContact);
    void editContact(const Contact& contact);
    void deleteContact(const std::string& contactId);
    void getAllContacts();
    void searchContact(const std::string& searchQuery);
    
    inline void setGuiCallBack(Callback guiCallback)
    {
        m_responseMgr->setGuiCallBack(guiCallback);
    }

private:
    Queue<std::string>*   m_responseQueue;
    CommunicationManager* m_comunicationMgr;
    ResponseManager*      m_responseMgr;
};

#endif
