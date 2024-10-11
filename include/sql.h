#ifndef __SQL_H
#define __SQL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <list.h>
#include <database.h>

// Structure representing a lexical token for SQL interpretation. Defined as a type.
struct Token
{
	int ID;
	char* value;
} typedef Token;

// Structure representing a node of a token linked list. Defined as a type.
struct TokenListNode
{
	Token value;
	struct TokenListNode* next;
} typedef TokenListNode;

/** Turns an SQL query into a token list.
 * @SQLQuery - a string containing an SQL query
 * Returns: a pointer to a head node of the resulting token list
 */
TokenListNode* tokenize(char* SQLQuery);

/** Most likely temporary SQL token parsing function.
 * @db - pointer to database to apply query to
 * @head - pointer to head node of the token list to parse
 * Returns: none
 * TODO: Actually use an AST for fuck's sake lol
 */
void primitiveParse(Database* db, TokenListNode* head);

#endif
