// sockets_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <WinSock2.h>
#include <inaddr.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


int main()
{
	int ret = 0;
	WSADATA wsa; //전화 선을 만들어 주기 위한 데이터 타입
	SOCKET sid; //집에 전화기를 여러 개 놓을 수 있다고 가정하고, 전화 선 마다 port 이름을 붙여주는 것이 sid

	ret = WSAStartup(MAKEWORD(2, 2), &wsa); //이정도의 전류가 들어왔으면 좋겠어
	//사용하려는 애에게 규격을 부여해준다.

	if (0 != ret) {
		printf("WSAStartup Error \n");
		return -1;
	}
	//집에 전화 설치하고 식별자를 부여
	sid = socket(AF_INET, SOCK_STREAM, 0);
	//sock_Stream : TCP 를 쓰겠다.

	if (INVALID_SOCKET == sid) {
		printf("socket() Error \n");
		return -1;
	}

	//address 집합의 구조체 , 주소들을 만들어 주기 위한 변수들이 집합되어 있다.
	SOCKADDR_IN saddr;
	in_addr addr; 


	memset(&saddr, 0x00, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(2019);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(sid, (SOCKADDR*)&saddr, sizeof(saddr)); 

	if (SOCKET_ERROR == ret) {
		printf("connect() Error! \n");
		return -1; 
	}
	else {
		printf("You are now connected with a contender! \n");
	}

	char send_data[128];
	char recv_data[128];

	while (1) {
		memset(send_data, 0x00, sizeof(send_data));
		memset(recv_data, 0x00, sizeof(recv_data));
		//데이터 보내는 애와 받는 애 주소 할당 
		
		printf("recv : ");
		recv(sid, recv_data, sizeof(recv_data), 0); //클라이언트는 receive 를 먼저 함 
		printf("%s", recv_data);

		printf("prompt > ");

		fgets(send_data, sizeof(send_data), stdin);

		send(sid, send_data, sizeof(send_data), 0); 
	}

	closesocket(sid);
	WSACleanup(); 

	return 0; 
}
