#include "stdafx.h"
#include "Connection.h"

MysqlConnection::MysqlConnection(const char * host, const char * user, const char * pwd, const char * dbname, unsigned int port, const char * unixSocket, unsigned long clientFlag)
{
	status = false;

	this->host = host;
	this->user = user;
	this->pwd = pwd;
	this->dbname = dbname;
	this->option = option;
	this->unixSocket = unixSocket;
	this->port = port;
	this->clientFlag = clientFlag;

	conn = mysql_init(NULL);

	if (SetOption() == 0 && Open() == 0) {
		status = true;
	}
}

bool MysqlConnection::GetStatus()
{
	return status;
}

int MysqlConnection::SetOption()
{
	if (mysql_options(conn, MYSQL_SET_CHARSET_NAME, option))
		return 1;
	return 0;
}

int MysqlConnection::Open()
{
	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr)) {
		return -1;
	}
	clientFlag |= CLIENT_MULTI_STATEMENTS;
	if (!mysql_real_connect(conn,host,user,pwd,dbname,port,unixSocket,clientFlag)) {
		return 1;
	}

	status = true;

	return 0;
}

int MysqlConnection::Close()
{
	if (status) {
		mysql_close(conn);
		::CoUninitialize();
		status = false;
	}
	return 0;
}

MYSQL_RES * MysqlConnection::Execute(const char * pchSql)
{
	int nError = 0;
	nError = mysql_query(conn, pchSql);

	MYSQL_RES* pRes = NULL;

	if (nError) {
		return pRes;
	}

	pRes = mysql_use_result(conn);
	return pRes;
}
