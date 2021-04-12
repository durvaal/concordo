#include <stdio.h>
#include <stdexcept>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <ctime>
#include <iostream>
#include "./headers/system_class.h"
#include "./headers/user_class.h"
#include "./headers/text_channel_class.h"
#include "./headers/voice_channel_class.h"
#include "./headers/methods.h"

System *concordoSystem = new System();
int currentUserId = 0;

void validateRequiredField(char *field, string fieldName) {
  if (field == NULL) {
    ostringstream oss;
    oss << "Runtime error: The field '" << fieldName << "' has required";
    throw runtime_error(oss.str());
  }
}

string convertCharToString(char *field) {
  string fieldValueConverted;
  fieldValueConverted = field;
  return fieldValueConverted;
}

void hasUserLogged() {
  if (concordoSystem->getUserLoggedId() == 0) {
    ostringstream oss;
    oss << "Runtime error: Access denied, you must be logged, try execute command 'login <userEmail> <userPassword>'";
    throw runtime_error(oss.str());
  }
}

void hasServerConnected() {
  if (concordoSystem->getCurrentServerName() == "") {
    ostringstream oss;
    oss << "Runtime error: You are not connected to a server";
    throw runtime_error(oss.str());
  }
}

void hasChannelConnected() {
  if (concordoSystem->getCurrentChannelName() == "") {
    ostringstream oss;
    oss << "Runtime error: You are not connected to a channel";
    throw runtime_error(oss.str());
  }
}

/*
  Cria um novo usuário caso todos os campos tenham sido informados e se não existir um usuário cadastrado com o email informado
*/
void createUser(char *arguments) {
  // Valida os campos necessário para criar o usuário
  // O primeiro (email) e segundo (password) argumento tem o delimitador de espaço, enquanto que o último é todo o resto do argumento (name)
  char *email = strtok(NULL, " ");
  validateRequiredField(email, "email");
  char *password = strtok(NULL, " ");
  validateRequiredField(password, "password");
  char *name = strtok(NULL, "");
  validateRequiredField(name, "name");

  User *user = new User();

  user->setEmail(convertCharToString(email));
  user->setPassword(convertCharToString(password));
  user->setName(convertCharToString(name));

  // Verifica na lista de usuários criados se existe um usuário com o email informado
  for (vector<int>::size_type i = 0; i < concordoSystem->getUsers().size(); i++) {
    if (concordoSystem->getUsers().at(i)->getEmail() == user->getEmail()) {
      ostringstream oss;
      oss << "Runtime error: User with email '" << user->getEmail() << "' already exists";
      throw runtime_error(oss.str());
    }
  }

  // O id é incrementado aqui, pois pode ser lançada a exceção ao encontrar um usuário, isso evita o incremento quando não puder inserir um novo usuário
  currentUserId++;
  user->setId(currentUserId);

  concordoSystem->addUser(user);

  cout << "\n::: Created user :::\n\n";
}

/*
 O id do usuário logado é iniciado com zero, e esse é o argumento para validação do usuário logado ou não
*/
void login(char *arguments) {
  char *email = strtok(NULL, " ");
  validateRequiredField(email, "email");
  char *password = strtok(NULL, "");
  validateRequiredField(password, "password");

  User *user = new User();

  user->setEmail(convertCharToString(email));
  user->setPassword(convertCharToString(password));

  // A cada novo login reseta o id do usuario logado
  concordoSystem->setUserLoggedId(0);

  // Verifica se há um usuário com o mesmo email e senha
  for (vector<int>::size_type i = 0; i < concordoSystem->getUsers().size(); i++) {
    if (concordoSystem->getUsers().at(i)->getEmail() == user->getEmail()
    && concordoSystem->getUsers().at(i)->getPassword() == user->getPassword()) {
      concordoSystem->setUserLoggedId(concordoSystem->getUsers().at(i)->getId());
      break;
    }
  }

  if (concordoSystem->getUserLoggedId() == 0) {
    ostringstream oss;
    oss << "Runtime error: Invalid email or password";
    throw runtime_error(oss.str());
  } else {
    // São resetadas as informações de servidor conectado e canal conectado, já que pode ser o login de usuário diferente
    concordoSystem->setCurrentServerName("");
    concordoSystem->setCurrentChannelName("");
    cout << "\n::: Logged is as " << user->getEmail() << " :::\n\n"; 
  }

  delete user;
}

