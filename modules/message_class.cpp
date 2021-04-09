#include "./headers/message_class.h"

Message::Message(){};
Message::~Message(){};

void Message::setDateTime(string dateTime) {
  this->dateTime = dateTime;
}
void Message::setSendBy(string sendBy) {
  this->sendBy = sendBy;
}
void Message::setContent(string content) {
  this->content = content;
}

string Message::getDateTime() {
  return this->dateTime;
}
string Message::getSendBy() {
  return this->sendBy;
}
string Message::getContent() {
  return this->content;
}