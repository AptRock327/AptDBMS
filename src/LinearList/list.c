#include <list.h>

void displayIntList(IntListNode* head)
{
	IntListNode* current = head;
	
	while(current->next)
	{
		printf("%d; ", current->value);
		current = current->next;
	}
	putchar('\n');
}
