#ifndef __UI_H
#define __UI_H

#include <database.h>
#include <sql.h>

/* Loads the demo database of students.
 * @db - pointer to the database struct that the data should be loaded into
 * Returns: none
 */
void loadStudentsDatabase(Database* db);

/* The program's main loop.
 * @db - pointer to the database struct that will be queried
 * Returns: none
 */
int mainLoop(Database* db);

#endif
