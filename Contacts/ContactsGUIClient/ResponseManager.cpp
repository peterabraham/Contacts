#include "ResponseManager.h"
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/optional.hpp>
//#include <boost/iostreams/stream.hpp>>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <sstream>
#include <thread>

namespace json = boost::json;

ResponseManager::ResponseManager(Queue<std::string>& responseQueue) : m_responseQueue(responseQueue)
{
    std::thread reponseThread(&ResponseManager::reponseThread, this);
    reponseThread.detach();
}

ResponseManager::~ResponseManager()
{
    terminateApp();
}

void ResponseManager::reponseThread()
{
    std::string response;
    while(true)
    {
        if (m_AppTerminated) break;

        response = m_responseQueue.waited_pop();

        auto jsonResponse = json::parse(response);
        auto operation = json::value_to<std::string>(jsonResponse.at("operation"));

        if (operation == "get-all-contacts" || operation == "search-contacts")
        {
            std::vector<Contact> contacts;
            auto data = jsonResponse.as_object()["data"].as_array();
            for (auto& item : data)
            {
                //auto& res = item.as_object();
                Contact contact;
                contact.firstname = json::value_to<std::string>(item.at("firstname"));
                contact.lastname  = json::value_to<std::string>(item.at("lastname"));
                contact.phone     = json::value_to<long>(item.at("phone"));
                contact.email     = json::value_to<std::string>(item.at("email"));
                contact.contactid = json::value_to<std::string>(item.at("contactid"));

                contacts.push_back(contact);
            }

            m_guiCallBack(contacts);
        }
//        boost::property_tree::ptree pt;
//        boost::iostreams::stream<boost::iostreams::array_source> stream(response.c_str(), response.size());
//        boost::property_tree::read_json(stream, pt);
    }
}
