
#include <thread>
#include <iostream>
//#include <zmq.hpp>
#include <chrono>
#include "ContactsManager.h"

using namespace std;
Contact create()
{
    string s;
    long n;
    Contact c;
    cout << "First name: \n";
    cin >> s;
    
    c.firstname = s;
    cout << "Last name: \n";
    cin >> s;
    c.lastname = s;
    
    cout << "Phone: \n";
    cin >> n;
    c.phone = n;
    
    cout << "Email: \n";
    cin >> s;
    c.email = s;
    
    return c;
}

int main()
{
    auto contactMgr = ContactsManager();
    
    cout << "Welcome to Contacts app\n";



    while (1)
    {
        cout << "Menu:\n";
        cout << "1. View all contacts\n";
        cout << "2. Create new contact\n";
        cout << "3. Search contacts by name\n";
        cout << "4. Edit contact\n";
        cout << "5. Delete contact\n";
        cout << "0. Exit\n";
        cout << "Enter an option:\n";
        int option = 0;
        cin >> option;
        
        switch (option)
        {
            case 1:
            {
                contactMgr.getAllContacts();
                break;
            }
            case 2:
            {
                auto contact = create();
                contactMgr.createContact(contact);
                break;
            }
            case 3:
            {
                cout << "Enter search query: \n";
                string query;
                cin >> query;
                contactMgr.searchContact(query);
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                cout << "Enter contact id to be deleted: \n";
                string id;
                cin >> id;
                contactMgr.deleteContact(id);
                break;
            }
            case 0:
            {
                goto exit_loop;
            }
                
//            default:
//                break;
        }
        cout << "Do you like to continue:(y/n):\n";
        char ch;
        cin >> ch;
        
        while (true) {
            if ( ch == 'n' || ch == 'y')
                break;
            cout << "Do you like to continue:(y/n):\n";
            char ch;
        }
        
        if (ch == 'n')
            break;
        else
            cout << "\033[2J\033[1;1H";
    }
    exit_loop:
    cout << "Exited from Contact app!\n";
    
//    auto comm = CommunicationManager();
//    std::this_thread::sleep_for(std::chrono::seconds(20));
//    std::cout << "Terminating the app\n";
//    comm.terminateApp();
    
//    // initialize the zmq context with a single IO thread
//    zmq::context_t context{1};
//
//    // construct a REQ (request) socket and connect to interface
//    zmq::socket_t socket{context, zmq::socket_type::req};
//    socket.connect("tcp://localhost:5555");
//
//    // set up some static data to send
//    const std::string data{"Hello"};
//
//    for (auto request_num = 0; request_num < 10; ++request_num)
//    {
//        // send the request message
//        std::cout << "Sending Hello " << request_num << "..." << std::endl;
//        socket.send(zmq::buffer(data), zmq::send_flags::none);
//
//        // wait for reply from server
//        zmq::message_t reply{};
//        socket.recv(reply, zmq::recv_flags::none);
//
//        std::cout << "Received " << reply.to_string();
//        std::cout << " (" << request_num << ")";
//        std::cout << std::endl;
//    }

    return 0;
}
