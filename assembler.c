#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


FILE * file = fopen("");
int address = 0;

int bin[4];


// searches for a particular string in a file 
int search_in_file(char * fname, char* strname){
	FILE * fp;
	fp = fopen(fname, "r");
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	int length = 0;
	int flag = 0;
	while((read = getline(&line, &len, fp)) != -1){
		length = strlen(line);
		line[length-1] = '\0';
		if (strstr(line , strname) != NULL){
			flag = 1;
		}
	}

	fclose(fp);

	if (flag = 1){
		return(1);
	}
	else{
		return(0);
	}
}





int opcode(char * str, int len){

	
	char opcd[5];
	while (str[i] == ' ' ){
		
		i++;

	}
	
	if (str[i] != '\n'){

		// execute thenormal routine
		
		int	j = 0; 
		while (str[i] != ' '){
			opcd[j] = str[i];
			j++;
		}
		opcd[j] = '\0';

		// now we have both the opcode and the length of the opcode stored in j
		// we have a string in opcode 
		// first we will search in file
		// now we will use strcmp with all the possible opcodes to analyse the string

		if (search_in_file("opTable.txt", opcd) == 1){
			// string already exist
		}
		else{
			// string not there
			// now we will add the string
			f = fopen("opTable.txt", "a+");
			
			for(int i = 0; i < j; i++){
				fputc(opcd[i], f);
			}
			fputc(" ", f);
			fputc(" ", f);
			int temp = address;
			char c;
	
			for(int i = 0; i < 4; i++){
				bin[3-i] = temp%16;
				temp = temp / 16;

			}

	


			for (int i = 0; i < 4; i++){
				switch(bin[i]){
					case 10: c = 'A';
						break;

					case 11: c = 'B';
						break;

					case 12: c = 'C';
						break;

					case 13: c = 'D';
						break;
					
					case 14: c = 'E';
						break;
					
					case 15: c = 'F';
						break;
					
					default: c = bin[i] + '0';
						break;
				}

				fputc(c, f);
			}

			// now we need to increment the address by the proper amount // this will depend upon the opcode value + the type of inputs provided to us
			if (strcmp(opcd, "MOV") == 0){
				address += 4;
			}
			else if (strcmp(opcd, "ADD") == 0){
				address += 4;


			}
			else if (strcmp(opcd, "SUB") == 0){
				address += 4;


			}
			else if (strcmp(opcd, "OR") == 0){
				address += 2;


			}
			else if (strcmp(opcd, "AND") == 0){
				address += 2;

				
			}
			else if (strcmp(opcd, "CMP") == 0){
				address += 4;
			}
			else if (strcmp(opcd, "MUL") == 0){

			}
			else if (strcmp(opcd, "JMP") == 0){

			}
			else if (strcmp(opcd, "JNZ") == 0){

			}
			else if (strcmp(opcd, "NOT") == 0){

			}
			else if (strcmp(opcd, "HLT") == 0){

			}
			else if (strcmp(opcd, "LOOP") == 0){

			}

		}

	}
	
	else{

		// dont execute anything 

	}

	fclose(f);


// will write for the opcode 


}



void label(char* str , int len){

// find the label and write in the text file 

	int i = 0;
	while (str[i] == ' '){
		i++;
	}



// will write the label
	
	f = fopen("symTable.txt", "a+");

	while (str[i] != ' ' || str[i] != '\0'){
		fputc(str[i], f);
		i++;
	}

	fputc(' ', f);
	fputc(' ', f);
	int temp = address;
	char c;
	
	for(int i = 0; i < 4; i++){
		bin[3-i] = temp%16;
		temp = temp / 16;

	}

	


	for (int i = 0; i < 4; i++){
		switch(bin[i]){
			case 10: c = 'A';
				break;

			case 11: c = 'B';
				break;

			case 12: c = 'C';
				break;

			case 13: c = 'D';
				break;
			
			case 14: c = 'E';
				break;
			
			case 15: c = 'F';
				break;
			
			default: c = bin[i] + '0';
				break;
		}

		fputc(c, f);
	}

	fputc('H', f);
	fputc('\n', f);
	fclose(f);
	str = str + i;
	// now str has been shifted to the point where str[0] points to the point which is the first character after the label 
	// now written the code for adding the label with the required address field
	opcode(str, len);


}







int func(char * str, int len){

	// now check the first word in the string

	int i = 0;
	while(str[i] == ' '){
		i++;
	}

	while(str[i] != ' ')}{
		i++;
	}
	if (str[i-1] == ':'){
		label(str, len);
	}
	else{
		opcode(str, len);
	}


}


int main(){

	FILE * f;
	char* linechars = NULL;
	size_t length = 0;
    ssize_t read;

    int len = 0;
	f = fopen("input.asm", "r");
	int flag = 0;
	while ((read = getline(&linechars, &length, f)) != -1) {
        //len = strlen(linechars); // gives the length of the string array with the new line in place 
        //printf("%s %d", linechars, len);
		len  =strlen(linechars);

		linechars[len-1] = '\0';

		if (strstr(linechars, "START")  != NULL || flag == 1){
			if (flag == 0){ 

				flag = 1;
				continue;

			}
			//flag = 1;

			// call the function giving them values 

			func(linechars, len);


		}




    }


    return(0);




}