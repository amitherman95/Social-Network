#ifndef READ_FILES
#define READ_FILES


#include "definitions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ReadLine( FILE *fp, char *str  )//Read a line from a file into an arrray of characters.
{
	char c;
	int i; //Counter

	i=0;
	c=getc(fp);
	while (c!='\n' && c!=EOF )
	{
		str[i]=c;
		i++;
		c=getc(fp);
	}
	str[i]='\0';
}

char * detect_separation(char * str)// finds _$_ and give pointer to 3 chars ahead/

{
	if(*str == '_' && *(str+1)=='$' && *(str+2)=='_')
		return str + 3;
	else
		return NULL;
	}

int bits2number(char * bits)
{
	int len, i, twos, number;
	twos=1;
	number=0;
	len = strlen(bits);
	for(i=len-1; i>=0; i--)
	{
		number = number + twos*( (int)bits[i] - (int)('0'));
		
		twos = twos*2;
	}
	return number;
}

char  * get_user(char * line, char * user_hlp)
{
	int i;
	char * helper;
	for(i=0; i<50; i++)
	{
		if (line[i]== '_')
		{
			helper = detect_separation(line+i);
				if (helper != NULL)
				{
					user_hlp[i]='\0';
					return helper;
				}
		}
			
		user_hlp[i] = line[i];
	}
}

char  * get_enc_pass(char * line, char * pass_hlp)
{
	int i;
	char * helper;
	for(i=0; i<33; i++)
	{
		if (line[i] == '_')
		{
			helper = detect_separation(line+i);
				if (helper != NULL)
				{
					pass_hlp[i]='\0';
					return helper;
				}
		}
			
		pass_hlp[i] = line[i];
	}
	}

int txt2int(char * number)
{
	int num;
	int i;
	num=0;
	for(i=0; i<strlen(number); i++)
	{
		num=num*10;
		num=num +  ( (int)(number[i]) - 48 );
	}
	return num;
}

	char  * get_ranNum(char * line, char * rnum_hlp)
{
	int i;
	char * helper;
	for(i=0; i<20; i++)
	{
		if (line[i] == '_')
		{
			helper = detect_separation(line+i);
				if (helper != NULL)
				{
					rnum_hlp[i]='\0';
					return helper;
				}
		}
			
		rnum_hlp[i] = line[i];
	}
	}

	void  get_answer(char * line, char * ans_hlp)
	{
	int i;
	char * helper;
	for(i=0; i<100; i++)
	{
		if (line[i] == '\0')
		{
			ans_hlp[i] = '\0';
		return;
		}
		ans_hlp[i] = line[i];
	}
	}

	Account * create_node(char * line)//working
	{
		char Username[51];
		char Pass_bits[33];
		char RanNum[20];
		char Answer[201];
		char * h1, *h2,* h3;
		Account  * new_node;
		h1 = get_user(line, Username);
		h2 = get_enc_pass(h1, Pass_bits);
		h3 = get_ranNum(h2, RanNum);
		get_answer(h3, Answer);
		
		new_node = (Account*) malloc(sizeof(Account));

		if (new_node==NULL)
		{
			printf("Error allocating memory/n");
			return NULL;
		}

		strcpy(new_node->Username, Username);
		new_node->enc_Pass = bits2number(Pass_bits);
		new_node->randomNum = txt2int(RanNum);
		strcpy(new_node->answer, Answer);
		new_node->next=NULL;
		return new_node;
	}

void read_validation(FILE * fp ,Account ** head)//working
{
	char line[306];
	Account * helper;
	while(!feof(fp))
	{
		ReadLine(fp, line);
		helper = create_node(line);
		*head = helper;
		head = &(*head)->next;
	}
}

#endif