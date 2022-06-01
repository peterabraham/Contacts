
//
//  ContactsManager.h
//  ContactsClient
//
//  Created by Peter on 25/04/22.
//

#include "ContactsManager.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <sstream>

ContactsManager::ContactsManager()
{
    m_ResponseQueue   = new Queue<std::string>();
    m_ComunicationMgr = new CommunicationManager(*m_ResponseQueue);
}

ContactsManager::~ContactsManager()
{
    delete m_ResponseQueue;
    delete m_ComunicationMgr;
}
    
void ContactsManager::createContact(const Contact& newContact)
{
    boost::property_tree::ptree pt;
    pt.put("operation", "create-contact");
    pt.put("data.firstname", newContact.firstname);
    pt.put("data.lastname", newContact.lastname);
    pt.put("data.phone", newContact.phone);
    pt.put("data.email", newContact.email);
    pt.put("data.contactid", newContact.contactid);
    
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    
    m_ComunicationMgr->addMessageToQueue(ss.str());
}

void ContactsManager::editContact(const Contact& contact)
{
    boost::property_tree::ptree pt;
    pt.put("operation", "update-contact");
    pt.put("data.firstname", contact.firstname);
    pt.put("data.lastname", contact.lastname);
    pt.put("data.phone", contact.phone);
    pt.put("data.email", contact.email);
    pt.put("data.contactid", contact.contactid);
    
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    
    m_ComunicationMgr->addMessageToQueue(ss.str());
}

void ContactsManager::deleteContact(const std::string& contactId)
{
    boost::property_tree::ptree pt;
    pt.put("operation", "delete-contact");
    pt.put("contactid", contactId);
    
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    
    m_ComunicationMgr->addMessageToQueue(ss.str());
}

std::vector<Contact> ContactsManager::getAllContacts()
{
    boost::property_tree::ptree pt;
    pt.put("operation", "get-all-contacts");
    
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    
    m_ComunicationMgr->addMessageToQueue(ss.str());
    
    // TODO - response handling
    return std::vector<Contact>();
}

std::vector<Contact> ContactsManager::searchContact(const std::string& searchQuery)
{
    boost::property_tree::ptree pt;
    pt.put("operation", "search-contact");
    pt.put("query", searchQuery);
    
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, pt);
    
    m_ComunicationMgr->addMessageToQueue(ss.str());
    
    // TODO - response handling
    return std::vector<Contact>();
}
