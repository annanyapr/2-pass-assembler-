#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


char * input = "input.asm";
//char * pseuopcode = "pseudo.txt";
char * op = "opcd.txt";

//FILE * file = fopen("");
int address = 0;



int convertoupper(char * str){
	for (int i = 0; i < strlen(str); i++){
		toupper(str[i]);
	}

	return(0);
}


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
		int length = strlen(line) -1;
		line[length] = '\0';
		if (strstr(line , strname) != NULL){
			fclose(fp);
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

		//if (search_in_file(pseuopcode, opcd) == 0){
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
				

				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "ADD") == 0){
								
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}

				
				fputc('\n', f);


			}

			else if (strcmp(opcd, "SUB") == 0){
				//ddress += 4;
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "OR") == 0){
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "AND") == 0){
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				
				fputc('\n', f);
				
			}

			else if (strcmp(opcd, "CMP") == 0){
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				
				fputc('\n', f);
			}


			else if (strcmp(opcd, "MUL") == 0){
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "JMP") == 0){
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "JNZ") == 0){
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "NOT") == 0){  // only take the register case 
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "HLT") == 0){
			
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;				
				}
				
				fputc('\n', f);
			}

			else if (strcmp(opcd, "LOOP") == 0){
				
				char* start = search_in_file2(op, opcd);
				int k = 0;
				while (start[k] != '0' && start[k] != '1'){
					k++;
				}
				while (start[k] == '0' || start[k] == '1'){
					fputc(start[k], f);
					k++;
				}
				
				fputc('\n', f);
			}

			fclose(f);


		}

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
			
		}

		else if (strcmp(opcd, "JMP") == 0){
			address += 3;
			
		}

		else if (strcmp(opcd, "JNZ") == 0){
			address += 3;
			
		}

		else if (strcmp(opcd, "NOT") == 0){  // only take the register case 
			address += 2;
			
		}

		else if (strcmp(opcd, "HLT") == 0){
			address += 1;
			
		}

		else if (strcmp(opcd, "LOOP") == 0){
			address += 7;
			}
		//}

	}
	
	else{

		// dont execute anything 

	}

	
	return(0);


// will write for the opcode 


}







