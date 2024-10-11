#ifndef __BTREE_H
#define __BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <array.h>
#include <list.h>

// Structure representing the node of a B-tree. Defined as a type.
struct BTreeNode
{
	ValueIndexPair elements[5];
	int elementCount;
	bool isRoot;
	struct BTreeNode* parent;
	struct BTreeNode** children; //5
	struct BTreeNode** siblings; //4
} typedef BTreeNode;

/** Searches for all instances of an integer value in a B-tree.
 * @root - root node of the B-tree
 * @search - integer to search for in the B-tree
 * Returns: pointer to head of an int list with indeces matching the search; if the value of the head is zero, no instance was found
 */
IntListNode* searchBTree(BTreeNode root, int search);

/** Inserts a ValueIndexPair into a B-tree.
 * @root - pointer to root node of the B-tree
 * @element - ValueIndexPair to insert into the B-tree
 * Returns: current root node pointer
 */
BTreeNode* insertIntoBTree(BTreeNode* root, ValueIndexPair element);

#endif
