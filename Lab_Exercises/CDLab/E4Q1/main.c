#include <iostream>
#include <string.h>

using namespace std;

struct Global{
    char lexeme[20];
    char type[20];
    int size;
    int symptr;
};

struct Local{
    char lexeme[20];
    char type[20];
    int size;
};

struct Function{
    char Fname[20];
    int ptr_LTable;
};

Global globalTable[100];
int Gcount = 0;

Local localTable[100];
int Lcount = 0;

Function functionTable[100];
int Fcount = 0;

int i, k;

int searchG(const char* lexeme){      //search function with char pointer to lexeme since lexeme is declares as char datatype
    for(i=0; i<Gcount; i++){          //going thru the global table
        if(globalTable[i].lexeme==lexeme){    //if lexeme already exists in globalTable
            return 1;}
    }
    return 0;                         //if it doesnt exist return 0
}

int searchL(const char* lexeme, int funcIndex){
    if(funcIndex>=0 && funcIndex<Fcount){
        int a=functionTable[funcIndex].ptr_LTable;         //gets the ptr stored with tht function index..the ptr points to the functions local table
        int b=(funcIndex==Fcount - 1) ? Lcount : functionTable[funcIndex + 1].ptr_LTable;
        /*Lcount is the count of ALL local veriables of diff functions
        So if index=Fcount-1 means if index=last function then b=Lcount ==>i loop shud stop end of local var is reached since it last function
        or else it stops when ptr is pointing to next function...funcIndex+1 (next function) ptr_LTable         */
        for(i=a; i<b; i++) {
            if(strcmp(localTable[i].lexeme, lexeme) == 0) {
                return 1;}
        }
    }
    return 0; // Symbol not found
}

int global_id = 501;

void insertGlobalSymbol(const char* lexeme, const char* type, int size) {
    if (searchG(lexeme) == 0) {
        strcpy(globalTable[Gcount].lexeme, lexeme);
        strcpy(globalTable[Gcount].type, type);
        globalTable[Gcount].size = size;
        globalTable[Gcount].symptr = global_id;
        Gcount++;
        global_id++;
    }
}

void insertLocalSymbol(const char* lexeme, const char* type, int size, int funcIndex) {
    if (funcIndex >= 0 && funcIndex < Fcount) {
        int symbolExists = searchL(lexeme, funcIndex);
        if (symbolExists == 0) {
            strcpy(localTable[Lcount].lexeme, lexeme);
            strcpy(localTable[Lcount].type, type);
            localTable[Lcount].size = size;
            Lcount++;
        }
    }
}

void displayglobalTable() {
    cout << "\n\n\t~~~GLOBAL SYMBOL TABLE~~~" << endl;
    cout << "| SNo |\t| Lexeme |\t| Type |\t| Ptr to SymTab |" << endl;
    for (int i = 0; i < Gcount; i++) {
        cout<<"   "<<i + 1 <<"\t" << globalTable[i].lexeme << "\t\t Function\t\t" << globalTable[i].symptr << endl;
    }
}

void displaylocalTable(int funcIndex) {
    if (funcIndex >= 0 && funcIndex < Fcount) {
        cout << "| SN0 |\t| Lexeme |\t\t| Type |\t| Size |" << endl;
        for (int i = 0; i < Lcount; i++) {
            cout<< "  "<<i + 1 << "\t  " << localTable[i].lexeme<<"\t\t\t  "<<localTable[i].type << "\t\t   "<<localTable[i].size << endl;
        }
    }
}

void updateFunctionTable(const char* returnType, const char* functionName){
    strcpy(functionTable[Fcount].Fname, functionName);
    functionTable[Fcount].ptr_LTable = Lcount;
    Fcount++;
}

int calculateVariableSize(const std::string& dataType) {
    if (dataType == "int") {
        return sizeof(int);
    } else if (dataType == "char") {
        return sizeof(char);
    } else if (dataType == "float") {
        return sizeof(float);
    } else if (dataType == "double") {
        return sizeof(double);
    } else if (dataType == "bool") {
        return sizeof(bool);
    }
}

struct TOKEN {
    int row;
    int col;
    const char* type;
    char value[100];
};

char declare_types[9][20] = {
    "int", "char", "float", "double", "bool",
    "short", "long", "void"
};

