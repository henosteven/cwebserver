#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "list.h"
#include "request.h"

/* 获取post提交的数据 */
linkList *getPostParams(char buf[], int len)
{

}

requestInfo *getRequestInfo(char buf[])
{
	requestInfo *hRequestInfo;
	hRequestInfo = malloc(sizeof(requestInfo));
	
	int requestLen = strlen(buf);

	/* 获取action */
	char *action;
	char *tmpAction;
	action = malloc(sizeof(char) * 4);
	tmpAction = action;

	/* 获取请求的URL */
	char *file;
	char *tmpFile;
	file = malloc(sizeof(char) * 20);
	tmpFile = file;

	int i;
	int space = 0;
	for (i = 0; i < requestLen; i++) {
		
		if (buf[i] == ' ') {
			space++;
		}

		if (space == 0) {
			*action++ = buf[i];
		}

		if (space == 1 && buf[i] != ' ') {
			*file++ = buf[i];
		}
	}
	*action = '\0';
	*file = '\0';
	
	hRequestInfo->method = malloc(sizeof(char) * 4);
	hRequestInfo->file = malloc(sizeof(char) * 20);
	hRequestInfo->method = tmpAction;
	hRequestInfo->file = tmpFile;
	//if (strcmp(hRequestInfo->file, "/") == 0) {
		hRequestInfo->file = "/index.html";
	//} 
	hRequestInfo->paramsList = getGetParams(tmpFile, strlen(tmpFile));
	return hRequestInfo;
}

void showRequestInfo(requestInfo *requestInfo)
{
	printf("request action: %s\n", requestInfo->method);
	printf("request file: %s\n", requestInfo->file);

	node *psNode;
	psNode = requestInfo->paramsList->head;
	int paramsCount = requestInfo->paramsList->linkLen;
	if (paramsCount > 0) {
		printf("request params:");
		int i = 0;
		for (i; i < paramsCount; i++) {
			printf("\t%s\t%s\n", psNode->key, psNode->val);
			psNode = psNode->next;
		}
	}
}

/* 获取get提交的数据 */
linkList *getGetParams(char buf[], int len)
{
	linkList *linkList;
	linkList = malloc(sizeof(linkList));
	int i = 0;
	node *node;
	node = malloc(sizeof(node));
	node->key = malloc(sizeof(char) * 20);
	node->val = malloc(sizeof(char) * 20);

	linkList->head = node;
	linkList->linkLen = 0;

	int meetWhy = 0;
	int meetEq = 0;
	int meetAnd = 0;

	int tmpKeyLen = 0;
	int tmpValLen = 0;
	int moreThanOne = 0;
	for (i; i < len; i++) {
		
		if (buf[i] == '?') {
			meetWhy = 1;
			continue;		
		}	

		if (!meetWhy) {
			continue;		
		}
		
		if (buf[i] == '=') {
			meetEq = 1;
			continue;		
		}

		if (buf[i] == '&') {
			meetAnd=  1;
		}

		if (!meetEq) {
			*node->key++ = buf[i];
			tmpKeyLen++;
		} else {
			if (!meetAnd) {
				*node->val++ = buf[i];
				tmpValLen++;
				moreThanOne = 1;

				if (i == (len - 1)) {
					*node->key = '\0';
					*node->val = '\0';
					node->key = node->key - tmpKeyLen;
					node->val = node->val - tmpValLen;
				}

			} else {
				meetEq = 0;
				meetAnd = 0;
				*node->key = '\0';
				*node->val = '\0';
				node->key = node->key - tmpKeyLen;
				node->val = node->val - tmpValLen;

				struct node *newNode;
				newNode = malloc(sizeof(struct node));
				newNode->key = malloc(sizeof(char) * 20);
				newNode->val = malloc(sizeof(char) * 20);
				newNode->next = NULL;
				node->next = newNode;

				node = newNode;
				linkList->linkLen += 1;
				tmpKeyLen = 0;
				tmpValLen = 0;
			}
		}
		
	}

	/* 补齐最后一项 */
	if (moreThanOne == 1) {
		linkList->linkLen += 1;
	}
	return linkList;
}


