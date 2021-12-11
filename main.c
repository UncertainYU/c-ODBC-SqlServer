#include"needHeader.h"


//========================须知==========================//
//注意：vs运行环境下，修改为多字符集，属性——高级——字符集
//为了方便学习查错，整个连接过程会打印输出
//当出现错误的地方，该错误会标红
//可以通过标红的地方，发现问题
//========================须知==========================//


//初始化过程
//注意：
//retcode:success:0,success with info:1,invalid:-2,error:-1
//这是retcode的四个返回值
//可以通过返回值判断sql语句是否成功执行
//因为其他函数都内置了判断执行情况，无需内置
//具体可以查阅头文件
int main(void) {
	RETCODE 	retcode;//作为以下函数返回值的存放变量
	retcode = connectDataSource();//申请环境句柄并配置环境属性
	retcode = allocConnectHandle();//申请连接句柄
	retcode = connectSQL();//连接数据库
	//这个函数里面需要配置，这里采用的是ODBC操作数据库
	//需要传递username和password
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
		connectNO();//连接失败
	}
	else {
		connectYES();//连接成功
		//=============需要对数据库操作的时候进行如下代码==============//
		allocHstmtHandle();//申请语句句柄
		BeginningView();//这个函数里面写对数据库的一些操作
		//例如SQLCHAR  sql[100]="",这里面就可以写sql语句,通过retcode判断是否成功执行
		closeHstmtHandle();//关闭申请语句句柄
		//=============需要对数据库操作的时候进行如上代码==============//
	}
	disconnet();//断开连接
	return 0;
}



