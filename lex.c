/*
DAVID QUALLS
JENNA BUSCH
KYLE MAUTER
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 1000
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5

lexeme *list;
int lex_index;

int alphaToken(char * input, int inputIndex);
int numberToken(char * input, int inputIndex);
int symbolToken(char * input, int inputIndex);
int comment(char * input, int inputIndex);
int reservedcheck(char *buffer);
void printlexerror(int type);
void printtokens();

int alphaToken(char * input, int inputIndex)
{
	char curChar = input[inputIndex];
	char nextChar = input[inputIndex + 1];
	int curIndex = inputIndex;
	
	char * buffer = calloc(12, sizeof(char));
}

lexeme *lexanalyzer(char *input, int printFlag)
{
	list = malloc(sizeof(lexeme) * MAX_NUMBER_TOKENS);
	lex_index = 0;
	
	int inputIndex = 0;
	char curChar = input[inputIndex];
	
	while (curChar != '\0')
	{
		if (isctrl(curChar) || isspace(curChar))
		{
			curChar = input[++inputIndex];
			continue;
		}
		
		else if (isdigit(curChar))
		{
			inputIndex = numberToken(input, inputIndex);
			
			/// Number Length Error
			if (inputIndex == -1)
			{
				if (printFlag)
					printlexerror(2);
				break;
			}
			
			/// Invalid Identifier Error
			else if (inputIndex == -2)
			{
				if (printFlag)
					printlexerror(1);	
				break;
			}
			
			/// Reached EOF
			else if (inputIndex == -3)
				break;	
			
			/// No errors
			else
			{
				curChar = input[inputIndex];
				continue;
			}
		}
		
		else if (isalpha(curChar))
		{
			inputIndex = alphaToken(input, inputIndex);
			
			/// Identifier Length Error
			if (inputIndex == -1)
			{
				if (printFlag)
					printlexerror(3);
				break;
			}
			
			/// Reached EOF
			else if (inputIndex == -2)
				break;	
			
			/// No error
			else
			{
				curChar = input[inputIndex];
				continue;
			}
		}
		
		else
		{
			inputIndex = symbolToken(input, inputIndex);
			
			/// Invalid Symbol Error
			if (inputIndex == -1)
			{
				if (printFlag)
					printlexerror(4);
				break;
			}
			
			/// Reached EOF
			else if (inputIndex == -2)
				break;	
			
			/// No error
			else
			{
				curChar = input[inputIndex];
				continue;
			}
		}
	}
	
	if (printFlag)
		printtokens();
	list[lex_index++].type = -1;
	return list;
}

void printtokens()
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
	for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case lbracketsym:
				printf("%11s\t%d", "[", lbracketsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case rbracketsym:
				printf("%11s\t%d", "]", rbracketsym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case questionsym:
				printf("%11s\t%d", "?", questionsym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case colonsym:
				printf("%11s\t%d", ":", colonsym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case lparenthesissym:
				printf("%11s\t%d", "(", lparenthesissym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case rparenthesissym:
				printf("%11s\t%d", ")", rparenthesissym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
			case neqsym:
				printf("%11s\t%d", "<>", neqsym);
				break;
			case modsym:
				printf("%11s\t%d", "%", modsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case subsym:
				printf("%11s\t%d", "-", subsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case addsym:
				printf("%11s\t%d", "+", addsym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			default:
				printf("%11s\t%s", "err", "err");
				break;
		}
		printf("\n");
	}
	printf("\n");
}

void printlexerror(int type)
{
	if (type == 1)
		printf("Lexical Analyzer Error: Invalid Identifier\n");
	else if (type == 2)
		printf("Lexical Analyzer Error: Number Length\n");
	else if (type == 3)
		printf("Lexical Analyzer Error: Identifier Length\n");
	else if (type == 4)
		printf("Lexical Analyzer Error: Invalid Symbol\n");
	else
		printf("Implementation Error: Unrecognized Error Type\n");
	
	free(list);
	return;
}
