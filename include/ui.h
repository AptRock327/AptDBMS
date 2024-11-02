#ifndef __UI_H
#define __UI_H

#include <database.h>
#include <sql.h>

/* UI function that loads a database based on provided user arguments.
 * @db - pointer to database struct to load the database into
 * @argc - user argument count
 * @argv - array of strings provided as arguments to the program
 * Returns: string with filename of imported database on success, null pointer on failure
 */
char* loadDB(Database* db, int argc, char** argv);

/* Performs an SQL transaction from a file based on provided user arguments.
 * @db - pointer to database struct to perform the transaction on
 * @argc - user argument count
 * @argv - array of string provided as arguments to the program
 * Returns: status; 0 success, -1 no transaction to perform, -2 failure
 */
int performTransaction(Database* db, int argc, char** argv);

/* The program's main loop.
 * @db - pointer to the database struct that will be queried
 * @filename - a string with the filename of the export file
 * Returns: status; 0 success, -1 failure
 */
int mainLoop(Database* db, char* filename);

#endif
