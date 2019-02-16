#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int address = 0 ; 

char * input = "input.asm";
char * pseudo = "pseudo.txt";
char * outable = "table.txt";
char * outlabel = "label.txt";

int firstpass(char * line);

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
	for(int s = 0; s < 5; s++)
	{
		hex[s] = '0';
	}
	
	for (int j = 4-i ; j<4 ; j++)
	{
		hex[j] = reverse[4-j-1];
	}
	hex[4]='\0';
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
//Not Checked yet
int  getopcode(FILE * fp ,char * ins,char * opcode)
{
	char * find = search_in_file(fp , ins);
	int i = 0 ;
	while (find[i++]!=' ');
	for (int j = 0;j<4;j++ )
	{
		opcode[j]= find[i+j];
	}
	opcode[4] = '\0';
	return 0;
}



int increment(char * str)
{
	if (strstr(str, "H") != NULL){
		address += 4;
	}
	else if (strstr(str, "B") != NULL){
		address += 4;
	}
	else if (strstr(str, "D") != NULL){
		address += 4;
	}
	else{
		address += 2;
	}
}

int opcode (char * op,char * oldline , int pos )
{
	findandprint(op);
	int i = pos;
	int n = strlen(oldline);
	char * line;
	line = malloc(sizeof(char)*n*2);
	for(int j = 0;j<(n-i);j++)
	{
		line[j] = oldline[i+j];
	}
	if(line[0]!='\0' && line[0] != '\n'  ){

		if (strcmp(op, "MOV") == 0){
			increment(line);
		}

		else if (strcmp(op, "ADD") == 0){
			increment(line);
		}

		else if (strcmp(op, "SUB") == 0){
			increment(line);
		}

		else if (strcmp(op, "OR") == 0){
			increment(line);
		}

		else if (strcmp(op, "AND") == 0){
			increment(line);
		}

		else if (strcmp(op, "CMP") == 0){
			increment(line);
		}

		else if (strcmp(op, "MUL") == 0){
			increment(line);
		}

		else if (strcmp(op, "JMP") == 0){
				address += 3;
		}

		else if (strcmp(op, "JNZ") == 0){
			address += 3;
		}

		else if (strcmp(op, "NOT") == 0){ 
			address += 2;
		}

		else if (strcmp(op, "HLT") == 0){
			address += 1;
		}

		else if (strcmp(op, "LOOP") == 0){
			address += 7;
			findandprint("SUB");
			findandprint("JNZ");
		}
	}
}

int label(char * lab , char  * line , int pos)
{
	FILE * out ;
	out = fopen (outlabel, "a+");
	char ad[1000],reverse[1000];
	int k = 0;
	int temp =address;
	printf("address : %d\n",address);
	while(temp>0){
		ad[k++] = temp%10 +'0';
		temp /= 10;
		
	}
	ad[k] = '\0';	
	int j;
	for ( j = 0 ; j< k ; j++)
	{
		reverse[j] = ad[k - j-1];
	}
	reverse[j]='\0';
	char hexad[1000];
	DtoH(reverse,hexad);
	fprintf(out,"%s: %sH\n",lab,hexad);
	fclose(out);
	int i = pos;
	i++;
	int n = strlen(line);
	char * newline;
	newline = malloc(sizeof(char)*n*2);
	for(int j = 0;j<(n-i);j++)
	{
		newline[j] = line[i+j];
	}
	firstpass(newline);
}


int firstpass(char * line)
{
	int i = 0;
	while(line[i] == ' '){
		i++;
	}
	char temp[20] ;
	int j =0 ;
	while (line[i] != ' ' && line[i] != ':' )
	{
		temp[j] = line[i];
		j++;
		i++;
	}
	temp[j]= '\0';
	if( line[i] == ':')
	{
		label(temp,line,i);
	}
	else
	{
		while(line[i]==' ' ){
			i++;
		}
		if (line[i] != ':')
		{
			printf("%s\n",temp);
			opcode(temp ,line,i);
		}
		else
		{
			label(temp,line, i);
		}
	}
	return 0;
	
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
			printf("%d\n",address);
    	}
    }
	fclose(inputf);
	return 0;
}