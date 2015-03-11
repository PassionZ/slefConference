// MysqlDB.h : header file
//
#ifndef __MYSQLDB_H__
#define __MYSQLDB_H__

#ifdef WIN32
#include "../MySQL/mysql/mysql.h"
#else
#include "../mysql/mysql.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#endif


/////////////////////////////////////////////////////////////////////////////
// CMysqlDB class

class CMysqlDB
{
// Construction
public:
	CMysqlDB();
	virtual ~CMysqlDB();

// Attributes
public:
	MYSQL Mysql;	//Global mysql struct	
	MYSQL_RES *Result;
	MYSQL_ROW Rows;
	bool Connected;
    
// Operations
public:

// Implementation
public:
	//Connect to mysql database
	bool Connect(const char* HostName,const char* UserName,const char* Password,const char* DataBase);
	bool SQLExec(const char *SQL);//执行SQL语句
	unsigned long AffectedRows();//update,insert,delete的影响行数
	
	bool SQLClose();//关闭一个Result(查询结果集合)
	unsigned long RecordCount();//返回查询select的数目
	MYSQL_ROW FetchRows();//取下一行
	
	bool Close();	//Close mysql connection
};

#endif