/*
  Caso haja id de usuário logado, busca-se a informação do usuário na lista de usuário do sistema através do id, para informar que este está sendo deslogado.
*/
void disconnect() {
  hasUserLogged();

  // Verifica se há um usuário com id do usuario logado
  // São resetadas as informações de id, servidor conectado e canal conectado
  for (vector<int>::size_type i = 0; i < concordoSystem->getUsers().size(); i++) {
    if (concordoSystem->getUsers().at(i)->getId() == concordoSystem->getUserLoggedId()) {
      concordoSystem->setUserLoggedId(0);
      concordoSystem->setCurrentServerName("");
      concordoSystem->setCurrentChannelName("");
      cout << "\n::: Disconnecting user " << concordoSystem->getUsers().at(i)->getEmail() << " :::\n\n"; 
      break;
    }
  }
}

/*
  Cria um servidor de nome único e com o usuário logado como proprietário
*/
void createServer(char *arguments) {
  hasUserLogged();

  // Valida os campos necessário para criar o servidor
  char *name = strtok(NULL, "");
  validateRequiredField(name, "name");

  Server *server = new Server();

  server->setName(convertCharToString(name));
  server->setOwnerUserId(concordoSystem->getUserLoggedId());

  // Verifica na lista de servidores criados se existe um servidor com o nome informado
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == server->getName()) {
      ostringstream oss;
      oss << "Runtime error: Server with name '" << server->getName() << "' already exists";
      throw runtime_error(oss.str());
    }
  }

  concordoSystem->addServer(server);

  cout << "\n::: Created server '" << server->getName() << "' :::\n\n";
}

/*
  Altera a descrição do servidor se o servidor existir e se o usuário logado for o proprietário
*/
void setServerDescription(char *arguments) {
  hasUserLogged();

  // Valida os campos necessário para alterar a descrição do servidor
  char *serverName = strtok(NULL, " ");
  validateRequiredField(serverName, "serverName");
  char *description = strtok(NULL, "");
  validateRequiredField(description, "description");

  bool updatedDescription = false;
  Server *server = new Server();

  server->setName(convertCharToString(serverName));
  server->setDescription(convertCharToString(description));

  // Verifica na lista de servidores criados se existe um servidor com o nome informado e com o usuario logado como proprietário
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == server->getName()) {
      if (concordoSystem->getServers().at(i)->getOwnerUserId() == concordoSystem->getUserLoggedId()) {
        updatedDescription = true;
        concordoSystem->getServers().at(i)->setDescription(server->getDescription());
      } else {
        ostringstream oss;
        oss << "Runtime error: You cannot change the description of a server that has not been created by you";
        throw runtime_error(oss.str());
      }
    }
  }

  if (updatedDescription) {
    cout << "\n::: Modified '" << server->getName() << "' server description! :::\n\n";
  } else {
    ostringstream oss;
    oss << "Runtime error: '" << server->getName() << "' server doesn’t exist";
    throw runtime_error(oss.str());
  }
}

/*
  Adiconar/remover o convite do servidor se o servidor existir e se o usuário logado for o proprietário
*/
void setServerInviteCode(char *arguments) {
  hasUserLogged();

  // Valida os campos necessário para alterar a descrição do servidor
  char *serverName = strtok(NULL, " ");
  validateRequiredField(serverName, "serverName");
  char *inviteCode = strtok(NULL, "");

  bool updatedInviteCode = false;
  Server *server = new Server();

  server->setName(convertCharToString(serverName));
  if (inviteCode == NULL) {
    server->setInviteCode("");
  } else {
    server->setInviteCode(convertCharToString(inviteCode));
  }

  // Verifica na lista de servidores criados se existe um servidor com o nome informado e com o usuario logado como proprietário
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == server->getName()) {
      if (concordoSystem->getServers().at(i)->getOwnerUserId() == concordoSystem->getUserLoggedId()) {
        updatedInviteCode = true;
        concordoSystem->getServers().at(i)->setInviteCode(server->getInviteCode());
      } else {
        ostringstream oss;
        oss << "Runtime error: You cannot change the invite code of a server that has not been created by you";
        throw runtime_error(oss.str());
      }
    }
  }

  if (updatedInviteCode) {
    if (server->getInviteCode() == "") {
      cout << "\n::: Removed '" << server->getName() << "' server invite code! :::\n\n";
    } else {
      cout << "\n::: Modified '" << server->getName() << "' server invite code! :::\n\n";
    }
  } else {
    ostringstream oss;
    oss << "Runtime error: '" << server->getName() << "' server doesn’t exist";
    throw runtime_error(oss.str());
  }
}

