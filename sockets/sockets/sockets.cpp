#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <WinSock2.h>
#include <inaddr.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main(int argc, char * argv[]) {

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
	memset(&saddr, 0x00, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(2019);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(sid, (SOCKADDR*)&saddr, sizeof(saddr));
	//전화 선과 전화선을 묶는 작업

	if (SOCKET_ERROR == ret) {
		printf("bind() Error! \n");
		return -1;
	}

	//전화가 오기를 기다리는 상태 , 소켓 연결 개수를 최대한 많이 주겠다. Socket max connection
	ret = listen(sid, SOMAXCONN);

	if (SOCKET_ERROR == ret) {
		printf("listen() Error! \n");
		return -1;
	}

	printf("Waiting for a contender...\n");

	SOCKET cid; 
	SOCKADDR_IN caddr; 

	int len = sizeof(caddr); 
	char send_data[128]; 
	char recv_data[128];

	cid = accept(sid, (SOCKADDR*)&caddr, &len);
	//나에게 전화를 건 애를 허용해서 붙여주겠다는 뜻 

	if (INVALID_SOCKET == cid) {
		printf("accept() Error \n");
		return -1; 
	}
	else {
		printf("You are now connected with a contender !");
	}

	while (1) {
		memset(send_data, 0x00, sizeof(send_data));
		memset(recv_data, 0x00, sizeof(recv_data));
		//데이터 보내는 애와 받는 애 주소 할당 

		printf("prompt > ");
		fgets(send_data, sizeof(send_data), stdin);

		send(cid, send_data, sizeof(send_data), 0);
		printf("recv : ");
		recv(cid, recv_data, sizeof(recv_data), 0);
		printf("%s", recv_data);
	}

	return 0;
}