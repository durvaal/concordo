#include "./headers/server_class.h"

Server::Server(){
  this->channels.reserve(1000);
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
void Server::setChannels(vector <Channel *> channels) {
  this->channels = channels;
}
void Server::setParticipantIds(vector <int> participantIds) {
  this->participantIds = participantIds;
}
void Server::addChannel(Channel *channel) {
  this->channels.push_back(channel);
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
vector <Channel *> Server::getChannels() {
  return this->channels;
}
vector <int> Server::getParticipantIds() {
  return this->participantIds;
}