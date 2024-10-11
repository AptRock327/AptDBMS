#include <sql.h>

/** Adds a new token with a given ID to a token list node.
 * @tokenID - integer containing the token's ID
 * @curr - double pointer to the token list's tail
 * Returns: none
 */
void addNewToken(int tokenID, TokenListNode** curr)
{
	Token newToken;
	newToken.ID = tokenID;
	TokenListNode* current = *curr;
	current->value = newToken;
	TokenListNode* newNode = malloc(sizeof(TokenListNode));
	current->next = newNode;
	*curr = current->next;
}

// Same as above but sets a string value for the token as well.
void addNewTokenWithValue(int tokenID, char* value, TokenListNode** curr)
{
	Token newToken;
	newToken.ID = tokenID;
	newToken.value = value;
	TokenListNode* current = *curr;
	current->value = newToken;
	TokenListNode* newNode = malloc(sizeof(TokenListNode));
	current->next = newNode;
	*curr = current->next;
}

TokenListNode* tokenize(char* SQLQuery)
{
	TokenListNode* head = malloc(sizeof(TokenListNode));
	TokenListNode* current = head;

	char* query = malloc(strlen(SQLQuery)+1);
	strcpy(query, SQLQuery);

	while(*query)
	{
		if(*query == ' ')
		{
			query++;
			continue;
		}

		bool notFound = false;

		switch(*query)
		{
			case '(':
				addNewToken(7, &current);
				break;
			case ')':
				addNewToken(8, &current);
				break;
			case ',':
				addNewToken(9, &current);
				break;
			case '*':
				addNewToken(10, &current);
				break;
			case '\'':
				addNewToken(11, &current);
				break;
			case '=':
				addNewToken(12, &current);
				break;
			default:
				notFound = true;
				break;
		}

		if(!strncmp(query, "SELECT", 6)) {addNewToken(1, &current); query += 6;}
		else if(!strncmp(query, "FROM", 4)) {addNewToken(2, &current); query += 4;}
		else if(!strncmp(query, "WHERE", 5)) {addNewToken(3, &current); query += 5;}
		else if(!strncmp(query, "INSERT", 6)) {addNewToken(4, &current); query += 6;}
		else if(!strncmp(query, "INTO", 4)) {addNewToken(5, &current); query += 4;}
		else if(!strncmp(query, "VALUES", 6)) {addNewToken(6, &current); query += 6;}
		else if(notFound)
		{
			int length = 0;
			while((*query != ' ') && (*query != '\0')
				&& (*query != '=') && (*query != '\'')
				&& (*query != ',') && (*query != '(')
				&& (*query != ')'))
			{
				length++;
				query++;
			}
			char* str = malloc(length+1);
			strncpy(str, query-length, length);
			addNewTokenWithValue(0, str, &current);
			continue;
		}

		query++;	
	}

	current = head;
	
	return head;
}
