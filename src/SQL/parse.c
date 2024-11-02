#include <sql.h>

/** Warning: this is the shittiest parser I have ever written.
 * This is a primitive parser that should be ideally rewritten entirely.
 * "Working" is the only thing it does - and that's enough for
 * the project at the moment.
 *
 * Please, never, by any means, consider this an example of good code.
 * One would have to be under the influence of a high amount
 * of illicit substances to consider this remotely OK.
 * Cheers.
 */

void displayTableTitle(Database db, const char* tableName, int columnDisplayCount)
{
	int subValue;
	if(strlen(tableName) & 1) subValue = strlen(tableName)/2;
	else subValue = strlen(tableName)/2 - 1;
	for(int i = 0; i < (columnDisplayCount * 21 + 1)/2 - subValue; i++)
		putchar('=');
	printf("%s", tableName);
	if(columnDisplayCount & 1)
	{
		for(int i = 0; i < (columnDisplayCount * 21 + 1)/2 - subValue - 1; i++)
			putchar('=');
	}
	else
	{
		for(int i = 0; i < (columnDisplayCount * 21 + 1)/2 - strlen(tableName)/2; i++)
			putchar('=');
	}
	putchar('\n');

}

int handleSelect(Database db, TokenListNode* head)
{
	bool displayAll = false;
	int columnDisplayCount = 0;
	TokenListNode* current;
	char** columns;	

	if(head->next) current = head->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}	

	if(current->value.ID == 10) displayAll = true;
	else
	{
		if(current->value.ID != 7) {printf("SYNTAX ERROR: '(' or '*' SYMBOL EXPECTED\n"); return -1;}
		columns = malloc(sizeof(char*) * 30); //effective size
		current = current->next;
	
		while(current->value.ID != 8)
		{
			if(current->value.ID == 9)
			{
				if(current->next) current = current->next;
				else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
				continue;
			}
			columns[columnDisplayCount] = malloc(100);
			strcpy(columns[columnDisplayCount], current->value.value);	
			columnDisplayCount++;	
			if(current->next) current = current->next;
			else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
		}
	}

	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
	if(current->value.ID != 2) {printf("SYNTAX ERROR: 'FROM' KEYWORD EXPECTED\n"); return -1;}
	
	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
	//TODO: Handle multiple tables for one database.
	const char* tableName = current->value.value;

	if(current->next->next) current = current->next;
	else
	{
		if(displayAll)
		{
			displayTableTitle(db, tableName, strlen(db.format));
			putchar('|');
			for(int i = 0; i < strlen(db.format); i++)
			{
				printf("%s ", db.columnNames[i]);
				for(int j = 0; j < 19-strlen(db.columnNames[i]); j++)
					putchar(' ');
				putchar('|');
			}
			putchar('\n');

			putchar('|');
			for(int i = 0; i < strlen(db.format); i++)
			{
				for(int j = 0; j < 20; j++)
					putchar('-');
				putchar('|');
			}
			putchar('\n');
			for(int i = 0; i < db.recordCount; i++)
				printRecordDB(db, i);
			for(int i = 0; i < strlen(db.format) * 21 + 1; i++)
				putchar('=');
			putchar('\n');
		}
		else
		{
			displayTableTitle(db, tableName, columnDisplayCount);
			putchar('|');
			for(int i = 0; i < columnDisplayCount; i++)
			{
				printf("%s ", columns[i]);
				for(int j = 0; j < 19-strlen(columns[i]); j++)
					putchar(' ');
				putchar('|');
			}
			putchar('\n');

			putchar('|');
			for(int i = 0; i < columnDisplayCount; i++)
			{
				for(int j = 0; j < 20; j++)
					putchar('-');
				putchar('|');
			}
			putchar('\n');
			for(int i = 0; i < db.recordCount; i++)
				printRecordColumnsDB(db, i, columns, columnDisplayCount);
			for(int i = 0; i < columnDisplayCount * 21 + 1; i++)
				putchar('=');
			putchar('\n');
		}

		return 0;
	}
	
	if(current->value.ID != 3) {printf("SYNTAX ERROR: 'WHERE' KEYWORD EXPECTED\n"); return -1;}
	
	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
	if(current->value.ID != 0) {printf("UNEXPECTED EXPRESSION\n"); return -1;}
	const char* column = current->value.value;
	
	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
	
	if(current->value.ID != 12) {printf("SYNTAX ERROR: '=' SYMBOL EXPECTED\n"); return -1;}
	
	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}

	IntListNode* searchResults;
	
	if(current->value.ID == 11)
	{
		if(current->next) current = current->next;
		else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}

		searchResults = searchStrInColumn(db, 
			decodeColumnName(db, column), current->value.value);
	}
	else
	{
		searchResults = searchIntInColumn(db, 
			decodeColumnName(db, column), atoi(current->value.value));
	}

	if(displayAll)
	{	
		displayTableTitle(db, tableName, strlen(db.format));
		putchar('|');
		for(int i = 0; i < strlen(db.format); i++)
		{
			printf("%s ", db.columnNames[i]);
			for(int j = 0; j < 19-strlen(db.columnNames[i]); j++)
				putchar(' ');
			putchar('|');
		}
		putchar('\n');

		putchar('|');
		for(int i = 0; i < strlen(db.format); i++)
		{
			for(int j = 0; j < 20; j++)
				putchar('-');
			putchar('|');
		}
		putchar('\n');
		displaySearchedRecords(db, searchResults);
		for(int i = 0; i < strlen(db.format) * 21 + 1; i++)
			putchar('=');
		putchar('\n');
	}
	else
	{
		displayTableTitle(db, tableName, columnDisplayCount);
		putchar('|');
		for(int i = 0; i < columnDisplayCount; i++)
		{
			printf("%s ", columns[i]);
			for(int j = 0; j < 19-strlen(columns[i]); j++)
				putchar(' ');
			putchar('|');
		}
		putchar('\n');

		putchar('|');
		for(int i = 0; i < columnDisplayCount; i++)
		{
			for(int j = 0; j < 20; j++)
				putchar('-');
			putchar('|');
		}
		putchar('\n');
		displaySearchedRecordColumns(db, searchResults, columns, columnDisplayCount);
		for(int i = 0; i < columnDisplayCount * 21 + 1; i++)
			putchar('=');
		putchar('\n');
	}

	return 0;
}

