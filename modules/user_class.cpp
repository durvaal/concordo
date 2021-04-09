#include "./headers/user_class.h"

User::User(){};
User::~User(){};

void User::setId(int id) {
  this->id = id;
}
void User::setName(string name) {
  this->name = name;
}
void User::setEmail(string email) {
  this->email = email;
}
void User::setPassword(string password) {
  this->password = password;
}

int User::getId() {
  return this->id;
}
string User::getName() {
  return this->name;
}
string User::getEmail() {
  return this->email;
}
string User::getPassword() {
  return this->password;
}