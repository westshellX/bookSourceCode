#include<Windows.h>
#include<stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	printf("ThreadProc \r\n");
	return 0;
}

int g_Num_one=0;
CRITICAL_SECTION g_cs;                           //临界区
DWORD WINAPI ThreadProcMul(LPVOID lpParam)
{
	int nTemp=0;
	for(int i=0;i<10;i++)
	{
		EnterCriticalSection(&g_cs);            //进入临界区
		nTemp=g_Num_one;
		nTemp++;

		//Sleep(1)的作用是让出CPU使其他线程被调度使用
		Sleep(1);
		g_Num_one=nTemp;
		LeaveCriticalSection(&g_cs);            //离开临界区
	}
	return 0;
}

int main(int argc,char *argv[])
{
	printf("多线程 \r\n");
	HANDLE hThread=CreateThread(NULL,0,
		ThreadProc,NULL,0,NULL);
	WaitForSingleObject(hThread,INFINITE);
	printf("main \r\n");
	CloseHandle(hThread);

	printf("多线程资源共享\r\n");
	InitializeCriticalSection(&g_cs);          //初始化临界区
	HANDLE hThreadMul[10]={0};
	for(int i=0;i<10;i++)
	{
		hThreadMul[i]=CreateThread(NULL,0,ThreadProcMul,NULL,0,NULL);
	}
	WaitForMultipleObjects(10,hThreadMul,true,INFINITE);
	for(int i=0;i<10;i++)
	{
		CloseHandle(hThreadMul[i]);
	}
	printf("%d\r\n",g_Num_one);
	DeleteCriticalSection(&g_cs);            //删除临界区
	return 0;
}