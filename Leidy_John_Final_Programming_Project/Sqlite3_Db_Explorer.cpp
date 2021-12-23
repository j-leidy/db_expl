/*


			---------------------------------------------------------------------------------------------
			Author: John Leidy II
			Date: 12/02/2021
			Version: 1.0
			Description: SQLITE3 c++ program
			---------------------------------------------------------------------------------------------



*/


#include "sqlite_resources/sqlite3.h"
#include "Db_Functions.h"
#include "Menus.h"
#include "Helpers.h"
#include "Printers.h"
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;








int main()
{
	int test_variable_for_push = 0;
	sqlite3* mydb;
	vector<string> tables;
	int s_num;
	//promt the user to run the program in fullscreen for best formatting
	warning();
	info();
	s_num = space_num();

	string c;
	string db_file_name;
	const char* f;
	c = new_or_existing(c);
	bool done = false;
	bool found = false;
	while (!done) {
		if (c == "1") {
			cout << "Please enter the name for your new database (.db must be put at the end of your choice of name):   \n";
			getline(cin, db_file_name);
			f = db_file_name.c_str();
			sqlite3_open(f, &mydb);
			menu_help(mydb, tables, s_num);
			done = true;
		}
		else if (c == "2") {
			while (!found) {
				cout << "Please enter the exact filename with .(filetype):  \n";
				getline(cin, db_file_name);
				ifstream isfile(db_file_name);
				if (isfile) {
					f = db_file_name.c_str();
					sqlite3_open(f, &mydb);
					menu_help(mydb, tables, s_num);
					done = true;
					found = true;
				}
				else {
					cout << "\n\nFile not found!\n\n";
				}
			}
		}
	}

}
