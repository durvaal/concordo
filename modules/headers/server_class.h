#include <string>
#include <vector>

using namespace std;

#ifndef __SERVER_CLASS_H_
#define __SERVER_CLASS_H_

#include "channel_class.h"

class Server {
  private:
    int ownerUserId;
    string name;
    string description;
    string inviteCode;
    vector <Channel *> channels;
    vector <int> participantIds;

  public:
    Server();
    ~Server();

    void setOwnerUserId(int ownerUserIds);
    void setName(string name);
    void setDescription(string description);
    void setInviteCode(string inviteCode);
    void setChannels(vector <Channel *> channels);
    void setParticipantIds(vector <int> participantIds);
    void addChannel(Channel *channel);
    void addParticipant(int participantId);

    int getOwnerUserId();
    string getName();
    string getDescription();
    string getInviteCode();
    vector <Channel *> getChannels();
    vector <int> getParticipantIds();
};

#endif