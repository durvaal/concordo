#include <vector>

using namespace std;

#ifndef __TEXT_CHANNEL_CLASS_H_
#define __TEXT_CHANNEL_CLASS_H_

#include "message_class.h"
#include "channel_class.h"

class TextChannel: public Channel {
  private:
    vector <Message *> messages;

  public:
    TextChannel();
    ~TextChannel();

    void addMessage(Message *message);

    vector <Message *> getMessages();
};

#endif