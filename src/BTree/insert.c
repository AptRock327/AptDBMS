#include <btree.h>

/* Initializes a root with a given ValueIndexPair.
 * @root - double pointer to a B-tree root node
 * @element - the ValueIndexPair for the node to contain
 * Returns: none
 */
void initializeRoot(BTreeNode** root, ValueIndexPair element)
{
	*root = malloc(sizeof(BTreeNode));
	(*root)->children = NULL;
	(*root)->parent = NULL;
	(*root)->elements[0] = element;
	(*root)->elementCount = 1;
	(*root)->isRoot = true;
}

BTreeNode* insertIntoBTree(BTreeNode* root, ValueIndexPair element)
{
	if(!root)
	{
		initializeRoot(&root, element);
		return root;
	}

	BTreeNode* current = root;
	int path;

	while(current->children) //Go to leaf.
	{
		path = decidePath( current->elements, current->elementCount, element.value );
		if(path >= 4) path-=4;
		if(current->children[path]) current = current->children[path];
		else
		{
			current->children = malloc(sizeof(BTreeNode*) * 6);

			BTreeNode* newChild = malloc(sizeof(BTreeNode));
			newChild->elementCount = 0;
			newChild->isRoot = false;
			newChild->parent = current;
			current->children[path] = newChild;
			current = newChild;
		}
	}

	if(current->elementCount < 4) //Can we safely insert?
	{
			//If yes, insert.
			sortedArrayInsert(current->elements, current->elementCount, element);
			current->elementCount++;
			return root;
	}

	ValueIndexPair midp = midPoint(current->elements, current->elementCount, element);

	//If not, ascend until we hit the root or a node where we can safely insert.
	while(!current->isRoot)
	{
		current = current->parent;
		if(current->elementCount < 4)
		{
			sortedArrayInsert(current->elements, current->elementCount, midp);
			current->elementCount++;
			return root;
		}
	}
	
	//Ascended all the way to the root? Split it and apply standard "recursive" B-tree insertion.

	sortedArrayInsert(current->elements, current->elementCount, element);
	current->elementCount >>= 1;
	current->isRoot = false;

	BTreeNode* splitNode = malloc(sizeof(BTreeNode));
	splitNode->elements[0] = current->elements[3];
	splitNode->elements[1] = current->elements[4];
	if(current->children)
	{
		splitNode->children = malloc(sizeof(BTreeNode*) * 6);
		if(current->children[3])
		{
			splitNode->children[3] = current->children[3];
			current->children[3] = NULL;
		}
		if(current->children[4])
		{
			splitNode->children[4] = current->children[4];
			current->children[4] = NULL;
		}
	}
	splitNode->elementCount = 2;
	splitNode->isRoot = false;		

	BTreeNode* newRoot = malloc(sizeof(BTreeNode));
	newRoot->elements[0] = current->elements[2];
	newRoot->elementCount = 1;
	newRoot->isRoot = true;
	newRoot->children = malloc(sizeof(BTreeNode*) * 6);
	newRoot->children[0] = current;
	newRoot->children[1] = splitNode;

	current->parent = newRoot;
	splitNode->parent = newRoot;

	//Return the new root created during the B-tree splitting process.

	return newRoot;
}
