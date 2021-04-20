#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

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
    void saveUsers() {
      ofstream users;

      users.open ("users.txt");
      users << this->getUsers().size() << "\n";
      
      for (vector<int>::size_type i = 0; i < this->getUsers().size(); i++) {
        users << this->getUsers().at(i)->getId() << "\n";
        users << this->getUsers().at(i)->getName() << "\n";
        users << this->getUsers().at(i)->getEmail() << "\n";
        users << this->getUsers().at(i)->getPassword() << "\n";
      }

      users.close();
    };
    void saveServers() {
      ofstream servers;

      servers.open ("servers.txt");
      servers << this->getServers().size() << "\n";

      for (vector<int>::size_type i = 0; i < this->getServers().size(); i++) {
        Server *server = this->getServers().at(i);
        servers << server->getOwnerUserId() << "\n";
        servers << server->getName() << "\n";
        servers << server->getDescription() << "\n";
        servers << server->getInviteCode() << "\n";
        servers << server->getParticipantIds().size() << "\n";
        for (vector<int>::size_type j = 0; j < server->getParticipantIds().size(); j++) {
          servers << server->getParticipantIds().at(j) << "\n";
        }
        servers << server->getTextChannels().size() + server->getVoiceChannels().size() << "\n";
        for (vector<int>::size_type j = 0; j < server->getTextChannels().size(); j++) {
          servers << server->getTextChannels().at(j)->getName() << "\n";
          servers << "TEXT\n";
          servers << server->getTextChannels().at(j)->getMessages().size() << "\n";
          for (vector<int>::size_type k = 0; k < server->getTextChannels().at(j)->getMessages().size(); k++) {
            servers << server->getTextChannels().at(j)->getMessages().at(k)->getSendBy() << "\n";
            servers << server->getTextChannels().at(j)->getMessages().at(k)->getDateTime() << "\n";
            servers << server->getTextChannels().at(j)->getMessages().at(k)->getContent() << "\n";
          }
        }
        for (vector<int>::size_type j = 0; j < server->getVoiceChannels().size(); j++) {
          servers << server->getVoiceChannels().at(j)->getName() << "\n";
          servers << "VOICE\n";
          servers << "1 \n";
          servers << server->getVoiceChannels().at(j)->getMessage()->getSendBy() << "\n";
          servers << server->getVoiceChannels().at(j)->getMessage()->getDateTime() << "\n";
          servers << server->getVoiceChannels().at(j)->getMessage()->getContent() << "\n";
        }
      }

      servers.close();
    };
    void loadUsers() {
      string line;
      ifstream users("users.txt");
      User *user = new User();
      this->users.reserve(1000);

      /**
       * -1 : primeiro elemento, tamanho da lista de usuário
       *  0 : segundo elemento, id do usuário
       *  1 : terceiro elemento, nome do usuário
       *  2 : quarto elemento, email do usuário
       *  3 : quinto elemento, senha do usuário
       * 
       * A ideia é ler o primeiro o elemento, e a partir disso criar um objeto usuário com os próximos 4 elementos, adicionar no array e ler os proximos 4 elementos para o novo usuário
       */
      if (users.is_open()) {
        int argument = -1;

        while (getline(users, line)) {
          if (argument == 0) {
            user->setId(stoi(line));
          }
          if (argument == 1) {
            user->setName(line);
          }
          if (argument == 2) {
            user->setEmail(line);
          }
          if (argument == 3) {
            user->setPassword(line);
          }
          
          argument++;
          
          if(argument == 4) {
            argument = 0;
            this->users.push_back(user);
          }
        }

        users.close();
      }
    }
    void loadServers() {
    }

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
    void save();
    void load();

    vector <User *> getUsers();
    vector <Server *> getServers();
    int getUserLoggedId();
    string getCurrentServerName();
    string getCurrentChannelName();
    User * getUserById(int id);
};

#endif