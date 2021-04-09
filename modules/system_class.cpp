#include "./headers/system_class.h"

System::System(){
  this->users.reserve(1000);
  this->servers.reserve(1000);
  this->userLoggedId = 0;
  this->currentServerName = "";
};
System::~System(){};

void System::setUsers(std::vector <User *> users) {
  this->users = users;
}
void System::setServers(std::vector <Server *> servers) {
  this->servers = servers;
}
void System::setUserLoggedId(int userLoggedId) {
  this->userLoggedId = userLoggedId;
}
void System::setCurrentServerName(std::string currentServerName) {
  this->currentServerName = currentServerName;
}
void System::setCurrentChannelName(std::string currentChannelName) {
  this->currentChannelName = currentChannelName;
}
void System::addUser(User *user) {
  this->users.push_back(user);
}
void System::addServer(Server *server) {
  this->servers.push_back(server);
}

std::vector <User *> System::getUsers() {
  return this->users;
}
std::vector <Server *> System::getServers() {
  return this->servers;
}
int System::getUserLoggedId() {
  return this->userLoggedId;
}
std::string System::getCurrentServerName() {
  return this->currentServerName;
}
std::string System::getCurrentChannelName() {
  return this->currentChannelName;
}
User * System::getUserById(int id) {
  User *user = new User();
  for (std::vector<int>::size_type i = 0; i < this->getUsers().size(); i++) {
    if (this->getUsers().at(i)->getId() == id) {
      user =  this->getUsers().at(i);
    }
  }

  return user;
}