#include "./headers/voice_channel_class.h"

VoiceChannel::VoiceChannel(){
  this->message = new Message();
};
VoiceChannel::~VoiceChannel(){};

void VoiceChannel::setMessage(Message *message) {
  this->message = message;
}

Message * VoiceChannel::getMessage() {
  return this->message;
}