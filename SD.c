#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char opcode[6];
int address = 0 ; 

char * input = "input.asm";
char * pseudo = "pseudo.txt";
char * outable = "table.txt";
char * outlabel = "label.txt";

//Conerting Decimal to Binary ( char input to char output )
int DtoB(char * num,char * binary)
{
	int len = strlen(num);
	int a = 0;
	int temp  = 1;
	for (int i = 0; i < len; ++i)
	{
		a += (num[len - i - 1]-'0')*temp;
		temp *= 10 ;
	}
	int i=0;
	char  reverse[20] ; 
	while(a >0)
	{
		reverse[i++] = a%2 + '0';
		a /= 2;
	}
	reverse[i]='\0';
	for (int j = 0 ; j< i ; j++)
	{
		binary[j] = reverse[i - j-1];
	}
	binary[i]='\0';
	return 0;
}
//Conerting Decimal to Hex ( char input to char output )
int  DtoH(char * num,char * hex)
{
	int len = strlen(num);
	int a = 0;
	int temp  = 1;
	for (int i = 0; i < len; ++i)
	{
		a += (num[len - i - 1]-'0')*temp;
		temp *= 10 ;
	}
	int i=0;
	char reverse[20];
	while(a >0)
	{	
		int temp2  ; 
		temp2= (a%(16)) ;
		if (temp2 >= 10)
		{
			reverse[i] =(char)((int) (temp2 - 10) + (int)('A'));
		}
		else
		{
			reverse[i]= temp2 + '0';
		}
		a /= 16;
		i++;
	}
	reverse[i]='\0';
	for (int j = 0 ; j< i ; j++)
	{
		hex[j] = reverse[i - j-1];
	}
	hex[i]='\0';
	return 0;
}

// Searches if strname is in the file pointer fp
char * search_in_file(FILE * fp, char* strname){
	char* line = NULL;
	size_t len = 0;
	while(getline(&line, &len, fp) != -1){
		if (strstr(line , strname) != NULL){
			return strstr(line , strname);
			
		}
	}
	return NULL;
}


int findandprint(char * ins)
{
	FILE * check,* old,* new;
	check = fopen (outable, "a+");
	fseek(check,0,SEEK_SET);
	char * find = search_in_file(check , ins);
	if( find != NULL)
	{
		return 0;
	}
	fclose(check);
	old = fopen(pseudo,"r");
	char * oldinput = search_in_file(old ,ins);
	int i = 0 ;
	while (oldinput[i++]!='(');
	char opcode [20];
	for (int j = 0;j<4;j++ )
	{
		opcode[j]= oldinput[i+j];
	}
	opcode[4] = '\0';
	fclose(old);
	new = fopen (outable, "a+");
	fprintf(new ,"%s %s\n",ins,opcode);
	fclose(new);
}
//Not Checed yet
int  getopcode(char * ins,char * opcode)
{
	FILE * fp;
	fp = fopen (outable, "r+");
	char * find = search_in_file(fp , ins);
	int i = 0 ;
	while (find[i++]!=' ');
	for (int j = 0;j<4;j++ )
	{
		opcode[j]= find[i+j];
	}
	opcode[4] = '\0';

	fclose(fp);
	return 0;
}

int firstpass(char * line)
{
	


}

int  main()
{
	FILE * inputf;
	char* line = NULL;
	size_t buflength = 0;
	int len = 0;
	int flag  = 0 ; 

	inputf = fopen(input, "r+");

    while (getline(&line, &buflength, inputf) != -1)
    {
    	len  = strlen(line);

    	if(strstr(line , "START") != NULL )
    	{
    		if (flag == 0 )
    		{
    			flag  = 1 ;
    		}
 	   		else
 	   		{
 	   			printf("ERROR , 2 STARTs\n");
 	   		}
    	}
    	else if(strstr(line,"END")!=NULL)
    	{
    		flag = 0;
    	}
    	else if (flag ==1 )
    	{	
    		line[len-1]= '\0';
    		firstpass(line);
    	}
    }
	return 0;
}