/*
  Lista os servidores cadastrados
*/
void listServers() {
  hasUserLogged();

  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    cout << "\n::: Server Name: " << concordoSystem->getServers().at(i)->getName();
    cout << "\n::: Description: " << concordoSystem->getServers().at(i)->getDescription();
    cout << "\n::: Invite Code: " << concordoSystem->getServers().at(i)->getInviteCode();
    cout << "\n";
  }
}

bool userHasAlreadyEnteredTheServer(Server *server) {
  bool hasAlreadyEntered = false;
  for (vector<int>::size_type i = 0; i < server->getParticipantIds().size(); i++) {
    if(server->getParticipantIds().at(i) == concordoSystem->getUserLoggedId()) {
      hasAlreadyEntered = true;
      break;
    }
  }

  return hasAlreadyEntered;
}

/*
  Entrar em um servidor com ou sem o codigo de convite
*/
void enterServer(char *arguments) {
  hasUserLogged();

  // Valida os campos necessário para entrar no servidor
  char *serverName = strtok(NULL, " ");
  validateRequiredField(serverName, "serverName");
  char *inviteCode = strtok(NULL, "");

  bool hasAccessToServer = false;
  bool serverNotFound = true;
  Server *server = new Server();

  server->setName(convertCharToString(serverName));
  if (inviteCode == NULL) {
    server->setInviteCode("");
  } else {
    server->setInviteCode(convertCharToString(inviteCode));
  }

  // Verifica na lista de servidores criados se existe um servidor com o nome informado
  // Caso haja invite é verificado se o codigo está correto
  // Antes, se o usuario logado é proprietário, a verificação do invite é desconsiderada
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == server->getName()) {
      serverNotFound = false;
      if(userHasAlreadyEnteredTheServer(concordoSystem->getServers().at(i)) && concordoSystem->getServers().at(i)->getInviteCode() != "") {
        hasAccessToServer = true;
        concordoSystem->setCurrentServerName(server->getName());
      } else {
        if (concordoSystem->getServers().at(i)->getOwnerUserId() == concordoSystem->getUserLoggedId() && concordoSystem->getCurrentServerName() == server->getName()) {
          hasAccessToServer = true;
          concordoSystem->getServers().at(i)->addParticipant(concordoSystem->getUserLoggedId());
          concordoSystem->setCurrentServerName(server->getName());
        } else {
          if (concordoSystem->getServers().at(i)->getInviteCode() == "") {
            hasAccessToServer = true;
            concordoSystem->getServers().at(i)->addParticipant(concordoSystem->getUserLoggedId());
            concordoSystem->setCurrentServerName(server->getName());
          } else {
            if (concordoSystem->getServers().at(i)->getInviteCode() == server->getInviteCode()) {
              hasAccessToServer = true;
              concordoSystem->getServers().at(i)->addParticipant(concordoSystem->getUserLoggedId());
              concordoSystem->setCurrentServerName(server->getName());
            } else {
              ostringstream oss;
              oss << "Runtime error: Server requires invitation code";
              throw runtime_error(oss.str());
            }
          }
        }
      }
    }
  }

  if (serverNotFound) {
    ostringstream oss;
    oss << "Runtime error: Server '" << server->getName() << "' not found";
    throw runtime_error(oss.str());
  }

  // É resetada a informação do canal conectado, pois ele se refere ao contexto do canal que foi desconectado
  if (hasAccessToServer) {
    concordoSystem->setCurrentChannelName("");
    cout << "\n::: Successfully connected on to the server '" << server->getName() << "' :::\n\n";
  }

  delete server;
}

/*
  Sai do servidor atualmente conectado
*/
void leaveServer() {
  hasUserLogged();

  // São resetadas as informações de servidor conectado e canal conectado
  if(concordoSystem->getCurrentServerName() != "") {
    cout << "\n::: Exiting the server '" << concordoSystem->getCurrentServerName() << "' :::\n\n";
    concordoSystem->setCurrentServerName("");
    concordoSystem->setCurrentChannelName("");
  } else {
    cout << "\n::: You are not viewing any servers :::\n\n";
  }
}

