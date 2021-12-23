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

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

string get_column_names(sqlite3* db, string table_name, int s_num) {
	string column_names = "";
	sqlite3_stmt* stmt1;
	string error1;
	string query1;
	query1 = "SELECT * FROM " + table_name + ";";


	if (sqlite3_prepare_v2(db, query1.c_str(), -1, &stmt1, NULL) != SQLITE_OK) {
		error1 = sqlite3_errmsg(db);
		sqlite3_finalize(stmt1);
		cout << "There was an error: " << error1 << "\n";
	}
	else {
		int cols = sqlite3_column_count(stmt1);
		for (int i = 0; i < cols; i++) {

			//adding all column names to our column name string
			column_names += reinterpret_cast<const char*>(sqlite3_column_name(stmt1, i));
			
			//do not put a comma after the last column name
			if (i < cols - 1) {
				column_names += ", ";
			}
		}
		cout << "\n\n"<< "Column names generated: " << column_names << "\n\n";
	}
	sqlite3_finalize(stmt1);

	return column_names;
}

string get_values(sqlite3* db, string table_name, int s_num) {
	string column_names = "";
	string temp = "";
	string values = "";
	sqlite3_stmt* stmt1;
	string error1;
	string query1;
	query1 = "SELECT * FROM " + table_name + ";";

	if (sqlite3_prepare_v2(db, query1.c_str(), -1, &stmt1, NULL) != SQLITE_OK) {
		error1 = sqlite3_errmsg(db);
		sqlite3_finalize(stmt1);
		cout << "There was an error: " << error1 << "\n";
	}
	else {
		int cols = sqlite3_column_count(stmt1);
		for (int i = 0; i < cols; i++) {
			//adding all column names to our column name string
			column_names += sqlite3_column_name(stmt1, i);
			cout << "Enter " << sqlite3_column_name(stmt1, i) << ": ";
			values += "'";
			getline(cin, temp);
			values += temp;
			if (i < cols - 1) {
				values += "', ";
			}
			if (i == cols - 1) {
				values += "'";
			}

		}
	}
	sqlite3_finalize(stmt1);
	cout << "SQL values statement generated: " << values << "\n";
	return values;
}

void get_table_names(sqlite3* db, vector<string>& tables) {
	int num = 0;
	vector<char> return_cars;
	//statement to grab table names
	string query = "SELECT name FROM sqlite_master WHERE type = 'table';";
	sqlite3_stmt* stmt;
	string error;
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
		error = sqlite3_errmsg(db);
		sqlite3_finalize(stmt);
		cout << "There was an error: " << error << "\n";
		return;
	}
	else {
		num = sqlite3_column_count(stmt);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			for (int i = 0; i < num; i++) {
				//add table names to vector
				tables.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
			}
		}
	}
	sqlite3_finalize(stmt);
}

void send_table_name(sqlite3* db, string which_function, vector<string>& tables, int s_num) {
	bool entry = false;
	string t;
	int index;
	while (!entry) {
		cout << "Please choose a table from the list below. (enter the number associated with the table you would like to select)" << "\n";
		for (int i = 0; i < tables.size(); i++) {
			cout << i << ". " << tables[i] << "\n";
		}
		try {
			getline(cin, t);
			index = stoi(t);
			entry = true;
		}
		catch (invalid_argument& e) {
			cout << "Converstion from string to int could not be performed.\n";
		}
		catch (out_of_range& e) {
			cout << "Converted value falls out of range.\n";
		}
		catch (exception& e) {
			cout << "Default exception.\n";
			cout << e.what() << "\n";
		}
	}
	
	if (which_function == "1") {
		insert(db, tables[index], s_num);
		tables.clear();
	}
	if (which_function == "2") {
		update(db, tables[index], s_num);
		tables.clear();
	}
	if (which_function == "3") {
		delete_row(db, tables[index], s_num);
		tables.clear();
	}
	if (which_function == "4") {
		print_table(db, tables[index], s_num);
		tables.clear();
	}
	else if (which_function == "8") {
		drop_table(db, tables[index]);
		tables.clear();
	}
}

