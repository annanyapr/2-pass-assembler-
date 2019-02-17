/*

CS244 SYSTEM PROGRAMMING
ASSIGNMENT 4(FINAL ASSIGNMENT ASSEMBLER)

-----TWO PASS ASSEMBLER-------

NAME : ARYAN AGRAWAL
ROLL NO. : 170101013


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INT_MAX 100000


int address_counter = 0;	//stores the current address of the program counter

/*array conating code of corresponding registers*/
char reg_address[32][6]={
					"00000\0",
					"00001\0",
					"00010\0",
					"00011\0",
					"00100\0",
					"00101\0",
					"00110\0",
					"00111\0",
					"01000\0",
					"01001\0",
					"01010\0",
					"01011\0",
					"01100\0",
					"01101\0",
					"01110\0",
					"01111\0",
					"10000\0",
					"10001\0",
					"10010\0",
					"10011\0",
					"10100\0",
					"10101\0",
					"10110\0",
					"10111\0",
					"11000\0",
					"11001\0",
					"11010\0",
					"11011\0",
					"11100\0",
					"11101\0",
					"11110\0",
					"11111\0"
				};

/*array to store the opcodes*/
char opcodetable[12][5];



char* hexatoBinary(char* string)
{
	/*A utility function that converts the hexadecimal string to binary

		Args: string in Hexadecimal
		Returns: string in binary

	*/
	char *binary = malloc(17);	//stores the binary string to be returned
	for (int i = 0; i < 16; ++i)
	{
		binary[i]='0';
	}
	binary[16]='\0';

	int i=strlen(string)-1;
	while(string[i]=='H' || string[i]=='\n')
		i--;

	int ind = 3;

	/*iterate character by character input hexadecimal string*/
    while (string[i])
    {
        /*convert numeric character to corresponding binary string and store in string binary*/
        switch (string[i])
        {
        case '0':
            binary[ind*4]='0';binary[ind*4+1]='0';
            binary[ind*4+2]='0';binary[ind*4+3]='0'; break;
        case '1':
            binary[ind*4]='0';binary[ind*4+1]='0';
            binary[ind*4+2]='0';binary[ind*4+3]='1'; break;
        case '2':
            binary[ind*4]='0';binary[ind*4+1]='0';
            binary[ind*4+2]='1';binary[ind*4+3]='0'; break;
        case '3':
            binary[ind*4]='0';binary[ind*4+1]='0';
            binary[ind*4+2]='1';binary[ind*4+3]='1'; break;
        case '4':
            binary[ind*4]='0';binary[ind*4+1]='1';
            binary[ind*4+2]='0';binary[ind*4+3]='0'; break;
        case '5':
            binary[ind*4]='0';binary[ind*4+1]='1';
            binary[ind*4+2]='0';binary[ind*4+3]='1'; break;
        case '6':
            binary[ind*4]='0';binary[ind*4+1]='1';
            binary[ind*4+2]='1';binary[ind*4+3]='0'; break;
        case '7':
            binary[ind*4]='0';binary[ind*4+1]='1';
            binary[ind*4+2]='1';binary[ind*4+3]='1'; break;
        case '8':
            binary[ind*4]='1';binary[ind*4+1]='0';
            binary[ind*4+2]='0';binary[ind*4+3]='0'; break;
        case '9':
            binary[ind*4]='1';binary[ind*4+1]='0';
            binary[ind*4+2]='0';binary[ind*4+3]='1'; break;
        case 'A':
            binary[ind*4]='1';binary[ind*4+1]='0';
            binary[ind*4+2]='1';binary[ind*4+3]='0'; break;
        case 'B':
            binary[ind*4]='1';binary[ind*4+1]='0';
            binary[ind*4+2]='1';binary[ind*4+3]='1'; break;
        case 'C':
            binary[ind*4]='1';binary[ind*4+1]='1';
            binary[ind*4+2]='0';binary[ind*4+3]='0'; break;
        case 'D':
            binary[ind*4]='1';binary[ind*4+1]='1';
            binary[ind*4+2]='0';binary[ind*4+3]='1'; break;
        case 'E':
            binary[ind*4]='1';binary[ind*4+1]='1';
            binary[ind*4+2]='1';binary[ind*4+3]='0'; break;
        case 'F':
            binary[ind*4]='1';binary[ind*4+1]='1';
            binary[ind*4+2]='1';binary[ind*4+3]='1'; break;
        }
        i--;
        ind--;
    }

    return binary;
}

