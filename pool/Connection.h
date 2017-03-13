#ifndef UTILITY_TOOLS_CONNECTION_H
#define UTILITY_TOOLS_CONNECTION_H

#include <mysql.h>
#include <memory>

class MysqlConnection{
public:
	MysqlConnection(const char* host,const char* user,const char* pwd,const char* dbname, unsigned int port,const char* unixSocket,unsigned long clientFlag);
public:
	MYSQL* conn;
private:
	const char* host;
	const char* user;
	const char* pwd;
	const char* dbname;
	const char* option;
	const char* unixSocket;
	unsigned int port;
	unsigned long clientFlag;

	bool status;	//连接状态
public:
	bool GetStatus();
	int SetOption();
	int Open();
	int Close();

	//执行单条sql语句
	MYSQL_RES* Execute(const char* pchSql);

};
#endif