#include <string>
#include <vector>

using namespace std;

#ifndef __SERVER_CLASS_H_
#define __SERVER_CLASS_H_

#include "text_channel_class.h"
#include "voice_channel_class.h"

class Server {
  private:
    int ownerUserId;
    string name;
    string description;
    string inviteCode;
    vector <TextChannel *> textChannels;
    vector <VoiceChannel *> voiceChannels;
    vector <int> participantIds;

  public:
    Server();
    ~Server();

    void setOwnerUserId(int ownerUserIds);
    void setName(string name);
    void setDescription(string description);
    void setInviteCode(string inviteCode);
    void setTextChannels(vector <TextChannel *> textChannels);
    void setVoiceChannels(vector <VoiceChannel *> voiceChannels);
    void setParticipantIds(vector <int> participantIds);
    void addTextChannel(TextChannel *textChannel);
    void addVoiceChannel(VoiceChannel *voiceChannel);
    void addParticipant(int participantId);

    int getOwnerUserId();
    string getName();
    string getDescription();
    string getInviteCode();
    vector <TextChannel *> getTextChannels();
    vector <VoiceChannel *> getVoiceChannels();
    vector <int> getParticipantIds();
};

#endif