char* decTohexa(int n)
{
	/*A utility function that converts the decimal number to hexadecimal

		Args: a decimal number
		Returns: string of hexadecimal representation of the corresponding number

	*/
	
	char *hexa = malloc(5);	//to store the corresponding hexadecimal representation of the numbers
	hexa[0]='0';
	hexa[1]='0';
	hexa[2]='0';
	hexa[3]='0';
	hexa[4]='\0';
	int ind=3;

	while(n)
	{
		int rm = n%16;
		n/=16;

		/*check the value of the remainder and store the corresponding hexadecimal form in hexa*/
		switch(rm)
		{
			case 0: hexa[ind] = '0';break;
			case 1: hexa[ind] = '1';break;
			case 2: hexa[ind] = '2';break;
			case 3: hexa[ind] = '3';break;
			case 4: hexa[ind] = '4';break;
			case 5: hexa[ind] = '5';break;
			case 6: hexa[ind] = '6';break;
			case 7: hexa[ind] = '7';break;
			case 8: hexa[ind] = '8';break;
			case 9: hexa[ind] = '9';break;
			case 10: hexa[ind] = 'A';break;
			case 11: hexa[ind] = 'B';break;
			case 12: hexa[ind] = 'C';break;
			case 13: hexa[ind] = 'D';break;
			case 14: hexa[ind] = 'E';break;
			case 15: hexa[ind] = 'F';break;
		}
		ind--;
		if(ind<0)
			break;
	}

	return hexa;
}

void address_counter_incrementer(char* line)
{
	/*function to increament tht address counter(program counter) 
		according to the input instruction
	
		args: line of the input file
		return: void 
	*/

	char* token = strtok(line, " ");
	char* start_label;	//stores the opcode of each line instruction
	
	if(strstr(line,":")!=NULL)
	{
		start_label = strtok(NULL," ");		
	}
	else
		start_label = token;

	if (start_label==NULL)
	{
		return;
	}
	
	int reg_count = 0;	/*Number OF REGISTERES INVOLVED IN OPERATION*/
	int H_count = 0;	/*Number OF Direct VALUES INVOLVED IN OPERATION*/
	
	while (token != NULL) 
	{ 		
		if(strstr(token,"R")!=NULL && strstr(token,"OR")==NULL )
			reg_count++;

		if(strstr(token,"H")!=NULL && strstr(token,"HLT")==NULL)
			H_count++; 
		
		token = strtok(NULL, " ");
	}


	/*MUL*/
	if(start_label[0]=='M' && start_label[1]=='U')
	{
		if(reg_count!=0)
			address_counter+=2;
		else
			address_counter+=4;
	}
	
	if (start_label[0]=='N')/*NOT*/
	{
		address_counter+=2;
	}
	
	if (start_label[0]=='J')/*JNZ and JMP*/
	{
		address_counter+=3;
	}
	
	if (start_label[0]=='L')/*LOOP*/
	{
		address_counter+=7;
	}
	
	if(start_label[0]=='H')/*HLT*/
	{
		address_counter++;
	}
	
	/*MOV ADD SUB CMP AND OR*/
	if((start_label[0]=='M' && start_label[1]=='O')  || start_label[0]=='A' ||start_label[0]=='S' ||
			start_label[0]=='C' ||start_label[0]=='O')
	{
		if (reg_count==2)
		{
			address_counter +=2;
		}
		else if(reg_count==1 )
		{
			if(H_count==0)
				address_counter+= 2;
			else if(H_count==1)
				address_counter+=4;
		}
		else	/*reg_count==0*/
		{
			if(H_count==2)
				address_counter+= 4;
			else if(H_count==1)
				address_counter+=2;	
		}	
	}
}

