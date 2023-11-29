%{
#include<stdio.h>
#include<stdlib.h>
%}

%%
^[0-9]* printf("It is a digit. ");
^[^0-9]|[0-9]*[a-zA-Z_] printf("It is not a digit. ");
. ;
%%

int yywrap() { return 0; }
int main()
{
yylex();
return 0;
}
