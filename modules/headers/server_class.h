#include <string>
#include <vector>

using namespace std;

#ifndef __SERVER_CLASS_H_
#define __SERVER_CLASS_H_

#include "channel_class.h"

class Server {
  private:
    int ownerUserId;
    std::string name;
    std::string description;
    std::string inviteCode;
    std::vector <Channel *> channels;
    std::vector <int> participantIds;

  public:
    Server();
    ~Server();

    void setOwnerUserId(int ownerUserIds);
    void setName(std::string name);
    void setDescription(std::string description);
    void setInviteCode(std::string inviteCode);
    void setChannels(std::vector <Channel *> channels);
    void setParticipantIds(std::vector <int> participantIds);
    void addChannel(Channel *channel);
    void addParticipant(int participantId);

    int getOwnerUserId();
    std::string getName();
    std::string getDescription();
    std::string getInviteCode();
    std::vector <Channel *> getChannels();
    std::vector <int> getParticipantIds();
};

#endif