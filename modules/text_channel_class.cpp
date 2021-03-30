#include "./headers/text_channel_class.h"

TextChannel::TextChannel(){};
TextChannel::~TextChannel(){};

void TextChannel::setMessages(std::vector <Message> messages) {
  this->messages = messages;
}

std::vector <Message> TextChannel::getMessages() {
  return this->messages;
}