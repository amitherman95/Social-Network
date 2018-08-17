#ifndef PENDING_H
#define PENDING_H
#include <stdlib.h>
#include <string.h>
#include "definitions_2.h"

void remove_request(Profile ** reqHead, char * user)
{
	
	Profile * helper;

	while(*reqHead!=NULL)
	{
		if(strcmp((*reqHead)->username, user)==0)
		{
			free((*reqHead)->username);
			free((*reqHead)->status);
			free((*reqHead)->friends);
			helper = (*reqHead)->RequestHead;
			free(*reqHead);
			*reqHead = helper;
			break;
		}
		reqHead = &((*reqHead)->RequestHead);
	}

}


void add_request(Profile ** reqHead, char * user)
{
	Profile * helper;

	while(*reqHead!=NULL)
	{
		reqHead = &((*reqHead)->RequestHead);
	}

	helper = (Profile*)malloc(sizeof(Profile));

		if(helper==NULL)
		{
		printf("Error");
		return;
		}


	helper->friends = (char*)malloc(1);

		if(helper->friends==NULL)
		{
		printf("Error");
		return;
		}


	helper->friends[0] = '\0';
	helper->status = (char*)malloc(1);

	if(helper->status==NULL)
		{
		printf("Error");
		return;
		}

	helper->status[0] = '\0';
	helper->RequestHead=NULL;
	helper->username = (char*)malloc(strlen(user)+1);

	if(helper->username==NULL)
		{
		printf("Error");
		return;
		}

	strcpy(helper->username, user);
	*reqHead = helper;

}

void print_requests(Profile *reqHead)
{
	if(reqHead==NULL)
		return;
	else
	{
		printf("-%s\n", reqHead->username);
		print_requests(reqHead->RequestHead);
	}
}

int num_of_nodes(Profile * reqHead)
{
	if(reqHead==NULL)
		return 0;
	return 1 + num_of_nodes(reqHead->RequestHead);
}

int is_user_in_requests(Profile * reqHead, char * user)
{
	if(reqHead==NULL)
		return 0 ;
	if(strcmp(reqHead->username, user)==0)
		return 1;
	return is_user_in_requests(reqHead->RequestHead, user);

}
#endif