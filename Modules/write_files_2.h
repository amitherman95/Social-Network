#ifndef WRITE_FILES_2
#define WRITE_FILES_2
#include "definitions_2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_friends(char* friends, FILE * fp)//belongs to friends, can be used for profile command
{
	int i, n;
	n = strlen(friends);
	i=0;

	while(i<n)
	{
		if(friends[i]==';')
			fprintf(fp,"_$_");
		else
			fputc(friends[i], fp);

		i++;
	}
}


void write_pending(Profile * reqHead, FILE * fp)
{


	if(reqHead==NULL)
		return;
	else if(reqHead->RequestHead==NULL)
	{
		fprintf(fp, "%s", reqHead->username);
	}

	else
	{
		fprintf(fp, "%s_$_", reqHead->username);
		write_pending(reqHead->RequestHead, fp);
	}

}





void write_prof(Profile ** head,  FILE * fp, int length)
{
	
	int  i;
	
	for(i=0; i<length-1; i++)
	{
	fprintf(fp, "Username_%s\n", head[i]->username);
	fprintf(fp, "Status_%s\n", head[i]->status);
	fprintf(fp, "Friends_");
	write_friends(head[i]->friends, fp);
	fprintf(fp, "\nPendings_");
	write_pending(head[i]->RequestHead, fp);
	fputc('\n', fp);
	}

	if(i==length-1)
	{

		fprintf(fp, "Username_%s\n", head[i]->username);
	fprintf(fp, "Status_%s\n", head[i]->status);
	fprintf(fp, "Friends_");
	write_friends(head[i]->friends, fp);
	fprintf(fp, "\nPendings_");
	write_pending(head[i]->RequestHead, fp);

	}
}
		
#endif