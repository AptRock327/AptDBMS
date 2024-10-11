#include <btree.h>

//Definition: a branch point is a B-tree node that one shall come back after exploring all branches from said point
//Definition: a branch path is a local branching process equivalent of the chosenPath

/* Recounts the number of paths to possibly take.
 * @paths - pointer to an integer storing the amount of possible paths
 * @branchPoint - double pointer to the branch point (definition above)
 * @branchPath - pointer to the branch path (definition above)
 * @current - pointer to the currently explored B-tree node
 * @search - integer searched for in the B-tree
 * Returns: none
 */
void recountPaths(int* paths, BTreeNode** branchPoint, int* branchPath, int chosenPath, BTreeNode* current, int search)
{
	*paths = pathCount( current->elements, current->elementCount, search );
	*branchPoint = current;
	*branchPath = chosenPath;
}

/* Append the index of the node that was found to match the searched value.
 * @current - pointer to the currently explored B-tree node
 * @lCurrent - double pointer to tail of the list to append the index to
 * @chosenPath - pointer to the integer storing the path currently followed
 * @search - integer searched for in the B-tree
 * Returns: none
 */
void addFoundIndex(BTreeNode* current, IntListNode** lCurrent, int* chosenPath, int search)
{
	(*lCurrent)->value = current->elements[*chosenPath].index;

	IntListNode* newNode = malloc(sizeof(IntListNode));
	(*lCurrent)->next = newNode;
	*lCurrent = newNode;

	for(int i = *chosenPath + 1; i < current->elementCount; i++)
	{
		if(search != current->elements[i].value) break;
		(*lCurrent)->value = current->elements[i].index;
		IntListNode* newerNode = malloc(sizeof(IntListNode));
		(*lCurrent)->next = newerNode;
		*lCurrent = newerNode;
	}

	*chosenPath += 4;
}

IntListNode* searchBTree(BTreeNode root, int search)
{
	BTreeNode* current = &root;
	BTreeNode* branchPoint = &root;
	IntListNode* head = malloc(sizeof(IntListNode));
	IntListNode* lCurrent = head;
	int paths = 0;
	int branchPath = 0;

	while(true)
	{
		int chosenPath = decidePath( current->elements, current->elementCount, search );	

		if(paths < 1) //No paths left
		{
			recountPaths(&paths, &branchPoint, &branchPath, chosenPath, current, search);
		}

		if(chosenPath < 4) //Found!
		{
			addFoundIndex(current, &lCurrent, &chosenPath, search);
		}

		if(current->children) //Do we still have children to check?
		{
			if(current->children[chosenPath - 4]) current = current->children[chosenPath - 4]; 
			else
			{
				paths--;
				branchPath++;
				if(paths < 1) break;
				else current = branchPoint->children[branchPath - 4];
			}
		}
		else
		{
			paths--;
			if(branchPath < 4) branchPath += 4;
			branchPath++;
			if(!branchPoint->children) break;

			if(paths < 1) break;
			else current = branchPoint->children[branchPath - 4];
		}
	}

	lCurrent->value = 0;
	lCurrent->next = 0;

	return head;
}
