#ifndef WRITE_F
#define WRITE_F


#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>
#include "definitions_2.h"

void int2bits(int num,  char * str)
{
	int i;
	str[32] = '\0';
	for (i=31; i>=0; i--)
	{
		str[i] = (int)('0') + (num % 2);
		num = num/2;
	}
}

int find_num_digits(int num)
{
	int ten;
	int i;
	ten=10;
	i = 1;
	while(num/ten>0)
	{
		ten = ten*10;
		i++;
	}
	return i;

}

char * int2txt(int num)// FIX
{
	//free the address after finishing;
	int i; //numbers of dgits in number;
char * helper;
i = find_num_digits(num);
helper = (char*)malloc(sizeof(char)*i+1);

if(helper==NULL)
		{
		printf("Error");
		return;
		}


helper[i] = '\0';

for(i=i-1; i>=0; i--)
{
helper[i]  =(int)('0') + num%10;
num = num/10;
}

return helper;
}



void write_validation( Account * current, FILE * fp)

{

	char bits[33];
	char * number;

	if(current==NULL)
	return ;

	
	
	fprintf(fp, "%s_$_", current->Username);//OK
	int2bits(current->enc_Pass, bits);//OK

	fprintf(fp, "%s_$_", bits);//OK
	number = int2txt(current->randomNum);//ok

	fprintf(fp, "%s_$_", number);



	fprintf(fp, "%s", current->answer);
	free(number);

	if(current->next!=NULL)
	fputc('\n', fp);

	write_validation(current->next, fp);


}



#endif