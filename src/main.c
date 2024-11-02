/* AptDBMS is a DataBase Management System released under
 * GNU GPLv2 by Dominik Śliwiński.
 *
 * It was created to deepen the author's understanding of
 * B-trees, as a mental exercise, and as a way to pass time.
 */

#include <stdio.h>

#include <database.h>
#include <ui.h>

int main(int argc, char** argv)
{
	Database db;
	char* dbFile;

	//Load database. Inform the user whether it was loaded successfully. Quit on failure.
	if(dbFile = loadDB(&db, argc, argv)) printf("Loaded database successfully.\n\n");
	else
	{
		printf("Couldn't import database.\nComitting suicide.\n");
		return -1;
	}

	//Was there a database transaction provided?
	switch(performTransaction(&db, argc, argv))
	{
		case -2: //Yes and there was a failure? Inform the user and quit.
			printf("Transaction failure.\nComitting suicide.\n");
			return -1;
		case 0: //Yes and it went successfully? Inform the user and quit.
			printf("Transaction success.\nExiting program.\n");
			return 0;
	} //If not, continue to main loop.

	while(true)
	{
		//Execute the main loop. Return value not zero? Quit.
		if(mainLoop(&db, dbFile)) break;
	}

	return 0;
}
