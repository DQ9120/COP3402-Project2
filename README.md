# COP3402-Project2
## COP3402 Systems Software Project 1 with
## David Qualls, Jenna Busch, and Kyle Mauter

==============================================

# Assignment Instructions
In this assignment we'll implement a lexical analyzer for PL/0. \
We'll account for numbers, identifiers, special symbols, and reserved words. \
We'll ignore spaces and comments, and recognize lexical errors. \
Grammar errors are found by the parser, and thus we will ignore them. \
To do this we'll be implementing the lexanalyzer function within lex.c \
This function is passed a string that contains the contents of the input file. \
It then returns an array of lexemes. The user specifies it's to be printed using -l in compiling. \

# Tokens
## Reserved Words
var, procedure, call, begin, end, if, do, while, read, write
## Special Symbols
. [ ] , ; := ? : ( ) == <> < <= > >= + - * / %
## Identifiers
letter (letter | digit)*
## Numbers
(digit)<sup>+</sup>
## Invisible Characters
tab or newline, detected with iscntrl() and whitespaces with isspace()
## Comments
Beign with // and end with newline or EOF ('\0') \
Comments should be ignored and not tokenized \
Newline on Macs/Linux are '\n' \
Newline on Windows are '\r\n' \
Need to account for both

# Errors
* Invalid Identifier: (identifiers don't begin with digits) \
* Number Length: (numbers at most 5 digits) \
* Identifier Length: (identifier at most 11 letters or digits)
* Invalid Symbol

# Appendixes
[Appendexes](HW2InstructionsSpring2022_Almalki.pdf)
