#include <ui.h>

/* Executes an SQL file.
 * @db - pointer to database to execute the SQL file on
 * @filename - filename of the SQL file
 * @transaction - is this a transaction?
 * Returns: status integer; 0 success, -1 failure
 */
int executeFile(Database* db, char* filename, bool transaction)
{
	FILE* file = fopen(filename, "r");

    	char line[256];
	int inserts = 0;

    	if (file != NULL)
	{
		while (fgets(line, sizeof(line), file))
		{
			line[strcspn(line, "\n")] = 0;
			if(primitiveParse(db, tokenize(line)) == 1)
			{
				if(transaction) strcpy(db->insertCommands[db->recordCount-1], line);
				else inserts++;
			}
			memset(line, 0, sizeof(line));
		}
        	fclose(file);
    	}
	else return -1;

	if(!transaction) db->startingRecordAmount = inserts;

	return 0;
}

/* Dumps a database to an aptdb file.
 * @db - database to dump
 * @filename - filename of the file to dump the database into
 * Returns: none
 */
void dumpDatabaseToFile(Database db, char* filename)
{
	FILE* file = fopen(filename, "a");
	for(int i = db.startingRecordAmount; i < db.recordCount; i++)
	{
		fprintf(file, db.insertCommands[i]);
		fprintf(file, "\n");
	}
	fclose(file);
}

/* Loads a database from a file to a database struct (auxiliary function).
 * @db - pointer to the database struct that the data should be loaded into
 * @filename - a string with the filename of the import file
 * Returns: status; 0 success, -1 failure
 */
int loadDatabase(Database* db, char* filename)
{
	for(int i = 0; i < 5; i++) { Record r = newRecord(4); }

	*db = newDatabase("isss");
	addColumnName(db, "StudentID", 0);
	addColumnName(db, "Name", 1);
	addColumnName(db, "Surname", 2);
	addColumnName(db, "Class", 3);
	
	if(executeFile(db, filename, false)) return -1;

	return 0;
}

char* loadDB(Database* db, int argc, char** argv)
{	
	char* str = malloc(256);

	if(argc > 1)
	{
		if(loadDatabase(db, argv[1])) //Load, if loading failed...
		{
			return 0;
		}
		//...otherwise continue.
		strcpy(str, argv[1]);
	}
	else
	{
		printf("Using demo database with 'students' table...\n");
		if(loadDatabase(db, "students.aptdb")) //Load, if loading failed...
		{
			return 0;
		}
		//...otherwise continue.
		strcpy(str, "students.aptdb");
	}

	return str;
}

int performTransaction(Database* db, int argc, char** argv)
{
	if(argc > 2)
	{
		if(executeFile(db, argv[2], true)) return -2;
		dumpDatabaseToFile(*db, argv[1]);
	}
	else return -1;
}

int mainLoop(Database* db, char* filename)
{
	TokenListNode* queryTokens;
	char queryContents[200];

	putchar('>');
	fgets(queryContents, 200, stdin);

	queryContents[strcspn(queryContents, "\n")] = 0;

	if(!strncmp(queryContents, "exit", 4))
	{
		dumpDatabaseToFile(*db, filename);
		return -1; //Exit.
	}

	queryTokens = tokenize(queryContents);
	if(primitiveParse(db, queryTokens) == 1)
	{
		strcpy(db->insertCommands[db->recordCount-1], queryContents);
	}
	free(queryTokens);

	return 0; //All correct.
}
