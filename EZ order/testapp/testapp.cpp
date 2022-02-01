#include <iostream>
#include <mysql.h>
#include <string>
#include "dbresponse.h"
#include "customer.h"
#include "seller.h"

using namespace std;

// Latest update 10/1/2022 12pm

//MYSQL* conn;
//int qstate;

/*class db_response
{
	public:
		static void dbconnect()
		{
			conn = mysql_init(0);
			if (conn)
			{
				cout << "connected" << endl;
			}
			else
				cout << "failed to connect" << endl;
			conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "testdb", 3306, NULL, 0);
			if (conn)
			{
				cout << "connected to the database!" << endl;
			}
			else
			{
				cout << "failed to connect to db! " << mysql_errno(conn) << endl;
			}
		}
};*/

int main()
{
	//db_response::dbconnect(); // initial connect
	dbresponse::dbconnect();

	int whoami;
	string who;

	cout << "Welcome to Food Ordering System!\nWho are you?" << endl;
	cout << endl;
	cout << "	1. Customer" << endl;
	cout << "	2. Seller" << endl;
	cout << "	3. Quit" << endl;
	cout << "\nChoose: ";
	cin >> who;

	if (who == "1" || who == "2" || who == "3")
	{
		whoami = stoi(who);
	}
	else
	{
		cout << "Invalid option!" << endl;
		cin.ignore();
		cout << "Press ENTER to restart back..";
		cin.get();
		exit(0);
	}

	while (cin.fail())
	{
		cout << "Invalid option!\n";
		cin.clear();
		cin.ignore();
		cout << "\nChoose: ";
		cin >> whoami;
	}
	switch (whoami)
	{
		case 1:
			system("cls");
			customerInitial();

			break;
		case 2:
			system("cls");
			sellerLogin();

			break;
		case 3:
			cout << "See you next time :)" << endl;
			
			break;
		default:
			cout << "Invalid option!" << endl;
			cin.ignore();
			cout << "Press ENTER to back to profile..";
			cin.get();
			system("cls");
			main();
	}
	
	mysql_close(conn);
	return 0;
}