%{
  //definition section
#include <stdio.h>
#include "tree.h"
#include "type.h" //symtab_type type
#include "interpret.tab.h"  //interpret.y에서 정의된 토큰 가져옴.
%}

letter			[a-zA-Z]
digit			[0-9]
id			{letter}({letter}|{digit})*

digits			{digit}{digit}*
fraction		("."{digits})
rnum			{digits}{fraction}
inum			{digits}
whitespace		[ \t]

relop			(">"|">="|"<"|"<="|"=="|"<>")
addop			("+"|"-")
mulop			("*"|"/")

%%
 /* reserved-word : nop, print ? */
"mainprog"|"MAINPROG"		{ return MAINPROG; }
"var"|"VAR"			{ return VAR; }
"of"|"OF"			{ return OF; }
"function"|"FUNCTION"		{ return FUNCTION; }
"procedure"|"PROCEDURE"		{ return PROCEDURE; }
"begin"|"BEGIN"			{ return BBEGIN; }
"end"|"END"			{ return END; }
"if"|"IF"			{ return IF; }
"then"|"THEN"			{ return THEN; }
"else"|"ELSE"			{ return ELSE; }
"while"|"WHILE"			{ return WHILE; }
"array"|"ARRAY"			{ return ARRAY; }
"float"|"FLOAT"			{ return FLOAT; }
"int"|"INT"			{ return INT; }
"return"|"RETURN"		{ return RETURN; }
"="				{ return ASSIGNOP; }
"print"|"PRINT"			{ return PRINT;	}
";"				{ return SEMI; }
","				{ return COMA; }
":"				{ return COLON; }
"("				{ return LPARENT;}
")"				{ return RPARENT;}
"["				{ return LSBRACK;}
"]"				{ return RSBRACK;}
"!"				{ return NOT; }
"."				{ return DOT; }
 /* sign operation
"+"			{ return POSITIVE;}                        
"-"			{ return NEGATIVE;}
 */
{addop}			{ yylval.opval = strdup(yytext); return ADDOP; }	//yylval.opval에 yytext(현재토큰) 복사 후 addop 리턴
{mulop}			{ yylval.opval = strdup(yytext); return MULOP; }
{relop}			{ yylval.opval = strdup(yytext); return RELOP; }
{id}			{ yylval.sval = strdup(yytext); return ID; }
{rnum}			{ yylval.rval = atof(yytext); return RNUM; }	//real type
{inum}			{ yylval.ival = atoi(yytext); return INUM; }	//int type
	
{whitespace}	        { }                    				/* whitespace */

"//".*			{ }						/* skip singleline comments */
"/*"               	{ int c;
                   	   while (c = input()) {
                  	      if (c == '*')
                        	  if ((c = input()) == '/')
                        	    break;
                       		  else
	                            unput(c);
        	           } }
\n			{ } 						// pass line
.			{ /*printf("unknown token (%c)\n",yytext[0]);*/ /*return yytext[0];*/ }

%%

void yyerror(char *msg) {
  fprintf(stderr, "error [line: %d]: %s at %s\n", yylineno, msg, yytext);
  exit(1);
}

/*
void error(char *msg) {
  fprintf(stderr, "error [line: %d]: %s at %s\n", yylineno, msg, yytext);
  exit(1);
}
*/
