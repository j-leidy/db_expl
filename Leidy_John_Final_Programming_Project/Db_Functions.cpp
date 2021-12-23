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

void drop_table(sqlite3* db, string table_name) {
	int rc;
	char* err;
	string query = "DROP TABLE " + table_name;

	rc = sqlite3_exec(db, query.c_str(), callback, 0, &err);
	if (rc != SQLITE_OK) {
		cout << "\n";
		fprintf(stderr, "SQL error: %s\n", err);
		sqlite3_free(err);
	}
	else {
		cout << "<<<Table was deleted succesfully>>>\n";
	}


}


void create_table(sqlite3* db, int s_num) {
	sqlite3_stmt* stmt;
	int count = 0;
	char* err;
	int rc;
	string table_name;
	vector<string> field_names;
	vector<string> data_types;
	string primary_key_field_name;
	string query;
	string p_key_name;
	bool p_key = false;
	string temp_f_n;
	string temp_d_t;
	string add_field;
	bool done = false;
	while (table_name.empty()) {
		cout << "Please enter a name for your table:\n";
		getline(cin, table_name);
		query = "CREATE TABLE " + table_name + "(";
	}
	while (!done) {
		temp_d_t = "";
		temp_f_n = "";
		cout << "Add field?\n";
		cout << "1. Yes\n";
		cout << "2. Finalize and create table\n";
		getline(cin, add_field);
		if (add_field == "1") {
			cout << "Enter the name of the field: \n";
			getline(cin, temp_f_n);
			field_names.push_back(temp_f_n);
			while (temp_d_t != "TEXT" && temp_d_t != "INTEGER" && temp_d_t != "VARCHAR") {
				cout << "Enter the data type: \n";
				getline(cin, temp_d_t);
			}
			data_types.push_back(temp_d_t);
			if (p_key == false) {
				try {
					cout << "Is " + temp_f_n + " your primary key? (1 yes 0 no)\n";
					getline(cin, p_key_name);
					p_key = stoi(p_key_name);
					if (p_key == 1) {
						data_types[count] += " PRIMARY KEY";
					}
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

		}
		else if (add_field == "2") {
			for (int i = 0; i < field_names.size(); i++) {
				query += field_names[i] + " " + data_types[i];
				if (i < field_names.size() - 1) {
					query += ", ";
				}
			}
			query += ");";
			cout << query << "\n";
			rc = sqlite3_exec(db, query.c_str(), callback, 0, &err);
			if (rc != SQLITE_OK) {
				cout << "\n";
				fprintf(stderr, "SQL error: %s\n", err);
				sqlite3_free(err);
			}
			else {
				print_table(db, table_name, s_num);
				cout << "<<<<<<<<Table Created>>>>>>>>" << "\n";
			}



			done = true;
		}
		for (int i = 0; i < field_names.size(); i++) {
			cout << field_names[i] << " " << data_types[i] << "  \n";
		}
		cout << count << "\n";
		count++;
				
	}



}

void insert(sqlite3* db, string table_name, int s_num) {
	int rc;
	char* err;

	//grab the column names from our table function (remember this function returns already in sql format)
	string column_names = get_column_names(db, table_name, s_num);

	//get the values the user wants to input (returns in sql values format)
	string values = get_values(db, table_name, s_num);

	//create query
	string insert = "INSERT INTO " + table_name + " (" + column_names + ") VALUES(" + values + ");";
	string error;

	//execute
	rc = sqlite3_exec(db, insert.c_str(), callback, 0, &err);

	//check if failed
	if (rc != SQLITE_OK) {
		cout << "\n";
		fprintf(stderr, "SQL error: %s\n", err);
		sqlite3_free(err);
	}
	else {
		print_table(db, table_name, s_num);
		cout << "<<<<<<<<Insert Completed>>>>>>>>" << "\n";
	}
}

void update(sqlite3* db, string table_name, int s_num) {
	cout << table_name << "\n";
	//grab the names of the column we are working in
	string names = get_column_names(db, table_name, s_num);
	cout << names << "\n";
	string choice;
	string value;
	string pkey;
	string pk;
	char* err;
	int rc;
	const char* data = "Callback function called";
	//primay key is the first column, break once we reach a comma
	for (char c : names) {
		if (c == ',') {
			break;
		}
		pkey += c;
	}
	print_table(db, table_name, s_num);
	cout << "Primary key column: " << pkey << "\n";
	cout << "Primary key value (Which row, Enter the primary key for the row you are changing): " << "\n";
	getline(cin, pk);
	cout << "Column to update (Enter the column name for the column that contains the value you would like to update.): " << "\n";
	getline(cin, choice);
	cout << "Value: " << "\n";
	getline(cin, value);
	string update = "UPDATE " + table_name + " set " + choice + " = '" + value + "' where " + pkey + "=" + pk + ";";
	rc = sqlite3_exec(db, update.c_str(), callback, (void*)data, &err);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err);
		sqlite3_free(err);
	}
	else {

		print_table(db, table_name, s_num);
		cout << "<<<<<<<<Update Completed>>>>>>>>" << "\n";
	}
}

void delete_row(sqlite3* db, string table_name, int s_num) {
	char* err = 0;
	int rc;
	const char* data = "Callback function called";
	string names = get_column_names(db, table_name, s_num);
	string pkey;
	string which_key;
	for (char c : names) {
		if (c == ',') {
			break;
		}
		pkey += c;
	}
	print_table(db, table_name, s_num);
	cout << "Primery key column: " << pkey << "\n";
	cout << "Which primary key value would you like to delete? " << "\n";
	getline(cin, which_key);
	string delete_sql = "DELETE FROM " + table_name + " where " + pkey + "=" + which_key + ";";
	rc = sqlite3_exec(db, delete_sql.c_str(), callback, (void*)data, &err);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err);
		sqlite3_free(err);
	}
	else {
		print_table(db, table_name, s_num);
		cout << "<<<<<<<<Deleted Successfully>>>>>>>>" << "\n";
	}

}

