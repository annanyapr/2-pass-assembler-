#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


char * input = "input.asm";
char * pseuopcode = "pseudo.txt";
char * op = "opcd.txt";

//FILE * file = fopen("");
int address = 0;

int bin[4];


// searches for a particular string in a file 
int search_in_file(char * fname, char* strname){
	FILE * fp;
	fp = fopen(fname, "a+");
	fseek(fp, 0, SEEK_SET);
	char* line = NULL;
	size_t len = 0;
	
	int length = 0;
	
	while((getline(&line, &len, fp)) != -1){

		if (strstr(line , strname) != NULL){
			
			fclose(fp);
			return(1);
		}
		
	}
	
	fclose(fp);
	return(0);

}

char * search_in_file2(char* fname, char* strname){  // returns the pointer to the particular string
	FILE * fp;
	fp = fopen(fname, "a+");
	fseek(fp, 0, SEEK_SET);
	char* line = NULL;
	size_t len = 0;
	while(getline(&line, &len, fp) != -1){
		if (strstr(line , strname) != NULL){
			fclose(fp)
			return strstr(line , strname);
			
		}
	}
	fclose(fp);
	return NULL;
}





int opcode(char * str){

	FILE * f;
	char opcd[5];
	int i = 0;
	while (str[i] == ' ' ){
		
		i++;

	}
	
	if (str[i] != '\0'){

		// execute thenormal routine
		
		int	j = 0; 
		while (str[i] != ' ' && str[i] != '\0'){
			opcd[j] = str[i];
			i++;
			j++;
		}
		str = str + i;
		opcd[j] = '\0';
		if (strcmp(opcd, "LOOP") == 0){
			
			opcode(" SUB H");
			opcode(" JNZ ");
			return(0);
		}

		// now we have both the opcode and the length of the opcode stored in j
		// we have a string in opcode 
		// first we will search in file
		// now we will use strcmp with all the possible opcodes to analyse the string

		if (search_in_file(pseuopcode, opcd) == 0){
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
				
				fputc(' ', f);
				fputc(' ', f);
				





				// now we need to increment the address by the proper amount // this will depend upon the opcode value + the type of inputs provided to us
				if (strcmp(opcd, "MOV") == 0){
					if (strstr(str, "H") != NULL){ // transfer the value directly to the register
						address += 4;
					}
					else if (strstr(str, "B") != NULL){
						address += 4;
					}
					else if (strstr(str, "D") != NULL){
						address += 4;
					}
					else{ // register to register
						address += 2;
					}

					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					// fputc('0', f);
					// fputc('0', f);
					// fputc('0', f);
					// fputc('0', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "ADD") == 0){
					if (strstr(str, "H") != NULL){ // transfer the value directly to the register
						address += 4;
					}
					else if (strstr(str, "B") != NULL){
						address += 4;
					}
					else if (strstr(str, "D") != NULL){
						address += 4;
					}
					else{ // register to register
						address += 2;
					}
					
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}

					// fputc('0', f);
					// fputc('0', f);
					// fputc('0', f);
					// fputc('1', f);
					fputc('\n', f);


				}

				else if (strcmp(opcd, "SUB") == 0){
					//ddress += 4;
					if (strstr(str, "H") != NULL){ // transfer the value directly to the register
						address += 4;
					}
					else if (strstr(str, "B") != NULL){
						address += 4;
					}
					else if (strstr(str, "D") != NULL){
						address += 4;
					}
					else{ // register to register
						address += 2;
					}
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					
					// fputc('0', f);
					// fputc('0', f);
					// fputc('1', f);
					// fputc('0', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "OR") == 0){
					if (strstr(str, "H") != NULL){ // transfer the value directly to the register
						address += 4;
					}
					else if (strstr(str, "B") != NULL){
						address += 4;
					}
					else if (strstr(str, "D") != NULL){
						address += 4;
					}
					else{ // register to register
						address += 2;
					}

					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					
					// fputc('0', f);
					// fputc('1', f);
					// fputc('1', f);
					// fputc('0', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "AND") == 0){
					if (strstr(str, "H") != NULL){ // transfer the value directly to the register
						address += 4;
					}
					else if (strstr(str, "B") != NULL){
						address += 4;
					}
					else if (strstr(str, "D") != NULL){
						address += 4;
					}
					else{ // register to register
						address += 2;
					}
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					
					// fputc('0', f);
					// fputc('1', f);
					// fputc('0', f);
					// fputc('1', f);
					fputc('\n', f);
					
				}

				else if (strcmp(opcd, "CMP") == 0){
					if (strstr(str, "H") != NULL){ // transfer the value directly to the register
						address += 4;
					}
					else if (strstr(str, "B") != NULL){
						address += 4;
					}
					else if (strstr(str, "D") != NULL){
						address += 4;
					}
					else{ // register to register
						address += 2;
					}
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					
					// fputc('0', f);
					// fputc('1', f);
					// fputc('0', f);
					// fputc('0', f);
					fputc('\n', f);
				}


				else if (strcmp(opcd, "MUL") == 0){
					if (strstr(str, "H") != NULL){ // transfer the value directly to the register
						address += 4;
					}
					else if (strstr(str, "B") != NULL){
						address += 4;
					}
					else if (strstr(str, "D") != NULL){
						address += 4;
					}
					else{ // register to register
						address += 2;
					}
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					
					// fputc('0', f);
					// fputc('0', f);
					// fputc('1', f);
					// fputc('1', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "JMP") == 0){
					address += 3;
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					
					// fputc('1', f);
					// fputc('0', f);
					// fputc('0', f);
					// fputc('0', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "JNZ") == 0){
					address += 3;
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					// fputc('1', f);
					// fputc('0', f);
					// fputc('1', f);
					// fputc('1', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "NOT") == 0){  // only take the register case 
					address += 2;
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					// fputc('0', f);
					// fputc('1', f);
					// fputc('1', f);
					// fputc('1', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "HLT") == 0){
					address += 1;
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					// fputc('1', f);
					// fputc('0', f);
					// fputc('1', f);
					// fputc('0', f);
					fputc('\n', f);
				}

				else if (strcmp(opcd, "LOOP") == 0){
					address += 7;
					char* start = search_in_file2(op, opcd);
					int k = 0;
					while (start[k] != '0' && start[k] != '1'){
						k++;
					}
					while (start[k] == '0' || start[k] == '1'){
						fputc(start[k], f);
					}
					// fputc('1', f);
					// fputc('0', f);
					// fputc('0', f);
					// fputc('1', f);
					fputc('\n', f);
				}

				fclose(f);


			}
		}

	}
	
	else{

		// dont execute anything 

	}

	
	return(0);


