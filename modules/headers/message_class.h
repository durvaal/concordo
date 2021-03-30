#include <string>

using namespace std;

#ifndef __MESSAGE_CLASS_H_
#define __MESSAGE_CLASS_H_

class Message {
  private:
    std::string dateTime;
    std::string sendBy;
    std::string content;

  public:
    Message();
    ~Message();

    void setDateTime(std::string dateTime);
    void setSendBy(std::string sendBy);
    void setContent(std::string content);

    std::string getDateTime();
    std::string getSendBy();
    std::string getContent();
};

#endif