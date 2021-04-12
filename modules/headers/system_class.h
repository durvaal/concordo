#include <string>
#include <vector>

using namespace std;

#ifndef __SYSTEM_CLASS_H_
#define __SYSTEM_CLASS_H_

#include "user_class.h"
#include "server_class.h"

class System {
  private:
    vector <User *> users;
    vector <Server *> servers;
    int userLoggedId;
    string currentServerName;
    string currentChannelName;

  public:
    System();
    ~System();

    void setUsers(vector <User *> users);
    void setServers(vector <Server *> servers);
    void setUserLoggedId(int userLoggedId);
    void setCurrentServerName(string currentServerName);
    void setCurrentChannelName(string currentChannelName);
    void addUser(User *user);
    void addServer(Server *server);
    void clearSystem();

    vector <User *> getUsers();
    vector <Server *> getServers();
    int getUserLoggedId();
    string getCurrentServerName();
    string getCurrentChannelName();
    User * getUserById(int id);
};

#endif