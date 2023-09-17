//To count characters and lines in a file
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL) 
    {
        perror("Error opening input file");
        return 1;
    }

    int lineCount = 0;
    int charCount = 0;
    int character;

    while ((character = fgetc(file)) != EOF) 
    {
        charCount++; 

        if (character == '\n') {
            lineCount++; 
        }
    }
    
    fclose(file);

    printf("Line count: %d\n", lineCount);
    printf("Character count: %d\n", charCount);

    return 0;
}