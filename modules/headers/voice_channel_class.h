#include <vector>

using namespace std;

#ifndef __VOICE_CHANNEL_CLASS_H_
#define __VOICE_CHANNEL_CLASS_H_

#include "message_class.h"
#include "channel_class.h"

class VoiceChannel: public Channel {
  private:
    Message *message;

  public:
    VoiceChannel();
    ~VoiceChannel();

    void setMessage(Message *message);

    Message * getMessage();
};

#endif