/* Write the YACC program to implement the Syntax-Directed definition for translating
assignment statements, if statements, if-else statements, while statements to three-
address code. The assignment statements need to be type checked. Use quadruple-record
structure for the representation of three address code. The three address statements have to be
sent to an output file. Quadruple is a record structure with four fields for the three-address
statements.
Quadruple is a record structure with four fields for the three-address statements.
As for example: a = b * - c

Label Op Arg1 Arg2 Result
00 uminus c T1
01 * b T1 T2
02 = T2 a

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void gen(char *op, char *arg1, char *arg2, char *result);


int temp_count = 0;
int label_count = 0;
FILE *fp;

char* newtemp() {
    char *temp = (char*)malloc(5 * sizeof(char));
    sprintf(temp, "T%d", temp_count++);
    return temp;
}

char* newlabel() {
    char *label = (char*)malloc(5 * sizeof(char));
    sprintf(label, "L%d", label_count++);
    return label;
}

void gen(char *op, char *arg1, char *arg2, char *result) {
    fprintf(fp, "%s\t%s\t%s\t%s\n", op, arg1, arg2, result);
}

int main() {
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Example: a = b * -c
    char *t1 = newtemp();
    char *t2 = newtemp();
    gen("uminus", "c", "", t1);
    gen("*", "b", t1, t2);
    gen("=", t2, "", "a");

    fclose(fp);
    return 0;
}