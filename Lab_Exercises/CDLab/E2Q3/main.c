#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

int isKeyword(char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;  
        }
    }
    return 0;  
}

int main() {
    FILE *inputFile;
    char fileName[] = "input.c";  

    inputFile = fopen(fileName, "r");

    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    char word[100];  

    while (fscanf(inputFile, "%s", word) != EOF) {
        
        for (int i = 0; word[i]; i++) {
            word[i] = toupper(word[i]);
        }

       
        if (isKeyword(word)) {
            printf("Keyword Found: %s\n", word);  
        }
    }

    fclose(inputFile);

    return 0;
}
