// winsock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void client() {
	SOCKET sock_out = INVALID_SOCKET;

	sock_out = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in sname;
	sname.sin_family = AF_INET;
	sname.sin_port = 6239;

	unsigned long my_addr = inet_addr("10.63.25.39");
	sname.sin_addr.S_un.S_addr = my_addr;

	if(connect(sock_out, (const sockaddr *)&sname, sizeof(sname))) {
		std::cout << "Connect failed on client. Error: " << WSAGetLastError() << std::endl;
		return;
	} else {
		std::cout << "Connect succeeded on client" << std::endl;
	}
	char* msg = "I am client, how are you, server?";
	send(sock_out, "I am client, how are you, server?", strlen(msg), 0);

	Sleep(5000);
	closesocket(sock_out);
}

void server() {
	SOCKET sock_listen = INVALID_SOCKET;
	SOCKET sock_in = INVALID_SOCKET;

	sock_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock_listen == INVALID_SOCKET) {
		std::cout << "Invalid socket on server. Error: " << WSAGetLastError() << std::endl;
		return;
	}

	struct sockaddr_in sname;
	sname.sin_family = AF_INET;
	sname.sin_port = 6239;

	unsigned long my_addr = inet_addr("10.63.25.39");
	sname.sin_addr.S_un.S_addr = my_addr;

	if(bind(sock_listen, (const sockaddr *)&sname, sizeof(sname))) {
		std::cout << "Bind failed on server. Error: " << WSAGetLastError() << std::endl;
		return;
	}
	if(listen(sock_listen, 1)) {
		std::cout << "Listen failed on server. Error: " << WSAGetLastError() << std::endl;
		return;
	}

	sock_in = accept(sock_listen, 0, 0);
	if(sock_in == INVALID_SOCKET) {
		std::cout << "Accept connection failed on server. Error: " << WSAGetLastError() << std::endl;
		return;
	} else {
		std::cout << "Accepted connection on server" << std::endl;
	}

	char buf[128];
	int numBytes = recv(sock_in, buf, 128, 0);

	if(numBytes <= 0) {
		std::cout << "Receive failed on server. Error: " << WSAGetLastError() << std::endl;
		return;
	}

	buf[numBytes] = '\0';
	std::cout << "Received the following on server:" << std::endl;
	std::cout << buf << std::endl;

	Sleep(5000);
	closesocket(sock_in);
	closesocket(sock_listen);
}

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1,0);

	int err = WSAStartup(wVersionRequested, &wsaData);
	if(err) {
		std::cout << "Winsock startup failed. Error: " << err << std::endl;
		return 1;
	}

	if(argc > 1) {
		server();
	} else {
		client();
	}

	WSACleanup();
	return 0;
}