int get_register_index(char* line)
{
	/*
		A utility function to return the register index present in the given line
	*/
	if(strstr(line,"R0")!=NULL)
		return 0;
	else if(strstr(line,"R1")!=NULL)
		return 1;
	else if(strstr(line,"R2")!=NULL)
		return 2;
	else if(strstr(line,"R3")!=NULL)
		return 3;
	else if(strstr(line,"R4")!=NULL)
		return 4;
	else if(strstr(line,"R5")!=NULL)
		return 5;
	else if(strstr(line,"R6")!=NULL)
		return 6;
	else if(strstr(line,"R7")!=NULL)
		return 7;
	else if(strstr(line,"R8")!=NULL)
		return 8;
	else if(strstr(line,"R9")!=NULL)
		return 9;
	else if(strstr(line,"R10")!=NULL)
		return 10;
	else if(strstr(line,"R11")!=NULL)
		return 11;
	else if(strstr(line,"R12")!=NULL)
		return 12;
	else if(strstr(line,"R13")!=NULL)
		return 13;
	else if(strstr(line,"R14")!=NULL)
		return 14;
	else if(strstr(line,"R15")!=NULL)
		return 15;
	else if(strstr(line,"R16")!=NULL)
		return 16;
	else if(strstr(line,"R17")!=NULL)
		return 17;
	else if(strstr(line,"R18")!=NULL)
		return 18;
	else if(strstr(line,"R19")!=NULL)
		return 19;
	else if(strstr(line,"R20")!=NULL)
		return 20;
	else if(strstr(line,"R21")!=NULL)
		return 21;
	else if(strstr(line,"R22")!=NULL)
		return 22;
	else if(strstr(line,"R23")!=NULL)
		return 23;
	else if(strstr(line,"R24")!=NULL)
		return 24;
	else if(strstr(line,"R25")!=NULL)
		return 25;
	else if(strstr(line,"R26")!=NULL)
		return 26;
	else if(strstr(line,"R27")!=NULL)
		return 27;
	else if(strstr(line,"R28")!=NULL)
		return 28;
	else if(strstr(line,"R29")!=NULL)
		return 29;
	else if(strstr(line,"R30")!=NULL)
		return 30;
	else if(strstr(line,"R31")!=NULL)
		return 31;
}

void pass1(char* line,FILE* fp_symbol,FILE* fp_opcode)
{
	/* Perform the pass 1 of assembler to generate the symbol-table 
		opcode-machine code table

		args: 1.line of the input file
			  2.file pointer for symbolTable file
			  3.file pointer for opcodetable file

		return : void  

	*/

	/*---comment handeleled---*/
	int flag=0;
	for (int i = 0; i <strlen(line) ; ++i)
	{
		if(line[i]==';')
			flag=1;
		if(flag)
			line[i]='\0';
	}
	
	if(strstr(line,"END")!=NULL)
	{
		address_counter=0;			
		return;
	}
	else if(strstr(line,"START")!=NULL)
	{
		address_counter=0;
		return;
	}

	/*OPTABLE GENERATOR*/
	
	static int flag_opcode[12]={0};	//to check on the multiple occurence of the same opcode

	if(strstr(line,"MOV")!=NULL && flag_opcode[0]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "MOV", opcodetable[0]);
		flag_opcode[0]++;
	}
	if(strstr(line,"ADD")!=NULL && flag_opcode[1]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "ADD", opcodetable[1]);
		flag_opcode[1]++;
	}
	if((strstr(line,"SUB")!=NULL || strstr(line,"LOOP")!=NULL) && flag_opcode[2]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "SUB",opcodetable[2]);
		flag_opcode[2]++;
	}
	if(strstr(line,"MUL")!=NULL && flag_opcode[3]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "MUL", opcodetable[3]);
		flag_opcode[3]++;
	}
	if(strstr(line,"CMP")!=NULL  && flag_opcode[4]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "CMP", opcodetable[4]);
		flag_opcode[4]++;
	}
	if(strstr(line,"AND")!=NULL  && flag_opcode[5]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "AND", opcodetable[5]);
		flag_opcode[5]++;
	}
	if(strstr(line,"OR")!=NULL  && flag_opcode[6]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "OR", opcodetable[6]);
		flag_opcode[6]++;
	}		
	if(strstr(line,"NOT")!=NULL  && flag_opcode[7]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "NOT", opcodetable[7]);
		flag_opcode[7]++;
	}
	if(strstr(line,"JMP")!=NULL && flag_opcode[8]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "JMP", opcodetable[8]);
		flag_opcode[8]++;
	}
	if(strstr(line,"HLT")!=NULL  && flag_opcode[10]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "HLT", opcodetable[10]);
		flag_opcode[10]++;
	}
	if((strstr(line,"JNZ")!=NULL || strstr(line,"LOOP")!=NULL) && flag_opcode[11]==0)
	{
		fprintf(fp_opcode, "%s\t%s\n", "JNZ", opcodetable[11]);
		flag_opcode[11]++;
	}

	/*symbol table generator*/
	if (strstr(line,":")!=NULL)
	{
		/*if line contains a symbol*/
		int ind=0;

		/*then get the label name*/
		for (int i = 0; i < strlen(line); ++i)
		{				
			if (line[i]==':')
			{
				break;
			}
			ind++;
		}
		char str[ind+2];	//stores the label name
		strncpy(str, line, ind+1);
		str[ind+1]='\0';
		
		/*print in the symbolTable file the <label,adresss> pair*/
		fprintf(fp_symbol, "%s ", str);
		fprintf(fp_symbol, "%sH\n",decTohexa(address_counter));			
	}

	/*increament the program counter*/
	address_counter_incrementer(line);
		
}

