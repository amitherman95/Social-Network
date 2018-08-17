#ifndef STATUS_H
#define STATUS_H

#include <stdio.h>
#include <string.h>
#include "profiles.h"

void print_friends_status(Profile ** prof_Array, Profile * user, int arr_len)
{
char helper[51];
int i, length, k;
Profile * friend_prof;

length = strlen(user->friends);
k=0;
for(i=0; i<=length; i++)
{
	if((user->friends)[i]=='\0')
	{
		helper[k] = '\0';
		friend_prof = find_profile(helper, prof_Array, arr_len);
			if(friend_prof!=NULL)
				printf("-%s Status:%s\n", friend_prof->username, friend_prof->status);
	}
	else if((user->friends)[i]==';')
	{
		helper[k] = '\0';
		friend_prof = find_profile(helper, prof_Array, arr_len);
		if(friend_prof!=NULL)
				printf("-%s Status:%s\n", friend_prof->username, friend_prof->status);
		k=0;
	}

	else
	{
		helper[k] = user->friends[i];
		k++;
	}

	
	}
}

void change_status(char * new_status, Profile * User)
{
	int length;
	length = strlen(new_status);
	free(User->status);
	User->status = (char*)malloc(length+1);

	if(User->status==NULL)
		{
		printf("Error");
		return;
		}

	strcpy(User->status, new_status);
}






#endif