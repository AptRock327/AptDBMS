#ifndef __ARRAY_H
#define __ARRAY_H

// ValueIndexPair structure which pairs two integers. Defined as a type.
struct ValueIndexPair
{
	int value;
	int index;
} typedef ValueIndexPair;

/** Shifts the elements of a ValueIndexPair array by one to the right.
 * @array - the array that the elements to be shifted are in
 * @n - the amount of actual elements in the array
 * @start - the index from which elements should be shifted
 * Returns: none
 */
void shiftArray(ValueIndexPair* array, int n, int start);

/** Inserts an element into a sorted ValueIndexPair array.
 * @array - the ValueIndexPair array for the element to be inserted into
 * @element - the ValueIndexPair to be inserted
 * @n - the amount of actual elements in the array
 * Returns: none
 */
void sortedArrayInsert(ValueIndexPair* array, int n, ValueIndexPair element);

/** Determines would the midpoint would be in the hypothetical scenario of sorted insertion.
 * @array - ValueIndexPair array to be checked
 * @element - the hypothetical element to be inserted
 * @n - the amount of actual elements in the array
 * Returns: hypothetical midpoint (ValueIndexPair)
 */
ValueIndexPair midPoint(ValueIndexPair* array, int n, ValueIndexPair element);

/** Decides the path to take in a B-tree.
 * @array - array of elements in the node of a B-tree
 * @n - the actual amount of elements in the array
 * @element - the element for the path decision
 * Returns: 0-3 for equality with elements 0-3, 4-8 for children paths
 */
int decidePath(ValueIndexPair* array, int n, int element);

/** Counts the paths that have to be taken in the B-tree.
 * @array - array of elements in the node of a B-tree
 * @n - the actual amount of elements in the array
 * @element - the element to check paths for
 * Returns: integer value corresponding to the path count
 * */
int pathCount(ValueIndexPair* array, int n, int element);

#endif
