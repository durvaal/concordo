#include <string>
#include <vector>

using namespace std;

#ifndef __SYSTEM_CLASS_H_
#define __SYSTEM_CLASS_H_

#include "user_class.h"
#include "server_class.h"
#include "channel_class.h"

class System {
  private:
    std::vector <User *> users;
    std::vector <Server *> servers;
    int userLoggedId;
    std::string currentServerName;
    std::string currentChannelName;

  public:
    System();
    ~System();

    void setUsers(std::vector <User *> users);
    void setServers(std::vector <Server *> servers);
    void setUserLoggedId(int userLoggedId);
    void setCurrentServerName(std::string currentServerName);
    void setCurrentChannelName(std::string currentChannelName);
    void addUser(User *user);
    void addServer(Server *server);

    std::vector <User *> getUsers();
    std::vector <Server *> getServers();
    int getUserLoggedId();
    std::string getCurrentServerName();
    std::string getCurrentChannelName();
};

#endif