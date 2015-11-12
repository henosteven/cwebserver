#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "list.h"

void showAllLinkList(linkList const *linkList)
{
	if (linkList->linkLen == 0) {
		return ;
	}

	node *head;

	head = linkList->head;

	int i = 0;
	for (i; i < linkList->linkLen; i++) {
		printf("key:%s--val:%s\n", head->key, head->val);
		head = head->next;
	}
}

int getLinkLinkLen(linkList const *linkList)
{
	return linkList->linkLen;
}


