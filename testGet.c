#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"


typedef struct news {
	char *name;
	char *age;
} news;

main()
{
	
	news *news;
	news = malloc(sizeof(news));
//	news->name = malloc(sizeof(char) * 100);
//	news->age = malloc(sizeof(char) * 100);
	news->name = "henosteven";
	news->age = "26";
	news->name += 2;
	news->name -= 2;
//	printf("%s - %s\n", news->name, news->age);

	char buf[] = "/index.html?name=jinjing&age=26";
	linkList *linkList;
	linkList = malloc(sizeof(linkList));
	linkList = getGetParams(buf, strlen(buf));
	showAllLinkList(linkList);
}
