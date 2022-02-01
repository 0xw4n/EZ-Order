#include "dbresponse.h"
#include <iostream>
#include <mysql.h>

using namespace std;

MYSQL* conn;
int qstate;
MYSQL_ROW row;
MYSQL_RES* result;

void dbresponse::dbconnect()
{
	conn = mysql_init(0);
	if (conn)
	{
		cout << "" ;
	}
	else
		cout << "failed to connect" << endl;
	conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "fos", 3306, NULL, 0);
	if (conn)
	{
		cout << "";
	}
	else
	{
		cout << "failed to connect to db! " << mysql_errno(conn) << endl;
	}
}
