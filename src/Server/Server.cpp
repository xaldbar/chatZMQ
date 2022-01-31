#include "Server.h"

#include <sstream>
#include <thread>

static zmq::context_t context;
using namespace std::literals::chrono_literals;

Server::Server() {
  IP = "tcp://127.0.0.1:/5555";
}

Server::Server(std::string IP) {
  this->IP = IP;
}

void Server::run() {
  std::cout << "SERVER START...\n";
  socket = zmq::socket_t(context, zmq::socket_type::router);
  socket.bind(IP);
}


void Server::reg(zmq::message_t& idt) {
  User q(idt);
  this->online.push_back(q);
  std::string msg = idt.to_string();
  send(idt, msg);
}


void Server::debugInfo() {
  std::cout << "==========DEBUG INFO==========\n";
  std::cout << "[\n";
  for (User item: online) {
    std::cout << "<ID: " << item.getId().to_string() << " USERNAME: " << item.getUsername() << " STATUS: " << item.getStatus() << ">\n";
  }
  std::cout << "]\n";
  std::cout << "==============================\n";
}


void Server::login(zmq::message_t& id, std::stringstream& iss) {
  std::string username;
  std::string response;
  iss >> username;

  if (!isOnline(username)) {
    for (int i = 0; i < online.size(); i++) {
      if (online[i].getId().to_string() == id.to_string() && online[i].getStatus() == false) {
        online[i].setUsername(username);
        online[i].setStatus(true);
      }
    }
    response = "LOGIN OK";
  }
  else {
    response = "LOGIN BAD";
  }

  send(id, response);
}

void Server::logout(zmq::message_t& id) {
  std::string response;
  for (int i = 0; i < online.size(); i++)
    if (online[i].getId().to_string() == id.to_string()) {
      online[i].setStatus(false);
      online[i].setUsername("");
    }
  response = "LOGOUT OK";
  send(id, response);
}

void Server::sendDelayMessage(std::string id, std::string str) {
  zmq::message_t iden(id);
  std::string c, u, m, w;
  int delay;
  std::stringstream s(str);
  s >> c >> delay >> u;
  while(s >> w) m += w + " ";
  std::string tmp = c + " " + u + " " + m;
  std::stringstream ss(tmp);
  std::string command;
  ss >> command;
  
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  sendMessage(iden, ss);
}

void Server::sendMessage(zmq::message_t& id, std::stringstream& iss) {

  std::string username, message, word;
  iss >> username;
  while(iss >> word) message += word + " ";

  if (isOnline(username)) {
    User user = serch(username);
    User sender = serch(id);
    zmq::message_t iden;
    iden.copy(user.getId());
    std::string r = sender.getUsername() + ": " + message;
    send(iden, r);
    send(id, "SENDING OK");
  }
  else {
    send(id, "USER NOT ONLINE");
  }
}


void Server::eventLoop() {

  while (true) {
    
    debugInfo();


    zmq::message_t id;
    zmq::message_t msg;

    socket.recv(id);
    socket.recv(msg);
    
    std::string m = msg.to_string();
    std::stringstream iss(m);
    std::string command;
    iss >> command;

    std::cout << "[" << command << "] " << id.to_string() << "| " << msg.to_string() << "\n";


    if (command == "REG") {
      reg(id);
    }
    
    else if (command == "LOGIN") {
      login(id, iss);      
    }
    
    else if (command == "SEND") {
      sendMessage(id, iss);
    }

    else if (command == "DELAYSEND") {
      std::thread t1(&Server::sendDelayMessage, this, id.to_string(), m);
      t1.detach();
    }
    else if (command == "LOGOUT") {
      logout(id);
    }
    else {
      std::string response;
      response = ("ERROR MSG");
      send(id, response);
      command = response;
    }
    
  }
}

void Server::stop() {
  socket.unbind(IP);
}

bool Server::isOnline(std::string username) {
  for (int i = 0; i  < online.size(); i++)
    if (online[i].getUsername() == username)
      return online[i].getStatus();
  return false;
}

User Server::serch(std::string username) {
  for (int i = 0; i < online.size(); i++)
    if (online[i].getUsername() == username)
      return online[i];
}

User Server::serch(zmq::message_t& id) {
  for (int i = 0; i < online.size(); i++)
    if (online[i].getId().to_string() == id.to_string())
      return online[i];
}

void Server::send(zmq::message_t& id, std::string message) {
  zmq::message_t msg(message);
  socket.send(id, ZMQ_SNDMORE);
  socket.send(msg);
}

Server::~Server() {
  
}