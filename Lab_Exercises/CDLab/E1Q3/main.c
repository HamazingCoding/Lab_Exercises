//merges lines alternatively from 2 files and stores it in a resultant file
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file1, *file2, *resultFile;
    char inputLine[1000];

    char file1Name[50], file2Name[50], resultFileName[50];

    printf("Enter the name of the first file: ");
    scanf("%s", file1Name);
    printf("Enter the name of the second file: ");
    scanf("%s", file2Name);

    file1 = fopen(file1Name, "r");
    file2 = fopen(file2Name, "r");

    if (file1 == NULL || file2 == NULL) {
        printf("Failed to open input files.\n");
        return 1;
    }

    printf("Enter the name of the result file: ");
    scanf("%s", resultFileName);
    resultFile = fopen(resultFileName, "w");

    if (resultFile == NULL) {
        printf("Failed to create result file.\n");
        fclose(file1);
        fclose(file2);
        return 1;
    }

    while (1) {
        if (fgets(inputLine, sizeof(inputLine), file1) != NULL) {
            fputs(inputLine, resultFile);
        } else {
            break;
        }

        if (fgets(inputLine, sizeof(inputLine), file2) != NULL) {
            fputs(inputLine, resultFile);
        } else {
            break;
        }
    }

    fclose(file1);
    fclose(file2);
    fclose(resultFile);

    printf("Lines merged successfully to %s.\n", resultFileName);

    return 0;
}