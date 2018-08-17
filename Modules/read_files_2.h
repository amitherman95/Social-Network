#ifndef READ_FILES_2
#define READ_FILES_2


#include <stdio.h>
#include <stdlib.h>
#include "definitions_2.h"

char * ReadLine_2(FILE * fp)
{
	int i;
	char * string;
	char chr;

	string = (char*)malloc(sizeof(char));

	if(string==NULL)
	{
		printf("Error allocating");
		return NULL;
	}

	string[0] = '\0';
	chr = fgetc(fp);
	i=0;
	while(chr!=EOF && chr!='\n')
	{
		string[i] = chr;
		i++;
		string = (char*)realloc(string, i+1*(sizeof(char)));
		string[i] = '\0';
		chr = fgetc(fp);
	}
	return string;
}
	
int find_sep(char * chr)
	//return 1 if there is a separation;
{
	if(*chr== '_' && *(chr+1)=='$' && *(chr+2)=='_')
		return 1;
	else
		return 0;
	}


Profile * create_pending(char * line)
{
	Profile * temp;
	int i, len;

	if(line[0]=='\0')
		return NULL;
	temp  = (Profile*)malloc(sizeof(Profile));

		if(temp==NULL)
		{
		printf("Error");
		return NULL;
		}

	len  = strlen(line);
	i=0;
	
	temp->username=NULL;
	for(i=0; i<=len; i++)
	{

		temp->username = (char*)realloc(temp->username, i+1);

		if(line[i]=='\0')
		{
			temp->username[i] = '\0';
			temp->RequestHead = NULL;
			break;
		}



		else if(find_sep(line+i))
		{
			temp->username[i] = '\0';
			temp->RequestHead = create_pending(line+ +i+ 3);
			break;
		}

	

		temp->username[i] = line[i];

	}
	temp->friends=NULL;
	temp->status  =NULL;
	return temp;
}


char * create_friends(char *line)

{
	char * helper=NULL;
	int length, i, k;
	length = strlen(line);

	i=0;
	k=0;
	while(i<=length)
	{


		 if(line[i]=='\0')
		{
			helper  = (char*)realloc(helper, k+1);
			helper[k] = '\0';
			i++;
			
		}

		else if(find_sep(line+i))
		{
			helper  = (char*)realloc(helper, k+1);
			helper[k] = ';';
			i = i+3;
		}

	
		
		else
		{
			helper  = (char*)realloc(helper, k+1);
			helper[k] = line[i];
			i++;
		}

		k++;
	}

	return helper;


	}

Profile * create_profile(FILE * fp)
{
	char * username_l, *username;
		char* status_l, *status;
		char* new_f;
		char * new_p;
		Profile * new_a;
		new_a = (Profile*)malloc(sizeof(Profile));


		username_l = ReadLine_2(fp);
		status_l = ReadLine_2(fp);
		new_f  =ReadLine_2(fp);
		new_p = ReadLine_2(fp);

		if(strstr(username_l,"Username_")==username_l)
	
		{
			username = (char*)malloc(strlen(username_l+9)+1);


			strcpy(username, username_l+9);//
			new_a->username  = username;
		}
		else
			goto Error;

		if(strstr(status_l,"Status_")==status_l)
		
		{
			status= (char*)malloc(strlen(status_l+7)+1);
			strcpy(status, status_l+7);//
			new_a->status  = status;
		}
		else
			goto Error;
		
		if(strstr(new_f,"Friends_")==new_f)
		{
		new_a->friends = create_friends(new_f+8);
		}
		else
			goto Error;
		if(strstr(new_p,"Pendings_")==new_p)
		new_a->RequestHead = create_pending(new_p+9);
		else
			goto Error;


	 free(username_l);
		free(status_l);
		free(new_f);
		free(new_p);


	return new_a;

	Error: free(username_l);
		free(status_l);
		free(new_f);
		free(new_p);
		printf("Error with profiles.txt\n");
		free(new_a);
		new_a=NULL;
		return NULL;
}

int read_profiles(FILE * fp, Profile *** head)
{
	int i;
	i = 0;		
	while(!feof(fp))
	{
		
		*head = (Profile**)realloc(*head, sizeof(Profile*)*(i+1));
		(*head)[i] = create_profile(fp);
			i++;
							

	}

	
	return i;
}
#endif