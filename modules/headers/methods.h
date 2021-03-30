#include <string>

using namespace std;

#ifndef __METHODS_H_
#define __METHODS_H_

void validateRequiredField(char *field, std::string fieldName);
std::string convertCharToString(char *field);
void hasUserLogged();
void createUser(char *arguments);
void login(char *arguments);
void disconnect();
void createServer(char *arguments);
void setServerDescription(char *arguments);
void setServerInviteCode(char *arguments);
void listServers();
void initializeProgram();

#endif