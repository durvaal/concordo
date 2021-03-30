#include <string>

using namespace std;

#ifndef __CHANNEL_CLASS_H_
#define __CHANNEL_CLASS_H_

class Channel {
  private:
    std::string name;

  public:
    Channel();
    ~Channel();

    void setName(std::string name);

    std::string getName();
};

#endif