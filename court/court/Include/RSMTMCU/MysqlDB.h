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
	bool SQLExec(const char *SQL);//ִ��SQL���
	unsigned long AffectedRows();//update,insert,delete��Ӱ������
	
	bool SQLClose();//�ر�һ��Result(��ѯ�������)
	unsigned long RecordCount();//���ز�ѯselect����Ŀ
	MYSQL_ROW FetchRows();//ȡ��һ��
	
	bool Close();	//Close mysql connection
};

#endif
