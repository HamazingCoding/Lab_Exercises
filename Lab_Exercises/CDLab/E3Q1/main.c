#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define MAX_TOKEN_LENGTH 100
 int row=1;
 int col=1;
 char *p="printf";
typedef enum
{
    ARITHMETIC_OPERATOR,
    RELATIONAL_OPERATOR,
    LOGICAL_OPERATOR,
    SPECIAL_SYMBOL,
    KEYWORD,
    NUMERICAL_CONSTANT,
    STRING_LITERAL,
    IDENTIFIER,
    END_OF_FILE
} TokenType;
typedef struct
{
    TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
} Token;
bool isSpecialSymbol(char ch)
{
    char specialSymbols[] = "+-*/%=<>!&|()[]{};";
    for (int i = 0; specialSymbols[i] != '\0'; i++)
    {
        if (ch == specialSymbols[i])
        {
            return true;
        }
    }
    return false;
}
Token getNextToken(FILE *inputFile)
{
    Token token;
    char ch;
    int lexemeIndex = 0;
    token.type = END_OF_FILE;
    token.lexeme[0] = '\0';
    while ((ch = fgetc(inputFile)) != EOF)
    {
        if (ch == '\n')
        {
            row++;
            col = 1;

        }
        else if( ch == ' '){
            col=col+1;

        }

        if (ch == p[0]){
                int i=0;
            while(ch==p[i]&&p[i]!='\0'){
                ch=fgetc(inputFile);
                i++;
            }
            if(i==6){
                while(ch!='\n'){
                    ch=fgetc(inputFile);
                }
                row++;
            }
            else{
                fseek(inputFile,-(i+1),SEEK_CUR);
            }
        }
        if (ch == '/'){
            if (ch == '/'){
                 while ((ch = fgetc(inputFile)) != EOF && ch != '\n')
            {
                // Keep reading characters until the end of the line
            }
            row++;
            col = 1;
            continue;
            }
            else if (ch=='*'){
                while ((ch = fgetc(inputFile)) != EOF && ch != '/')
            {
                // Keep reading characters until the end of the line
            }
            row++;
            col = 1;
            continue;
            }
        }
        if (ch == '#')
        {

            while ((ch = fgetc(inputFile)) != EOF && ch != '\n')
            {
                // Keep reading characters until the end of the line
            }
            row++;
            col = 1;
            continue;
        }
        if (isspace(ch))
        {
            continue;
        }

        if (isSpecialSymbol(ch))
        {
            token.type = SPECIAL_SYMBOL;
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            return token;
        }
        if (isalpha(ch) || isdigit(ch) || ch == '_')
        {
            token.lexeme[lexemeIndex++] = ch;
            while ((ch = fgetc(inputFile)) != EOF && (isalnum(ch) || ch == '_'))
            {
                token.lexeme[lexemeIndex++] = ch;
            }
            ungetc(ch, inputFile);
            token.lexeme[lexemeIndex] = '\0';
            char *keywords[] = {"int", "if", "else", "while", "for", "return"};
            for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
            {
                if (strcmp(token.lexeme, keywords[i]) == 0)
                {
                    token.type = KEYWORD;
                    return token;
                }

            }
            bool isNumericConstant = true;
            for (int i = 0; i < lexemeIndex; i++)
            {
                if (!isdigit(token.lexeme[i]))
                {
                    isNumericConstant = false;
                    break;
                }
            }
            if (isNumericConstant)
            {
                token.type = NUMERICAL_CONSTANT;
                return token;
            }
            token.type = IDENTIFIER;
            return token;
        }
        if (ch == '"')
        {
            token.type = STRING_LITERAL;
            while ((ch = fgetc(inputFile)) != EOF && ch != '"')
            {
                token.lexeme[lexemeIndex++] = ch;
            }
            token.lexeme[lexemeIndex] = '\0';
            return token;
        }
    }
    return token;
}
int main()
{

    char inputFileName[100];
    int skipNextLine = 0;
    printf("Enter the input file name: ");
    scanf("%s", inputFileName);
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        return 1;
    }
    Token token;
    
    do
    {
        token = getNextToken(inputFile);
        if (token.type != END_OF_FILE)
        {
            printf("Row: %d, Col: %d, Type: %d, Token: %s\n", row, col, token.type, token.lexeme);
            int j=strlen(token.lexeme);
            col=col+j;
        }
    }
    while (token.type != END_OF_FILE);
    fclose(inputFile);

    return 0;


}