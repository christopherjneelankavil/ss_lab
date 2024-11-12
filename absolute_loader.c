// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main() {
//     char input[10];
//     int start, length, address = 0;

//     FILE *fp1, *fp2;
//     fp1 = fopen("hello.txt", "r");
//     fp2 = fopen("output.txt", "w");

//     if (fp1 == NULL || fp2 == NULL) {
//         printf("ERROR: Unable to open file(s)\n");
//         return 0;
//     }

//     fscanf(fp1, "%s", input);
//     while (strcmp(input, "E") != 0) {
//         if (strcmp(input, "H") == 0) {
//             fscanf(fp1, "%d %d", &start, &length);
//             address = start;
//         } else if (strcmp(input, "T") == 0) {
//             fscanf(fp1, "%d", &address);
//             for (int i = 0; i < 4; i++) {
//                 fscanf(fp1, "%s", input); // Read two characters at a time
//                 fprintf(fp2, "%d\t%c %c\n", address, input[0], input[1]);
//                 address++; // Increment address after each byte
//             }
//         } else {
//             fscanf(fp1, "%s", input); // Read six characters in the else case
//             fprintf(fp2, "%d\t%c %c\n", address, input[0], input[1]);
//             fprintf(fp2, "%d\t%c %c\n", address + 1, input[2], input[3]);
//             fprintf(fp2, "%d\t%c %c\n", address + 2, input[4], input[5]);
//             address += 3; // Increment by 3 after writing three pairs
//         }
//         fscanf(fp1, "%s", input); // Read the next input record
//     }

//     fclose(fp1);
//     fclose(fp2);

//     printf("Processing completed successfully. Output written to output.txt\n");
//     return 0;
// }


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char input[10];
    FILE *fp1,*fp2;
    int start, length, address = 0;
    fp1 = fopen("hello.txt","r");
    fp2 = fopen("output.txt","w");

    if(fp1==NULL|| fp2 == NULL){
        return 0;
    }

    fscanf(fp1,"%s",input);
    while (strcmp(input,"E")!=0){
        if(strcmp(input,"H")==0){
            fscanf(fp1,"%d %d",&start,&length);
            address = start;
        }else if(strcmp(input,"T")==0){
            fscanf(fp1,"%d",&address);
            for(int i=0;i<4;i++){
                fscanf(fp1,"%s",input);
                fprintf(fp2,"%d\t%c %c",address,input[0],input[1]);
                address++;
            }
        }else{
            fprintf(fp2,"%d\t%c %c",address,input[0],input[1]);
            fprintf(fp2,"%d\t%c %c",address+1,input[2],input[3]);
            fprintf(fp2,"%d\t%c %c",address+2,input[4],input[5]);

            address+=3;
        }
        fscanf(fp1,"%s",input);
    }
    return 0;
    
}