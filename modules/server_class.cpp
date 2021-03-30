#include "./headers/server_class.h"

Server::Server(){};
Server::~Server(){};

void Server::setOwnerUserId(int ownerUserId) {
  this->ownerUserId = ownerUserId;
}
void Server::setName(std::string name) {
  this->name = name;
}
void Server::setDescription(std::string description) {
  this->description = description;
}
void Server::setInviteCode(std::string inviteCode) {
  this->inviteCode = inviteCode;
}
void Server::setChannels(std::vector <Channel *> channels) {
  this->channels = channels;
}
void Server::setParticipantIds(std::vector <int> participantIds) {
  this->participantIds = participantIds;
}

int Server::getOwnerUserId() {
  return this->ownerUserId;
}
std::string Server::getName() {
  return this->name;
}
std::string Server::getDescription() {
  return this->description;
}
std::string Server::getInviteCode() {
  return this->inviteCode;
}
std::vector <Channel *> Server::getChannels() {
  return this->channels;
}
std::vector <int> Server::getParticipantIds() {
  return this->participantIds;
}