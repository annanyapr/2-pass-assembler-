#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

FILE *op; //pointer to Op_Table file contating instructions and opcodes for current assembly code 
FILE *out; //pointer to output file containing machine level code
int k=0;
//Contains operation code(in binary) for each of the 12 instructions
struct opcode_all{
	char instruction[30];
	char opcode[30];
	int present; 
};
//contains label names and corresponding addressses
struct symbol_table{
	char label[30],address[30];
};
//prints the instructions and corresponding opcode into the machine_opcdoe file
void get_index(struct opcode_all a1[], char inst[30]){
	for(int i=0;i<12;i++){
		if(strcmp(a1[i].instruction,inst)==0){
			if(a1[i].present==0){
    			a1[i].present = 1;
    			fprintf(op, "%s %s\n",a1[i].instruction,a1[i].opcode);	
    			return ;
    		}	
    	}	
	}
}
//returns hexadecimal symbol corresponding to its decimal equivalent
char get_char(int val){
	switch(val){
		case 0: return '0';break;
		case 1: return '1';break;
		case 2: return '2';break;
		case 3: return '3';break;
		case 4: return '4';break;
		case 5: return '5';break;
		case 6: return '6';break;
		case 7: return '7';break;
		case 8: return '8';break;
		case 9: return '9';break;
		case 10: return 'A';break;
		case 11: return 'B';break;
		case 12: return 'C';break;
		case 13: return 'D';break;
		case 14: return 'E';break;
		case 15: return 'F';break;
	}
}
//converts current address in decimal to hexadecimal
void convert_to_hex(int val,char ans[30]){
	int temp=3;
	int p=temp;
	while(temp!=-1){
		int t=val%16;
		ans[temp--]=get_char(t);
		val/=16;
	}

	ans[p+2]='\0';
	ans[p+1]='H';
}
//converts current address in decimal to hexadicmal but doesnt add H in the end
void convert_to_hex2(int val,char ans[30]){
	int temp=3;
	int p=temp;
	while(temp!=-1){
		int t=val%16;
		ans[temp--]=get_char(t);
		val/=16;
	}
	ans[p+1]='\0';
}

//converts decimal register number to binary
void conv_to_bin(int reg_num,char register_ch[30]){
	int temp=4;
	int p=temp;
	while(temp!=-1){
		int t=reg_num%2;
		register_ch[temp--]=get_char(t);
		reg_num/=2;
	}

	register_ch[p+1]='\0';
}
//takes in register input and stores binary equivalent of register number
void register_number(char b[30],char register_ch[30]){
	if(b[1]>=48 && b[1]<=57){
		if(b[2]>=48 && b[2]<=57)
			conv_to_bin(((b[1]-48)*10+(b[2]-48)),register_ch);	
		else
			conv_to_bin(b[1]-48,register_ch);
	}
}
//converts hexadicmal character to its binary equivalent
void hex_to_bin(char ch,int start, char ans[30]){
	char temp[6];
	switch(ch){
		case '0': strcpy(temp,"0000");break;
		case '1': strcpy(temp,"0001");break;
		case '2': strcpy(temp,"0010");break;
		case '3': strcpy(temp,"0011");break;
		case '4': strcpy(temp,"0100");break;
		case '5': strcpy(temp,"0101");break;
		case '6': strcpy(temp,"0110");break;
		case '7': strcpy(temp,"0111");break;
		case '8': strcpy(temp,"1000");break;
		case '9': strcpy(temp,"1001");break;
		case 'A': strcpy(temp,"1010");break;
		case 'B': strcpy(temp,"1011");break;
		case 'C': strcpy(temp,"1100");break;
		case 'D': strcpy(temp,"1101");break;
		case 'E': strcpy(temp,"1110");break;
		case 'F': strcpy(temp,"1111");break;
	}
	for(int i=start;i<start+4;i++){
		ans[i]=temp[i-start];
	}
}
//converts a 16 bit hexadecimal number to its binary equivalent
void hexa_number(char b[30],char ans[30]){
	for(int i=0;i<4;i++){
		hex_to_bin(b[i],i*4,ans);
	}
	ans[16]='\0';
}

