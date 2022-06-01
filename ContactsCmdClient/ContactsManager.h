//
//  ContactsManager.h
//  ContactsClient
//
//  Created by Peter on 25/04/22.
//

#ifndef _CONTACTS_MANAGER_H
#define _CONTACTS_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "Contact.h"
#include "Queue.h"
#include "CommunicationManager.h"

class ContactsManager
{
public:
    ContactsManager();
    ~ContactsManager();
    
    void createContact(const Contact& newContact);
    void editContact(const Contact& contact);
    void deleteContact(const std::string& contactId);
    std::vector<Contact> getAllContacts();
    std::vector<Contact> searchContact(const std::string& searchQuery);
    
private:
    Queue<std::string>* m_ResponseQueue;
    CommunicationManager* m_ComunicationMgr;
};

#endif