/*
  Lista todos os participantes do servidor atualmente conectado
*/
void listParticipants() {
  hasUserLogged();
  hasServerConnected();

  cout << "\n::: Server participants :::\n\n";
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == concordoSystem->getCurrentServerName()) {
      Server *server = concordoSystem->getServers().at(i);
      if (server->getParticipantIds().size() > 0) {
        for (vector<int>::size_type j = 0; j < server->getParticipantIds().size(); j++) {
          User *user = concordoSystem->getUserById(server->getParticipantIds().at(j));
          cout << "★ " << user->getName() << "\n";
        }
      } else {
        cout << "\n: No registered participants :\n";
      }
      cout << "\n";
    }
  }
}

/*
  Lista todos os canais disponíves do servidor atualmente connectado
*/
void listChannels() {
  hasUserLogged();
  hasServerConnected();

  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == concordoSystem->getCurrentServerName()) {
      Server *server = concordoSystem->getServers().at(i);
      cout << "\n::: # Channel of text :::\n\n";
      if (server->getTextChannels().size() <= 0) {
        cout << "\n: No registered channels of voice :\n";
      }
      for (vector<int>::size_type j = 0; j < server->getTextChannels().size(); j++) {
        cout << "★ " << server->getTextChannels().at(j)->getName() << "\n";
      }
      cout << "\n";
      cout << "\n::: # Channel of voice :::\n\n";
      if (server->getVoiceChannels().size() <= 0) {
        cout << "\n: No registered channels of text :\n";
      }
      for (vector<int>::size_type j = 0; j < server->getVoiceChannels().size(); j++) {
        cout << "★ " << server->getVoiceChannels().at(j)->getName() << "\n";
      }
      cout << "\n";
    }
  }
}

/*
  Cria um canal de voz ou text no servidor atualmente conectado
*/
void createChannel(char *arguments) {
  hasUserLogged();
  hasServerConnected();

  // Valida os campos necessário para criar o canal no servidor
  char *name = strtok(NULL, " ");
  validateRequiredField(name, "name");
  char *type = strtok(NULL, "");
  validateRequiredField(type, "type");

  string channelName = convertCharToString(name);

  if(convertCharToString(type) != "text" && convertCharToString(type) != "voice") {
    ostringstream oss;
    oss << "Runtime error: Not a valid type, please inform: 'text' or 'voice'";
    throw runtime_error(oss.str());
  }

  // Encontra o servidor conectado, e dependo do tipo do canal, busca se há canal com o mesmo nome, caso não exista insere um novo canal
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == concordoSystem->getCurrentServerName()) {
      Server *server = concordoSystem->getServers().at(i);

      if(strcmp(type, "text") == 0) {
        for (vector<int>::size_type j = 0; j < server->getTextChannels().size(); j++) {
          if (server->getTextChannels().at(j)->getName() == channelName) {
            ostringstream oss;
            oss << "Runtime error: Channel with name '" << server->getName() << "' already exists";
            throw runtime_error(oss.str());
          }
        }

        TextChannel *textChannel = new TextChannel();
        textChannel->setName(channelName);

        server->addTextChannel(textChannel);
      } else {
        for (vector<int>::size_type j = 0; j < server->getVoiceChannels().size(); j++) {
          if (server->getVoiceChannels().at(j)->getName() == channelName) {
            ostringstream oss;
            oss << "Runtime error: Channel with name '" << server->getName() << "' already exists";
            throw runtime_error(oss.str());
          }
        }

        VoiceChannel *voiceChannel = new VoiceChannel();
        voiceChannel->setName(channelName);

        server->addVoiceChannel(voiceChannel);
      }
    }
  }

  cout << "\n::: Created channel '" << channelName << "' of type '" << type << "' :::\n\n";
}

/*
  Entrar em um canal do servidor atualmente conectado
*/
void enterChannel(char *arguments) {
  hasUserLogged();
  hasServerConnected();

  // Valida os campos necessário para entrar no canal
  char *name = strtok(NULL, "");
  validateRequiredField(name, "name");

  bool hasAccessToChannel = false;
  bool channelNotFound = true;

  string channelName = convertCharToString(name);

  // Encontra o servidor conectado, e dependo do tipo do canal, busca se há canal com o mesmo nome, caso não exista insere um novo canal
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == concordoSystem->getCurrentServerName()) {
      Server *server = concordoSystem->getServers().at(i);
    
      for (vector<int>::size_type j = 0; j < server->getTextChannels().size(); j++) {
        if (server->getTextChannels().at(j)->getName() == channelName) {
          channelNotFound = false;
          hasAccessToChannel = true;
          concordoSystem->setCurrentChannelName(channelName);
        }
      }

      for (vector<int>::size_type j = 0; j < server->getVoiceChannels().size(); j++) {
        if (server->getVoiceChannels().at(j)->getName() == channelName) {
          channelNotFound = false;
          hasAccessToChannel = true;
          concordoSystem->setCurrentChannelName(channelName);
        }
      }
    }
  }

  if (channelNotFound) {
    ostringstream oss;
    oss << "Runtime error: Channel '" << channelName << "' not found";
    throw runtime_error(oss.str());
  }

  if (hasAccessToChannel) {
    cout << "\n::: Joined the channel '" << channelName << "' :::\n\n";
  }
}