void oct_to_bin(char ch,int start, char ans[30]){
	char temp[6];
	switch(ch){
		case '0': strcpy(temp,"000");break;
		case '1': strcpy(temp,"001");break;
		case '2': strcpy(temp,"010");break;
		case '3': strcpy(temp,"011");break;
		case '4': strcpy(temp,"100");break;
		case '5': strcpy(temp,"101");break;
		case '6': strcpy(temp,"110");break;
		case '7': strcpy(temp,"111");break;
	}
	for(int i=start;i<start+3;i++){
		ans[i]=temp[i-start];
	}
}

void octa_number(char b[30],char ans[30]){
	for(int i=0;i<6;i++){
		oct_to_bin(b[i],i*3,ans);
	}
	for(int i=0;i<16;i++)
		ans[i]=ans[i+2];
	ans[16]='\0';
}

//prints current address in hexadecimal in output file
void print_addr(int curr_add){
	char ans[10];
	convert_to_hex2(curr_add,ans);
	fprintf(out, "%s\t\t",ans);
}
//prints opcode for the instruction in output file
void printop_code(char x[30], struct opcode_all a1[]){
	for(int i=0;i<12;i++){
		if(strcmp(a1[i].instruction,x)==0){
			fprintf(out, "%s ",a1[i].opcode);
			return;
		}
	}
}
//searches for label during pass 2 and stores its address in binary form
void get_label_address(char a[30],char ch1[30],struct symbol_table st[]){
	for(int i=0;i<k;i++){
		if(strcmp(st[i].label,a)==0){
			char temp[30];
			hexa_number(st[i].address,temp);
			strcpy(ch1,temp);
			return;
		}
	}
}
//cheks if input in hexadecimal or not
int check_hexa(char b[30]){
	int n=strlen(b);
	if(b[n-1]!='H')
		return 0;
	//if input is hexa it should be of length 16 bit 
	if(n>=5){
		for(int i=n-5;i<=n-1;i++)
			b[i-n+5]=b[i];
	}
	else{
		for(int i=n-1;i>=0;i--)
			b[i+5-n]=b[i];
		for(int i=0;i<5-n;i++)
			b[i]='0';
	}
	return 1;
}

int check_octa(char b[30]){
	int n=strlen(b);
	if(b[n-1]!='O')
		return 0;
	//if input is octa it should be of length 16 bit 
	if(n>=7){
		for(int i=n-7;i<=n-1;i++)
			b[i-n+7]=b[i];
	}
	else{
		for(int i=n-1;i>=0;i--)
			b[i+7-n]=b[i];
		for(int i=0;i<7-n;i++)
			b[i]='0';
	}
	return 1;
}
//checks if input is decimal or not
int check_dec(char b[30]){
	int n=strlen(b);
	if(b[n-1]!='D')
		return 0;
	b[n-1]='\0';
	return 1;
}
//checks if input is binary or not
int check_bin(char b[30]){
	int n=strlen(b);
	if(b[n-1]!='B')
		return 0;
	//if input is hexa it should be of length 16 bit
	if(n>=17){
		for(int i=n-17;i<=n-1;i++)
			b[i-n+17]=b[i];
	}
	else{
		for(int i=n-1;i>=0;i--)
			b[i+17-n]=b[i];
		for(int i=0;i<17-n;i++)
			b[i]='0';
	}
	b[16]='\0';
	return 1;
}

//converts decimal number to binary string of 16 bits
void dec_number(char b[30],char ch[30]){
	int n=strlen(b);
	int x;
	sscanf(b,"%d",&x);
	int i=15;
	while(i!=-1)
	{
		if(x%2==0)
			ch[i]='0';
		else
			ch[i]='1';
		x/=2;
		i--;
	}
	ch[16]='\0';
}
//converts a given string to its upper case
void convert_to_upper(char x[30]){
	for(int i=0;i<strlen(x);i++)
		x[i]=toupper(x[i]);
}
//removes any attached semicolon due to comments in the assembly code
void remove_semicolon(char b[30]){
	if(b[0]==';')
		return;
	for(int i=0;i<strlen(b);i++){
		if(b[i]==';'){
			b[i]='\0';
			break;
		}
	}

}

