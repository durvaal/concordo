#include <string>

using namespace std;

#ifndef __MESSAGE_CLASS_H_
#define __MESSAGE_CLASS_H_

class Message {
  private:
    string dateTime;
    string sendBy;
    string content;

  public:
    Message();
    ~Message();

    void setDateTime(string dateTime);
    void setSendBy(string sendBy);
    void setContent(string content);

    string getDateTime();
    string getSendBy();
    string getContent();
};

#endif