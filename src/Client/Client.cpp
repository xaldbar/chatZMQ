#include "Client.h"
#include <thread>

static zmq::context_t context;
using namespace std::literals::chrono_literals;

Client::Client() {
  IP = "tcp://127.0.0.1:/5555";
}

Client::Client(std::string IP) {
  this->IP = IP;
}

void Client::connect() {
  std::cout << "CLIENT CONNECT...\n";
  socket = zmq::socket_t(context, zmq::socket_type::dealer);
  socket.connect(IP);
  registerSocket();
  
}


void Client::registerSocket() {
  std::string tmp = "REG";
  zmq::message_t reg(tmp);
  socket.send(reg);
  zmq::message_t iden;
  socket.recv(iden);
  user.setId(iden);
}

void Client::read(){
  while(true) {
    zmq::message_t response;
    socket.recv(response);
    std::cout << response.to_string()<< "\n";
    if (response.to_string() == "LOGIN OK") {
      user.setStatus(true);
      loggedIn = true;
    }
    if (response.to_string() == "LOGIN BAD") {
      user.setUsername("");
      loggedIn = false;
    }
    
    if (response.to_string() == "LOGOUT OK") {
      user.setStatus(false);
      loggedIn = false;
    }
  }
}

void Client::eventLoop() {
  std::thread recv(&Client::read, this);
  while (true) {
    std::string command;
    if (loggedIn) {
      std::cout << user.getUsername() << ": ";
    }
    else {
      std::cout << "PLS LOG IN: ";
    }
    std::cin >> command;
    if (command == "LOGIN") {
      std::string username;
      std::cin >> username;
      command = command + " " + username;
      user.setUsername(username);
      send(command);
    }
    else if (command == "SEND") {
      if (loggedIn) {
        std::string username, message;
        std::cin >> username; int c = getchar();
        getline(std::cin, message);
        command = command + " " + username + " " + message;
        send(command);
      }

      else {
        std::cout << "You must login first!\n";
      }
    }
    else if (command == "DELAYSEND") {
      if (loggedIn) {
        std::string delay, username, message;
        std::cin >> delay;
        std::cin >> username; int c = getchar();
        getline(std::cin, message);
        command = command + " " + delay + " " + username + " " + message;
        send(command);
      }
      else {
        std::cout << "You must login first!\n";
      }

    }
    else if (command == "LOGOUT") {
      if (loggedIn) {
        send(command);
      }
      else {
        std::cout << "You must login first!\n";
      }
    }
    else {
      std::cout << "Bad command\n";
    }
    
    
    std::this_thread::sleep_for(250ms);
  }
}

void Client::disconnect() {
  socket.disconnect(IP);
}

void Client::send(std::string text) {
  zmq::message_t request(text);
  socket.send(request);
}

Client::~Client() {

}

