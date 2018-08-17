#ifndef NEW_ACC
#define NEW_ACC
#include "definitions.h"
#include <string.h>
#include <stdlib.h>


int chk_if_sletter(char c)
{
//	int i;
//for(i=(int)('a'); i<=(int)('z'); i++)
	//if (c==(char)(i))
	//	return 1;


return (c>96 && c<123);
}

int chk_if_cletter(char c)
{
//	int i;
//for(i=(int)('A'); i<=(int)('Z'); i++)
	//if (c==(char)(i))
	//	return 1;
return (c>64 && c<91);
}

int chk_if_digit(char c)
{
	//int i;
//for(i=(int)('0'); i<=(int)('9'); i++)
	//if (c==(char)(i))
	//	return 1;

return (c>47 && c<58);

}

int user_vaild_rec(char * user)
{
	if(*(user+1)=='\0')
		return (chk_if_sletter(*user) || chk_if_cletter(*user) || *user==' ');

		return (chk_if_sletter(*user) || chk_if_cletter(*user) || *user==' ') && (user_vaild_rec(user+1));

	
}

int is_username_valid(char * user)
{
	if(*user=='\0')
		return 0;



	return user_vaild_rec(user);
}

int pass_vaild_rec(char *pass)
{
	if (*pass == '\0')
		return 8;
	else if(chk_if_sletter(*pass))
		return 1 |  pass_vaild_rec(pass+1);
	else if(chk_if_cletter(*pass))
		return 2 |  pass_vaild_rec(pass+1);
	else if(chk_if_digit(*pass))
		return 4 |  pass_vaild_rec(pass+1);
	else 
		return 0;
}


int answer_valid_rec(char*ans)
{
		if(*(ans+1)=='\0')
		return (chk_if_sletter(*ans) || chk_if_cletter(*ans) || *ans==' ' || chk_if_digit(*ans));

		return (chk_if_sletter(*ans) || chk_if_cletter(*ans) || *ans==' ' || chk_if_digit(*ans)) && (user_vaild_rec(ans+1));
}

int is_ans_valid(char * ans)
{
	if(*ans=='\0')
		return 0;



	return answer_valid_rec(ans);
}




int pass_valid(char *pass)//check
{
	if(pass_vaild_rec(pass)==15)
		return 1;
	else
		return 0;
}







void add_account(Account ** head, Account * new_one)
{

	Account * helper;
	if(new_one==NULL)
		return;

	if(*head==NULL)
	{
		*head = new_one;
		return ;
	}

	helper = *head;

	while(helper->next!=NULL)
		helper = helper->next;

	helper->next = new_one;


}


Account * new_account_node(char * username,  char *  password, char * Answer)
{

	Account * new_acc;
	int RanNum;

	new_acc = (Account*)malloc(sizeof(Account));
	
	if(new_acc==NULL)
		{
		printf("Error");
		return;
		}


	strcpy(new_acc->Username, username);//Part
	RanNum  = rand();//
	//printf("%d", RanNum);
	new_acc->enc_Pass = encryption(password, RanNum);//
	new_acc->randomNum = RanNum;//
	strcpy(new_acc->answer, Answer);//
	new_acc->next=NULL;//


	return new_acc;
}


#endif