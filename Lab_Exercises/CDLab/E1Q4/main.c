#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an array of predefined verbs
char *verbs[] = {
    "run", "jump", "eat", "write", "read", "sing", "dance", "sleep", "swim", "talk"
};
int numVerbs = sizeof(verbs) / sizeof(verbs[0]); // Calculate the number of verbs in the array

// Function to check if a word is a verb from the predefined array
int isVerb(char *word) {
    for (int i = 0; i < numVerbs; i++) {
        if (strcmp(word, verbs[i]) == 0) {
            return 1; // It's a verb
        }
    }
    return 0; // It's not a verb
}

int main() {
    char input[100];

    printf("Enter a statement: ");
    fgets(input, sizeof(input), stdin);

    // Tokenize the input statement to extract words
    char *token = strtok(input, " ");
    while (token != NULL) {
        // Remove newline character from the token
        char *newline = strchr(token, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        // Check if the token is a verb from the predefined array
        if (isVerb(token)) {
            printf("Verb '%s' found\n", token);
        }

        token = strtok(NULL, " ");
    }

    return 0;
}
