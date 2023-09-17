//To discard preprocessor directives from the given input ‘C’ file.
#include <stdio.h>

int main(){
    FILE *inputFile;
    inputFile = fopen("input.c", "r");

    if (inputFile == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    int character;
    int inDirective = 0; // to track if we are inside a directive
    
    while ((character = fgetc(inputFile)) != EOF)
    {
        if (character == '#')
        {
            inDirective = 1; //Start of directive
        } 
        else if (character == '\n') 
        {
            inDirective = 0; //End of line, exit directive mode
        }
        
        //If not in a directive, write the character to output
        if (!inDirective)
        {
            putchar(character);
        }
    }

    fclose(inputFile);
    
    return 0;
}