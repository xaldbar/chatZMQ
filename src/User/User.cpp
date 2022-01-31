#include "../User/User.h"

User::User() {
  this->loggedIn = false;
}

User::User(zmq::message_t& id) {
  this->id.copy(id);
  this->loggedIn = false;
}

User::User(zmq::message_t& id, std::string username) {
  this->id.copy(id);
  this->username = username;
  this->loggedIn = false;
}

User::User(const User& user) {
  this->id.copy(&user.id);
  this->username = user.username;
  this->loggedIn = user.loggedIn;
}

std::string User::getUsername() {
  return username;
}

zmq::message_t& User::getId() {
  return id;
}

bool User::getStatus() {
  return loggedIn;
}


void User::setUsername(std::string username) {
  this->username = username;
}
void User::setId(zmq::message_t& id) {
  this->id.copy(&id);
}
void User::setStatus(bool status) {
  this->loggedIn = status;
}