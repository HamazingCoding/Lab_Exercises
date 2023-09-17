//To reverse the file contents and store in another file. Also display the size of file using file handling function.
#include <stdio.h>

int main() {
    FILE *originalFile, *reversedFile;
    char originalFileName[50], reversedFileName[50];
    long fileSize;

    printf("Enter the name of the original file: ");
    scanf("%s", originalFileName);

    originalFile = fopen(originalFileName, "rb");
    if (originalFile == NULL) {
        printf("Failed to open the original file.\n");
        return 1;
    }

    fseek(originalFile, 0, SEEK_END);
    fileSize = ftell(originalFile);
    fseek(originalFile, 0, SEEK_SET);

    printf("Enter the name of the reversed file: ");
    scanf("%s", reversedFileName);

    reversedFile = fopen(reversedFileName, "wb");
    if (reversedFile == NULL) {
        printf("Failed to create the reversed file.\n");
        fclose(originalFile);
        return 1;
    }
    
    for (int i = fileSize - 1; i >= 0; i--) {
        fseek(originalFile, i, SEEK_SET);
        char ch = fgetc(originalFile);
        fputc(ch, reversedFile);
    }
    
    fclose(originalFile);
    fclose(reversedFile);

    printf("Size of the original file: %ld bytes\n", fileSize);
    printf("Size of the reversed file: %ld bytes\n", fileSize);

    return 0;
}