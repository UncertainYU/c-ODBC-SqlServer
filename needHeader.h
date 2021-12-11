#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<odbcss.h>
#define makered makecolor(4) //输出变红色
#define makewhite makecolor(7)//输出变白色

typedef signed short            RETCODE;
//retcode:success:0,success with info:1,invalid:-2,error:-1
RETCODE connectDataSource();//申请环境句柄并配置环境属性
RETCODE allocConnectHandle();//申请连接句柄
RETCODE connectSQL();//申请连接数据库
RETCODE allocHstmtHandle();//申请SQL语句句柄
RETCODE closeHstmtHandle();//关闭SQL语句句柄
RETCODE disconnet();//断开连接并释放其他句柄
void makecolor(short x);//更改部分输出颜色
void connectYES();//连接成功后执行的代码段
void connectNO();//连接失败后执行的代码段
void BeginningView();//开始菜单
SQLHENV henv = SQL_NULL_HENV;
SQLHDBC hdbc1 = SQL_NULL_HDBC;
SQLHSTMT hstmt1 = SQL_NULL_HSTMT;


//申请环境句柄并配置环境属性
RETCODE connectDataSource() {
	RETCODE retcode;
	//申请环境句柄
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("环境句柄申请成功!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("无效的环境句柄\n"); makewhite; break;
	case SQL_ERROR:makered; printf("环境句柄申请失败\n"); makewhite; break;
	}
	//设置环境属性
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,
		SQL_IS_INTEGER);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("环境句柄属性配置成功!\n"); break;
	case SQL_INVALID_HANDLE:printf("无效的环境句柄属性配置\n"); break;
	case SQL_ERROR:printf("环境句柄属性配置失败\n"); break;
	}
	return retcode;
}
//申请连接句柄
RETCODE allocConnectHandle() {
	RETCODE retcode;
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);//申请连接句柄
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("连接句柄申请成功!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("无效的连接句柄\n"); makewhite; break;
	case SQL_ERROR:makered; printf("连接句柄申请失败\n"); makewhite; break;
	}
	return retcode;
}
//连接数据库
//这里提供了两种方式
//默认方式是代码初始化
//另一种方式是控制台输入初始化
//可以自行选择
RETCODE connectSQL() {
	UCHAR  szDSN[SQL_MAX_DSN_LENGTH + 1] = "", szUID[MAXNAME] = "", szAuthStr[MAXNAME] = "";
	RETCODE retcode;
	//printf("请输入参数1(数据源名称):");
	//gets(szDSN);
	//printf("请输入参数2(用户名):");
	//gets(szUID);
	//printf("请输入参数3(密码):");
	//gets(szAuthStr);
	retcode = SQLConnect(hdbc1, szDSN, strlen(szDSN), szUID, strlen(szUID), szAuthStr, strlen(szAuthStr));
	return retcode;
}
//申请SQL语句句柄
RETCODE allocHstmtHandle() {
	RETCODE retcode;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("SQL语句句柄申请成功!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("无效的SQL语句句柄\n"); makewhite; break;
	case SQL_ERROR:makered; printf("SQL语句句柄申请失败\n"); makewhite; break;
	}
	return retcode;
}
//关闭SQL语句句柄
RETCODE closeHstmtHandle() {
	RETCODE retcode;
	retcode = SQLCloseCursor(hstmt1);
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("SQL语句句柄关闭成功!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("无效的SQL语句句柄\n"); makewhite; break;
	case SQL_ERROR:makered; printf("SQL语句句柄关闭失败\n"); makewhite; break;
	}
	return retcode;
}
//断开连接并释放其他句柄
RETCODE disconnet() {
	RETCODE retcode;
	retcode = SQLDisconnect(hdbc1);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, henv);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("断开连接成功!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("无效的断开连接\n"); makewhite; break;
	case SQL_ERROR:makered; printf("断开连接失败\n"); makewhite; break;
	}
	return retcode;
}
//更改部分输出语句颜色
void makecolor(short x)	//自定义函根据参数改变颜色 
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//连接成功
void connectYES() {
	//system("cls");
	printf("连接成功!\n");
}
//连接失败
void connectNO() {
	makered;
	printf("连接失败!\n");
	makewhite;
}
//开始菜单
void BeginningView() {
}
