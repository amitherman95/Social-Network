#ifndef COMMANDS_H
#define COMMANDS_H
#include "status.h"
#include <stdio.h>
#include "new_acc.h"
#include "pending.h"
#include <string.h>
#include "friends.h"
void remove_newline(char * str)//really needed
{

	int i;
	for(i=0; i<strlen(str); i++)
	{
	if(str[i] == '\n')
		str[i] = '\0';
	}
}

void print_sep();

//==============================profile======================================


void profile(Account * acc_head, Profile ** prof_Array, Profile * User , int arr_len)
{
	
	printf("Your status:%s", User->status);
	putchar('\n');
	printf("Your friends status:\n");
	print_friends_status(prof_Array, User, arr_len) ;
	return;

}
//============================checkRequest=================
void checkRequests(Profile * User, Profile ** prof_Array, int arr_len)
{
	char instruction[65];
	Profile * helper;
	printf("Dear %s, you have %d friend requests\n",User->username,  num_of_nodes(User->RequestHead) );
		printf("The following people are requesting you add them as friends:\n");
		print_requests(User->RequestHead);
	Input:	printf("\nTo approve a request enter: ''approve::<username>''\n");
		printf("To refuse and delete a request enter: ''refuse::<username>''\n");
		printf("To go back to the main selection menu etner: '&'\n");
		printf("Input:");
		
	scanf ("%[^\n]%*c", instruction);//Fix exception
	

	if(  strstr(instruction,"approve::")==instruction  )
	{

		if(is_user_in_requests(User->RequestHead, instruction+9))
		{
		helper = find_profile(instruction+9, prof_Array, arr_len) ;
		remove_request(&(User->RequestHead), instruction+9);
		add_friend(instruction+9,&(User->friends));
		add_friend(User->username,&(helper->friends));
		printf("%s was successfully add as a friend \n", instruction+9);
		return;
		}

		else
		{
			printf("\nThere is no such user in the list\n");
			goto Input;
		}
	}
	else if(  strstr(instruction,"refuse::")==instruction  )
	{
		if(is_user_in_requests(User->RequestHead, instruction+8))
		{
		remove_request(&(User->RequestHead), instruction+8);
		printf("%s was successfully removed from your pending list. \n", instruction+8);
		return;
		}

		else
		{
			printf("\nThere is no such user in the list\n");
			goto Input;
		}

	}
	else if(strstr(instruction,"&")==instruction  )
	{
		putchar('\n');
		return;
	}

	else
	{
		printf("\nInvalid input\n");
		goto Input;
	}


}
//==========================request==============
void request(Profile ** prof_Array, char*dest, int arr_len ,Profile * user)
{
	{
	Profile * target;

	if(strcmp(dest, user->username)==0)
	{
		printf("\nYou can't send request to yourself.");
		return;
	}

	target = find_profile(dest, prof_Array, arr_len);
	if(target == NULL)
	{
		printf("\nNo such user");
		return;
	}

	else if(is_user_in_requests(target->RequestHead, user->username))
	{
		printf("You already sent a request to this user");
		return;
	}

	else if(is_in_friend(dest, user->friends))
	{
		printf("This user is already your friend");
		return;
	}
	else
	{
		add_request(&(target->RequestHead), user->username);
		printf("The request was succesfuly sent, waiting for the user to accept you.");
	}




}
}
//=======================status============================================


void status(Account * acc_head, Profile ** prof_Array, Profile * User)
{
	char option;
	char status[514];
	printf("Update your SocioPath status to share with your friends\n");
	Input:printf("Input:");
	fflush(stdin);
	fgets(status, 514, stdin);
	remove_newline(status);
	if(strlen(status) == 513)
	{
		printf("This length of this status exceeds the possible length,\nDo you wish to update your status with first 512 characters?\ntype 'y' for yes 'n' for no\nInput:)");
		Input2:option = getchar();
		switch (option)
		{
		case 'y':
			status[513] = '\0';
			change_status(status, User);
			printf("The status was successfully changed\n");
			fflush(stdin);
			return;
		case 'n':
			printf("Please pick other status.\n");
			goto Input;
		default:
			printf("Invalid input, type y/n:\nInput:");
			fflush(stdin);
			goto Input2;

		}


	}


	change_status(status, User);
	printf("The status was successfully changed\n");
	return;

}


//======================unfriend=====================

void unfriend(char*friend_n, char** friends_of_current_user, Profile ** prof_Array, int arr_len, Profile * User)
{
	Profile * helper;
	if(is_in_friend(friend_n, *friends_of_current_user))
	{
		helper = find_profile(friend_n, prof_Array, arr_len); 
		remove_friend(friend_n, friends_of_current_user);
		remove_friend(User->username, &(helper->friends));
		printf("%s was removed from your friend list", friend_n);
	}

	else
		printf("%s is not in your friend list", friend_n);


}

//=============================checkStatus==========================================

void checkStatus(Account * acc_head, Profile ** prof_Array, Profile * User, char * friend_n, int arr_len )
{
	Profile * friend_prof;
	if(is_in_friend(friend_n, User->friends))
		{
			friend_prof = find_profile(friend_n, prof_Array, arr_len);
			printf("%s Status:%s\n",friend_n,  friend_prof->status);
			return;

		}

		printf("Friend was not found\n");
		return;

}