int label(char* str){

// find the label and write in the text file 
	int hex[4];
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
		hex[3-i] = temp%16;
		temp = temp / 16;

	}

	


	for (int i = 0; i < 4; i++){
		switch(hex[i]){
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
			
			default: c = hex[i] + '0';
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


// char* concat(const char *s1, const char *s2)
// {
//     char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
//     // in real code you would check for errors in malloc here
//     strcpy(result, s1);
//     strcat(result, s2);
//     return result;
// }

int pass1(char * str){

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

int address2 = 0;



char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int pass2(char* str);


int filewrite(char* str){

	int i = 0;
	while (str[i] == ' '){
		i++;
	}
	if (str[i] == '\0'){
		return(0);
	}

	char opcd[5];
	int j = 0;

	while (str[i] != ' '){
		opcd[j] = str[i];
		i++;
		j++;
	}
	// now i is immediately after the opcode
	opcd[j] = '\0';

	
	

	FILE * f;
	f = fopen("output.o", "a+");



	if (strcmp(opcd, "LOOP") != 0){
		
		int hex[4];
		int temp = address2;
		char c;
		
		for(int i = 0; i < 4; i++){
			hex[3-i] = temp%16;
			temp = temp / 16;

		}

		


		for (int i = 0; i < 4; i++){
			switch(hex[i]){
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
				
				default: c = hex[i] + '0';
					break;
			}

			fputc(c, f);
		}

		fputc('H', f);
		fputc(' ', f);
		fputc(' ', f);


		char* str1 = search_in_file2("opTable.txt" , opcd);
		if (str1 != NULL){
		
			for (int k = 0; k < 4; k++){
				fputc(str1[j+k+2], f);
			}
			fputc(' ', f);
		}

	}


	
	
	

	// now use the loop again to scan through the next parts 
	if (strcmp(opcd, "AND") == 0 || strcmp(opcd, "OR") == 0 || strcmp(opcd, "MOV") == 0 || strcmp(opcd, "SUB") == 0 || strcmp(opcd, "ADD") == 0 || strcmp(opcd, "CMP") == 0){
		while(str[i] != 'R'){
			i++;
		}
		i++;
		int arr[5]; 
		// now i is positioned at the register number 
		if (str[i+1] == ' ' || str[i+1] == ','){
			// only singlr digit value 
			int a = str[i] - '0';
			
			for (int i = 0; i < 5; i++){
				arr[4-i] = a % 2;
				a = a /2;
			}
			i += 1;
		}
		else if (str[i+2] == ' ' || str[i+2] == ','){
			// double digit value
			int a = (str[i]- '0')* 10 + (str[i+1] - '0');
			for (int i = 0; i < 5; i++){
				arr[4-i] = a % 2;
				a = a /2;
			}
			i += 2;

		}

		for (int i = 0 ; i < 5; i++){
			fputc(arr[i] + '0', f);
		}

		fputc(' ', f);
		while (str[i] == ' '|| str[i] == ',' ){
			i++;
		}
		// now you are either on a number or a letter in case of the register
		int num = 0;
		if (strstr(str+i, "H") != NULL){
			// you have a hexa value in front of you
			int temp = 0;
			while(str[i] != 'H'){
				temp *= 16;
				switch(str[i]){
					case 'A': temp += 10;
						break;

					case 'B': temp += 11;
						break;

					case 'C': temp += 12;
						break;

					case 'D': temp += 13;
						break;
					
					case 'E': temp += 14;
						break;
					
					case 'F': temp += 15;
						break;
					
					default: temp += str[i] - '0';
						break;
		
				}
				i++;

			}

			int numb[16];
			for (int i = 0; i < 16; i++){
				numb[15-i] = temp % 2;
				temp = temp /  2;
			}	 
			// now place the values in the file 
			for (int i = 0; i < 16; i++){
				fputc(numb[i] + '0', f);
			}

			
			fputc(' ', f);
			fputc('\n', f);
			address2 += 4;
		}
		else if (strstr(str+i, "D") != NULL){
			// you have a Decimal value in front of you

			int temp = 0 ;
			int numb[16];
			while (str[i] != 'D'){
				temp *= 10;
				temp += str[i] - '0';
				i++;
			}
			

			for (int i = 0; i < 16; i++){
				numb[15-i] = temp % 2;
				temp = temp /  2;
			}	 
			// now place the values in the file 
			for (int i = 0; i < 16; i++){
				fputc(numb[i] + '0', f);
			}

			
			fputc(' ', f);
			fputc('\n', f);
			address2 += 4;

		}
		else if (strstr(str+i, "B") != NULL ){
			// you have a decimal value in front of you

			int temp = 0 ;
			int numb[16];
			while (str[i] != 'B'){
				temp *= 2;
				temp += str[i] - '0';
				i++;
			}
			

			for (int i = 0; i < 16; i++){
				numb[15-i] = temp % 2;
				temp = temp /  2;
			}	 
			// now place the values in the file 
			for (int i = 0; i < 16; i++){
				fputc(numb[i] + '0', f);
			}

			fputc(' ', f);
			fputc('\n', f);
			address2 += 4;


		}
		else{
			i++; // now we have jumped to the numerical value on the register

			int arr[5] ;
			// now i is positioned at the register number 
			if (str[i+1] == ' ' || str[i+1] == ','){
				// only singlr digit value 
				int a = str[i] - '0';
				
				for (int i = 0; i < 5; i++){
					arr[4-i] = a % 2;
					a = a /2;
				}
				i += 1;
			}
			else if (str[i+2] == ' ' || str[i+2] == ','){
				// double digit value
				int a = (str[i]- '0')* 10 + (str[i+1] - '0');
				for (int i = 0; i < 5; i++){
					arr[4-i] = a % 2;
					a = a /2;
				}
				i += 2;

			}

			for (int i = 0 ; i < 5; i++){
				fputc(arr[i] + '0', f);
			}
			fputc(' ', f);
			fputc('\n', f);
			address2 += 2;


		}

	}
	else if (strcmp(opcd, "NOT") == 0 || strcmp(opcd, "MUL") == 0 ){
		if (strcmp(opcd, "MUL") == 0){
			fputc('0', f);
			fputc('0', f);
			fputc('0', f);
			fputc('0', f);
			fputc('1', f);
			fputc(' ', f);
		}

		while(str[i] != 'R'){
				i++;
			}
		i++;
		int arr[5] ;
		// now i is positioned at the register number 
		if (str[i+1] == ' ' || str[i+1] == ','){
			// only singlr digit value 
			int a = str[i] - '0';
			
			for (int i = 0; i < 5; i++){
				arr[4-i] = a % 2;
				a = a /2;
			}
			i += 1;
		}
		else if (str[i+2] == ' ' || str[i+2] == ','){
			// double digit value
			int a = (str[i]- '0')* 10 + (str[i+1] - '0');
			for (int i = 0; i < 5; i++){
				arr[4-i] = a % 2;
				a = a /2;
			}
			i += 2;

		}

		for (int i = 0 ; i < 5; i++){
			fputc(arr[i] + '0', f);
		}
		address2 += 2;
		fputc(' ', f);
		fputc('\n', f);

	}
	else if (strcmp(opcd, "HLT") == 0){
		fputc('\n', f);
		address2 += 1;
	}
	else{
		if (strcmp(opcd, "LOOP") == 0){
			// call itself by using two strings
			pass2(" SUB R31, 0001H ");
			char * loop1 = " JNZ ";
			// NOW CALL WITH THE JNZ command with the label in the front
			while(str[i] == ' '){
				i++;
			}
			// while(str[i] != ' '){
			// 	concat(loop1, str + i); // now loop1 holds the concatenated string
			// }
			pass2(concat(loop1, str + i));
			fclose(f);
			return(0);
		

		}
		else{
			
			while (str[i] == ' '){
				i++;
			}

			int t = i;
			while(str[t] != ' ' && str[t] != '\0'){
				t++;
			}
			str[t] = '\0';

			char* lab = search_in_file2("symTable.txt", str + i);

			int q = 0;
			while(lab[q] != ' '){
				q++;
			}
			while(lab[q] == ' '){
				q++;
			}

			// now you are at the hexadecimal value



			int temp = 0;
			while(lab[q] != 'H'){
				temp *= 16;
				switch(lab[q]){
					case 'A': temp += 10;
						break;

					case 'B': temp += 11;
						break;

					case 'C': temp += 12;
						break;

					case 'D': temp += 13;
						break;
					
					case 'E': temp += 14;
						break;
					
					case 'F': temp += 15;
						break;
					
					default: temp += lab[q] - '0';
						break;
		
				}
				q++;

			}


			int numb[16];
			for (int i = 0; i < 16; i++){
				numb[15-i] = temp % 2;
				temp = temp /  2;
			}	 
			// now place the values in the file 
			for (int i = 0; i < 16; i++){
				fputc(numb[i] + '0', f);
			}
			address2 += 3;
			fputc(' ', f);
			fputc('\n', f);

		}
	}

	fclose(f);



}


int pass2(char* str){


	// read line by line On one side there will be regular opcdodes like add and subtract
	// On the other side there will be JMP LOOP JNZ
	// first check if the line has a label
	int flag = 0; 
	for (int i = 0; i < strlen(str); i++){
		if (str[i] == ':'){
			flag = 1;
		}
	}
	
	if (flag == 1){
		// contains a label;
		int i = 0;
		while (str[i] != ':'){
			i++;
		}
		str = str + i + 1;
		filewrite(str);


	}
	else{
		filewrite(str);

	}


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
		for (int i = 0; i < len; i++){
			if (linechars[i] == ';'){
				linechars[i] = '\0';
			}
		}

		if (strstr(linechars, "START")  != NULL || flag == 1){
			if (flag == 0){ 

				flag = 1;
				linechars = NULL;
				continue;

			}

			if (strstr(linechars, "END") != NULL)
				break;
			


			// call the function giving them values 
			// convert a string to upper
			// convertoupper(linechars);
			//strupr(linechars);
			pass1(linechars);


		}

		linechars = NULL;


    }

    linechars = NULL;
    fclose(f);
    f = fopen(input, "r");
    flag = 0;

	while ((read = getline(&linechars, &length, f)) != -1) {
        //len = strlen(linechars); // gives the length of the string array with the new line in place 
        //printf("%s %d", linechars, len);
		len = strlen(linechars);

		linechars[len-1] = '\0';
		for (int i = 0; i < len; i++){
			if (linechars[i] == ';'){
				linechars[i] = '\0';
			}
		}

		if (strstr(linechars, "START")  != NULL || flag == 1){
			if (flag == 0){ 

				flag = 1;
				linechars = NULL;
				continue;

			}

			if (strstr(linechars, "END") != NULL)
				break;
			
			// call the function giving them values 
			// convert a string to upper
			//convertoupper(linechars);
			//strupr(linechars);
			pass2(linechars);


		}

		linechars = NULL;


    }








    return(0);




}