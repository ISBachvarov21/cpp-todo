#include "endpoints.hpp"

int main(int argc, char** argv) {
	CppHttp::Net::Router router;
	CppHttp::Net::TcpListener server;
	server.CreateSocket();

	int requestCount = 0;

	auto onReceive = [&](CppHttp::Net::Request req) {
		router.Handle(req);
	};

	server.SetOnReceive(onReceive);

	router.AddRoute("GET",    "/", 	     Index);
	router.AddRoute("GET", "/todos", GetTodos);
	router.AddRoute("POST",   "/add",    AddTodo);
	router.AddRoute("DELETE", "/remove", RemoveTodo);

	server.Listen("0.0.0.0", 80, std::thread::hardware_concurrency());
}