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
        Server *server = new Server();
        server = this->getServers().at(i);
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
          if (server->getVoiceChannels().at(j)->getMessage()->getSendBy() != "") {
            servers << "1 \n";
            servers << server->getVoiceChannels().at(j)->getMessage()->getSendBy() << "\n";
            servers << server->getVoiceChannels().at(j)->getMessage()->getDateTime() << "\n";
            servers << server->getVoiceChannels().at(j)->getMessage()->getContent() << "\n";
          } else {
            servers << "0 \n";
          }
        }
      }

      servers.close();
    };
    /**
     * Verifica se há primeira linha o número de usuários não está vazio
     * Esse valor é usado como referência no laço enquanto, para que a cada indice sejam
     * lidas todas as informações de um usuário
     */
    void loadUsers() {
      string line;
      ifstream users("users.txt");

      if (users.is_open()) {
        User *user = new User();

        getline(users, line);
        if (line != "") {
          int userLength = stoi(line);

          while (userLength > 0) {
            getline(users, line);
            user->setId(stoi(line));

            getline(users, line);
            user->setName(line);

            getline(users, line);
            user->setEmail(line);

            getline(users, line);
            user->setPassword(line);
            
            this->users.push_back(user);
            user = new User();
            
            userLength--;
          }
        }
      }

      users.close();
    }
    /**
     * Verifica se há primeira o número de servidores não está vazio
     * Esse valor é usado como referência no laço enquanto, para que a cada indice sejam
     * lidas todas as informações de um servidor
     * O mesmo vale para as condições de parada do número de participante, canais
     * e mensagens
     */
    void loadServers() {
      string line;
      ifstream servers("servers.txt");

      if (servers.is_open()) {
        Server *server = new Server();

        getline(servers, line);
        if (line != "") {
          int serverLength = stoi(line);

          while (serverLength > 0) {
            getline(servers, line);
            server->setOwnerUserId(stoi(line));

            getline(servers, line);
            server->setName(line);

            getline(servers, line);
            server->setDescription(line);

            getline(servers, line);
            server->setInviteCode(line);
            
            getline(servers, line);
            int participantsLength = stoi(line);

            while (participantsLength > 0) {
              getline(servers, line);
              server->addParticipant(stoi(line));
              participantsLength--;
            }
            
            getline(servers, line);
            int channelsLength = stoi(line);

            while (channelsLength > 0) {
              string channelName;
              string channelType;
              TextChannel *textChannel = new TextChannel();
              VoiceChannel *voiceChannel = new VoiceChannel();

              getline(servers, line);
              channelName = line;

              getline(servers, line);
              channelType = line;

              if (channelType == "TEXT") {
                textChannel = new TextChannel();
                textChannel->setName(channelName);
              }
              if (channelType == "VOICE") {
                voiceChannel = new VoiceChannel();
                voiceChannel->setName(channelName);
              }

              getline(servers, line);
              int messagesLength = stoi(line);

              while (messagesLength > 0) {
                Message *message = new Message();

                getline(servers, line);
                message->setSendBy(line);

                getline(servers, line);
                message->setDateTime(line);
                
                getline(servers, line);
                message->setContent(line);
                
                if (channelType == "TEXT") {
                  textChannel->addMessage(message);
                }
                if (channelType == "VOICE") {
                  voiceChannel->setMessage(message);
                }

                messagesLength--;
              }

              if (textChannel->getName() != "") {
                server->addTextChannel(textChannel);
                textChannel = new TextChannel();
              }
              if (voiceChannel->getName() != "") {
                server->addVoiceChannel(voiceChannel);
                voiceChannel = new VoiceChannel();
              }

              channelsLength--;
            }

            this->addServer(server);
            server = new Server();

            serverLength--;
          }
        }
      }

      servers.close();
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