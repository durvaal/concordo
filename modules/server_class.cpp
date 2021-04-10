#include "./headers/server_class.h"

Server::Server(){
  this->textChannels.reserve(1000);
  this->voiceChannels.reserve(1000);
  this->participantIds.reserve(1000);
};
Server::~Server(){};

void Server::setOwnerUserId(int ownerUserId) {
  this->ownerUserId = ownerUserId;
}
void Server::setName(string name) {
  this->name = name;
}
void Server::setDescription(string description) {
  this->description = description;
}
void Server::setInviteCode(string inviteCode) {
  this->inviteCode = inviteCode;
}
void Server::setTextChannels(vector <TextChannel *> textChannels) {
  this->textChannels = textChannels;
}
void Server::setVoiceChannels(vector <VoiceChannel *> voiceChannels) {
  this->voiceChannels = voiceChannels;
}
void Server::setParticipantIds(vector <int> participantIds) {
  this->participantIds = participantIds;
}
void Server::addTextChannel(TextChannel *textchannel) {
  this->textChannels.push_back(textchannel);
}
void Server::addVoiceChannel(VoiceChannel *voiceChannel) {
  this->voiceChannels.push_back(voiceChannel);
}
void Server::addParticipant(int participantId) {
  this->participantIds.push_back(participantId);
}

int Server::getOwnerUserId() {
  return this->ownerUserId;
}
string Server::getName() {
  return this->name;
}
string Server::getDescription() {
  return this->description;
}
string Server::getInviteCode() {
  return this->inviteCode;
}
vector <TextChannel *> Server::getTextChannels() {
  return this->textChannels;
}
vector <VoiceChannel *> Server::getVoiceChannels() {
  return this->voiceChannels;
}
vector <int> Server::getParticipantIds() {
  return this->participantIds;
}