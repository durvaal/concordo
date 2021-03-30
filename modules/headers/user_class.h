#include <string>

using namespace std;

#ifndef __USER_CLASS_H_
#define __USER_CLASS_H_

class User {
  private:
    int id;
    std::string name;
    std::string email;
    std::string password;

  public:
    User();
    ~User();

    void setId(int id);
    void setName(std::string name);
    void setEmail(std::string email);
    void setPassword(std::string password);

    int getId();
    std::string getName();
    std::string getEmail();
    std::string getPassword();
};

#endif