// will write for the opcode 


}



int label(char* str){

// find the label and write in the text file 
	FILE * f;
	int i = 0;
	while (str[i] == ' '){
		i++;
	}



// will write the label
	
	f = fopen("symTable.txt", "a+");

	while (str[i] != ':' &&  str[i] != '\0'){
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
	fputc(' ', f);
	fputc('\n', f);
	fclose(f);
	str = str + i;
	if (str[0] == ':'){
		str++;
	}
	// now str has been shifted to the point where str[0] points to the point which is the first character after the label 
	// now written the code for adding the label with the required address field
	opcode(str);

	return(0);


}

int func(char * str){

	// now check the first word in the string

	int i = 0;
	while(str[i] != '\0'){
		i++;
		if (str[i] == ':'){
			label(str);
			return(0);
		}
	}
	opcode(str);
	return(0);



}


int main(){

	FILE * f;
	char* linechars = NULL;
	size_t length = 0;
    ssize_t read;

    int len = 0;
	f = fopen(input, "r");
	int flag = 0;
	while ((read = getline(&linechars, &length, f)) != -1) {
        //len = strlen(linechars); // gives the length of the string array with the new line in place 
        //printf("%s %d", linechars, len);
		len = strlen(linechars);

		linechars[len-1] = '\0';

		if (strstr(linechars, "START")  != NULL || flag == 1){
			if (flag == 0){ 

				flag = 1;
				linechars = NULL;
				continue;

			}

			if (strstr(linechars, "END") != NULL)
				break;
			//flag = 1;


			// call the function giving them values 

			func(linechars);


		}

		linechars = NULL;


    }


    return(0);




}