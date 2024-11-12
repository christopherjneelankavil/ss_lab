#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char opcode[10], operand[10], label[10], code[10], mnemonic[10], symbol[10];
    int locctr, start, length, address;

    FILE *fp1, *fp2, *fp3, *fp4, *fp5;

    fp1 = fopen("input.txt", "r");      // Input file
    fp2 = fopen("optab.txt", "r");      // Opcode table
    fp3 = fopen("symtab.txt", "r");     // Symbol table
    fp4 = fopen("intermediate.txt", "r");        // Intermediate output from Pass 1
    fp5 = fopen("object.txt", "w");     // Object code output

    fscanf(fp1,"%s %s %s",label,operand,opcode);

    if(strcmp(opcode,"START")==0){
        fprintf("H^00%s,^00%s^%06X\n",label,operand,start);
        start = atoi(operand);
        locctr = start;
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }

    fprintf(fp5, "T^%06X^", locctr);

    while(strcmp(opcode,"END")!=0){
        fscanf(fp4, "%d %s %s %s", &locctr, label, opcode, operand);

        if(strcmp(opcode,"BYTE")==0){
            fprintf(fp5,"^");
            if(operand[0]=='C'){
                for(int i=2;i<strlen(operand)-1;i++){
                    fprintf(fp5,"^%02X",operand[i]);
                }

            }else if(operand[0]=='X'){
                fprintf(fp5,"^%06X",atoi(operand+2));
            }
        }else if(strcmp(opcode,"WORD")==0){
            fprintf(fp5,"^%06X",operand);
        }else if(strcmp(opcode,"RESW")==0 || strcmp(opcode,"RESB")==0){
            //
        }else{
            rewind(fp2);
            fscanf(fp2,"%s %s",code,mnemonic);
            while(strcmp(code,"END")!=0){
                if(strcmp(opcode,code)==0){
                    fprintf(fp5,"^%02X",mnemonic);
                    break;
                }
                fscanf(fp2,"%s %s",code,mnemonic);
            }

            rewind(fp3);
            fscanf(fp3,"%s %d",symbol,&address);
            while (strcmp(symbol,"END")!=0){
                if(strcmp(operand,symbol)==0){
                    fprintf(fp5,"^%06X",address);
                    break;
                }
                fscanf(fp3,"%s %d",symbol,&address);
            }
            
        }
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(fp5,"E^%06X",start);

     fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}