void pass2(char *line, FILE * fp_output)
{
	/*Performs the pass2 of two pass assembler and generates the object file output.o 
		which contains the final machine code 
		
		Args: 1. line of the input file
			  2. file pointer of the output file

		Return: Void
	
	*/

	/*----comment handeleled----*/
	int flag=0;
	for (int i = 0; i <strlen(line) ; ++i)
	{
		if(line[i]==';')
			flag=1;
		if(flag)
			line[i]='\0';
	}

	if(strstr(line,"END")!=NULL)
	{
		/*if line conatins END then its the end of the program*/
		address_counter=0;			
		return;
	}
	else if(strstr(line,"START")!=NULL)
	{
		address_counter=0;
		return;
	}
	
	int reg_present[2] = { 0 };	//to store the register no. that are involved in the opcode
	


	char* token = strtok(line, " ");
	char* start_label;	//stores the opcode of each line instruction
	
		
	if(strstr(line,":")!=NULL)
	{
		start_label = strtok(NULL," ");
	}
	else
		start_label = token;

	int reg_count = 0;	/*Number OF REGISTERES INVOLVED IN OPERATION*/
	int H_count = 0;	/*Number OF Direct VALUES INVOLVED IN OPERATION*/
	char *direct[2];	/*stores the direct values if present in the opcode*/
	char* label = NULL;	/*stores the label if present in the current line*/

	/*reading line word by word after start label*/
	while (token != NULL) 
	{ 
		
		if(strstr(token,"R")!=NULL && strstr(token,"OR")==NULL)
		{
			/*if word contains Register then check which 
				register is this and store the register no.*/
			reg_present[reg_count]=get_register_index(token);			
			reg_count++;

			/*if no space between two registers then that is a syntax error */
			if(strstr(token,",")!=NULL && strstr(token,", ")==NULL)
			{
				/*SHOW SYNTAX ERROR*/
			}
		}

		if(strstr(token,"H")!=NULL && strstr(token,"HLT")==NULL)
		{
			/*if word contains H or direct value then store that value*/
			if(strstr(token,",")!=NULL)
				direct[H_count]=strtok(token,",");
			else
				direct[H_count]=token;
			H_count++;
		}
		else
		{	
			/*if word is not register nor a direct value then it must be a label so store it */
			label=token;
		} 
		token = strtok(NULL, " ");
	}

	/*Print instruction in the output.o file according to the start label(opcode)*/

	/*---------------MOV----------------*/

	if (!strcmp(start_label,"MOV") || (start_label[0]=='M' && start_label[1]=='O'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter));	//address of the instruction
		fprintf(fp_output, "%s ",opcodetable[0]);	//opcode

		if (reg_count==2)
		{
			/*if reg_count==2 then two registers are involved so print there address*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],reg_address[reg_present[1]]);
		}
		else if(reg_count==1 )
		{
			/*else if one register and one immediate addressing is 
				present then print the corresponding binary code*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],hexatoBinary(direct[0]));
		}
		
		/*increament the address counter correspondingly*/
		if (reg_count==2)
			{
				address_counter +=2;
			}
			else if(reg_count==1 )
			{
				if(H_count==0)
					address_counter+= 2;
				else if(H_count==1)
					address_counter+=4;
			}
			else	/*reg_count==0*/
			{
				if(H_count==2)
					address_counter+= 4;
				else if(H_count==1)
					address_counter+=2;	
			}		
		
	}

	/*-----------------ADD---------------------*/
	if (!strcmp(start_label,"ADD") || (start_label[0]=='A' && start_label[1]=='D'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[1]); //opcode
		if (reg_count==2)
		{
			/*if reg_count==2 then two registers are involved so print there address*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],reg_address[reg_present[1]]);
		}
		else if(reg_count==1 )
		{
			/*else if one register and one immediate addressing is 
				present then print the corresponding binary code*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],hexatoBinary(direct[0]));
		}

		/*increament the address counter correspondingly*/
		if (reg_count==2)
			{
				address_counter +=2;
			}
			else if(reg_count==1 )
			{
				if(H_count==0)
					address_counter+= 2;
				else if(H_count==1)
					address_counter+=4;
			}
			else	/*reg_count==0*/
			{
				if(H_count==2)
					address_counter+= 4;
				else if(H_count==1)
					address_counter+=2;	
			}
				
		
	}

	/*--------------------SUB-------------------------*/
	if (!strcmp(start_label,"SUB") || (start_label[0]=='S' && start_label[1]=='U'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[2]); //opcode

		if (reg_count==2)
		{
			/*if reg_count==2 then two registers are involved so print there address*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],reg_address[reg_present[1]]);
		}
		else if(reg_count==1 )
		{
			/*else if one register and one immediate addressing is 
				present then print the corresponding binary code*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],hexatoBinary(direct[0]));
		}
		
		/*increament the address counter correspondingly*/
		if (reg_count==2)
			{
				address_counter +=2;
			}
			else if(reg_count==1 )
			{
				if(H_count==0)
					address_counter+= 2;
				else if(H_count==1)
					address_counter+=4;
			}
			else	/*reg_count==0*/
			{
				if(H_count==2)
					address_counter+= 4;
				else if(H_count==1)
					address_counter+=2;	
			}		
		
	}

	/*--------------------MUL---------------------------*/
	if (!strcmp(start_label,"MUL") || (start_label[0]=='M' && start_label[1]=='U'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[3]); //opcode
		if (reg_count==1)
		{
			fprintf(fp_output, "%s %s\n",reg_address[1],reg_address[reg_present[0]]);
		}
		else if(H_count==1 )
		{
			fprintf(fp_output, "%s %s\n",reg_address[1],hexatoBinary(direct[0]));
		}

		/*increament the address counter correspondingly*/
		if(reg_count!=0)
			address_counter+=2;
		else
			address_counter+=4;		
	}

	/*-------------------CMP----------------------*/
	if (!strcmp(start_label,"CMP") || (start_label[0]=='C' && start_label[1]=='M'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[4]); //opcode
		if (reg_count==2)
		{
			/*if reg_count==2 then two registers are involved so print there address*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],reg_address[reg_present[1]]);
		}
		else if(reg_count==1 )
		{
			/*else if one register and one immediate addressing is 
				present then print the corresponding binary code*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],hexatoBinary(direct[0]));
		}

		/*increament the address counter correspondingly*/
		if (reg_count==2)
		{
			address_counter +=2;
		}
		else if(reg_count==1 )
		{
			if(H_count==0)
				address_counter+= 2;
			else if(H_count==1)
				address_counter+=4;
		}
		else	/*reg_count==0*/
		{
			if(H_count==2)
				address_counter+= 4;
			else if(H_count==1)
				address_counter+=2;	
		}
	}

	/*-----------------AND-----------------*/
	if (!strcmp(start_label,"AND") || (start_label[0]=='A' && start_label[1]=='N'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[5]); //opcode
		if (reg_count==2)
		{
			/*if reg_count==2 then two registers are involved so print there address*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],reg_address[reg_present[1]]);
		}
		else if(reg_count==1 )
		{
			/*else if one register and one immediate addressing is 
				present then print the corresponding binary code*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],hexatoBinary(direct[0]));
		}

		/*increament the address counter correspondingly*/
		if (reg_count==2)
			{
				address_counter +=2;
			}
			else if(reg_count==1 )
			{
				if(H_count==0)
					address_counter+= 2;
				else if(H_count==1)
					address_counter+=4;
			}
			else	/*reg_count==0*/
			{
				if(H_count==2)
					address_counter+= 4;
				else if(H_count==1)
					address_counter+=2;	
			}
	}

	/*------------------------OR----------------*/
	if (!strcmp(start_label,"OR") || (start_label[0]=='O' && start_label[1]=='R'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[6]); //opcode
		
		if (reg_count==2)
		{
			/*if reg_count==2 then two registers are involved so print there address*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],reg_address[reg_present[1]]);
		}
		else if(reg_count==1 )
		{
			/*else if one register and one immediate addressing is 
				present then print the corresponding binary code*/
			fprintf(fp_output, "%s %s\n",reg_address[reg_present[0]],hexatoBinary(direct[0]));
		}

		/*increament the address counter correspondingly*/
		if (reg_count==2)
		{
			address_counter +=2;
		}
		else if(reg_count==1 )
		{
			if(H_count==0)
				address_counter+= 2;
			else if(H_count==1)
				address_counter+=4;
		}
		else	/*reg_count==0*/
		{
			if(H_count==2)
				address_counter+= 4;
			else if(H_count==1)
				address_counter+=2;	
		}
	}

	/*-------------------NOT---------------------*/
	if (!strcmp(start_label,"NOT")|| (start_label[0]=='N' && start_label[1]=='O'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[7]); //opcode
		if (reg_count==1)
		{
			fprintf(fp_output, "%s\n",reg_address[reg_present[0]]);
		}

		/*increament the address counter correspondingly*/
		address_counter+=2;
	}

	/*------------------------JMP---------------*/
	if (!strcmp(start_label,"JMP") || (start_label[0]=='J' && start_label[1]=='M'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter));
		fprintf(fp_output, "%s ",opcodetable[8]); //opcode
		
		if(label!=NULL)
		{
			int flag1=0;
			char labelAddress[5];
			labelAddress[4]='\0';
			
			
			char* truncated = strtok(label,"\n");
			FILE* symTable;
			symTable = fopen("symTable.txt","r");
			char buffer[INT_MAX];
			while(fgets(buffer, INT_MAX,symTable))
			{
				char* token = strtok(buffer," ");
				if(strstr(token,label)!=NULL)
				{
					flag1=1;
					char* temp = strtok(NULL," ");
					
					for (int i = 0; i < strlen(temp)-2; ++i)
					{
						
						labelAddress[i]=temp[i];
					}
				}
			}
			fclose(symTable);
			if(flag1)
			{
				fprintf(fp_output, "%s\n",hexatoBinary(labelAddress));
			}
			else
			{
				/*ERROR*/
			}
		}

		/*increament the address counter correspondingly*/
		address_counter+=3;
	}

	/*------------------------LOOP-----------------------*/
	if (!strcmp(start_label,"LOOP") || (start_label[0]=='L' && start_label[1]=='O'))
	{
		char labelAddress[5];
		labelAddress[4]='\0';
		
		if(label!=NULL)
		{
			int flag1=0;			
			
			char* truncated = strtok(label,"\n");
			FILE* symTable;
			symTable = fopen("symTable.txt","r");
			char buffer[INT_MAX];
			while(fgets(buffer, INT_MAX,symTable))
			{
				char* token = strtok(buffer," ");
				if(strstr(token,label)!=NULL)
				{
					flag1=1;
					char* temp = strtok(NULL," ");
					
					for (int i = 0; i < strlen(temp)-2; ++i)
					{
						
						labelAddress[i]=temp[i];
					}
				}

			}

			fclose(symTable);
			if(!flag1)
			{
				/*SYNTAX ERROR IN PROGRAM GIVE WARNING MESSEAGE*/
			}

		}
		else
		{
			/*SYNTAX ERROR IN PROGRAM GIVE WARNING MESSEAGE*/
		}

		fprintf(fp_output, "%s\t%s %s %s\n",decTohexa(address_counter),opcodetable[2], 
				reg_address[31], hexatoBinary("0001") );
		/*increament the address counter correspondingly*/
		address_counter+=4;

		fprintf(fp_output, "%s\t%s %s\n",decTohexa(address_counter),opcodetable[11], hexatoBinary(labelAddress));
		/*increament the address counter correspondingly*/
		address_counter+=3;
	}

	

	/*--------------------------HLT-------------------------*/
	if (start_label[0]=='H' || !strcmp(start_label,"HLT"))
	{
		
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s\n",opcodetable[10]); //opcode

		/*increament the address counter correspondingly*/
		address_counter++;
	}

	/*----------------------JNZ------------------------------*/
	if (!strcmp(start_label,"JNZ") || (start_label[0]=='J' && start_label[1]=='N'))
	{
		fprintf(fp_output, "%s\t",decTohexa(address_counter)); //address of the instruction
		fprintf(fp_output, "%s ",opcodetable[11]); //opcode
		
		if(label!=NULL)
		{
			int flag1=0;
			char labelAddress[5];
			labelAddress[4]='\0';
						
			char* truncated = strtok(label,"\n");
			FILE* symTable;
			symTable = fopen("symTable.txt","r");
			char buffer[INT_MAX];
			while(fgets(buffer, INT_MAX,symTable))
			{
				char* token = strtok(buffer," ");
				if(strstr(token,label)!=NULL)
				{
					flag1=1;
					char* temp = strtok(NULL," ");
					
					for (int i = 0; i < strlen(temp)-2; ++i)
					{
						
						labelAddress[i]=temp[i];
					}
				}
			}
			fclose(symTable);
			if(flag1)
			{
				fprintf(fp_output, "%s\n",hexatoBinary(labelAddress));
			}
			else
			{
				/*SYNTAX ERROR IN PROGRAM GIVE WARNING MESSEAGE*/
			}
		}

		/*increament the address counter correspondingly*/
		address_counter+=3;
	}

}

void read_opcodes(char* filename)
{
	FILE* fp;
	fp = fopen(filename,"r");
	char buffer[INT_MAX];
	while(fgets(buffer, INT_MAX,fp))
	{
		char* token = strtok(buffer," ");
		int ind=0;
		if(!strcmp(token,"MOV"))
			ind=0;
		if(!strcmp(token,"ADD"))
			ind=1;
		if(!strcmp(token,"SUB"))
			ind=2;
		if(!strcmp(token,"MUL"))
			ind=3;
		if(!strcmp(token,"CMP"))
			ind=4;
		if(!strcmp(token,"AND"))
			ind=5;
		if(!strcmp(token,"OR"))
			ind=6;
		if(!strcmp(token,"NOT"))
			ind=7;
		if(!strcmp(token,"JMP"))
			ind=8;
		if(!strcmp(token,"LOOP"))
			ind=9;
		if(!strcmp(token,"HLT"))
			ind=10;
		if(!strcmp(token,"JNZ"))
			ind=11;

		char* temp = strtok(NULL," ");
		if(temp==NULL)
			continue;
		for (int i = 0; i < strlen(temp); ++i)
		{
			opcodetable[ind][i]=temp[i];
		}
		opcodetable[ind][4]='\0';
	}
	fclose(fp);
}

int main()
{
	 FILE * fp;

    char * line=NULL;
    size_t len = 0;
    int read;


    read_opcodes("opcode.txt");	//for reading the opcodes

    /*-------CALLING PASS1 FUNCTION--------*/
    
    FILE * fp_symbol,*fp_opcode;
	fp_symbol = fopen("symTable.txt","w+");
	fp_opcode = fopen("opTable.txt","w+");
    fp = fopen("input.asm","r");    
    while ((read = getline(&line, &len, fp)) != -1) {
    
    /*to handle the lowercase letter and convert into uppercase*/
    	for (int i = 0; i < strlen(line); ++i)
    	{
    		line[i]=toupper(line[i]);
    	}
       pass1(line,fp_symbol ,fp_opcode);        
    }
    
    fclose(fp);
    fclose(fp_opcode);
	fclose(fp_symbol);
    
    if (line)
        free(line);

    /*------CALLING PASS2 FUNCTION----------*/
    address_counter=0;
    line=NULL;
    FILE *fp_output;
    fp_output = fopen("output.o","w+");
    fp = fopen("input.asm","r");    
    fprintf(fp_output, "%s\t%s\n","ADDRESS","INSTRUCTION" );
    while ((read = getline(&line, &len, fp)) != -1) {

    /*to handle the lowercase letter and convert into uppercase*/
       for (int i = 0; i < strlen(line); ++i)
    	{
    		line[i]=toupper(line[i]);
    	}
       pass2(line,fp_output);        
    }
    fclose(fp);
    if (line)
        free(line);

	return 0;
}
