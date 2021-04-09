#include "./headers/text_channel_class.h"

TextChannel::TextChannel(){};
TextChannel::~TextChannel(){};

void TextChannel::setMessages(vector <Message> messages) {
  this->messages = messages;
}

vector <Message> TextChannel::getMessages() {
  return this->messages;
}