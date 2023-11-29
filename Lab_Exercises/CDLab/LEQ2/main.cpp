#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

struct Token {
    int row;
    int col;
    const char* type;
    char value[100];
};

int lin=1, col=1;

Token getNextToken(FILE *file) {
    int i = 0, j, flag;
    char c, c1, str[100];

    Token token;
    token.row = 0;
    token.col = 0;
    token.type = nullptr;
    token.value[0] = '\0';

    char keywords[5][20] = {
        "void", "main", "int", "if", "else"
    };

    c = getc(file);
    while (c != EOF) {
        i = 0;
        flag = 0;

        if (isalpha(c)) {
            token.row = lin;
            token.col = col;
            str[i] = c;
            i++;
            c = getc(file);
            col++;
            while (isalnum(c) && c != ' ') {
                str[i] = c;
                i++;
                c = getc(file);
                col++;
            }
            str[i] = '\0';

            for (j = 0; j <= 30; j++) {
                if (strcmp(str, keywords[j]) == 0) {
                    flag = 1;
                    break;
                }
            }

            token.row = lin;
            token.col = col - i;
            if (flag == 1) {
                token.type = "Keyword";
            } else {
                token.type = "Identifier";
            }
            strcpy(token.value, str);
            ungetc(c,file);
            return token;
        }

        if (c == ',' || c == ';' || c == '{' || c == '}' || c == '(' || c == ')') {
            token.row = lin;
            token.col = col;
            token.type = "Special Symbol";
            token.value[0] = c;
            token.value[1] = '\0';
            col++;
            return token;
        }

        if (c == '\n') {
            lin++;
            col = 1;
        } else {
            col++;
        }

        c = getc(file);
    }

    token.row = lin;
    token.col = col;
    token.type = nullptr;
    token.value[0] = '\0';
    return token;
}

int main() {
    char filename[100];

    FILE* file = fopen("testfile.txt", "r");
    if (file == NULL) {
        cout << "Cannot open file: " << filename << endl;
        exit(0);
    }


    Token token;
    cout<<"\tRow \tColumn \tType"<< endl;
    cout<<endl;

    while (true) {
        token = getNextToken(file);
        if (token.type == nullptr) {
            break;
        }
        else
            cout<<"\t"<<token.row<<"\t"<<token.col<<"\t"<<token.type<<endl;
    }

    fclose(file);
    return 0;
}