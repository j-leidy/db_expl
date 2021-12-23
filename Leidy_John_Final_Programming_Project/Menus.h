#ifndef MENUS_H_
#define MENUS_H_

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

int space_num();
string new_or_existing(string c);
string main_menu(string c);
void menu_help(sqlite3* mydb, vector<string>& tables, int s_num);

#endif
