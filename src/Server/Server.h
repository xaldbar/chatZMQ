#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <zmq_addon.hpp>
#include <vector>
#include "../User/User.h"



class Server {
  public:
    Server();
    Server(std::string IP);

    bool isOnline(std::string username);
    void reg(zmq::message_t& id);
    void send(zmq::message_t& id, std::string message);
    void login(zmq::message_t& id, std::stringstream& iss);
    void logout(zmq::message_t& id);
    void sendMessage(zmq::message_t& id, std::stringstream& iss);
    void sendDelayMessage(std::string id, std::string message);
    void run();
    void eventLoop();
    void stop();
    void debugInfo();
    
    User serch(std::string username);
    User serch(zmq::message_t& id);

    ~Server();

  private:
    std::string IP;
    static Server instance;
    zmq::socket_t socket;
    std::vector<User> online;
};

#endif // SERVER_H