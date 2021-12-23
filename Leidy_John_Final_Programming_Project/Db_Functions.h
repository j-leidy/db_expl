#ifndef _DB_FUNCTIONS_H
#define _DB_FUNCTIONS_H

#include "sqlite_resources/sqlite3.h"
#include "Db_Functions.h"
#include "Menus.h"
#include "Helpers.h"
#include "Printers.h"
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
void drop_table(sqlite3* db, string table_name);
void create_table(sqlite3* db, int s_num);
void insert(sqlite3* db, string table_name, int s_num);
void update(sqlite3* db, string table_name, int s_num);
void delete_row(sqlite3* db, string table_name, int s_num);

#endif