#include <database.h>

/** Hashes a string into an integer.
 * @str - string to be hashed
 * @mod - a value one greater than the maximum hash value
 * Returns: an integer which is the hash.
 */
int hash(const char* str, int mod)
{
	int hashValue = 0;

	for(int i = 0; i < strlen(str); i++)
	{
		hashValue += str[i] * (i + 1);
		hashValue %= mod;
	}

	return hashValue;
}

Database newDatabase(char* format)
{
	Database db;
	db.format = format;
	db.recordCount = 0;
	db.records = malloc(sizeof(Record) * db.capacity);
	db.forest = malloc(sizeof(BTreeNode*)*strlen(format));
	db.capacity = 100;
	return db;
}

Record newRecord(int len)
{
	Record r;
	r.values = malloc(sizeof(char*)*len);
	r.numeric = malloc(sizeof(int)*len);
	r.valueCount = 0;
	return r;
}

void addIntToRecord(Record* r, int num)
{
	r->numeric[r->valueCount] = num;
	r->valueCount++;
}

void addStrToRecord(Record* r, char* str)
{
	r->values[r->valueCount] = str;
	r->numeric[r->valueCount] = hash(str, 300000);
	r->valueCount++;
}

void addRecordToDB(Database* db, Record record)
{
	if(db->recordCount >= db->capacity)
	{
		db->capacity = db->recordCount * 2;
		db->records = realloc(db->records, sizeof(Record) * db->capacity);
	}
	while(!db->records)
	{	
		db->records = realloc(db->records, sizeof(Record) * db->capacity);
	}
	db->records[db->recordCount] = record;
	for(int i = 0; i < strlen(db->format); i++)
	{
		ValueIndexPair element = {record.numeric[i], db->recordCount};
		//printf("%d %d\n", record.numeric[i], db->recordCount);
		db->forest[i] = insertIntoBTree(db->forest[i], element);
	}
	db->recordCount++;
}

void printRecordDB(Database db, int index)
{
	putchar('|');
	for(int i = 0; i < strlen(db.format); i++)
	{
		if(db.format[i] == 'i')
		{
			printf("%d ", db.records[index].numeric[i]);
			for(int j = 0; j < 18-log10(db.records[index].numeric[i]); j++)
				putchar(' ');
			putchar('|');
		}
		else if(db.format[i] == 's')
		{
			printf("%s ", db.records[index].values[i]);
			for(int j = 0; j < 19-strlen(db.records[index].values[i]); j++)
				putchar(' ');
			putchar('|');
		}
	}
	putchar('\n');
}

void printRecordColumnsDB(Database db, int index, char** columnNames, int n)
{
	putchar('|');
	for(int i = 0; i < strlen(db.format); i++)
	{
		bool toBePrinted = false;
		for(int j = 0; j < n; j++)
		{
			if(decodeColumnName(db, columnNames[j]) == i) toBePrinted = true;
		}
		if(!toBePrinted) continue;
		if(db.format[i] == 'i')
		{
			printf("%d ", db.records[index].numeric[i]);
			for(int j = 0; j < 18-log10(db.records[index].numeric[i]); j++)
				putchar(' ');
			putchar('|');
		}
		else if(db.format[i] == 's')
		{
			printf("%s ", db.records[index].values[i]);
			for(int j = 0; j < 19-strlen(db.records[index].values[i]); j++)
				putchar(' ');
			putchar('|');
		}
	}
	putchar('\n');
}

void addColumnName(Database* db, const char* name, int columnIndex)
{
	db->columns[hash(name, 1000)] = columnIndex;
	db->columnNames[columnIndex] = malloc(strlen(name));
	strcpy(db->columnNames[columnIndex], name);
}

int decodeColumnName(Database db, const char* column)
{
	return db.columns[hash(column, 1000)];
}

IntListNode* searchIntInColumn(Database db, int columnIndex, int search)
{
	return searchBTree(*db.forest[columnIndex], search);
}

IntListNode* searchStrInColumn(Database db, int columnIndex, char* search)
{
	return searchBTree(*db.forest[columnIndex], hash(search, 300000));
}

void displaySearchedRecords(Database db, IntListNode* searchResult)
{
	IntListNode* current = searchResult;
	
	while(current->next)
	{
		printRecordDB(db, current->value);
		current = current->next;
	}
}

void displaySearchedRecordColumns(Database db, IntListNode* searchResult, char** columnNames, int n)
{	
	IntListNode* current = searchResult;
	
	while(current->next)
	{
		printRecordColumnsDB(db, current->value, columnNames, n);
		current = current->next;
	}
}
