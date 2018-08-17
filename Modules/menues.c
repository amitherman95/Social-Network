


#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_files.h"
#include "profiles.h"
#include "exit_program.h"
#include <string.h>
#include "login.h"
#include "forgot_password.h"
#include "new_acc.h"
#include <conio.h>
#include "definitions_2.h"
#include "commands.h"
#include "read_files_2.h"



void read_asterkis(char * target, int length)
{
	char c;
	int i; 
	for(i=0; i<length; i++)
	{
		c=getch();
		if(c=='\n')
		{
			putch(c);
			break;
		}

		putch('*');
		target[i]=c;
		
	}
	target[i] = '\0';

}
void print_sep()
{
	printf("\n\n===============================================================================\n\n");
}

void print_commands()
{
	printf("\"profile\" - show your profile\n");
	printf("\"status\" - update your current status\n");
	printf("\"checkStatus <friend_username>\" - check the current status of a specific friend whom username is entered in the place of <friend_username>\n");
	printf("\"checkRequests\" - check incoming friend requests.\n");
	printf("\"printFriends\" - print the list of your friends(usernames)\n");
	printf("\"search\" - search SocioPath network for a username\n");
	printf("\"request <username>\" - send a friend request to a given username\n");
	printf("\"unfriend <friend_username>\" - unfriend the entered friend\n");
	printf("\"printNetowrk\" - print your social netowrk\n");
	printf("\"#\" - log out and return to the first App screen\n");
	printf("\"$\" - exit the app\n");
}
void logged_in(Account * acc_head, Profile ** prof_Array, int arr_len, Profile * current_user)
{

	char command[65];//Should be enough
	printf("Hello %s, Welcome to your profile!\n",  current_user->username);
	profile(acc_head, prof_Array, current_user, arr_len);
Command:printf("\nWhat would you like to do next?\n");
	print_commands();
	printf("Input:");
	scanf ("%[^\n]%*c", command);
	//command[65] = '\0';//In case someone tries to outsmart the system EXCEPTION
	if(strcmp(command,"#")==0)
		return;
	read_commands(acc_head, prof_Array, current_user, command, arr_len);
	goto Command;
}

void new_account(Account ** acc_head, Profile *** Array,int *arr_len)//Needs diet, THIS FUNCTION NEED TO CREATE NEW PROFILE FOR THE ACCOUNT
{
	Profile * new_p;
	Account * new_acc;
	char username[51];
	char Answer[513];
	char password[9];
	char password_2[9];
	int RanNum;
	printf("Hello dear guest\n");
	printf("Please choose a username\n");
User:printf("Input:");

	scanf ("%[^\n]%*c", username);
	if(is_username_valid(username)==0)
	{
		printf("\nInvalid username, Try again\n");
		goto User;
	}

	if(find_username(username, *acc_head)!=NULL)
	{
		printf("\nWe are truly sorry, but the username you chose is already taken\nPlease choose other\n");
		goto User;
	}

	printf("\nHello %s\n", username);
	printf("Please type a password\n");
	Pass:printf("Input:");
	read_asterkis(password, 8);
	
	if(pass_valid(password)==0)
	{
		printf("\nInvalid password, Try again\n\n");
		goto Pass;
	}

	if(strlen(password)!=8)
	{
		printf("\nThe length of a password must be 8 chars, Try again\n");
		goto Pass;
	}

	printf("\n\nPlease type the password again\n");
	printf("Input:");
	read_asterkis(password_2, 8);

	if(strcmp(password, password_2)!=0)
	{
		printf("\nThe password do not match, Type a new password\n");
		goto Pass;
	}

	printf("\n\nQuestion:When did you perform your last air guitar jam?\n");
	Question:printf("Input:");
	scanf ("%[^\n]%*c", Answer);

	if(is_ans_valid(Answer)==0)
	{
		printf("\nInvalid answer, only letters digits and spaces, try again\n");
		goto Question;
	}


	new_acc = new_account_node(username, password, Answer);
	add_account(acc_head, new_acc);
	
	
	new_p = new_profile(username);
	add_profile(new_p, Array, arr_len); 
	printf("The procedure was successful, thank you for choosing SocioPath");
	print_sep();
}




void forgot_password(Account * acc_head, Account * user, Profile ** prof_Array, int arr_len)//add profile because get_out updates profile too
{
	char answer[201];
	char password[9];
	int tries;
	tries = 3;

	while(tries>0)
	{
	printf("Please anwer the following question, you have %d chances\n", tries);
	printf("\nQuestion:When did you perform your last air guitar jam?\nInput:");
		//fgets(answer, 200, stdin);
		scanf ("%[^\n]%*c", answer);

		if (strcmp(answer, "$") == 0)
		get_out(acc_head, prof_Array, arr_len);//prof_head

	else if((strcmp(answer, "#") == 0))
		{
		print_sep();
		return ;
		}


		if(compare_ans(user, answer))
		{

			printf("Correct, Hello %s\n", user->Username);
		TryAgain:printf("Type your new password\nInput:");
			//fgets(password, 8, stdin);
			scanf ("%[^\n]%*c", password);
			if(strlen(password)!=8 || pass_valid(password)==0 )
			{
				printf("\nInvalid password try again\n");
					goto TryAgain;
			}
			
			change_pass(user, password);
			printf("Your password was successfuly changed");
			return;
		}
		printf("Wrong answer\n");
		tries--;
	}
		printf("You only had 3 chances goodbye");
		get_out(acc_head,prof_Array, arr_len);
}