/*
  Sai do canal atualmente conectado
*/
void leaveChannel() {
  hasUserLogged();
  hasServerConnected();

  if(concordoSystem->getCurrentChannelName() != "") {
    cout << "\n::: Exiting the channel '" << concordoSystem->getCurrentChannelName() << "' :::\n\n";
    concordoSystem->setCurrentChannelName("");
  } else {
    cout << "\n::: You are not viewing any channels :::\n\n";
  }
}

string getDateTimeNow() {
  auto customTime = time(nullptr);
  auto customLocalTime = *localtime(&customTime);
  ostringstream oss;
  
  oss << put_time(&customLocalTime, "%d/%m/%Y %H:%M");
    
  return oss.str();
}

/*
  Envia uma menssagem ao canal atualmente conectado do servidor atualmente conectado
*/
void sendMessage(char *arguments) {
  hasUserLogged();
  hasServerConnected();
  hasChannelConnected();

  // Valida os campos necessário para enviar mensagem ao canal
  char *message = strtok(NULL, "");
  validateRequiredField(message, "message");

  Message *userMessage = new Message();
  User *user = concordoSystem->getUserById(concordoSystem->getUserLoggedId());

  userMessage->setContent(message);
  userMessage->setDateTime(getDateTimeNow());
  userMessage->setSendBy(user->getName());

  // Encontra o canal e o servidor conectado, e dependo do tipo do canal, enviara a mensagem de voz ou texto
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == concordoSystem->getCurrentServerName()) {
      Server *server = concordoSystem->getServers().at(i);
    
      for (vector<int>::size_type j = 0; j < server->getTextChannels().size(); j++) {
        if (server->getTextChannels().at(j)->getName() == concordoSystem->getCurrentChannelName()) {
          server->getTextChannels().at(j)->addMessage(userMessage);
        }
      }

      for (vector<int>::size_type j = 0; j < server->getVoiceChannels().size(); j++) {
        if (server->getVoiceChannels().at(j)->getName() == concordoSystem->getCurrentChannelName()) {
          server->getVoiceChannels().at(j)->setMessage(userMessage);
        }
      }
    }
  }

  cout << "\n::: Message sent on the '" << concordoSystem->getCurrentServerName() << "' server '" << concordoSystem->getCurrentChannelName() << "' channel :::\n\n";
}

/*
  Lista as menssagens do canal atualmente conectado do servidor atualmente conectado
*/
void listMessages() {
  hasUserLogged();
  hasServerConnected();
  hasChannelConnected();

  bool isTextChannel = false;

  // Encontra o canal e o servidor conectado, e dependo do tipo do canal, enviara a mensagem de voz ou texto
  for (vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == concordoSystem->getCurrentServerName()) {
      Server *server = concordoSystem->getServers().at(i);
    
      for (vector<int>::size_type j = 0; j < server->getTextChannels().size(); j++) {
        if (server->getTextChannels().at(j)->getName() == concordoSystem->getCurrentChannelName()) {
          isTextChannel = true;
          TextChannel *textChannel = server->getTextChannels().at(j);
          
          cout << "\n";
          
          for (vector<int>::size_type k = 0; k < textChannel->getMessages().size(); k++) {
            Message *message = textChannel->getMessages().at(k);

            cout << message->getSendBy() << "<" << message->getDateTime() << ">: " << message->getContent() << "\n";
          }

          cout << "\n\n";
        }
      }

      if (isTextChannel == false) {
        for (vector<int>::size_type j = 0; j < server->getVoiceChannels().size(); j++) {
          if (server->getVoiceChannels().at(j)->getName() == concordoSystem->getCurrentChannelName()) {
            VoiceChannel *voiceChannel = server->getVoiceChannels().at(j);
            Message *message = voiceChannel->getMessage();
            
            cout << "\n";
            
            if (message != NULL) {
              cout << message->getSendBy() << "<" << message->getDateTime() << ">: " << message->getContent();
            }

            cout << "\n\n";
          }
        }
      }
    }
  }
}

