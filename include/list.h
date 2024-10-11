#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>

// Structure representing the node of a integer linked list. Defined as a type.
struct IntListNode
{
	int value;
	struct IntListNode* next;
} typedef IntListNode;

/** Displays an integer linked list.
 * @head - pointers to head node of the list
 * Returns: none
 */
void displayIntList(IntListNode* head);

#endif
