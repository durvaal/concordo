#include <string>

using namespace std;

#ifndef __CHANNEL_CLASS_H_
#define __CHANNEL_CLASS_H_

class Channel {
  private:
    string name;

  public:
    Channel();
    ~Channel();

    void setName(string name);

    string getName();
};

#endif