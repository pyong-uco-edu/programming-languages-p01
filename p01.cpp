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
//----------------------------------------------------------------------
// File p01.cpp processes command line arguments and invokes lex (yylex)
// to find tokens in the input file.
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// C++ include files
//----------------------------------------------------------------------
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <iomanip>
using namespace std;
//----------------------------------------------------------------------
// Application include files
//----------------------------------------------------------------------
#include "p01lex.h"
//----------------------------------------------------------------------
// FileException is thrown when a file whose name is given on the command line
// cannot be opened.
//----------------------------------------------------------------------
struct FileException
{
    FileException(const char *fn)
    {
        cout << endl;
        cout << "File " << fn << " cannot be opened.";
        cout << endl;
    }
};
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Commandlineerror is thrown when too many arguments are put on the
// command line
//----------------------------------------------------------------------
struct CommandLineException
{
    CommandLineException(int m, int a)
    {
        cout << endl;
        cout << "Too many file names on the command line.";
        cout << endl;
        cout << "A maximum of " << m << " file names can appear on the command line.";
        cout << endl;
        cout << a << " file names were entered.";
        cout << endl;
        cout << "p01 (<input file name>)";
    }
};
//-----------------------------------------------------------------------
// Function LexMgr processes the input file, calls yylex, the scanner, and
// produces the output file.
//-----------------------------------------------------------------------
void LexMgr(FILE *i, ostream &o)
{
    static const char *TokenName[] =
        {"EOF", "AND", "ARRAY", "BEGAN", "DIV", "DO", "DOWNTO", "ELSE", "END", "FOR", "FUNCTION", "IF", "MOD", "NOT", "OF", "OR", "PROCEDURE", "PROGRAM", "REPEAT", "THEN", "TO", "UNTIL", "VAR", "WHILE", "EQU", "NEQ", "LES", "LEQ", "GRT", "GEQ", "PLUS", "MINUS", "STAR", "SLASH", "ASSIGN", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "COLON", "SEMICOLON", "COMMA", "PERIOD", "RANGE", "ID", "INTLIT", "CHRLIT", "REALIT", "APOSTROPHE", "QUOTE", "ASPERAND", "UNDERSCORE", "ERROR"};
    Lexer L(i); // Redirect yylex to read file i instead of
    // the command line

    for (int t = yylex(); t > 0; t = yylex())
    {
        string token = "token \"";
        token.append(L.FetchSpelling());
        token.append("\"");
        o << setw(20) << left << token;
        o << "pos(";
        o << setw(2) << right << L.FetchRowPosition() << ",";
        o << setw(2) << L.FetchColPosition() << ")";
        o << " code(";
        o << setw(2) << t;
        o << ") symbol:" << TokenName[t];
        o << endl;
        L.UpdateCol();
    }
}

//-----------------------------------------------------------------------
// Function main processes command line arguments
//-----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    try
    {
        char ifn[255], ofn[255];
        string input_file = "";
        string output_file = "";
        switch (argc)
        {
        case 1: // no files on the command line
            cout << "Enter the input file name. ";
            cin >> input_file;
            if (input_file.substr(input_file.length() - 4) != ".pas")
            {
                cout << "Error: Input file must have suffix .pas";
                throw invalid_argument("Input file must have suffix .pas");
                break;
            }
            strcpy(ifn, input_file.c_str());
            output_file = input_file.substr(0, input_file.length() - 4);
            output_file.append(".trc");
            strcpy(ofn, output_file.c_str());
            // ofn
            break;
        case 2: // input file on the command line/prompt for output file
            input_file.assign(argv[1]);
            if (input_file.substr(input_file.length() - 4) != ".pas")
            {
                cout << "Error: Input file must have suffix .pas";
                throw invalid_argument("Input file must have suffix .pas");
                break;
            }
            strcpy(ifn, input_file.c_str());
            output_file = input_file.substr(0, input_file.length() - 4);
            output_file.append(".trc");
            strcpy(ofn, output_file.c_str());
            break;
        default:
            throw CommandLineException(1, argc - 1);
            break;
        }
        FILE *i = fopen(ifn, "r");
        if (!i)
            throw FileException(ifn);
        ofstream o(ofn);
        if (!o)
            throw FileException(ofn);
        LexMgr(i, o);
        fclose(i);
        o.close();
    }
    catch (...)
    {
        cout << endl;
        cout << "Program Terminated!";
        cout << endl;
        cout << "I won't be back!";
        cout << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}