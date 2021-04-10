# Concordo
Clone do Discord, para humanos mais civilizados.

## Integrante ✨

**20190104147 - PAULO DE L. XAVIER**

## Como compilar o programa

```
make
```

## Como executar o programa

```
./concordo
```

## Métodos suportadas

### Sair do sistema

```
quit
```

### Criar usuário

```
create-user <email> <senha> <nome>
```

### Login

```
login <email> <senha>
```

### Desconectar usuário

```
disconnect
```

### Criação de servidor

```
create-server <nome>
```

### Mudar descrição do servidor

```
set-server-desc <nome> <descricao>
```

### Manipular código de convite do servidor

```
set-server-invite-code <nome> <codigo-de-convite>
```
> Código de convite opcional.

### Listar servidores

```
list-servers
```

### Entrar em um servidor

```
enter-server <nome> <codigo-de-convite>
```
> Código de convite opcional.

### Sair do servidor atualmente conectado

```
leave-server
```

### Listar os participatentes do servidor atualmente conectado
```
list-participants
```

### Listar canais disponíveis
```
list-channels
```

### Criar canal
```
create-channel <nome> <tipo>
```
> O tipo deve ser `text` ou `voice`

### Entrar em um canal no servidor atualmente conectado
```
enter-channel <nome>
```

### Sair de um canal no servidor atualmente conectado
```
leave-channel
```

## WIP

Algumas funcionalidades requeridas não foram implementadas do item 2.7 em diante.