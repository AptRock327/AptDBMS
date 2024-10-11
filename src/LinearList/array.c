#include <array.h>

void shiftArray(ValueIndexPair* array, int n, int start)
{
	for(int i = n; i > start; i--)
	{
		array[i] = array[i - 1];
	}
}

void sortedArrayInsert(ValueIndexPair* array, int n, ValueIndexPair element)
{
	for(int i = 0; i < n; i++)
	{
		if(element.value < array[i].value)
		{
			shiftArray(array, n, i);
			array[i].value = element.value;
			array[i].index = element.index;
			return;
		}
	}

	array[n].value = element.value;
	array[n].index = element.index;
}

ValueIndexPair midPoint(ValueIndexPair* array, int n, ValueIndexPair element)
{
	ValueIndexPair arr[n+1];
	for(int i = 0; i < n; i++)
	{
		arr[i] = array[i];
	}
	sortedArrayInsert(arr, n, element);
	return arr[n/2];
}

int decidePath(ValueIndexPair* array, int n, int element)
{
	for(int i = 0; i < n; i++)
	{
		if(element == array[i].value)
			return i;
	}
	
	for(int i = 0; i < n; i++)
	{
		if(element < array[i].value)
			return 4 + i;
	}

	return 4 + n;
}

int pathCount(ValueIndexPair* array, int n, int element)
{
	for(int i = 0; i < n; i++)
	{
		if(element <= array[i].value)
		{
			for(int j = i + 1; j < n; j++)
			{
				if(array[i].value != array[j].value)
				{
					return j - i;
				}
			}
			return n - i;
		}
	}

	return 1;
}
