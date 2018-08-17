#ifndef FRIENDS_H
#define FRIENDS_H
#include <string.h>
#include "new_acc.h"
#include <stdlib.h>

int is_in_friend(char * user, char * friends)
{
	int i, k, len, Flag, outcome;
	char helper[51];

	len=strlen(friends);
	Flag = 0;//1 means done

	outcome = 0;
	i=0;
	k=0;
	while(i<=len && !Flag)
	{
		if (friends[i]=='\0')
		{
			helper[k]='\0';
			if(strcmp(helper, user)==0)
			{
				outcome=1;
				Flag = 1;
			}
				
		}

		else if(friends[i]==';')
		{
		
			helper[k]='\0';
			if(strcmp(helper, user)==0)
			{
				outcome=1;
				Flag = 1;
			}
				
			k=0;
		}
		
		else
		{
			helper[k]=friends[i];
			k++;
		}


	i++;

	}
	return outcome;

}

void remove_friend(char *user, char**friends)
{
	char * helper;
	char* holder;
	int length, i, k;

	helper = strstr(*friends, user);
	holder = *friends;
	k=0;
	length = strlen(user);
	for(i=0; i<length; i++)
	{
		helper[i] = '0';
		k++;
	}

	if(helper[i]==';')
	{
		helper[i] = '0';
		k++;
	}
	else if(&(helper[i-k-1])>=holder)
	{
		helper[i-k-1]='0';
		k++;
	}

	*friends = (char*)malloc(strlen(holder)+1-k);

	if(*friends==NULL)
		{
		printf("Error");
		return;
		}


	length = strlen(holder);

	k=0;
	for(i=0; i<=length; i++)
	{
		if(holder[i]!='0')
		{
			(*friends)[k] = holder[i];
			k++;
		}
	}
	
	free(holder);


}

void add_friend(char *user, char**friends)


{
	if(*friends[0] == '\0')//if list is empty
	{
		*friends = (char*)realloc(*friends, strlen(*friends)+strlen(user)+1);

		strcat(*friends, user);
	}

	else
	{
	*friends = (char*)realloc(*friends, strlen(*friends)+strlen(user)+2);
	strcat(*friends, ";");
	strcat(*friends, user);
	}

}



#endif