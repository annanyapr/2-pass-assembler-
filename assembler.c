#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


FILE * file = fopen("")
int address = 0;


void opcode(char * str, int len){



// will write for the opcode 


}



void label(char* str , int len){

// find the label and write in the text file 

	int i = 0;
	while (str[i] == ' '){
		i++;
	}


// will write the label



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