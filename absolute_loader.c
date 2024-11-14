#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp1;
    fp1 = fopen("abs_loader_input.txt", "r");

    if (fp1 == NULL) {
        printf("Error opening abs_loader_input.txt\n");
        return 1;
    }

    char line[50], addr[7];
    int i, j, hexaddr;

    do {
        fscanf(fp1, "%s", line);
        if (line[0] == 'T') {
            // Extract the address part (characters 1 to 6) from the line
            for (i = 1, j = 0; i < 7; i++, j++) {
                addr[j] = line[i];
            }
            addr[j] = '\0';  // Null-terminate the string
            
            // Convert the extracted address string to a hexadecimal integer
            sscanf(addr, "%x", &hexaddr);

            i = 9;  // Start reading data from index 9
            while (line[i] != '\0') {
                printf("%x    %c%c\n", hexaddr, line[i], line[i + 1]);
                i += 2;
                hexaddr++;
            }
        }
    } while (!feof(fp1));

    fclose(fp1);
    return 0;
}
