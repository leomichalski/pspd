# gRPC lab

gRPC: Google Remote Procedure Call

## Configuração e execução

É necessário ter Go instalado.

### Instalar compilador de protobufs

```bash
sudo apt install protobuf-compiler
```

Mais opções de instalação em: https://grpc.io/docs/protoc-installation/

### Instalar plugins para o compilador de protobuf

```bash
go install google.golang.org/protobuf/cmd/protoc-gen-go@latest
go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@latest
```

### Iniciar workspace

```bash
go work init ./
```

### Compilar servidor e cliente

```bash
GO111MODULE=auto go build -o server src/server/server.go
GO111MODULE=auto go build -o client src/client/client.go
```

### Executar binário do servidor

```bash
./server
```

### Executar binário do cliente

```bash
./client
```

## Informações úteis

### Como compilar arquivos protobuf

```bash
protoc --go_out=./ --go_opt=paths=source_relative \
       --go-grpc_out=./ --go-grpc_opt=paths=source_relative \
       ./src/operandos/operandos.proto
```

### Como gerar go.mod e go.sum

```bash
go mod init leomichalski.xyz/labrpc
go mod tidy
```
