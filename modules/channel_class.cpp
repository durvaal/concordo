#include "./headers/channel_class.h"

Channel::Channel(){};
Channel::~Channel(){};

void Channel::setName(std::string name) {
  this->name = name;
}

std::string Channel::getName() {
  return this->name;
}