int handleInsert(Database* db, TokenListNode* head)
{	
	TokenListNode* current;
	unsigned int columnDisplayCount = 0;
	char** columns;

	if(head->next) current = head->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}

	if(current->value.ID != 6) {printf("SYNTAX ERROR: 'VALUES' KEYWORD EXPECTED\n"); return -1;}
	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}

	if(current->value.ID != 7) {printf("SYNTAX ERROR: '(' or '*' SYMBOL EXPECTED\n"); return -1;}
	columns = malloc(sizeof(char*) * strlen(db->format));
	current = current->next;
	
	while(current->value.ID != 8)
	{
		if(current->value.ID == 9)
		{
			if(current->next) current = current->next;
			else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
			continue;
		}
		columns[columnDisplayCount] = malloc(100);
		strcpy(columns[columnDisplayCount], current->value.value);	
		columnDisplayCount++;	
		if(current->next) current = current->next;
		else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}
	}

	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}

	if(current->value.ID != 5) {printf("SYNTAX ERROR: 'INTO' KEYWORD EXPECTED\n"); return -1;}
	if(current->next) current = current->next;
	else {printf("UNEXPECTED QUERY TERMINATION\n"); return -1;}

	if(current->value.ID != 0) {printf("SYNTAX ERROR: TABLE NAME NOT PROVIDED\n"); return -1;}

	Record r = newRecord(strlen(db->format));
	for(int i = 0; i < strlen(db->format); i++)
	{	
		switch(db->format[i])
		{
			case 'i':
				addIntToRecord(&r, atoi(columns[i]));
				break;
			case 's':	
				addStrToRecord(&r, columns[i]);
				break;
			default:
				addStrToRecord(&r, columns[i]); //blob
				break;
		}
		
	}
	addRecordToDB(db, r);

	return 0;
}

int primitiveParse(Database* db, TokenListNode* head)
{
	TokenListNode* current = head;

	while(current->next)
	{
		current = current->next;
	}

	clock_t t;
	int status;

	switch(head->value.ID)
	{
		case 1:
			putchar('\n');
			t = clock();
			status = handleSelect(*db, head);
			t = clock() - t;
			if(status) printf("SELECTing failed\n"); 
			else printf("\nSELECTed successfully in %f seconds.\n", ((double)t)/CLOCKS_PER_SEC);
			break;
		case 4:
			t = clock();
			status = handleInsert(db, head);
			t = clock() - t;
			if(status) printf("INSERTing failed\n");
			else
			{
				printf("INSERTed successfully in %f seconds.\n", ((double)t)/CLOCKS_PER_SEC);
				return 1;
			}
			break;
		default:
			printf("UNKNOWN COMMAND\n");
			break;
	}

	return status;
}
