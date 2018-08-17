#ifndef EXIT_PROGRAM_H
#define EXIT_PROGRAM_H


#include "definitions.h"
#include <stdlib.h>
#include "write_files.h"
#include "write_files_2.h"

//NEED TO PROFILES TOO
void print_help()
{
}

void free_user_db(Account * head)
{

	if(head==NULL)
	return ;

	free_user_db(head->next);
		free(head);

}

void free_profile(Profile * prof)//belong to exit_program
{


	if(prof==NULL)
	return;
	else
	{
		
		free_profile(prof->RequestHead);
		free(prof->friends);
		free(prof->status);
		free(prof->username);
		free(prof);

	}
}

void free_prof_array(Profile ** Array, int length)//main function for releasing memory of profiles belong to exit_program
{
	int i;

	for(i=0; i<length; i++)
	{
		free_profile(Array[i]);
	}

}

void get_out(Account * acc_head, Profile ** prof_Array, int arr_len)//Profile ** prof_array
{

	FILE * fp;


	fp = fopen("validation.txt", "w");
	if (fp==NULL)
	{
		printf("Error");
		return ;
	}
	write_validation(acc_head, fp);
	fclose(fp);




	fp = fopen("profile.txt", "w");
	if (fp==NULL)
	{
		printf("Error");
			return;
	}

	write_prof(prof_Array, fp, arr_len);
	fclose(fp);

	free_prof_array(prof_Array,arr_len);
	free_user_db(acc_head);
	free(prof_Array);
	printf("\nThank you for using SocioPath, Good bye!\n");

	
	
	exit(EXIT_SUCCESS);


}




#endif