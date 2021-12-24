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

void adding_test_push() {

}

void warning() {
	cout << setw(25) << " " << "<*****************************************************************>" << "\n";
	cout << setw(25) << " " << "<*****************************************************************>" << "\n";
	cout << setw(25) << " " << "<*****************************************************************>" << "\n";
	cout << setw(25) << " " << "<*                                                               *>" << "\n";
	cout << setw(25) << " " << "<*PLEASE MAXIMIZE THE CMD WINDOW FOR FORMATTING TO WORK PROPERLY!*>" << "\n";
	cout << setw(25) << " " << "<*                                                               *>" << "\n";
	cout << setw(25) << " " << "<*****************************************************************>" << "\n";
	cout << setw(25) << " " << "<*****************************************************************>" << "\n";
	cout << setw(25) << " " << "<*****************************************************************>" << "\n";
}

void info() {


	cout << "\n\n\n";
	cout << setw(25) << " " << "=> Creator: John Leidy II\n";
	cout << setw(25) << " " << "=> Version: 1.0\n\n\n";
	cout << setw(25) << " " << "<************************Program Information**********************>\n\n\n";
	cout << setw(25) << " " << "This program uses the c++ sqlite3 wrapper. It allows the user to \n";
	cout << setw(25) << " " << "utilize this wrapper to explore and modify a database of their \n";
	cout << setw(25) << " " << "choice. The user is able to View, Update, Insert and Remove data.\n\n\n";
	cout << setw(25) << " " << "NOTE: Ensure your database is located in the same folder as your\n";
	cout << setw(25) << " " << ".exe application file for this program.\n";
	cout << setw(25) << " " << "NOTE: If using the source code ensure your database is located in\n";
	cout << setw(25) << " " << "the same folder as your source files.\n\n\n";
	cout << setw(25) << " " << "NOTE: You may want to change the font size of your cmd window as\n";
	cout << setw(25) << " " << "well if your database has large entries or a lot of columns in a\n";
	cout << setw(25) << " " << "select table.\n";
	cout << setw(25) << " " << "<*****************************************************************>" << "\n\n\n";
}

void print_column_names(string x, int col_num, int space_num, string table_name) {
	string full_print;
	string temp;
	cout << setw(25);

	//iterate through given column name sql format string we are given
	for (char& c : x) {
		if (c == ',') {
			//if we c that there is a , character from our sql statement we do add it to our string we are going to print from
		}
		else {
			//if c is not a , then we add it to our printing string
			full_print += c;
		}
	}

	//format and print our string with ',' removed
	for (char& b : full_print) {
		temp += b;
		//if we see a space we need to space the column name according to the space_num we generated back in print_table from set_space_num
		if (b == ' ') {
			cout << setw(space_num) << temp;
			temp = "";
		}
	}
	cout << setw(space_num) << temp;
	cout << "\n";



	//printing the line below the column names
	for (int i = 0; i < col_num * space_num; i++) {

		if (i > 5) {
			cout << "_";
		}
		else {
			cout << " ";
		}

	}
	cout << "\n";
}

void print_table(sqlite3* db, string table_name, int space_num) {
	string column_names;
	//grab the column names in a format that can be used in our SQL statement

	//sql statement processing
	column_names = get_column_names(db, table_name, space_num);
	string query = "SELECT " + column_names + " FROM " + table_name + ";";
	sqlite3_stmt* stmt;
	string error;
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
		error = sqlite3_errmsg(db);
		sqlite3_finalize(stmt);
		cout << "There was an error: " << error << "\n";
		return;
	}
	else {
		int cols2 = sqlite3_column_count(stmt);
		//print the column names first using the column names we obtained earlier
		print_column_names(column_names, cols2, space_num, table_name);
		cout << "\n";
		cout << setw(space_num);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			for (int i = 0; i < cols2; i++) {
				if (sqlite3_column_text(stmt, i) == NULL) {
					cout << setw(space_num) << "-" << setw(space_num);
				}
				else {
					cout << setw(space_num)  << sqlite3_column_text(stmt,i) ;
				}

			}
			sqlite3_errcode(db);
			cout << "\n";

		}
	}
	cout << " " << "\n";
	sqlite3_finalize(stmt);

}

void send_print_all(sqlite3* db, vector<string>& tables, int s_num) {
	for (int i = 0; i < tables.size(); i++) {
		cout << "\n" << "\n" << "\n";
		cout << "      _____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________" << "\n";
		cout << "      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << "\n";
		cout << "      `````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````" << "\n";
		cout << "\n" << "\n" << "\n";
		print_table(db, tables[i], s_num);
	}

}