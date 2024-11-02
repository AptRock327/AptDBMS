#ifndef __DATABASE_H
#define __DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <btree.h>
#include <list.h>

// Struct representing a database record. Defined as a type.
struct Record
{
	char** values;
	int* numeric;
	unsigned int valueCount;
} typedef Record;

// Struct representing a database. Defined as a type.
struct Database
{
	char columns[1000]; //effective size of around 30 (birthday paradox)
	char* columnNames[1000];
	char insertCommands[1000][256];
	char* format;
	unsigned int recordCount;
	Record* records;
	BTreeNode** forest;
	int capacity;
	int startingRecordAmount;
} typedef Database;

/** Creates a new database.
 * @format - string storing record format
 * Returns: a newly created database
 */
Database newDatabase(char* format);

/** Creates a new record.
 * @len - amount of elements in the record
 * Returns: a newly created record
 */
Record newRecord(int len);

/** Adds an integer value to a record.
 * @r - pointer to a record
 * @num - integer to add to the record
 * Returns: none
 */
void addIntToRecord(Record* r, int num);

/** Adds a string value to a record.
 * @r - pointer to a record
 * @str - string to add to the reocrd
 * Returns: none
 */
void addStrToRecord(Record* r, char* str);

/** Adds a record to a database
 * @db - pointer to a database
 * @record - record to add
 * Returns: none
 */
void addRecordToDB(Database* db, Record record);

/** Prints the record at a given index.
 * @db - database that the record is in
 * @index - index of the record
 * Returns: none
 */
void printRecordDB(Database db, int index);

/** Prints given columns of a record at a given index. 
 * @db - database that the record is in
 * @index - index of the record
 * @columnNames - string array of names of columns to display
 * @n - amount of column names
 * Returns: none
 */
void printRecordColumnsDB(Database db, int index, char** columnNames, int n);

/** Attaches a given column index a name.
 * @db - pointer to a database with the necessary column
 * @name - string with the name to be given to the column
 * @columnIndex - column index
 * Returns: none
 */
void addColumnName(Database* db, const char* name, int columnIndex);

/** Decodes the name of a column into its column index.
 * @db - database with the necessary column
 * @column: string containing the column name
 * Returns: integer corresponding to the column index
 */
int decodeColumnName(Database db, const char* column);

/** Searches a database for an int based on column.
 * @db - database to search
 * @columnIndex - index of the column to search
 * @search - integer to search for in the B-tree of the column
 * Returns: pointer to head of list with indices where a result was found
 */
IntListNode* searchIntInColumn(Database db, int columnIndex, int search);

/** Searches a database for a string based on column.
 * @db - database to search
 * @columnIndex - index of the column to search
 * @search - string for whose hash to search for in the B-tree of the column
 * Returns: pointer to head of list with indices where a result was found
 */
IntListNode* searchStrInColumn(Database db, int columnIndex, char* search);

/** Displays records matching a search.
 * @db - database containing the records to display
 * @searchResult - pointer to head of list with search results
 * Returns: none
 */
void displaySearchedRecords(Database db, IntListNode* searchResult);

/** Displays given columns of records matching a search.
 * @db - database containing the records to display
 * @searchResult - pointer to head of list with search results
 * @columnNames - string array of names of columns to display
 * @n - amount of column names
 * Returns: none
 */
void displaySearchedRecordColumns(Database db, IntListNode* searchResult, char** columnNames, int n);

#endif
