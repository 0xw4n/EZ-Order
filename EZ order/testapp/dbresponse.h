#ifndef DBRESPONSE_H
#define DBRESPONSE_H
#include <mysql.h>

extern MYSQL* conn;
extern int qstate;
extern MYSQL_ROW row;
extern MYSQL_RES* result;

class dbresponse
{
public:
	static void dbconnect();
};

#endif