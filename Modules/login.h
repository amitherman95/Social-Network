#ifndef LOGIN
#define LOGIN


#include "definitions.h"
#include <string.h>
#include "read_files.h"
#include "encoding.h"

char * separation(char * string)
{
	char * helper;
	helper = strstr( string, "::");
		if (helper ==NULL)
		{
			return NULL;
		}
		return helper;
}


Account * find_username( char * user, Account * head)
	//Found-return account*
	//Not found-return NULL
{
	if (head==NULL)
		return NULL;
	if(strcmp(head->Username, user)==0)//Is it right?
		return head;
	else
		find_username(user, head->next);
}

int compare_password(Account * node, char * pass)
{
	return node->enc_Pass == encryption(pass, node->randomNum);
}
#endif