//==================================printFriends=====================
int string_comp( char * c1, char * c2)
	//lexicographical comaprison between 2 strings: if c1>c2 return1; else return 0.
{

	int c, len1, len2, i, Flag;


		if(c1[0]!='\0' && c2[0]!='\0')
		{
		len1 = strlen(c1);
		len2 = strlen(c2);
			c=0;

		 if(len1>len2)
			{
				len1 = len2;
				c =1;
			}

			i=0;
			Flag=1;
			while(Flag)
			{
				if(i==len1)
					Flag = 0;

				else if(chk_if_cletter(c1[i]) && chk_if_sletter(c2[i]))
				{
					Flag = 0;
					c = 1;
				}

				else if(chk_if_cletter(c2[i]) && chk_if_sletter(c1[i]))
				{
					Flag = 0;
					c = 0;
				}

				else if(c1[i]>c2[i])
				{
					Flag = 0;
					c = 1;
				}

				else if(c2[i]>c1[i])
				{
					Flag = 0;
					c = 0;
				}
	
				

				i++;
			}
		}
		else
			c = 1;


		return c;


}



void lex_print(char * friends)//works
{
	int Flag, length, i, k;
	char last[51],min[51], helper[51]; ;
	Flag = 1;
	length = strlen(friends);

	if(friends[0]!='\0');
	{
		last[0] = '\0';

		while(Flag)
		{
		Flag = 0;
		min[0] = '\0';
		k=0;
			for(i=0;i<=length;i++)
			{
				if( friends[i] =='\0' || friends[i] ==';')
				{
					helper[k] = '\0';
					if(string_comp(min, helper))
						if(string_comp(helper, last))
						{
							Flag = 1;
							strcpy(min, helper);
						}

						k=0;
				}

				else
				{
					helper[k] = friends[i];
					k++;
				}

			}
			if(min[0]!='\0')
			{
			printf("%s\n", min);
			strcpy(last, min);
			}

		}
	}

}



void printFriends(Profile * User)
{
	if((User->friends)[0] =='\0')
	{
		printf("You don't have any friends\n");
		return;
	}
	
	else
	{
		printf("Friends:\n");
		lex_print(User->friends);
		return ;

	}

}

//======================print_social_netowrk==========================

char* create_list(char*friends, int * status, int arr_len, Profile ** prof_Array)
{

char helper[52];
char * new_list=NULL;
int i=0, k=0, length=0, n=0;

new_list = (char*)malloc(1);

	if(new_list==NULL)
	{
		printf("Error");
			return NULL;
	}

new_list[0] = '\0';
length = strlen(friends);

for(i=0;i<=length;i++)
{
	if(friends[i] =='\0')
	{
		helper[k] = '\0';
		n=find_profile_index(helper, prof_Array, arr_len);
		if(status[n]==0)
		{
			status[n] = 1;
			new_list = (char*)realloc(new_list,  strlen(new_list) + strlen(helper) + 1);

				if(new_list==NULL)
				{
				printf("Error");
				return NULL;
				}

		strcat(new_list, helper);//assume there is null terminator
		}

		else
		{
			if(new_list[strlen(new_list)-1]==';')
				new_list[strlen(new_list)-1]='\0';
		}

	}



	else if(friends[i] ==';')
	{

		helper[k] = '\0';
		n=find_profile_index(helper, prof_Array, arr_len);
		helper[k] = ';';
		helper[k+1] = '\0';
		if(status[n]==0)
		{
			status[n] = 1;
			new_list = (char*)realloc(new_list,  strlen(new_list) + strlen(helper) + 1);
			strcat(new_list, helper);
		}
		k=0;
	}

	else
	{
		helper[k] = friends[i];
		k++;
	}

}

return new_list;
}


char * fof(char*friends, int * status, int arr_len, Profile ** prof_Array)//fof = friends of friends
{

	Profile * friend_p=NULL;
	char helper[51];
	int length=0, i=0, k=0;

	char * sum=NULL;//needs malloc
	char * new_list=NULL;

	sum = (char*)malloc(1);

		if(sum==NULL)
		{
		printf("Error");
		return NULL;
		}
		
	sum[0]  = '\0';



	length = strlen(friends);
	for(i=0; i<=length; i++)
	{
		

		if(friends[i] =='\0')
		{
			helper[k]= '\0';
			friend_p = find_profile(helper, prof_Array, arr_len);
			new_list = create_list(friend_p->friends, status, arr_len, prof_Array);
			sum = (char*)realloc(sum, strlen(sum) + strlen(new_list) + 1);
			strcat(sum, new_list);
			free(new_list);
			k=0;
		}

		else if(friends[i] ==';')
		{
			helper[k]= '\0';
			friend_p = find_profile(helper, prof_Array, arr_len);
			new_list = create_list(friend_p->friends, status, arr_len, prof_Array);
			if(sum[0]!='\0' && new_list[0] !='\0')
			{
				sum = (char*)realloc(sum, strlen(sum) + 1 + 1);
				strcat(sum, ";");
			}
			sum = (char*)realloc(sum, strlen(sum) + strlen(new_list) + 1);
			strcat(sum, new_list);
			free(new_list);
			k=0;
		}

		else
		{
			helper[k] = friends[i];
			k++;
		}
	}

	return sum;

}




