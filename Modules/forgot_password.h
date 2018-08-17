#ifndef FORGOT_P
#define FORGOT_P



#include "definitions.h"
#include <stdio.h>
#include <string.h>
#include "encoding.h"

int compare_ans(Account * user, char * ans)
{
	if(strcmp(user->answer, ans)==0)
		return 1;
	else 
		return 0;
}

void change_pass(Account * user, char * new_pass)
{
	int new_enc;
	new_enc = encryption(new_pass, user->randomNum);
	user->enc_Pass = new_enc;
}
#endif