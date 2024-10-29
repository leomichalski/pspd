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

### Clonar o repositório e ir para esta pasta

```bash
git clone https://github.com/leomichalski/pspd.git
cd pspd/grpc
```

### Iniciar workspace

```bash
go work init ./
```

### Compilar servidor e cliente

```bash
GO111MODULE=auto go build -o server server/server.go
GO111MODULE=auto go build -o client client/client.go
```

### Executar binário do servidor

```bash
./server/server
```

### Executar binário do cliente

```bash
./client/client
```

## Informações úteis

### Como compilar arquivos protobuf

```bash
protoc --go_out=./ --go_opt=paths=source_relative \
       --go-grpc_out=./ --go-grpc_opt=paths=source_relative \
       ./operandos/operandos.proto
```

### Como gerar go.mod e go.sum

```bash
go mod init github.com/leomichalski/pspd/grpc
go mod tidy
```
