#include <stdio.h>
#define MAX_FILE_NAME 100
#include <string.h>
#include <stdlib.h>
int main()
{
    FILE *fp;
    char filename[MAX_FILE_NAME];
    char c; 
	char str[100];    
	printf("Enter file name: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }
    int i=0;
    for (c = fgetc(fp); c != EOF; c = fgetc(fp)){
		*(str+i)=c;
        printf("%s", c);
        i=i+1;
        }
    fclose(fp);
    printf("The file reversed is %s", strrev(str)); 
    return 0;
}