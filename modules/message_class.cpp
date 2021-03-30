#include "./headers/message_class.h"

Message::Message(){};
Message::~Message(){};

void Message::setDateTime(std::string dateTime) {
  this->dateTime = dateTime;
}
void Message::setSendBy(std::string sendBy) {
  this->sendBy = sendBy;
}
void Message::setContent(std::string content) {
  this->content = content;
}

std::string Message::getDateTime() {
  return this->dateTime;
}
std::string Message::getSendBy() {
  return this->sendBy;
}
std::string Message::getContent() {
  return this->content;
}