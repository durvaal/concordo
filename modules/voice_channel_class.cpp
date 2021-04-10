#include "./headers/voice_channel_class.h"

VoiceChannel::VoiceChannel(){};
VoiceChannel::~VoiceChannel(){};

void VoiceChannel::setMessage(Message *message) {
  this->message = message;
}

Message * VoiceChannel::getMessage() {
  return this->message;
}