void space_after_8(char ch[30])
{
	for(int i=17;i>=9;i--)
		ch[i]=ch[i-1];
	ch[8]=' ';
}

int main(){
	FILE *fp1; //pointer to input assembly code file
	FILE *fp2; // pointer to input instruction and opcode file
			   //format of this file is instruction-whitespace-opcode in each line
	FILE *sym; // pointer to symbol Table file created
	fp1=fopen("input.asm","r");
	fp2 =fopen("opcode_machincode.txt","r");
	sym=fopen("symTable.txt","w");
	op=fopen("opTable.txt","w");
	out=fopen("output.o","w");
	fprintf(out, "ADDRESS\t\tINSTRUCTION\n");
	//input file not fount
	if(fp1 == NULL){
		printf("Input file not found");
		return 0;
	}
	//instructions to machine code file not found
	if(fp2 == NULL){
		printf("Input file for instruction-machine opcodes not found");
		return 0;
	}

	char x[30],help[30],help2;
	//structure to store all 12 instructions and their opcodes
	struct opcode_all a1[12];
	//structure to store labels and their addresses
	struct symbol_table st[100];
	int i=0;
	//copy all instructions and opcodes from file
	while (fscanf(fp2, "%s", x) == 1){
		if(i%2==0)
			strcpy(a1[i/2].instruction,x);
		else
			strcpy(a1[i/2].opcode,x);
		
		a1[i/2].present=0;
		i++;
    }

	i=0;
	int temp;
	char a[30],b[30],tem; //a nd b take input strings
	int curr_add=0; //stores current address in decimal
	char y[30];

	//**********PASS1*********//

	while (fscanf(fp1, "%s", x) == 1){
		remove_semicolon(x);
		strcpy(y,x);
		convert_to_upper(x); //convert to upper case
      	int flag=0;
		if(strcmp(x,"MOV")==0 || strcmp(x,"ADD")==0 || strcmp(x,"SUB")==0 ){
			fscanf(fp1, " %[^,]%c%s", a,&tem,b); //if cmp, and, or, read two inputs
			remove_semicolon(b); //remove semicolon if any due to comments
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			convert_to_upper(b);
			if (b[0]=='R') //if both inputs register
				curr_add+=2;
			else
				curr_add+=4;
		}
		else if(strcmp(x,"MUL")==0){
			fscanf(fp1, "%s", a); //if MUL read only one input
			remove_semicolon(a); //remove semicolons due to comments
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			if (a[0]=='R') // if input is froma register
				curr_add+=2;
			else  //if immediate addressing
				curr_add+=3;
		}
		else if(strcmp(x,"CMP")==0 || strcmp(x,"AND")==0 || strcmp(x,"OR")==0){
			fscanf(fp1, " %[^,]%c%s", a,&tem,b); //if cmp, and, or, read two inputs
			remove_semicolon(b); //remove semicolon if any due to comments
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			convert_to_upper(b);
			if (a[0]=='R' && b[0]=='R') //if both inputs register
				curr_add+=2;
			else if ((a[0]=='R' && b[0]!='R')||(a[0]!='R' && b[0]=='R')) //if one register and other immediate addressing
				curr_add+=4;
			else //if both immediate addressing
				curr_add+=5;
		}
		else if(strcmp(x,"NOT")==0){
			fscanf(fp1, "%s", a); //if NOT read only one input
			remove_semicolon(a); //remove semicolon if any due to comments
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			if (a[0]=='R') //if input is register addressed
				curr_add+=2;
			else	//if input is immediate addressing
				curr_add+=3;
		}
		else if(strcmp(x,"JMP")==0 || strcmp(x,"JNZ")==0){
			fscanf(fp1, "%s", a); //if JMP or JNZ read only one input
			remove_semicolon(a); //remvoe semicolon if any due to comments
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
				curr_add+=3;
		}
		else if(strcmp(x,"LOOP")==0){
			fscanf(fp1, "%s",a); //read label name after loop
			remove_semicolon(a); //remove semicolon if any due to commenting
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a); 
				curr_add+=7;
			get_index(a1,"JNZ"); //write commands JNZ and SUB in opcode table 
			get_index(a1,"SUB");
			flag=1;

		}
		else if(strcmp(x,"HLT")==0){
			fscanf(fp1,"%[^\n]",help); //scan for any comments in the line
			curr_add+=1;
		}
		else if(strcmp(x,"START")==0){
			fscanf(fp1,"%[^\n]",help); //scan for any comments in the line
			continue;
		}
		else if(strcmp(x,"END")==0){
			fscanf(fp1,"%[^\n]",help); //scan for any comments in the line
			break;
		}
		else if(x[0]==';'){
			fscanf(fp1,"%[^\n]",help); //ignore line if cooment present
		}
		else{ //indicates a label
			strcpy(x,y);
			for(int j=0;j<strlen(x);j++)
				if(x[j]==':')
					x[j]='\0'; //remove the semicolon

			strcpy(st[k].label,x); //copy label name
			char addr[30];
			convert_to_hex(curr_add,addr); //convert cuurent address in hexadecimal
			strcpy(st[k].address,addr);
			k++;
			fprintf(sym, "%s: %s\n",x,addr); //print the address in symbolTable.txt file
			flag=1;
		}
		if(flag==0)
			get_index(a1,x); //print the opcode for instruction in opTable.txt

    }
    fclose(fp1);
    fclose(fp2);
    fclose(sym);
    fclose(op);
    
    //**********PASS1 ENDS*********//

    curr_add=0;
    fp1=fopen("input.asm","r");

    //**********PASS2*********//

 	while (fscanf(fp1, "%s", x) == 1){
 		remove_semicolon(x);
 		strcpy(y,x);
		convert_to_upper(x); //convert to upper case
		if(strcmp(x,"MOV")==0 || strcmp(x,"ADD")==0 || strcmp(x,"SUB")==0){
			print_addr(curr_add); //print address and opcode in output file
			printop_code(x,a1);
			fscanf(fp1, " %[^,]%c%s", a,&tem,b); //if add or mov or sub, read two inputs
			remove_semicolon(b);
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			convert_to_upper(b);
			char ch1[30],ch2[30];
			register_number(a,ch1);
			if (b[0]=='R'){
				register_number(b,ch2);
				curr_add+=2;
			}
			else{
				if (check_hexa(b))
					hexa_number(b,ch2);
				if (check_bin(b))
					strcpy(ch2,b);
				if(check_dec(b))
					dec_number(b,ch2);
				if(check_octa(b))
					octa_number(b,ch2);
				space_after_8(ch2);
				curr_add+=4;
			}
			fprintf(out,"%s %s\n",ch1,ch2);
		}
		else if(strcmp(x,"MUL")==0){
			print_addr(curr_add); //print address and opcode in output file
			printop_code(x,a1);
			fscanf(fp1, "%s", a); //if MUL read only one input
			remove_semicolon(a);
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			char ch1[30],ch2[30];
			register_number("R1",ch1);
			if (a[0]=='R'){
				register_number(a,ch2);
				curr_add+=2;
			}
			else{
				if (check_hexa(a))
					hexa_number(a,ch2);
				if (check_bin(a))
					strcpy(ch2,a);
				if(check_dec(a))
					dec_number(a,ch2);
				space_after_8(ch2);
				curr_add+=3;
			}
			fprintf(out, "%s %s\n",ch1,ch2);
		}
		else if(strcmp(x,"CMP")==0 || strcmp(x,"AND")==0 || strcmp(x,"OR")==0){
			print_addr(curr_add); //print address and opcode in output file
			printop_code(x,a1);
			fscanf(fp1, " %[^,]%c%s", a,&tem,b);
			remove_semicolon(b);
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			convert_to_upper(b);
			char ch1[30],ch2[30];
			if (a[0]=='R') //if register addressing mode
				register_number(a,ch1);
			else{ //if direct addressing mode
				if (check_hexa(a)) //check for hexadecimal input
					hexa_number(a,ch1); //if true convert to binary
				if (check_bin(a)) //check for binary input
					strcpy(ch1,a); //if true output binary in output file
				if(check_dec(a)) //check for decimal input
					dec_number(a,ch1); //if true convert to binary
				if(check_octa(a))
					octa_number(a,ch1);
				space_after_8(ch1);
			}
			if (b[0]=='R')
				register_number(b,ch2);
			else{
				if (check_hexa(b)) //check for hexadecimal input
					hexa_number(b,ch2); //if true convert to binary
				if (check_bin(b)) //check for binary input
					strcpy(ch2,b); //if true output binary in output file
				if(check_dec(b)) //check for decimal input
					dec_number(b,ch2); //if true convert to binary
				if(check_octa(b))
					octa_number(b,ch2);
				space_after_8(ch2);
			}
			if (a[0]=='R' && b[0]=='R')
				curr_add+=2; 
			else if ((a[0]=='R' && b[0]!='R')||(a[0]!='R' && b[0]=='R'))
				curr_add+=4;
			else
				curr_add+=5;
			fprintf(out, "%s %s\n",ch1,ch2);
		}
		else if(strcmp(x,"NOT")==0){
			print_addr(curr_add); //print address and opcode in output file
			printop_code(x,a1);
			fscanf(fp1, "%s", a);
			remove_semicolon(a); //if NOT read only one input
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			char ch1[30];
			if (a[0]=='R'){
				register_number(a,ch1);
				curr_add+=2;
			}
			else{
				if (check_hexa(a)) //check for hexadecimal number
					hexa_number(a,ch1); //if true conveert hexa to bin
				if (check_bin(a)) //check for binary number
					strcpy(ch1,a); //if true copy binary in output
				if(check_dec(a)) //check for decimal number
					dec_number(a,ch1); //if true convert dec to bin
				if(check_octa(a))
					octa_number(a,ch1);
				space_after_8(ch1);
				curr_add+=3;
			}
			fprintf(out, "%s\n",ch1);
		}
		else if(strcmp(x,"JMP")==0 || strcmp(x,"JNZ")==0){
			print_addr(curr_add); //print address and opcode in output file
			printop_code(x,a1);
			fscanf(fp1, "%s", a); //if JMP or JNZ read only one input
			remove_semicolon(a);
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
				curr_add+=3;
			char ch1[30];
			get_label_address(a,ch1,st);
			space_after_8(ch1);
			fprintf(out, "%s\n",ch1);
		}
		else if(strcmp(x,"LOOP")==0){
			print_addr(curr_add); //print address and opcode in output file
			printop_code("SUB",a1);
			fscanf(fp1, "%s",a); //if LOOP read label name
			remove_semicolon(a);
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			convert_to_upper(a);
			curr_add+=4;
			fprintf(out,"%s %s\n","11111","00000000 00000001"); //for subtracting 1 from R31
			print_addr(curr_add);
			printop_code("JNZ",a1); //print opcode for JNZ
			curr_add+=3;
			char ch1[30];
			get_label_address(a,ch1,st); //print label address after JNZ opcode
			space_after_8(ch1);
			fprintf(out, "%s\n",ch1);
		}
		else if(strcmp(x,"HLT")==0){
			print_addr(curr_add); //print address and opcode in output file
			printop_code(x,a1);
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			curr_add+=1;
		}
		else if(strcmp(x,"START")==0){
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			continue;
		}
		else if(strcmp(x,"END")==0){
			fscanf(fp1,"%[^\n]",help); //read for any comment in the same line
			break;
		}
		else if(x[0]==';'){
			fscanf(fp1,"%[^\n]",help); //ignore line if cooment present
		}
		else{
			continue;
		}
    }
    fclose(out);
    fclose(fp1);

    //**********PASS2 ENDS*********//

	return 0;
}