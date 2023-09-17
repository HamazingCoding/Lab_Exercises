#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if(inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen("output.txt", "w");

    if(outputFile == NULL) {
        perror("Error opening output file");
        return 1;
    }

    int character;
    while ((character = fgetc(inputFile)) != EOF)
    {
        if (character == ' ' || character == '\t') {
            fputc(' ', outputFile);
        }
        else 
        {
            fputc(character, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    

    return 0;
}