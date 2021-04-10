#include "./headers/system_class.h"

System::System(){
  this->users.reserve(1000);
  this->servers.reserve(1000);
  this->userLoggedId = 0;
  this->currentServerName = "";
  this->currentChannelName = "";
};
System::~System(){};

void System::setUsers(vector <User *> users) {
  this->users = users;
}
void System::setServers(vector <Server *> servers) {
  this->servers = servers;
}
void System::setUserLoggedId(int userLoggedId) {
  this->userLoggedId = userLoggedId;
}
void System::setCurrentServerName(string currentServerName) {
  this->currentServerName = currentServerName;
}
void System::setCurrentChannelName(string currentChannelName) {
  this->currentChannelName = currentChannelName;
}
void System::addUser(User *user) {
  this->users.push_back(user);
}
void System::addServer(Server *server) {
  this->servers.push_back(server);
}

vector <User *> System::getUsers() {
  return this->users;
}
vector <Server *> System::getServers() {
  return this->servers;
}
int System::getUserLoggedId() {
  return this->userLoggedId;
}
string System::getCurrentServerName() {
  return this->currentServerName;
}
string System::getCurrentChannelName() {
  return this->currentChannelName;
}
User * System::getUserById(int id) {
  User *user = new User();
  for (vector<int>::size_type i = 0; i < this->getUsers().size(); i++) {
    if (this->getUsers().at(i)->getId() == id) {
      user =  this->getUsers().at(i);
    }
  }

  return user;
}