void  wrong_password(Account * acc_head, Account * user, Profile ** prof_Array, int arr_len) //NEEDS TO SEND PROFILE TO LOGGED_IN
{
	char input[10];
	printf("\nIncorrect password\n");
	Incorrect: printf("Please type the password again, Or:\ntype # for the main men\ntype $ to exit SocioPath\ntype ! if you forgot your password\nInput: ");
	//fgets(input, 10, stdin);
	scanf ("%[^\n]%*c", input);

	if (strcmp(input, "$") == 0)
		get_out(acc_head, prof_Array,arr_len);//prof_head

	else if((strcmp(input, "#") == 0))
	{
		return;
	}

	else if((strcmp(input, "!") == 0))
	{
		forgot_password(acc_head, user, prof_Array, arr_len);//add 
		return;
	}

	if(compare_password(user, input))
	{				print_sep();
					logged_in(acc_head, prof_Array, arr_len, find_profile(user->Username, prof_Array, arr_len));
					return;
	}
	else
	{
		printf("Incorrect\n\n");
		goto Incorrect;
	}


}

void login(Account * acc_head, Profile ** prof_Array, int arr_len)//NEEDS TO SEND PROFILE TO LOGGED_IN
{
	char input[100];// should be enough;
	Account * user;
	char * helper;
	int user_found, pass_corrent;

	printf("Please enter your username and password and in the format username::password\n");
	printf("to go back to the first screen: #\nTo exit the program:$\n\n");
Input:printf("Input:");
	//fgets(input, 100, stdin);
	scanf ("%[^\n]%*c", input);

	if (strcmp(input, "$") == 0)
		get_out(acc_head, prof_Array, arr_len);

	else if((strcmp(input, "#") == 0))
	{
		print_sep();
		return;
	}
	else
	{
		helper  = separation(input);
		if(helper==NULL)//If something wrong with the input
		{
			printf("Error:Wrong format try again\n");
			goto Input;
		}
		else//everything ok
		{
			*helper = '\0';
			user = find_username(input, acc_head);
			if(user!=NULL)//User found
			{
				if(compare_password(user, helper+2))//If pass correct
				{
					print_sep();
					logged_in(acc_head, prof_Array, arr_len, find_profile(user->Username, prof_Array, arr_len));
					print_sep();
					return;
					
				}
				else 
				{ //Pass incorrect
					
					wrong_password(acc_head, user, prof_Array, arr_len );
					print_sep();
				return;
				}
		
			}
			else//User was not found
			{
				printf("There is no such user");
				print_sep();
					return;
			}
		
		}
	}
}




void main_menu(Account * acc_head, Profile ** prof_Array, int arr_len)//needs to update each get_out and send profile array to new account and login

{
	FILE * fp;
	char option;

	Enter: printf("Hello dear guest and welcome to SocioPath\n");
	printf("What would you like to do next\n1.Login\n2.Create new account\n3. Exit\n");
	Input:printf("Input :");
	option = getch();

	switch (option)
	{
	case '1': //login
		print_sep();
		login(acc_head,prof_Array,arr_len );//prof_array

		fp = fopen("profile.txt", "w");
		if (fp==NULL)
		{
		printf("Error");
			return;
		}

		write_prof(prof_Array, fp, arr_len);
		fclose(fp);
		goto Enter;
	case '2':
		print_sep();
		new_account(&acc_head, &prof_Array,&arr_len );//prof_array
		goto Enter;
	case '3':
		get_out(acc_head, prof_Array,arr_len);////prof_array
	default:
		printf("Invalid input, try again\n");
		goto Input;
	}





}

int main()//needs to load profile.txt
{

	Account * acc_head=NULL;
	Profile ** prof_Array=NULL;
	FILE * fp;
	char c;
	int arr_len=0;
	fp = fopen("validation.txt", "r");
	if (fp==NULL)
	{
		printf("Error");
		return 0;
	}
	if((c=fgetc(fp))!=-1)
	{
		
	rewind(fp);
	read_validation(fp, &acc_head);

	}
	fclose(fp);

	fp = fopen("profile.txt", "r");//
	if (fp==NULL)
	{
		printf("Error");
		return 0;
	}

	if((c=fgetc(fp))!=-1)//
	{
	rewind(fp);
	arr_len=read_profiles(fp, &prof_Array);
	}
	fclose(fp);


	fclose(fp);
	main_menu(acc_head,  prof_Array, arr_len);
	return 0;
}