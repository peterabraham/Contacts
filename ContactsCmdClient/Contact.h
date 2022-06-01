#ifndef _CONTACTS_H_
#define _CONTACTS_H_

#include <string>

struct Contact
{
    std::string firstname;
    std::string lastname;
    long        phone;
    std::string email;
    std::string contactid;
    
    Contact() = default;
    Contact(std::string firstName, std::string lastName, long phone, std::string email, std::string contactId) :
        firstname(firstName), lastname(lastName), phone(phone), email(email), contactid(contactId)
    {}
};

#endif
