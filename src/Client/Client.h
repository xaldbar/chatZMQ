#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <zmq_addon.hpp>
#include "../User/User.h" 

class Client {
  public:
    Client();
    Client(std::string IP);
    

    void send(std::string text);
    void read();
    void connect();
    void eventLoop();
    void disconnect();
    void registerSocket();
    ~Client();

  private:
    std::string IP;
    static Client instance;
    zmq::socket_t socket;
    User user;
    bool loggedIn = false;
};

#endif // CLIENT_H