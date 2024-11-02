#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>

// Structure representing the node of a integer linked list. Defined as a type.
struct IntListNode
{
	int value;
	struct IntListNode* next;
} typedef IntListNode;

// Structure representing the node of a string linked list. Defined as a type.
struct StringListNode
{
	char* value;
	struct StringListNode* next;
	
} typedef StringListNode;

/** Displays an integer linked list.
 * @head - pointers to head node of the list
 * Returns: none
 */
void displayIntList(IntListNode* head);

#endif
