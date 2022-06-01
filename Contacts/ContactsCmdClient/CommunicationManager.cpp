
#include "CommunicationManager.h"
#include <zmq.hpp>
#include <iostream>
#include <thread>

CommunicationManager::CommunicationManager(Queue<std::string>& responseQueue):
    m_ResponseQueue(responseQueue)
{
    std::thread messageThread(&CommunicationManager::messagingThread, this);
    messageThread.detach();
}

void CommunicationManager::messagingThread()
{
    std::cout << "CommunicationManager messagingThread\n";
    
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};
    
    // construct a REQ (request) socket and connect to interface
    zmq::socket_t socket{context, zmq::socket_type::req};
    socket.connect("tcp://localhost:5555");

    // Request to sent
    std::string request {""};
    std::string response {""};

    while (1)
    {
        if (m_AppTerminated) break;
        
        request = m_MessageQueue.waited_pop();
        std::cout << request << std::endl;
        // Send the request message
        socket.send(zmq::buffer(request), zmq::send_flags::none);
        
        // Wait for reply from server
        zmq::message_t reply{};
        socket.recv(reply, zmq::recv_flags::none);
        response = reply.to_string();
        std::cout << "Recieved response: " << response << std::endl;
        m_ResponseQueue.push(response);
    }
    
    std::cout << "Exited from the messaging thread.\n";
}
