#include "./headers/text_channel_class.h"

TextChannel::TextChannel(){
  this->messages.reserve(1000);
};
TextChannel::~TextChannel(){};

void TextChannel::addMessage(Message *message) {
  this->messages.push_back(message);
}

vector <Message *> TextChannel::getMessages() {
  return this->messages;
}