char keywords[31][20] = {
    "int", "if", "bool", "else", "do", "while", "for", "return",
    "break", "continue", "switch", "case", "default", "char", "const", "double", "float", "long", "short",
    "unsigned", "void", "auto", "extern", "static", "struct", "class", "namespace", "template",
    "new", "delete"
};

int lin =1, col =1;

struct TOKEN getNextToken(FILE *fptr) {
    int i=0, j, flag;
    char c, c1, str[100];

    TOKEN token;
    token.row = 0;
    token.col = 0;
    token.type= nullptr;
    token.value[0] = '\0';

    c=getc(fptr);
    while (c!= EOF){
        i=0;
        flag=0;
        if(c=='/'){
            c1=getc(fptr);
            if(c1=='/') {
                token.row=lin;
                token.col=col;
                c=fgetc(fptr);
                while(c!='\n') {
                    str[i++]=c;
                    c=fgetc(fptr);
                }
                str[i]='\0';
                lin++;
                strcpy(token.value, str);
                token.type="SINGLE LINE COMMENT";
                return token;
            }
            else if (c1 == '*') {
                token.row=lin;
                token.col=col;
                char prevChar = '\0';
                while (!(prevChar == '*' && c == '/')) {
                    prevChar=c;
                    c = fgetc(fptr);
                    col++;
                    str[i++]=c;
                    if (c == '\n') {
                        lin++;
                        col=1;
                    }
                }
                str[i--];
                str[i--];
                str[i]='\0';
                strcpy(token.value, str);
                token.type="MULTILINE COMMENT";
                return token;
            }
        }
        if (c=='#') {
            token.row=lin;
            token.col=col;
            c = fgetc(fptr);
            while (c != '\n') {
                 str[i++]=c;
                 c = fgetc(fptr);
            }
            str[i]='\0';
            lin++;
            col=1;
            strcpy(token.value, str);
            token.type="PREPROCESSOR DIRECTIVES";
            return token;
        }
        if (c == '"') {
            token.row=lin;
            token.col=col;
            c = fgetc(fptr);
            while (c != '"'){
                str[i++]=c;
                c = fgetc(fptr);
                col++;
            }
            col++;
            str[i--];
            str[i]='\0';
            strcpy(token.value, str);
            token.type="STRING LITERAL";
            return token;
        }
        if (isalpha(c) || c=='_') {
            token.row=lin;
            str[i++]=c;
            c=fgetc(fptr);
            col++;
            while (isalnum(c) && c!=' '){
                str[i++]=c;
                c=fgetc(fptr);
                col++;
            }
            str[i]='\0';
            for (j=0; j<=30; j++) {
                if(strcmp(str,keywords[j])==0) {
                    flag=1;
                    break;
                }
            }
            string obj1="cout", obj2="cin", obj3="printf", obj4="scanf";
            if ((str == obj1) || (str == obj2) || (str == obj3) || (str == obj4)) {
                    flag = 2;
            }
            if(flag==1) {
                token.type="KEYWORD";
            }
            else if (flag==2){
                token.type="Predefined objects";
            }
            else{
                token.type="IDENTIFIER";
            }
            token.col=col-i;
            strcpy(token.value,str);
            ungetc(c,fptr);
            return token;
        }
        if (isdigit(c)){
            token.row=lin;
            token.type="NUMERIC CONSTANT";
            str[i++]=c;
            c=fgetc(fptr);
            col++;
            while(isdigit(c)){
                str[i++]=c;
                c=fgetc(fptr);
                col++;
            }
            str[i]='\0';
            token.col=col-i;
            strcpy(token.value,str);
            ungetc(c,fptr);
            return token;
        }
        if (c=='&' || c=='|' || c=='!') {
            str[i++]=c;
            c=fgetc(fptr);
            col++;
            if (c== '&'||c=='|'){
                str[i++]=c;
                col++;
                str[i]='\0';
            }
            else if(str[0]=='!'){
                str[i]='\0';
                ungetc(c,fptr);
            }
            token.row=lin;
            token.col=col-i;
            token.type="LOGICAL OPERATOR";
            strcpy(token.value,str);
            return token;
        }
        if (c=='+' || c=='-' || c=='*' || c=='/' || c=='%') {
            str[i]=c;
            i++;
            c = fgetc(fptr);
            col++;
            if (c=='+'|| c=='-'){
                str[i++]=c;
                col++;
                str[i]='\0';
            }
            else{
                str[i]='\0';
                ungetc(c,fptr);
            }
            token.row = lin;
            token.col = col-i;
            token.type = "ARITHMETIC OPERATOR";
            strcpy(token.value,str);
            return token;
        }
        if (c=='=' || c=='!' || c=='<' || c=='>') {
            str[i]=c;
            i++;
            c = fgetc(fptr);
            col++;
            if (c=='='){
                str[i++]=c;
                col++;
                str[i]= '\0';
                token.type = "RELATIONAL OPERATOR";
            }
            else if (c=='<' || c=='>'){
                str[i++] = c;
                col++;
                str[i] = '\0';
                token.type = "(<<) OPERATOR";
            }
            else{
                str[i] = '\0';
                ungetc(c,fptr);
                token.type = "RELATIONAL OPERATOR";
            }
            token.row=lin;
            token.col=col-i;
            strcpy(token.value,str);
            return token;
        }
        if (c==',' || c==';' || c=='{' || c=='}' || c=='(' || c==')' || c =='[' || c==']' || c=='?' || c=='@'){
            token.row=lin;
            token.col=col;
            str[i++]=c;
            str[i]='\0';
            token.type="SPECIAL SYMBOL";
            strcpy(token.value,str);
            col++;
            return token;
        }
        if (c == '\n') {
            lin++;
            col =1;
        }
        else {
            col++;
        }
        c = getc(fptr);
    }
    token.row = lin;
    token.col = col;
    token.type = nullptr;
    token.value[0] = '\0';
    return token;
}

