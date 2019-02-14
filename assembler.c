// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// struct optab
// {
//     char   code[12],objcode[12];
// }myoptab[12]={
//                    {"MOV","0000"},
//                    {"ADD","0001"},
//                    {"SUB","0010"},
//                    {"MUL","0011"},
//                    {"CMP","0100"},
//                    {"AND","0101"},
//                    {"OR","0110"},
//                    {"NOT","0111"},
//                    {"JMP","1000"},
//                    {"LOOP","1001"},
//                    {"HLT","1010"},
//                    {"JNZ","1011"},
//              };

// //bool code_started = false;
// void pass1(char* line)
// {
// 	// if(!code_started)
// 	// {
// 	// 	for (int i = 0; line[i]!='\n'; ++i)
// 	// 	{
// 	// 		if (/* condition */)
// 	// 		{
// 	// 			/* code */
// 	// 		}
// 	// 	}
// 	// }
// }
// int main()
// {
// 	 FILE * fp;
//     char * line=NULL;
//     size_t len = 0;
//     int read;

//     fp = fopen("input.asm","r");
    
//     while ((read = getline(&line, &len, fp)) != -1) {
//         pass1(line);
//     }

//     fclose(fp);
//     if (line)
//         free(line);
// 	return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    int a=54325;
    char buffer[20];
    //itoa(a,buffer,2);   // here 2 means binary
    snprintf (buffer, sizeof(buffer), "%d",a);
    printf("Binary value = %s\n", buffer);
 	
    
    return 0;
}