#include <vector>

using namespace std;

#ifndef __TEXT_CHANNEL_CLASS_H_
#define __TEXT_CHANNEL_CLASS_H_

#include "message_class.h"

class TextChannel {
  private:
    vector <Message> messages;

  public:
    TextChannel();
    ~TextChannel();

    void setMessages(vector <Message> messages);

    vector <Message> getMessages();
};

#endif