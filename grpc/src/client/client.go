package main

import (
	"context"
	"time"
	"log"

	"google.golang.org/grpc"
	// "google.golang.org/grpc/credentials"
	"google.golang.org/grpc/credentials/insecure"

	pb "leomichalski.xyz/labrpc/src/operandos"
)

func main() {
	resultado := new(pb.OperandosResultado);

	// Conexao com o servidor
	var opts []grpc.DialOption
	opts = append(opts, grpc.WithTransportCredentials(insecure.NewCredentials()))
	conn, err := grpc.NewClient("localhost:50051", opts...)
	if err != nil {
		log.Fatalf("deu ruim: %v", err)
	}
	defer conn.Close()

	// Criar service client
	operandosServiceClient := pb.NewOperandosServiceClient(conn)

	// Fazer algo
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()
	resultado, err = operandosServiceClient.Add(ctx, &pb.Operandos{X: 100, Y: 2})
	if err != nil {
		log.Fatalf("operandosServiceClient.Add falhou: %v", err)
	}
	log.Println(resultado)
}
