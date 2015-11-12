#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include "server.h"
#include "websignal.h"
#include "list.h"
#include "request.h"


main() {
	int sockfd, newfd;
	struct sockaddr_in s_addr, c_addr; 
	socklen_t len;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	
	if (sockfd < 0) {
		printf("create socket error\n");
		exit(0);
	}

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);
	s_addr.sin_addr.s_addr = INADDR_ANY;

	int bindResult;
	bindResult = bind(sockfd, (struct sockaddr*) & s_addr, sizeof(struct sockaddr));
	if (bindResult == -1) {
		printf("bind PORT error");
		exit(0);
	}

	listen(sockfd, LISTNUM);
	
	signal(SIGHUP, signalHandler);
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);

	while(1) {
		printf("开始聊天\n");
		len = sizeof(struct sockaddr);
		newfd = accept(sockfd, (struct sockaddr*) & c_addr, &len);
		printf("正在跟你聊天的机器是%s-%d", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));

		char tmpbuf[40000];
		len = recv(newfd, tmpbuf, 40000, 0);
		printf("接收到客户端的消息：%s,共有字节数是: %d\n", tmpbuf, len);


		requestInfo *hRequestInfo;
		hRequestInfo = malloc(sizeof(requestInfo));
		hRequestInfo = getRequestInfo(tmpbuf);
		showRequestInfo(hRequestInfo);
		
		/* 返回数据给客户端 */
		httpResponse(newfd, hRequestInfo);
		
	//	shutdown(newfd, SHUT_RDWR);
		close(newfd);	
	}

}
