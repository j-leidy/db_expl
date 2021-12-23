#ifndef _HELPERS_H
#define _HELPERS_H

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
string get_column_names(sqlite3* db, string table_name, int s_num);
string get_values(sqlite3* db, string table_name, int s_num);
void get_table_names(sqlite3* db, vector<string>& tables);
void send_table_name(sqlite3* db, string which_function, vector<string>& tables, int s_num);

#endif
