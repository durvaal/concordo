#include <string>
#include "server_class.h"

using namespace std;

#ifndef __METHODS_H_
#define __METHODS_H_

void validateRequiredField(char *field, string fieldName);
string convertCharToString(char *field);
void hasUserLogged();
void hasServerConnected();
void createUser(char *arguments);
void login(char *arguments);
void disconnect();
void createServer(char *arguments);
void setServerDescription(char *arguments);
void setServerInviteCode(char *arguments);
void listServers();
bool userHasAlreadyEnteredTheServer(Server *server);
void enterServer(char *arguments);
void leaveServer();
void listParticipants();
void listChannels();
void createChannel(char *arguments);
void enterServer(char *arguments);
void leaveChannel();
void listAvailableCommands();
void initializeProgram();

#endif