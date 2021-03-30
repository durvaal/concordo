#include "./headers/user_class.h"

User::User(){};
User::~User(){};

void User::setId(int id) {
  this->id = id;
}
void User::setName(std::string name) {
  this->name = name;
}
void User::setEmail(std::string email) {
  this->email = email;
}
void User::setPassword(std::string password) {
  this->password = password;
}

int User::getId() {
  return this->id;
}
std::string User::getName() {
  return this->name;
}
std::string User::getEmail() {
  return this->email;
}
std::string User::getPassword() {
  return this->password;
}