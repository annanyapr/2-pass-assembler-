#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int address = 0 ; 

char * input = "input.asm";
char * pseudo = "pseudo.txt";
char * outable = "table.txt";
char * outlabel = "label.txt";
char * outans = "ouput.o";

int firstpass(char * line);


void spacing(char * ch)
{
	for(int i=17;i>=9;i--)
		ch[i]=ch[i-1];
	ch[8]=' ';
}
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
//Conerting Decimal to Hex ( int input to char output )
int  DtoH(int  a,char * hex)
{
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
void HtoB(char * hex , char * binary){
	char ch;
	binary[0]= '\0';
	for(int i=1;i<5;i++)
	{
		ch = hex[i];
		switch(ch){
		case '0': strcat(binary,"0000");break;
		case '1': strcat(binary,"0001");break;
		case '2': strcat(binary,"0010");break;
		case '3': strcat(binary,"0011");break;
		case '4': strcat(binary,"0100");break;
		case '5': strcat(binary,"0101");break;
		case '6': strcat(binary,"0110");break;
		case '7': strcat(binary,"0111");break;
		case '8': strcat(binary,"1000");break;
		case '9': strcat(binary,"1001");break;
		case 'A': strcat(binary,"1010");break;
		case 'B': strcat(binary,"1011");break;
		case 'C': strcat(binary,"1100");break;
		case 'D': strcat(binary,"1101");break;
		case 'E': strcat(binary,"1110");break;
		case 'F': strcat(binary,"1111");break;
		}
	}
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

int remove_comments(char * old)
{
	int i = 0;
	for(int i=0;i<strlen(old);i++){
	if(old[i]==';' || old[i]=='#'){
		old[i]='\0';
		return 0 ;
		}
	}
}

void convert_to_upper(char * x){
	for(int i=0;i<strlen(x);i++)
		x[i]=toupper(x[i]);
}
//Not Checked yet
int  getopcode(char * ins,char * opcode)
{
	FILE * fp;
	fp = fopen(outable,"r+");
	char * find = search_in_file(fp , ins);
	int i = 0 ;
	while (find[i]!=' ')
	{
		i++;
	}
	i++;
	for (int j = 0;j<4;j++ )
	{
		opcode[j]= find[i+j];
	}
	opcode[4] = '\0';
	return 0;
}

int getlabel(char * ans, char * label)
{
	FILE * fp;
	char temp[30];
	fp = fopen(outlabel,"r+");
	char * find = search_in_file(fp , label);
	int i = 0 ;
	while (find[i]!=' ')
	{
		i++;
	}
	i++;
	for (int j = 1;j<5;j++ )
	{
		temp[j]= find[i+j-1];
	}
	temp[0] = '0';
	temp[5] = '\0';
	HtoB(temp,ans);
	spacing(ans);
	return 0;
}

void printop(FILE * outputf ,char * opcode)
{
	char  add[10] ;
	DtoH(address,add);
	char opchar[8];
	getopcode(opcode, opchar);
	fprintf(outputf,"%s\t\t%s ",add,opchar);	
}

void regnum(char  * ans, char * reg)
{
	int n = strlen(reg);
	char temp[30];
	int i = 0;
	printf("%s\n",reg);
	for(i = 0 ; i<n;i++ )
	{
		temp[i]=reg[i+1];
	}
	DtoB(temp,ans);
	n = strlen(ans);
	if(n<5)
	{
		for(int i=n-1;i>=0;i--)
			ans[i+5-n]=ans[i];
		for(int i=0;i<5-n;i++)
			ans[i]='0';
	}
	ans[5] = '\0';
}

void hexnum(char * ans , char * hex)
{
	int n = strlen(hex);
	if(n<6)
	{
		for(int i=n-1;i>=0;i--)
			hex[i+6-n]=hex[i];
		for(int i=0;i<6-n;i++)
			hex[i]='0';
	}
	HtoB(hex,ans);
	spacing(ans);
}

void binaryNum(char * ans , char * binary)
{
	int n = strlen(binary);
	if(n<17)
	{
		for(int i=n-1;i>=0;i--)
			binary[i+17-n]=binary[i];
		for(int i=0;i<17-n;i++)
			binary[i]='0';
	}
	binary[16] = '\0';
	ans = binary;
	spacing(ans);
}

void decinum(char * ans , char * deci)
{
	int n = strlen(deci);
	deci[n-1]= '\0';
	DtoB(deci,ans);
	n = strlen(ans);
	if(n<16)
	{
		for(int i=n-1;i>=0;i--)
			ans[i+16-n]=ans[i];
		for(int i=0;i<16-n;i++)
			ans[i]='0';
	}
	ans[16] = '\0';
	spacing(ans);
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
		if (strcmp(op, "MOV") == 0|| strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0 || strcmp(op, "MUL") == 0){
			if (strstr(line, "H") != NULL){
				address += 4;
			}
			else if (strstr(line, "B") != NULL){
				address += 4;
			}
			else if (strstr(line, "D") != NULL){
				address += 4;
			}
			else{
				address += 2;
			}
		}

		else if (strcmp(op, "OR") == 0 || strcmp(op, "AND") == 0 || strcmp(op, "CMP") == 0){
			if (strstr(line, "H") != NULL){
				address += 4;
			}
			else if (strstr(line, "B") != NULL){
				address += 4;
			}
			else if (strstr(line, "D") != NULL){
				address += 4;
			}
			else{
				address += 2;
			}
		}

		else if (strcmp(op, "JMP") == 0 || strcmp(op, "JNZ") == 0){
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



int label(char * lab , char  * line , int pos)
{
	FILE * out ;
	out = fopen (outlabel, "a+");
	char ad[1000],reverse[1000];
	int k = 0;
	printf("address : %d\n",address);
	char hexad[1000];
	DtoH(address,hexad);
	fprintf(out,"%s: %sH\n",lab,hexad);
	fclose(out);
	int i = pos;
	i++;
	int n = strlen(line);
	char * newline;
	newline = malloc(sizeof(char)*n*2);
	int j =0;
	for(j = 0;j<(n-i);j++)
	{
		newline[j] = line[i+j];
	}
	newline[j] = '\0';
	firstpass(newline);
}


int firstpass(char * line)
{
	remove_comments(line);
	convert_to_upper(line);
	int i = 0;
	while(line[i] == ' '|| line[i]=='\t'){
		i++;
	}
		if (line[i]=='\0')
	{
		return 0;
	}
	char temp[20] ;
	int j =0 ;
	while (line[i] != ' ' && line[i] != ':' && line[i] != '\0' )
	{
		temp[j] = line[i];
		j++;
		i++;
	}
	temp[j]= '\0';
	if (temp[0]=='\0')
	{
		return 0;
	}
	while(line[i]==' '|| line[i]=='\t'){
		i++;
	}
	if( line[i] == ':')
	{
		label(temp,line,i);
	}
	if (line[i] != ':')
	{
		printf("%s\n",temp);
		opcode(temp ,line,i);
	}
	return 0;
}

int secondpassexecute(FILE * outputf,char * op,char * oldline , int pos )
{

	int n = strlen(oldline);
	char * line;
	line = malloc(sizeof(char)*n*2);
	int k =0;
	for( k = 0;k<(n-pos);k++)
	{
		line[k] = oldline[pos+k];
	}
	line[k]= '\0';
		
		char a[30],b[30];
		int i = 0;
		while(line[i] != ' ' && line[i] != '\t' && line[i] != '\0' & line[i] != ',' )
		{
			a[i] = line[i];
			i++;
		}
		a[i]='\0';
		while((line[i] == ' ' || line[i] == ',' || line[i] == '\t') && line[i] != '\0' )
		{
			i++;
		}
		int j = 0;
		while (line[i]!=' ' && line[i]!='\n' && line[i] != '\t' && line[i] != '\0' )
		{
			b[j] = line[i];
			j++;
			i++;
		}
		b[j] = '\0';
		char ch1[30],ch2[30];

		if (strcmp(op, "MOV") == 0|| strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0 || strcmp(op, "OR") == 0 || strcmp(op, "AND") == 0 || strcmp(op, "CMP") == 0 ){
			printop(outputf, op);
			regnum(ch1,a);
			if (strstr(b, "H") != NULL){
				hexnum(ch2,b);
				address += 4;
			}
			else if (strstr(b, "B") != NULL){
				binaryNum(ch2,b);
				address += 4;
			}
			else if (strstr(b, "D") != NULL){
				decinum(ch2,b);
				address += 4;
			}
			else{
				regnum(ch2,b);
				address += 2;
			}
			fprintf(outputf, "%s %s\n", ch1 , ch2);
		}

		else if (strcmp(op, "MUL") == 0){
			printop(outputf, op);
			regnum(ch1,"R1");
			regnum(ch2,a);
			if (strstr(b, "H") != NULL){
				hexnum(ch2,b);
				address += 4;
			}
			else if (strstr(b, "B") != NULL){
				binaryNum(ch2,b);
				address += 4;
			}
			else if (strstr(b, "D") != NULL){
				decinum(ch2,b);
				address += 4;
			}
			else{
				regnum(ch2,b);
				address += 2;
			}
			fprintf(outputf, "%s %s\n", ch1 , ch2);
		}

		else if (strcmp(op, "JMP") == 0 || strcmp(op, "JNZ") == 0){
			printop(outputf, op);
			getlabel(ch1,a);
			address += 3;
			fprintf(outputf, "%s\n", ch1 );
		}

		else if (strcmp(op, "NOT") == 0){ 
			printop(outputf, op);
			regnum(ch1,a);
			address += 2;
			fprintf(outputf, "%s\n", ch1 );
		}

		else if (strcmp(op, "HLT") == 0){
			printop(outputf, op);
			address += 1;
			fprintf(outputf, "\n");
		}

		else if (strcmp(op, "LOOP") == 0){
		
			printop(outputf, "SUB");
			fprintf(outputf,"%s %s\n","11111","00000000 00000001");
			address += 4;
			printop(outputf, "JNZ");
			address += 3;
			getlabel(ch1,a);
			fprintf(outputf, "%s\n", ch1 );
		}
}


int secondpass(FILE * outputf,char  * line )
{
	
	remove_comments(line);
	convert_to_upper(line);
	int i = 0;

	while(line[i] == ' '|| line[i]=='\t'){
		i++;
	}	
	if (line[i]=='\0')
	{
		return 0;
	}
	char temp[20] ;
	int j =0 ;
	while (line[i] != ' ' && line[i] != ':' && line[i] != '\0' )
	{
		temp[j] = line[i];
		j++;
		i++;
	}
	temp[j]= '\0';
	
	if ( temp[0]=='\0')
	{
		return 0;
	}
	while(line[i]==' '|| line[i]=='\t'){
		i++;
	}
	if( line[i] == ':')
	{
		i++;
		int n = strlen(line);
		char * newline;
		newline = malloc(sizeof(char)*n*2);
		int j = 0;
		for(j = 0;j<(n-i);j++)
		{
			newline[j] = line[i+j];
		}
		newline[j] = '\0';
		secondpass(outputf,newline);
	}
	else
	{
		printf("%s\n",temp);
		secondpassexecute(outputf,temp ,line,i);
	}
	return 0;

}

int  main()
{
	FILE * inputf, * outputf,*newfiles;
	char* line = NULL;
	size_t buflength = 0;
	int len = 0;
	int flag  = 0 ; 
	newfiles = fopen(outlabel, "w+");
	fclose(newfiles);
	newfiles = fopen(outable, "w+");
	fclose(newfiles);
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
			break;
    	}
    	else if (flag ==1 )
    	{	
    		line[len-1]= '\0';
    		firstpass(line);
			printf("%d\n",address);
    	}
    }
	address = 0;
	fclose(inputf);
	inputf = fopen(input, "r+");
	outputf =  fopen(outans, "w+");
	fprintf(outputf,"ADDRESS \tINSTRUCTION\n");
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
			break;
    	}
    	else if (flag ==1 )
    	{	
    		line[len-1]= '\0';
    		secondpass(outputf,line);
    	}
    }
	fclose(inputf);
	return 0;
}