int main() {
    FILE *fptr=fopen("l4q1in.c", "r");

    if (fptr==NULL) {
        cout<<"Cannot open file"<<endl;
        exit(0);
    }
    string datatype, datatype2;
    string returnType;

    TOKEN token;

    while(true) {

        int currentFunctionIndex = -1;
        token=getNextToken(fptr);
        if(token.type==nullptr) {
            break;
        }
        else if (token.type=="STRING LITERAL" || token.type=="SINGLE LINE COMMENT" || token.type=="MULTILINE COMMENT" || token.type=="PREPROCESSOR DIRECTIVES"){
            continue;
        }
        else if (token.type=="IDENTIFIER"){
            string Gvar=token.value;
            token=getNextToken(fptr);
            if (strcmp(token.value,"(")==0){
                    returnType = datatype;
                    updateFunctionTable(returnType.c_str(), Gvar.c_str());
                     int k,f=0;
                    for (k=0; k<=10; k++) {
                          if(datatype==declare_types[k]){
                               f=1;
                               break;
                          }
                    }
                    if (f==1){
                        int variableSize = calculateVariableSize(datatype);
                        insertGlobalSymbol(Gvar.c_str(), datatype.c_str(), variableSize);
                    }
                    else
                        continue;
                    while (strcmp(token.value, "{") != 0) {
                        token=getNextToken(fptr);
                    }
                    currentFunctionIndex = Fcount - 1;
                    cout<<"\n\t~~~LOCAL TABLE: "<<Gvar<<"  ~~~"<<endl;
                    do{
                        token=getNextToken(fptr);
                        if (token.type=="IDENTIFIER"){
                               int variableSize = calculateVariableSize(datatype2);
                               string Lvar=token.value;
                               f=0;
                               for (k=0; k<=10; k++) {
                                     if(datatype2==declare_types[k]){
                                            f=1;
                                            break;
                                     }
                               }
                               if (f==1){
                                    token=getNextToken(fptr);
                                    while((strcmp(token.value, ",") != 0) && (strcmp(token.value, ";") != 0)){
                                           token=getNextToken(fptr);
                                    }
                                    if(strcmp(token.value, ",") == 0){
                                           insertLocalSymbol(Lvar.c_str(), datatype2.c_str(), variableSize, currentFunctionIndex);
                                        }
                                    else if (strcmp(token.value, ";") == 0){
                                            insertLocalSymbol(Lvar.c_str(), datatype2.c_str(), variableSize, currentFunctionIndex);
                                            datatype2='\0';
                                    }
                                }
                                else
                                    continue;
                        }
                        if (token.type=="KEYWORD"){
                                datatype2=token.value;
                        }
                    }while (strcmp(token.value, "}") != 0);
            int currentFunctionIndex = Fcount - 1; // Update the current function index
            displaylocalTable(currentFunctionIndex);
            Lcount = 0;
            }
        }
        if (token.type=="KEYWORD"){
            datatype=token.value;}
         }
    displayglobalTable();
    fclose(fptr);
    return 0;
}