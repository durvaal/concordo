#include <stdio.h>
#include <stdexcept>
#include <sstream>
#include <string.h>
#include <iostream>
#include "./headers/system_class.h"
#include "./headers/user_class.h"
#include "./headers/methods.h"

class System *concordoSystem = new System();
int currentUserId = 0;

void validateRequiredField(char *field, std::string fieldName) {
  if (field == NULL) {
    std::ostringstream oss;
    oss << "Runtime error: The field '" << fieldName << "' has required";
    throw std::runtime_error(oss.str());
  }
}

std::string convertCharToString(char *field) {
  std::string fieldValueConverted;
  fieldValueConverted = field;
  return fieldValueConverted;
}

void hasUserLogged() {
  if (concordoSystem->getUserLoggedId() == 0) {
    std::ostringstream oss;
    oss << "Runtime error: Access denied, you must be logged, try execute command 'login <userEmail> <userPassword>";
    throw std::runtime_error(oss.str());
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

  class User *user = new User();

  user->setEmail(convertCharToString(email));
  user->setPassword(convertCharToString(password));
  user->setName(convertCharToString(name));

  // Verifica na lista de usuários criados se existe um usuário com o email informado
  for (std::vector<int>::size_type i = 0; i < concordoSystem->getUsers().size(); i++) {
    if (concordoSystem->getUsers().at(i)->getEmail() == user->getEmail()) {
      std::ostringstream oss;
      oss << "Runtime error: User with email '" << user->getEmail() << "' already exists";
      throw std::runtime_error(oss.str());
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

  class User *user = new User();

  user->setEmail(convertCharToString(email));
  user->setPassword(convertCharToString(password));

  // A cada novo login reseta o id do usuario logado
  concordoSystem->setUserLoggedId(0);

  // Verifica se há um usuário com o mesmo email e senha
  for (std::vector<int>::size_type i = 0; i < concordoSystem->getUsers().size(); i++) {
    if (concordoSystem->getUsers().at(i)->getEmail() == user->getEmail()
    && concordoSystem->getUsers().at(i)->getPassword() == user->getPassword()) {
      concordoSystem->setUserLoggedId(concordoSystem->getUsers().at(i)->getId());
      break;
    }
  }

  if (concordoSystem->getUserLoggedId() == 0) {
    std::ostringstream oss;
    oss << "Runtime error: Invalid email or password";
    throw std::runtime_error(oss.str());
  } else {
    std::cout << "\n::: Logged is as " << user->getEmail() << " :::\n\n"; 
  }
}

/*
  Caso haja id de usuário logado, busca-se a informação do usuário na lista de usuário do sistema através do id, para informar que este está sendo deslogado.
*/
void disconnect() {
  hasUserLogged();

  // Verifica se há um usuário com id do usuario logado
  for (std::vector<int>::size_type i = 0; i < concordoSystem->getUsers().size(); i++) {
    if (concordoSystem->getUsers().at(i)->getId() == concordoSystem->getUserLoggedId()) {
      concordoSystem->setUserLoggedId(0);
      std::cout << "\n::: Disconnecting user " << concordoSystem->getUsers().at(i)->getEmail() << " :::\n\n"; 
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

  class Server *server = new Server();

  server->setName(convertCharToString(name));
  server->setOwnerUserId(concordoSystem->getUserLoggedId());

  // Verifica na lista de servidores criados se existe um servidor com o nome informado
  for (std::vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == server->getName()) {
      std::ostringstream oss;
      oss << "Runtime error: Server with name '" << server->getName() << "' already exists";
      throw std::runtime_error(oss.str());
    }
  }

  concordoSystem->addServer(server);

  cout << "\n::: Created server :::\n\n";
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
  class Server *server = new Server();

  server->setName(convertCharToString(serverName));
  server->setDescription(convertCharToString(description));

  // Verifica na lista de servidores criados se existe um servidor com o nome informado e com o usuario logado como proprietário
  for (std::vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == server->getName()) {
      if (concordoSystem->getServers().at(i)->getOwnerUserId() == concordoSystem->getUserLoggedId()) {
        updatedDescription = true;
        concordoSystem->getServers().at(i)->setDescription(server->getDescription());
      } else {
        std::ostringstream oss;
        oss << "Runtime error: You cannot change the description of a server that has not been created by you";
        throw std::runtime_error(oss.str());
      }
    }
  }

  if (updatedDescription) {
    cout << "\n::: Modified '" << server->getName() << "' server description! :::\n\n";
  } else {
    std::ostringstream oss;
    oss << "Runtime error: '" << server->getName() << "' server doesn’t exist";
    throw std::runtime_error(oss.str());
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
  class Server *server = new Server();

  server->setName(convertCharToString(serverName));
  if (inviteCode == NULL) {
    server->setInviteCode("");
  } else {
    server->setInviteCode(convertCharToString(inviteCode));
  }

  // Verifica na lista de servidores criados se existe um servidor com o nome informado e com o usuario logado como proprietário
  for (std::vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    if (concordoSystem->getServers().at(i)->getName() == server->getName()) {
      if (concordoSystem->getServers().at(i)->getOwnerUserId() == concordoSystem->getUserLoggedId()) {
        updatedInviteCode = true;
        concordoSystem->getServers().at(i)->setInviteCode(server->getInviteCode());
      } else {
        std::ostringstream oss;
        oss << "Runtime error: You cannot change the invite code of a server that has not been created by you";
        throw std::runtime_error(oss.str());
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
    std::ostringstream oss;
    oss << "Runtime error: '" << server->getName() << "' server doesn’t exist";
    throw std::runtime_error(oss.str());
  }
}

/*
  Lista os servidores cadastrados
*/
void listServers() {
  hasUserLogged();

  for (std::vector<int>::size_type i = 0; i < concordoSystem->getServers().size(); i++) {
    cout << "\n::: Server Name: " << concordoSystem->getServers().at(i)->getName();
    cout << "\n::: Description: " << concordoSystem->getServers().at(i)->getDescription();
    cout << "\n::: Invite Code: " << concordoSystem->getServers().at(i)->getInviteCode();
    cout << "\n";
  }
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

  do {
    scanf("%[^\n]", commandLine);
    while ((c = getchar()) != '\n' && c != EOF) {} // Clear buffer

    char *arguments = strtok(commandLine, " ");

    try {
      if (strcmp(arguments, "login") == 0) {
        login(arguments);
      } else if (strcmp(arguments, "quit") == 0) {
        cout << "Bye bye... \n";
        free(concordoSystem);
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
      } else {
        throw std::runtime_error("Runtime error: Command not found");
      }
    } catch (const std::exception& e) {
      std::cout << "\n:: " << e.what() << " ::\n\n";
    }
  }
  
  while (true);
}