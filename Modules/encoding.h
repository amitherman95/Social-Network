#ifndef ENC
#define ENC

#include <stdio.h>
char AND_chars(char* pass)
{
	if(*(pass+1)=='\0')
		return *pass;
	return *pass  & AND_chars( pass+1);
}

int encryption(char * pass, int randomNum)
{
	int temp;
	temp = AND_chars(pass);
	if(temp%2==0)
		temp = temp<<4;
	else
		temp = temp>>6;
	temp  = temp ^ randomNum;
	return temp;
}

#endif
