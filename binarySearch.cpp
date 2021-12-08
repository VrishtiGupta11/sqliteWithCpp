#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
#define N 6

using namespace std;

string rollNo[10];
int c = 0;

static int createDB(const char* s);
static int createTable(const char* s);
static int insertData(const char* s);
static int selectData(const char* s);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);

void binarySearch(string toSearch) {
	int i = 0, firstInd = 0, lastInd = N-1, midInd;
	midInd = (firstInd + lastInd) / 2;

	// Sorting
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (rollNo[i] < rollNo[j]) {
				string temp = rollNo[j];
				rollNo[j] = rollNo[i];
				rollNo[i] = temp;
			}
		}
	}

	// Binary Search

	while (firstInd <= lastInd) {
		if (toSearch == rollNo[midInd]) {
			cout << "Roll number " << toSearch << " found at position " << midInd + 1 << endl;
			break;
		}
		else if (toSearch > rollNo[midInd]) {
			firstInd = midInd + 1;
		}
		else {
			lastInd = midInd - 1;
		}
		midInd = (firstInd + lastInd) / 2;
		if (firstInd > lastInd) {
			cout << "Roll number " << toSearch << " not found\n";
		}
	}
}

int main()
{
	const char* dir = R"(D:\DeleteMe\STUDENTS.db)";

	createDB(dir);
	//createTable(dir);
	//insertData(dir); // uncomment the deleteData above to avoid duplicates
	selectData(dir);

	string toSearch;
	cout << "Enter Element to Search: ";
	cin >> toSearch;
	binarySearch(toSearch);


	return 0;
}

static int createDB(const char* s)
{
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);

	return 0;
}

static int createTable(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "CREATE TABLE IF NOT EXISTS StudentData("
		"ROLLNO    INT NOT NULL, "
		"FNAME     TEXT NOT NULL, "
		"LNAME     TEXT NOT NULL); ";

	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), callback, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error in createTable function." << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Table created Successfully" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

static int insertData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql(
		"INSERT INTO StudentData(ROLLNO, FNAME, LNAME) VALUES(1915084, 'Varanpreet', 'Kaur');"
		"INSERT INTO StudentData (ROLLNO, FNAME, LNAME) VALUES(1915085, 'Vishal', 'Dutta');"
		"INSERT INTO StudentData (ROLLNO, FNAME, LNAME) VALUES(1915086, 'Vrishti', 'Gupta');"
		"INSERT INTO StudentData(ROLLNO, FNAME, LNAME) VALUES(1915087, 'Yuvraj', 'Khanna');"
		"INSERT INTO StudentData (ROLLNO, FNAME, LNAME) VALUES(1915103, 'Priyanka', 'Jhamb');"
		"INSERT INTO StudentData (ROLLNO, FNAME, LNAME) VALUES(1915105, 'Amanjot', 'Singh');"
	);

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records inserted Successfully!" << endl;

	return 0;
}


static int selectData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM StudentData;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records selected Successfully!" << endl;

	return 0;
}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	rollNo[c] = argv[0];
	c++;

	return 0;
}
