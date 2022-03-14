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
int reservedCheck(char *buffer);
void printlexerror(int type);
void printtokens();

int alphaToken(char * input, int inputIndex)
{
	char curChar = input[inputIndex];
	char nextChar = input[inputIndex + 1];
	int curIndex = inputIndex;
	
	char buffer[13] = "\0";
	strncat(buffer, &curChar, 1);
	
	while (strlen(buffer) < 12)
	{
		if (isdigit(nextChar) || isalpha(nextChar))
		{
			curChar = nextChar;
			curIndex++;
			strncat(buffer, &curChar, 1);
			nextChar = input[curIndex + 1];
			continue;
		}
		
		break;
	}
	
	/// Identifier Length Error
	if (strlen(buffer) == 12)
		return -1;
	
	/// If buffer is a reserved word, it will be handled within reservedCheck
	/// Otherwise buffer is an identifier
	if (reservedCheck(buffer) == 0)
	{
		list[lex_index].type = identsym;
		strcpy(list[lex_index++].name, buffer);
	}
	
	return ++curIndex;
}

int reservedCheck(char * buffer)
{
	token_type type;
	
	if (strcmp(buffer, "var") == 0)
		type = varsym;
	else if (strcmp(buffer, "procedure") == 0)
		type = procsym;
	else if (strcmp(buffer, "call") == 0)
		type = callsym;
	else if (strcmp(buffer, "begin") == 0)
		type = beginsym;
	else if (strcmp(buffer, "end") == 0)
		type = endsym;
	else if (strcmp(buffer, "if") == 0)
		type = ifsym;
	else if (strcmp(buffer, "do") == 0)
		type = dosym;
	else if (strcmp(buffer, "read") == 0)
		type = readsym;
	else if (strcmp(buffer, "write") == 0)
		type = writesym;
	else if (strcmp(buffer, "while") == 0)
		type = whilesym;
	else
		return 0;
	
	list[lex_index++].type = type;
	return 1;
}

int numberToken(char * input, int inputIndex)
{
	char curChar = input[inputIndex];
	char nextChar = input[inputIndex + 1];
	int curIndex = inputIndex;
	
	char buffer[7] = "\0";
	strncat(buffer, &curChar, 1);
	
	while (strlen(buffer) < 6)
	{
		/// Invalid Identifier Error
		if (isalpha(nextChar))
			return -2;
		
		else if (isdigit(nextChar))
		{
			curChar = nextChar;
			curIndex++;
			strncat(buffer, &curChar, 1);
			nextChar = input[curIndex + 1];
			continue;
		}
		
		break;
	}
	
	/// Number Length Error
	if (strlen(buffer) == 6)
		return -1;
	
	list[lex_index].type = numbersym;
	list[lex_index++].value = atoi(buffer);
	return ++curIndex;
}

int symbolToken(char * input, int inputIndex)
{
	char curChar = input[inputIndex];
	char nextChar = input[inputIndex + 1];
	int curIndex = inputIndex;
	
	switch (curChar)
	{
		case '.':
			list[lex_index++].type = periodsym;
			return ++inputIndex;
		case '[':
			list[lex_index++].type = lbracketsym;
			return ++inputIndex;
		case ']':
			list[lex_index++].type = rbracketsym;
			return ++inputIndex;
		case ',':
			list[lex_index++].type = commasym;
			return ++inputIndex;
		case ';':
			list[lex_index++].type = semicolonsym;
			return ++inputIndex;
		case '?':
			list[lex_index++].type = questionsym;
			return ++inputIndex;
		case '(':
			list[lex_index++].type = lparenthesissym;
			return ++inputIndex;
		case ')':
			list[lex_index++].type = rparenthesissym;
			return ++inputIndex;
		case '%':
			list[lex_index++].type = modsym;
			return ++inputIndex;
		case '*':
			list[lex_index++].type = multsym;
			return ++inputIndex;
		case '-':
			list[lex_index++].type = subsym;
			return ++inputIndex;
		case '+':
			list[lex_index++].type = addsym;
			return ++inputIndex;
		case '<':
			if (nextChar == '>')
			{
				list[lex_index++].type = neqsym;
				return inputIndex + 2;
			}
			
			if (nextChar == '=')
			{
				list[lex_index++].type = leqsym;
				return inputIndex + 2;
			}
			
			list[lex_index++].type = lsssym;
			return ++inputIndex;
		case ':':
			if (nextChar == '=')
			{
				list[lex_index++].type = assignsym;
				return inputIndex + 2;
			}

			list[lex_index++].type = colonsym;
			return ++inputIndex;
		case '=':
			if (nextChar == '=')
			{
				list[lex_index++].type = eqlsym;
				return inputIndex + 2;
			}
			
			return -1;
		case '>':
			if (nextChar == '=')
			{
				list[lex_index++].type = geqsym;
				return inputIndex + 2;
			}
			
			list[lex_index++].type = gtrsym;
			return ++inputIndex;
		case '/':
			/// I think this correctly handles comments, won't know till test
			if (nextChar == '/')
			{
				curChar = nextChar;
				curIndex++;
				while (curChar != '\n' || curChar != '\0')
				{
					curChar = input[++curIndex];
				}
				
				return ++curIndex;
			}
			
			list[lex_index++].type = divsym;
			return ++inputIndex;
		default:
			return -1;
	}
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
