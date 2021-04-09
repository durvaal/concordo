#include <string>

using namespace std;

#ifndef __USER_CLASS_H_
#define __USER_CLASS_H_

class User {
  private:
    int id;
    string name;
    string email;
    string password;

  public:
    User();
    ~User();

    void setId(int id);
    void setName(string name);
    void setEmail(string email);
    void setPassword(string password);

    int getId();
    string getName();
    string getEmail();
    string getPassword();
};

#endif