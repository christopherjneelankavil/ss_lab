#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[10], symbol[10];
    int locctr, start, length, address, len, i, temp, error_flag = 0;

    FILE *fp1, *fp2, *fp3, *fp4, *fp5;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("intermediate.txt", "w");
    fp5 = fopen("object.txt", "w");

    fscanf(fp1, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp4, "\n\t\t%d\t%s\t%s\t%s", locctr, label, opcode, operand);

        if (strcmp(label, "*") != 0) {
            fprintf(fp3, "\n%d\t%s", locctr, label);
        } else {
            printf("Duplicate label\tError flag set at %s %d\n", label, locctr);
            error_flag = 1;
        }

        int opcode_found = 0;
        rewind(fp2);
        while (fscanf(fp2, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                opcode_found = 1;
                break;
            }
        }

        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            temp = atoi(operand);
            locctr += 3 * temp;
        } else if (strcmp(opcode, "BYTE") == 0) {
            len = strlen(operand) - 3;
            locctr += (operand[0] == 'C') ? len : len / 2;
        } else if (strcmp(opcode, "RESB") == 0) {
            temp = atoi(operand);
            locctr += temp;
        } else if (!opcode_found) {
            printf("Invalid opcode\tError flag set at %s %d\n", opcode, locctr);
            error_flag = 1;
        }

        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }

    fprintf(fp5, "H^%s^00%X^%06X\n", label, operand, start);
    fprintf(fp5, "T^%06X^", locctr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    if (error_flag) {
        printf("Assembly completed with errors.\n");
    } else {
        printf("Assembly completed successfully.\n");
    }

    return 0;
}