void print_string_properly(char * string)//print strings but if the char is ';' it replaces it with ", "
{

	int n, i, k;
	n = strlen(string);
	k=0;
	for(i=0; i<n ;i++)
	{
		if(string[i] == ';')
		{	
			if(k==5)
			{
			putchar('\n');
			k=0;
			}
			else
			{
			printf(", ");
			k++;
			}
		}
		else
			putchar(string[i]);
	}
}





void printNetowrk(Profile** prof_Array, int arr_len, Profile * user)
{	int * status;//saves which user was already printed
	
	
	int i=0, cycle=0;
	char *str1;
	char *str2;
	
	str1=NULL;
	str2=NULL;


		status = (int*)malloc(sizeof(int)*arr_len);

		if(status==NULL)
		{
		printf("Error");
		return;
		}



	for(i=0; i<arr_len; i++)
	{
		status[i]=0;// 0 not printed, 1 printed

	}
	printf("Dear %s, your social netowrk:\n", user->username);
	printf("You: %s\n", user->username);
	status[find_profile_index(user->username ,prof_Array, arr_len)]  = 1;

	str1 = fof(user->username, status, arr_len, prof_Array);//last

	if(str1[0] == '\0')
	return;

	printf("Your friends:" );//1
	print_string_properly(str1);//2

	str2 = str1;
	str1 = fof(str2, status, arr_len, prof_Array); //4
	free(str2);

	putchar('\n');//6

	if(str1[0] == '\0')
	return;

	printf("Friends of friends:" );//1
	print_string_properly(str1);//2

	str2 = str1;
	str1 = fof(str2, status, arr_len, prof_Array); //4
	free(str2);

	putchar('\n');//6

	cycle = 3;

	while(str1[0]!='\0')
	{
	printf("Circle %d of friends:", cycle);//1
	print_string_properly(str1);//2

	str2 = str1;
	str1 = fof(str2, status, arr_len, prof_Array); //4
	free(str2);

	putchar('\n');//6
	cycle++;
	}
	
	free(str1);
	free(status);

}


//============================search======================
char * ci_strstr( char *arg1, char *arg2)//case insensitive strstr
{                  
   const char *a, *b;
                   
   for(;*arg1;*arg1++) {
                   
     a = arg1;
     b = arg2;
     
     while((*a++ | 32) == (*b++ | 32))
       if(!*b) 
         return (arg1);
     
   }
     
   return(NULL);
}

void search(Profile ** prof_Array, int arr_len, char * query)
{
	int i;
	printf("The system found the following users for the query: \"%s\"\n", query);

	for(i=0; i<arr_len; i++)
	{
		if(ci_strstr(prof_Array[i]->username, query)!=NULL)
			printf("-%s\n", prof_Array[i]->username);
	}
}



//============================read_command==============

void read_commands(Account * acc_head, Profile ** prof_Array, Profile * User, char * command, int arr_len)
{
	if(strcmp(command,"$")==0)
		get_out(acc_head, prof_Array, arr_len);

	else if(  strcmp(command,"profile")==0  )
	{
		print_sep();
		profile(acc_head, prof_Array, User, arr_len);
		print_sep();
			return;
	}

	else if(  strcmp(command,"status")==0  )
	{
		print_sep();
		status(acc_head, prof_Array, User);
		print_sep();
		profile(acc_head, prof_Array, User, arr_len);
			return;
	}

	else if(  strstr(command,"checkStatus ")==command  )
	{
		print_sep();
		checkStatus(acc_head, prof_Array, User, command+12, arr_len);
			print_sep();
			return;
	
	}
	else if(  strcmp(command,"printFriends")==0  )
	{
		print_sep();
		printFriends(User);
			print_sep();
			return;
	
	}
	else if(  strcmp(command,"printNetwork")==0  )
	{
		print_sep();
		printNetowrk(prof_Array,arr_len, User);
			print_sep();
			return;
	
	}
	else if(  strcmp(command,"checkRequests")==0  )
	{
		print_sep();
		checkRequests(User, prof_Array, arr_len);
		print_sep();
			return;
	
	}


	else if(  strstr(command,"request ")==command  )
	{
		print_sep();
		request(prof_Array,command+8, arr_len, User); 
			print_sep();
			return;
	
	}

	else if(  strstr(command,"unfriend ")==command  )
	{

		unfriend(command+9, &(User->friends), prof_Array, arr_len, User);
			print_sep();
			return;
	
	}
	else if(  strstr(command,"search ")==command  )
	{
		print_sep();
		search(prof_Array, arr_len, command+7); 
			print_sep();
			return;
	
	}


	else
	{
		putchar('\n');
		printf("Unknown command\n");
		print_sep();
		return;
	}
}



#endif