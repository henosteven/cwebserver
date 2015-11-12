#ifndef _LIST_H
#define _LIST_H

typedef struct node {
	char *key;
	char *val;
	struct node *next;
} node;

typedef struct linkList {
	node *head;
	int linkLen;
} linkList;

void showAllLinkList(linkList const *linkList);
int getLinkLinkLen(linkList const *linkList);

#endif
