#include <stdio.h>
#include "lex.h"
#include <stdlib.h>

FILE *yyin;
char *yytext;
int main(int argc, char *argv[]) {
    int token;
    if(argc !=2 ) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if(!yyin) {
        perror("Error opening file");
        return 1;
    }
    yytext = (char *)malloc(100);
    if(!yytext) {
        perror("Error allocating memory");
        return 1;
    }
    while((token = yylex()) != 0) {
        printf("Token: %d\n", token);
    }
    fclose(yyin);
    free(yytext);
    return 0;
}