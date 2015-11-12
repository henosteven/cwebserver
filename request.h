#ifndef _REQUEST_H
#define _REQUEST_H

typedef struct requestInfo {
	char *method;
	char *file;
	linkList *paramsList;
} requestInfo;


requestInfo *getRequestInfo(char buf[]);
linkList *getGetParams(char buf[], int len);
linkList *getPostParams(char buf[], int len);

#endif 
