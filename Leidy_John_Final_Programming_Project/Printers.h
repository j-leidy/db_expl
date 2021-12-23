#ifndef PRINTERS_H
#define PRINTERS_H

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

void warning();
void info();
void print_column_names(string x, int col_num, int space_num, string table_name);
void print_table(sqlite3* db, string table_name, int s_num);
void send_print_all(sqlite3* db, vector<string>& tables, int s_num);

#endif
