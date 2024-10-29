package main

import (
	"context"
	// "io"
	"log"
	"net"

	"google.golang.org/grpc"
	// "google.golang.org/grpc/credentials"
	// "google.golang.org/grpc/examples/data"
	// "google.golang.org/protobuf/proto"

	// pb "calcula"
	pb "leomichalski.xyz/labrpc/src/operandos"
)

type operandosServiceServer struct {
	pb.UnimplementedOperandosServiceServer
}

func (svc operandosServiceServer) Add(ctx context.Context, operandos *pb.Operandos) (*pb.OperandosResultado, error) {
	var resultado = new(pb.OperandosResultado)
	resultado.Resultado = operandos.GetX() + operandos.GetY()
	return resultado, nil
}

func newServiceServer() *operandosServiceServer {
	return &operandosServiceServer{}
}

func main() {
	// Iniciar socket anunciando uma porta num IP
	lis, err := net.Listen("tcp", "localhost:50051")
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	// 
	// var opts []grpc.ServerOption
	// grpcServer := grpc.NewServer(opts...)
	grpcServer := grpc.NewServer()

	// Registrar service servers
	pb.RegisterOperandosServiceServer(grpcServer, newServiceServer())

	grpcServer.Serve(lis)
}