void listAvailableCommands() {
  cout << "\n:::: Available Commands ::::\n\n";
  cout << "quit                                           Exit the system\n";
  cout << "create-user <email> <password> <name>          Create new user\n";
  cout << "login <email> <password>                       Login user\n";
  cout << "disconnect                                     Disconnects the user\n";
  cout << "create-server <name>                           Create new server\n";
  cout << "set-server-desc <name> <description>           Change server description\n";
  cout << "set-server-invite-code <name> <inviteCode>     Change server invite code, optional inviteCode argument\n";
  cout << "list-servers                                   List all servers\n";
  cout << "enter-server <name> <inviteCode>               Enter in the server, optional inviteCode argument\n";
  cout << "leave-server                                   Exit the currently connected server\n";
  cout << "list-participants                              Lists participants from the currently connected server\n";
  cout << "list-channels                                  Lists the channels available on the currently connected server\n";
  cout << "create-channel                                 Create new channel on the currently connected server\n";
  cout << "enter-channel <name>                           Enter in the channel on the currently connected server\n";
  cout << "leave-channel                                  Exit the currently connected channel on the currently connected server\n";
  cout << "send-message <message>                         Send message to the connected channel\n";
  cout << "list-messages                                  List all messages from the connected channel\n";
  cout << "\n";
}

/*
  Inicializa a escuta dos comandos até que a saída seja interrompida através do comando 'quit'
  Faz a leitura da linha de comando e captura o primeiro argumento, que é separado dos demais argumentos pelo caractere de espaço
  O primeiro argumento significa a operação que se deseja realizar, e os demais argumentos são usados nos respectivos métodos das operações
  Há um controle de exceção que fica a cargo do método interno lançar ou quando o primeiro argumento (operação) não é encontrado nas operações disponíveis
*/
void initializeProgram() {
  char c;
  char commandLine[1000];

  cout << "::::: Welcome to Concordo :::::\n\n";
  cout << ":::: Type 'help' to list the available commands ::::\n\n";

  do {
    scanf("%[^\n]", commandLine);
    while ((c = getchar()) != '\n' && c != EOF) {} // Clear buffer

    char *arguments = strtok(commandLine, " ");

    try {
      if (strcmp(arguments, "login") == 0) {
        login(arguments);
      } else if (strcmp(arguments, "quit") == 0) {
        concordoSystem->clearSystem();
        cout << "\n Bye bye... \n";
        exit(0);
      } else if (strcmp(arguments, "create-user") == 0) {
        createUser(arguments);
      } else if (strcmp(arguments, "disconnect") == 0) {
        disconnect();
      } else if (strcmp(arguments, "create-server") == 0) {
        createServer(arguments);
      } else if (strcmp(arguments, "set-server-desc") == 0) {
        setServerDescription(arguments);
      } else if (strcmp(arguments, "set-server-invite-code") == 0) {
        setServerInviteCode(arguments);
      } else if (strcmp(arguments, "list-servers") == 0) {
        listServers();
      } else if (strcmp(arguments, "enter-server") == 0) {
        enterServer(arguments);
      } else if (strcmp(arguments, "leave-server") == 0) {
        leaveServer();
      } else if (strcmp(arguments, "list-participants") == 0) {
        listParticipants();
      } else if (strcmp(arguments, "list-channels") == 0) {
        listChannels();
      } else if (strcmp(arguments, "create-channel") == 0) {
        createChannel(arguments);
      } else if (strcmp(arguments, "enter-channel") == 0) {
        enterChannel(arguments);
      } else if (strcmp(arguments, "leave-channel") == 0) {
        leaveChannel();
      } else if (strcmp(arguments, "send-message") == 0) {
        sendMessage(arguments);
      } else if (strcmp(arguments, "list-messages") == 0) {
        listMessages();
      } else if (strcmp(arguments, "help") == 0) {
        listAvailableCommands();
      } else {
        throw runtime_error("Runtime error: Command not found");
      }
    } catch (const exception& e) {
      cout << "\n:: " << e.what() << " ::\n\n";
    }
  }
  
  while (true);
}