#ifndef PROFILES_H
#define PROFILES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions_2.h"

void print_pending(Profile * reqHead)//belong to pending
{

	if (reqHead == NULL)
	return;

	else
	{
		printf("%s\n", reqHead->username);
		print_pending(reqHead->RequestHead);
	}

}



Profile * find_profile(char * username, Profile ** prof_Array,int arr_len)
{
int i;

for(i=0;i<arr_len;i++)
{
	if(strcmp(prof_Array[i]->username, username)==0)
		return prof_Array[i];

}
return NULL;
}


int  find_profile_index(char * username, Profile ** prof_Array,int arr_len)
{
int i;

for(i=0;i<arr_len;i++)
{
	if(strcmp(prof_Array[i]->username, username)==0)
		return i;

}
return -1;
}



Profile * new_profile(char * username)
{
	Profile * new_p;

	new_p = (Profile*)malloc(sizeof(Profile));

		if(new_p==NULL)
		{
		printf("Error");
		return;
		}



	new_p->username = (char*)malloc(strlen(username)+1);

	if(new_p->username==NULL)
		{
		printf("Error");
		return;
		}

	strcpy(new_p->username, username);
	new_p->friends=(char*)malloc(1);

	if(new_p->friends==NULL)
		{
		printf("Error");
		return;
		}


	new_p->friends[0] = '\0';
	new_p->RequestHead = NULL;
	new_p->status=(char*)malloc(1);

	if(new_p->status==NULL)
		{
		printf("Error");
		return;
		}


	new_p->status[0] = '\0';
	 return new_p;
}

void add_profile(Profile* new_p, Profile *** Array, int*arr_len)
{
	if (new_p==NULL)
		return;

	*arr_len = *arr_len + 1 ;
	*Array = (Profile**)realloc(*Array, (*arr_len)*sizeof(Profile*));


	*((*Array)+*arr_len-1) = new_p;

}

#endif