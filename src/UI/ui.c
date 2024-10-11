#include <ui.h>

void loadStudentsDatabase(Database* db)
{
	for(int i = 0; i < 5; i++) { Record r = newRecord(4); }

	*db = newDatabase("isss");
	addColumnName(db, "StudentID", 0);
	addColumnName(db, "Name", 1);
	addColumnName(db, "Surname", 2);
	addColumnName(db, "Class", 3);
	
	TokenListNode* demoTokens;

	demoTokens = tokenize("INSERT VALUES (4, Chris, London, 4D) INTO uczniowie");
	primitiveParse(db, demoTokens);
	demoTokens = tokenize("INSERT VALUES (18, Cookie, Easy, 2C) INTO uczniowie");
	primitiveParse(db, demoTokens);
	demoTokens = tokenize("INSERT VALUES (24, Mitsubishi, White, 2A) INTO uczniowie");
	primitiveParse(db, demoTokens);
	demoTokens = tokenize("INSERT VALUES (28, Pimpus, Sadelko, 2A) INTO uczniowie");
	primitiveParse(db, demoTokens);
	demoTokens = tokenize("INSERT VALUES (29, Goro, Akechi, 2D) INTO uczniowie");
	primitiveParse(db, demoTokens);
}

int mainLoop(Database* db)
{
	TokenListNode* queryTokens;
	char queryContents[200];

	putchar('>');
	fgets(queryContents, 200, stdin);

	queryContents[strcspn(queryContents, "\n")] = 0;

	if(!strncmp(queryContents, "exit", 4)) return -1; //Exit.

	queryTokens = tokenize(queryContents);
	primitiveParse(db, queryTokens);

	return 0; //All correct.
}
