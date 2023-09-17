#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

int main() {
    FILE *inputFile;
    inputFile = fopen("input.c", "r");

    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    char line[1024]; // Buffer to store each line

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char *token = strtok(line, " \t\n"); // Tokenize the line

        while (token != NULL) {
            // Convert the token to uppercase
            for (int i = 0; token[i]; i++) {
                token[i] = toupper(token[i]);
            }

            // Check if the token is a C keyword
            for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
                if (strcmp(token, keywords[i]) == 0) {
                    printf("%s\n", token);
                    break;
                }
            }

            token = strtok(NULL, " \t\n"); // Get the next token
        }
    }

    fclose(inputFile);

    return 0;
}