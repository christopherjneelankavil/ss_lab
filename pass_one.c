#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char label[10],opcode[10],operand[10],code[10],mnemonic[10];
    int locctr,start,len,i,temp;

    FILE *fp1,*fp2,*fp3,*fp4;
    
    fp1 = fopen("input.txt","r");
    //fp2 = fopen("optab.txt","r");
    fp3 = fopen("symtab.txt","w");
    fp4 = fopen("intermediate.txt","w");

    fscanf(fp1,"%s %s %s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        start = atoi(operand);
        locctr = start;
        fscanf(fp1,"%s %s %s",label,opcode,operand);
    }else{
        locctr =0;
    }

    while(strcmp(opcode,"END")!=0){
        fprintf(fp4,"%d\t%s\t%s\t%s",locctr,label,opcode,operand);

        if(strcmp(label,"*")!=0){
            fprintf(fp3,"%s\t%d",label,locctr);
        }else{
            printf("Duplicate label\tError flag set at %s %d\n",label,locctr);
        }

        fp2 = fopen("optab.txt","r");
        fscanf(fp2,"%s %s",code,mnemonic);
        while(strcmp(code,"END")!=0){
            if(strcmp(opcode,code)==0){
                locctr+=3;
                break;
            }else{
                fscanf(fp2,"%s %s",code,mnemonic);
            }
        }
        if(strcmp(opcode,"WORD")==0){
            locctr+=3;
        }else if(strcmp(opcode,"RESW")==0){
            temp = atoi(operand);
            locctr += 3*temp;
        }else if(strcmp(opcode,"BYTE")==0){
            i=0;
            len =0;
            while(operand[i]!='\0'){
                len++;
                i++;
            }
            locctr += len;
        }else if(strcmp(opcode,"RESB")==0){
            temp = atoi(operand);
            locctr += temp;
        }else{
            printf("Invalid opcode\tError flag set at %s %d\n",opcode,locctr);
        }
        fscanf(fp1,"%s %s %s",label,opcode,operand);
    }
    return EXIT_SUCCESS;

}