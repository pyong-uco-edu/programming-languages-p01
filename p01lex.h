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
#ifndef p01lex_h
#define p01lex_h 1
//--------------------------------------------------------------------
// File p01lex.h defines class Lexer.
//--------------------------------------------------------------------
// Author: Thomas R. Turner
// E-Mail: trturner.uco.edu
// Date: March, 2003
//--------------------------------------------------------------------
// Revised January, 2015
//--------------------------------------------------------------------
// Copyright March, 2003 by Thomas R. Turner
// Do not reproduce without permission from Thomas R. Turner.
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Standard C and C++ include files
//--------------------------------------------------------------------
#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;
//--------------------------------------------------------------------
// Token definitions
//--------------------------------------------------------------------
// #include "y.tab.h"
#include "p01tkn.h"
//--------------------------------------------------------------------
// Function: yylex
// Function yylex is the p01ner. Function yylex returns an integer
// token code as defined above or 0 if end-of-file has been
// reached.
//--------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
#endif
    int
    yylex(void);
//--------------------------------------------------------------------
// Class Lexer defines the attributes of a Scanner
//--------------------------------------------------------------------
class Lexer
{
    int tokencode; // Code for the most recent token found
public:
    Lexer(FILE *i);             // Constructor used to redirect the keyboard
                                //(stdin) to file i.
    int Lex(void);              // Call the scanner yylex and return the code
                                // found by yylex
    int FetchTokenCode(void);   // Return the code of the most recent token
    void StoreTokenCode(int T); // Store the token code.
    char *FetchSpelling(void);  // Return the spelling of the most recent
                                // token
    void UpdateCol(void);       // either resets or increases col by token length
    int FetchRowPosition(void); // Return the token row
    int FetchColPosition(void); // Return the token column
};
#endif