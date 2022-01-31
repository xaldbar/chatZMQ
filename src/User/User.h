#ifndef USER_H
#define USER_H

#include <string>
#include <zmq_addon.hpp>



class  User {
    public:
        User();
        User(zmq::message_t& id);
        User(zmq::message_t& id, std::string username);
        User(const User& user);
        std::string getUsername();
        zmq::message_t& getId();
        bool getStatus();
        
        void setUsername(std::string username);
        void setId(zmq::message_t& id);
        void setStatus(bool status);

        
    private:
        std::string username;
        zmq::message_t id;
        bool loggedIn;
};

#endif // USER_H