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

string new_or_existing(string c) {
	while (c != "1" && c != "2") {
		cout << "1. New Database\n";
		cout << "2. Existing Database\n";
		getline(cin, c);
	}
	return c;
}



int space_num() {
	bool valid = false;
	string new_space_num;
	int s_num = 0;
	while (!valid) {
		cout << "Please enter a new spacing number to fit your table (A good number to start with is 50.):   ";
		getline(cin, new_space_num);
		try {
			s_num = stoi(new_space_num);
			valid = true;
		}
		catch(invalid_argument& e){
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
	return s_num;
}

string main_menu(string c) {
	bool valid = false;
	while (!valid) {
		cout << "Please enter a choice from the menu. (Enter the number associated with the action you want to perform.)" << "\n";
		cout << "1. Add data" << "\n";
		cout << "2. Update data" << "\n";
		cout << "3. Remove data" << "\n";
		cout << "4. Show a table" << "\n";
		cout << "5. Print all tables" << "\n";
		cout << "6. Change format spacing" << "\n";
		cout << "7. Create table" << "\n";
		cout << "8. Drop table" << "\n";
		cout << "9. Exit" << "\n";
		getline(cin, c);
		if (c == "1" || c == "2" || c == "3" || c == "4" || c == "5" || c == "6" || c == "7" || c == "8" || c == "9") {
			valid = true;
		}
	}
	return c;
}


void menu_help(sqlite3* mydb, vector<string> &tables, int s_num) {
	string choice;
	cout << setw(25) << " " << "_________________________________________________________________" << "\n";
	cout << setw(25) << " " << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << "\n";
	while (choice != "9") {
		choice = main_menu(choice);

		if (choice == "1") {
			cout << "________________________" << "\n";
			cout << "<<<<<<<<Add data>>>>>>>>" << "\n";
			get_table_names(mydb, tables);
			send_table_name(mydb, choice, tables, s_num);
			tables.clear();
		}
		if (choice == "2") {
			cout << "____________________________________" << "\n";
			cout << "<<<<<<<<Update existing data>>>>>>>>" << "\n";
			get_table_names(mydb, tables);
			send_table_name(mydb, choice, tables, s_num);
			tables.clear();
		}
		if (choice == "3") {
			cout << "___________________________" << "\n";
			cout << "<<<<<<<<Remove data>>>>>>>>" << "\n";
			get_table_names(mydb, tables);
			send_table_name(mydb, choice, tables, s_num);
			tables.clear();
		}
		if (choice == "4") {
			cout << "_____________________________" << "\n";
			cout << "<<<<<<<<Print a table>>>>>>>>" << "\n";
			get_table_names(mydb, tables);
			send_table_name(mydb, choice, tables, s_num);
			tables.clear();
		}
		if (choice == "5") {
			cout << "________________________________" << "\n";
			cout << "<<<<<<<<Print all tables>>>>>>>>" << "\n";
			get_table_names(mydb, tables);
			send_print_all(mydb, tables, s_num);
			tables.clear();
		}
		if (choice == "6") {
			s_num = space_num();
		}
		if (choice == "7") {
			cout << "________________________________" << "\n";
			cout << "<<<<<<<<<<Create Table>>>>>>>>>>" << "\n";
			create_table(mydb,s_num);
		}
		else if (choice == "8") {
			cout << "________________________________" << "\n";
			cout << "<<<<<<<<<<<Drop Table>>>>>>>>>>>" << "\n";
			cout << "-------------WARNING------------" << "\n";
			cout << "Dropping a table will result in " << "\n";
			cout << "a permanent loss of data." << "\n";
			get_table_names(mydb, tables);
			send_table_name(mydb, choice, tables, s_num);
			tables.clear();
		}

	}

}