#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[] = "input.txt";     
    char outputFileName[] = "output.txt";   

    inputFile = fopen(inputFileName, "r");
    outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening files");
        return 1;
    }

    int prevChar = ' ';  

    int currentChar;
    while ((currentChar = fgetc(inputFile)) != EOF) {
        
        if (currentChar == ' ' || currentChar == '\t') {
            
            if (prevChar != ' ') {
                fputc(' ', outputFile);
            }
        } else {
            
            fputc(currentChar, outputFile);
        }

        prevChar = currentChar;  
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Spaces and tabs replaced in '%s' and saved to '%s'.\n", inputFileName, outputFileName);

    return 0;
}
