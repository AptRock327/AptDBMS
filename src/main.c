/* AptDBMS is a DataBase Management System released under
 * GNU GPLv2 by Dominik Śliwiński.
 *
 * It was created to deepen the author's understanding of
 * B-trees, as a mental exercise, and as a way to pass time.
 */

#include <stdio.h>

#include <array.h>
#include <list.h>
#include <btree.h>
#include <database.h>
#include <sql.h>
#include <ui.h>

int main()
{
	printf("Using demo database with 'students' table...\n");
	
	Database db;
	loadStudentsDatabase(&db);

	printf("Loaded demo database successfully.\n\n");

	while(true)
	{
		//Execute the main loop. Return value not zero? Quit.
		if(mainLoop(&db)) break;
	}

	return 0;
}
