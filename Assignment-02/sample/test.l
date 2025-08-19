%{
#include<stdio.h>
#include "tok_def.h"
%}

%%
;                                {return(SEMICOLON_TOK);}
int                              {return(INT_TOK);}

%%
int main()
{
    int val;
    while((val = yylex()) > 0)
    {
        printf("Token ===%s; Token ID ====%d\n", yytext, val);
        
    }
    
    return(0);
}
