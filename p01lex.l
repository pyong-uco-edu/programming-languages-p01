%{
//-------------------------------------------------------------
// Team Identification Block
// Author 1:	            Lisa Sun
// Student ID:	            *20300925
// E-Mail:		            lsun1@uco.edu
// Student 1 CRN:           22142, Spring 2023
// Author 2:	            Philip Yong
// Student ID:	            *20512220
// E-Mail:		            pyong@uco.edu
// Student 2 CRN:	        21502, Spring 2023
// Course:		            CMSC 4023 - Programming Languages
// Project:	 	            p01
// Due:		 	            Febuary 13, 2023
// Project Account Number:	tt048
//--------------------------------------------------------------
//--------------------------------------------------------------------
// Lex Literal Block
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// File p01lex.l defines a prototype scanner for the micro language.
// The scanner definition is a lex specification.
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Standard C and C++ Library Include Files
//--------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
//--------------------------------------------------------------------
// Application Includes
//--------------------------------------------------------------------
#include "p01lex.h"
//--------------------------------------------------------------------
//Token definitions
//--------------------------------------------------------------------
// #include "y.tab.h"
#include "p01tkn.h"
//--------------------------------------------------------------------
//Namespaces
//--------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------
//Externals
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Lex Definitions
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//Global Variables
//--------------------------------------------------------------------
int TokenMgr(int t); //Token post processing
void ignoreComment(void);

string tokens[] = {
    "AND", "ARRAY", "BEGAN", "DIV", "DO", "DOWNTO", "ELSE", "END", "FOR", "FUNCTION", "IF", "MOD", "NOT", "OF", "OR", "PROCEDURE", "PROGRAM", "REPEAT", "THEN", "TO", "UNTIL", "VAR", "WHILE", "EQU", "NEQ", "LES", "LEQ", "GRT", "GEQ", "PLUS", "MINUS", "STAR", "SLASH", "ASSIGN", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "COLON", "SEMICOLON", "COMMA", "PERIOD", "RANGE", "ID", "INTLIT", "CHRLIT", "REALIT", "APOSTROPHE", "QUOTE", "ASPERAND", "UNDERSCORE", "ERROR"};

int row = 1;
int col = 1;
int commentLength = 0;
//--------------------------------------------------------------------
%}
%%
[ ] col++; 
[\t]    col = col + 4;
\n  row++; col = 1;
[{][^}]*[]}]    ignoreComment();
[_a-zA-Z][_a-zA-Z0-9]* return TokenMgr(ID);
[0-9]+ return TokenMgr(INTLIT);
['][.]+['] return TokenMgr(CHRLIT);
[0-9]+[\.[0-9]+]?[E[+-]?[0-9]+]? return TokenMgr(REALIT);
":=" return TokenMgr(ASSIGN);
";" return TokenMgr(SEMICOLON);
"," return TokenMgr(COMMA);
"(" return TokenMgr(LPAREN);
")" return TokenMgr(RPAREN);
"+" return TokenMgr(PLUS);
"-" return TokenMgr(MINUS);
"=" return TokenMgr(EQU);
"<>" return TokenMgr(NEQ);
"<" return TokenMgr(LES);
"<=" return TokenMgr(LEQ);
">" return TokenMgr(GRT);
">=" return TokenMgr(GEQ);
"*" return TokenMgr(STAR);
"/" return TokenMgr(SLASH);
"[" return TokenMgr(LBRACKET);
"]" return TokenMgr(RBRACKET);
":" return TokenMgr(COLON);
"." return TokenMgr(PERIOD);
".." return TokenMgr(RANGE);
"\'" return TokenMgr(APOSTROPHE);
"\"" return TokenMgr(QUOTE);
"@" return  TokenMgr(ASPERAND);
"_" return TokenMgr(UNDERSCORE);
. return TokenMgr(ERROR);
%%
//--------------------------------------------------------------------
// Lex User Subroutines
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//Class Lexer implementation
//--------------------------------------------------------------------
//Function TokenMgr processes the token after it has been recognized
//--------------------------------------------------------------------
int TokenMgr(int t)
{
if (t!=ID) return t;

// find the integer code of a reserved word
if ((string)yytext=="and") return AND;
if ((string)yytext=="array") return ARRAY;
if ((string)yytext=="begin") return BEGAN;
if ((string)yytext=="div") return DIV;
if ((string)yytext=="do") return DO;
if ((string)yytext=="downto") return DOWNTO;
if ((string)yytext=="else") return ELSE;
if ((string)yytext=="end") return END;
if ((string)yytext=="for") return FOR;
if ((string)yytext=="function") return FUNCTION;
if ((string)yytext=="if") return IF;
if ((string)yytext=="mod") return MOD;
if ((string)yytext=="of") return OF;
if ((string)yytext=="or") return OR;
if ((string)yytext=="procedure") return PROCEDURE;
if ((string)yytext=="program") return PROGRAM;
if ((string)yytext=="repeat") return REPEAT;
if ((string)yytext=="then") return THEN;
if ((string)yytext=="to") return TO;
if ((string)yytext=="until") return UNTIL;
if ((string)yytext=="var") return VAR;
if ((string)yytext=="while") return WHILE;
return ID;
}

int yywrap()
{
    return 1;
}

//--------------------------------------------------------------------
//Constructor Lexer is used to redirect the input file stream from the
//keyboard to input file stream i.
//--------------------------------------------------------------------
Lexer::Lexer(FILE* i)
{ yyin=i;
}
//--------------------------------------------------------------------
//Function Lex calls yylex
//--------------------------------------------------------------------
int Lexer::Lex(void)
{ tokencode=yylex();
 return tokencode;
}
//--------------------------------------------------------------------
//Function FetchSpelling returns a pointer to the spelling of the most
//recent token.
//--------------------------------------------------------------------
char* Lexer::FetchSpelling(void)
{
 return (char*)yytext;
}
//--------------------------------------------------------------------
//Function UpdateCol either resets or increases col by token length
//--------------------------------------------------------------------
void Lexer::UpdateCol(void)
{
    if (((string)yytext)[0] == '\n') col = 1;
    else col = col + ((string)yytext).length();
}
//Function FetchTokenCode returns the code of the most recent token
//--------------------------------------------------------------------
int Lexer::FetchTokenCode(void)
{ return tokencode;
}
//--------------------------------------------------------------------
//Function StoreTokenCode records the most recent token code
//--------------------------------------------------------------------
void Lexer::StoreTokenCode(int T)
{ tokencode=T;
}
//--------------------------------------------------------------------
//Function FetchRowPosition returns the row of the token
//--------------------------------------------------------------------
int Lexer::FetchRowPosition(void)
{ return row;
}
//Function FetchColPosition returns the row of the token
//--------------------------------------------------------------------
int Lexer::FetchColPosition(void)
{ return col;
}
//--------------------------------------------------------------------
// IgnoreComment increments col
//--------------------------------------------------------------------
void ignoreComment(void)
{ 
    commentLength = ((string)yytext).length();
    col = col + commentLength;
}
//-----------------------End of Lex Definition------------------------