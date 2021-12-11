#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<odbcss.h>
#define makered makecolor(4) //������ɫ
#define makewhite makecolor(7)//������ɫ

typedef signed short            RETCODE;
//retcode:success:0,success with info:1,invalid:-2,error:-1
RETCODE connectDataSource();//���뻷����������û�������
RETCODE allocConnectHandle();//�������Ӿ��
RETCODE connectSQL();//�����������ݿ�
RETCODE allocHstmtHandle();//����SQL�����
RETCODE closeHstmtHandle();//�ر�SQL�����
RETCODE disconnet();//�Ͽ����Ӳ��ͷ��������
void makecolor(short x);//���Ĳ��������ɫ
void connectYES();//���ӳɹ���ִ�еĴ����
void connectNO();//����ʧ�ܺ�ִ�еĴ����
void BeginningView();//��ʼ�˵�
SQLHENV henv = SQL_NULL_HENV;
SQLHDBC hdbc1 = SQL_NULL_HDBC;
SQLHSTMT hstmt1 = SQL_NULL_HSTMT;


//���뻷����������û�������
RETCODE connectDataSource() {
	RETCODE retcode;
	//���뻷�����
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("�����������ɹ�!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("��Ч�Ļ������\n"); makewhite; break;
	case SQL_ERROR:makered; printf("�����������ʧ��\n"); makewhite; break;
	}
	//���û�������
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,
		SQL_IS_INTEGER);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("��������������óɹ�!\n"); break;
	case SQL_INVALID_HANDLE:printf("��Ч�Ļ��������������\n"); break;
	case SQL_ERROR:printf("���������������ʧ��\n"); break;
	}
	return retcode;
}
//�������Ӿ��
RETCODE allocConnectHandle() {
	RETCODE retcode;
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);//�������Ӿ��
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("���Ӿ������ɹ�!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("��Ч�����Ӿ��\n"); makewhite; break;
	case SQL_ERROR:makered; printf("���Ӿ������ʧ��\n"); makewhite; break;
	}
	return retcode;
}
//�������ݿ�
//�����ṩ�����ַ�ʽ
//Ĭ�Ϸ�ʽ�Ǵ����ʼ��
//��һ�ַ�ʽ�ǿ���̨�����ʼ��
//��������ѡ��
RETCODE connectSQL() {
	UCHAR  szDSN[SQL_MAX_DSN_LENGTH + 1] = "csql", szUID[MAXNAME] = "test", szAuthStr[MAXNAME] = "test123456";
	RETCODE retcode;
	//printf("���������1(����Դ����):");
	//gets(szDSN);
	//printf("���������2(�û���):");
	//gets(szUID);
	//printf("���������3(����):");
	//gets(szAuthStr);
	retcode = SQLConnect(hdbc1, szDSN, strlen(szDSN), szUID, strlen(szUID), szAuthStr, strlen(szAuthStr));
	return retcode;
}
//����SQL�����
RETCODE allocHstmtHandle() {
	RETCODE retcode;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("SQL���������ɹ�!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("��Ч��SQL�����\n"); makewhite; break;
	case SQL_ERROR:makered; printf("SQL���������ʧ��\n"); makewhite; break;
	}
	return retcode;
}
//�ر�SQL�����
RETCODE closeHstmtHandle() {
	RETCODE retcode;
	retcode = SQLCloseCursor(hstmt1);
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("SQL������رճɹ�!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("��Ч��SQL�����\n"); makewhite; break;
	case SQL_ERROR:makered; printf("SQL������ر�ʧ��\n"); makewhite; break;
	}
	return retcode;
}
//�Ͽ����Ӳ��ͷ��������
RETCODE disconnet() {
	RETCODE retcode;
	retcode = SQLDisconnect(hdbc1);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, henv);
	switch (retcode) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:printf("�Ͽ����ӳɹ�!\n"); break;
	case SQL_INVALID_HANDLE:makered; printf("��Ч�ĶϿ�����\n"); makewhite; break;
	case SQL_ERROR:makered; printf("�Ͽ�����ʧ��\n"); makewhite; break;
	}
	return retcode;
}
//���Ĳ�����������ɫ
void makecolor(short x)	//�Զ��庯���ݲ����ı���ɫ 
{
	if (x >= 0 && x <= 15)//������0-15�ķ�Χ��ɫ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else//Ĭ�ϵ���ɫ��ɫ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//���ӳɹ�
void connectYES() {
	//system("cls");
	printf("���ӳɹ�!\n");
}
//����ʧ��
void connectNO() {
	makered;
	printf("����ʧ��!\n");
	makewhite;
}
//��ʼ�˵�
void BeginningView() {
}