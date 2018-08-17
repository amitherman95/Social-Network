#ifndef DEF_H
#define DEF_H
#include <stdio.h>


typedef struct acc {
	char Username[51];
	int enc_Pass;
	int randomNum;
	char answer[200];
	struct acc * next;
} Account;


#endif
