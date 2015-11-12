#include <stdio.h>
#include <malloc.h>
#include "string.h"
#include "list.h"
#include "request.h"
#include "server.h"

void httpResponse(int acceptSock, requestInfo *hRequestInfo)
{
	int len;
	FILE *fp;
	char buf[BUFLEN] = "HTTP/1.1 200 OK\r\nConent-Type: text/html; charset=utf-8\r\nServer: Python-slp version 1.0\r\nConent-Length: %d\r\n\r\n%s\r\n\r\n";


	char *filePath;
	filePath = malloc(sizeof(char) * 100);
	strcat(filePath, WEBROOTDIR);
	strcat(filePath, hRequestInfo->file);

	char fbuf[1000] = "default";
	if ((fp = fopen(filePath, "r")) != NULL) {
		while(!feof(fp)) {
			fgets(fbuf, 1000, fp);
		}
		fclose(fp);
	} else {
		printf("failed to open the file: %s\n", hRequestInfo->file);
	}

	char output[2000];
	sprintf(output, buf, strlen(fbuf), fbuf);

	len = send(acceptSock, output, strlen(output), 0);

	if (len > 0) {
		printf("response to client success\n");
	} else {
		printf("response to client failed\n");
	}
}


