DAVID QUALLS
JENNA BUSCH
KYLE MAUTER

In this project we implemented lexanalyzer, which goes character by character until the EOF occurs. 

If the current character is whitespace, we get the next character and continue.

If the current character is a digit, we call the numberToken function which returns the index of the next character or an error code.
If it returns -1, we have a number length error, and if it returns -2, we have an invalid identifier error.
The numberToken function uses a buffer that can hold 6 characters and a null terminator. It loops across the input starting with the current character.
If a letter occurs, we have an invalid identifier error. Otherwise, we add to our buffer until there are either 6 digits inside or a non-alphanumeric character occurs.
If the buffer has a length of 6, we have a number length error.
Otherwise it is a valid number, and we tokenize it and add it to the lexeme list.

If the current character is a letter, we call the alphaToken function which returns the index of the next character or an error code.
If it returns -1, we have an identifier length error.
The alphaToken function uses a buffer than can hold 12 characters and a null terminator. It loops across the input starting with the current character.
If a digit or letter occur, we add it to our buffer. We stop when either the buffer has 12 characters inside or a non-alphanumeric character occurs.
If the buffer has a length of 12, we have an identifier length error.
Otherwise we call the reservedCheck function to see if the buffer is a reserved word.
If the buffer is a reserved word, reservedCheck adds it accordingly to the lexeme list.
If it's not, it's added to the lexeme list as an identifier and its name is recorded.

If the current character is not whitespace or alphanumeric, we assume it is a special symbol. 
We call the symbolToken function which returns the index of the next character or an error code.
If it returns -1, we have an invalid symbol error.
The symbolToken function uses a switch statement on the current character. 
In the case of a two character special symbol, there's an if statement within those cases to check the next character.
They are then added to the lexeme list accordingly.
If we encounter a '//', we have a comment. We then loop across the input starting with the current character until we hit a new line or EOF. Then we return the new index.
In the '=' case, if the next character isn't a '=' we have an invalid symbol error.
If none of the cases hit, then we have an invalid symbol error.

In the case that any of the helper functions return an error code, the program stops and the appropriate message is printed if printFlag is true.
