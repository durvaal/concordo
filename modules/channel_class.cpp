#include "./headers/channel_class.h"

Channel::Channel(){};
Channel::~Channel(){};

void Channel::setName(string name) {
  this->name = name;
}

string Channel::getName() {
  return this->name;
}