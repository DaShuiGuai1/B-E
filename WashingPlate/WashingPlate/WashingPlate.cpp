// WashingPlate.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


/*
Author:Wu
Date:2019/4/2

Fuction main would show the max prefix and corresponding possibilities on the screen. In order to verify the caculation, this program
would generate 3 files if 'printlist' has been defined.
	Record.txt: listing all possibilities
	Numbers.txt: listing all prefixs from the possibilities
	Result.txt: showing the max prefix and listing all possibilities which have the max prefix
If you want to change the input, just change the input array in function main.
*/
#include "ListNode.h"
#include "PlateStack.h"
#include <iostream>
#include <crtdbg.h>
#include <Windows.h>
bool checkinput(uint plate[])//检查输入的数据是否正确
{
	bool ret = false;
	return ret;
}
int main()
{
#ifdef WIN32
#define new new(_CLIENT_BLOCK,_FILE_,_LINE_)
	int tmpflag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpflag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpflag);
	_CrtSetBreakAlloc(0);
#endif // WIN32
	double time_test = 0.0;
	LARGE_INTEGER nfreq, nbegin, nend, ntotalbegin, ntotalend;
	QueryPerformanceFrequency(&nfreq);

	uint num[] = { 10,9,5,6,7,8,3,4,1,2,10 };
	//uint num[] = { 8,4,5,2,6,3,7,1,8 };
	//uint num[] = { 9,4,9,5,2,6,3,7,1,8 };
	//uint num[] = { 5,4,5,3,2,1 };
	//if (checkinput(num))
	{
		fopen_s(&ptxt, "Record.txt", "w");
		fopen_s(&presult, "Result.txt", "w");
		BandE acouple(num, sizeof(num) / sizeof(uint));
		QueryPerformanceCounter(&ntotalbegin);
		if (ptxt && presult)
		{
			QueryPerformanceCounter(&nbegin);
			printf("\nSoping...\n");
			acouple.soap();
			QueryPerformanceCounter(&nend);
			time_test = (double)(nend.QuadPart - nbegin.QuadPart) / (double)(nfreq.QuadPart);
			printf("It takes %10.6f seceond(s) to soap.\n", time_test);

			QueryPerformanceCounter(&nbegin);
			printf("\nWashing...\n");
			acouple.wash();
			QueryPerformanceCounter(&nend);
			time_test = (double)(nend.QuadPart - nbegin.QuadPart) / (double)(nfreq.QuadPart);
			printf("It takes %10.6f seceond(s) to wash.\n", time_test);

			printf("\nFinding the max prefix...");
			QueryPerformanceCounter(&nbegin);
			acouple.CheckNumList();
			QueryPerformanceCounter(&nend);
			time_test = (double)(nend.QuadPart - nbegin.QuadPart) / (double)(nfreq.QuadPart);
			printf("\nIt takes %10.6f seceond(s) to find the max prefix.\n", time_test);
		}
		printf("\nCompleted...\n");
		QueryPerformanceCounter(&ntotalend);
		time_test = (double)(ntotalend.QuadPart - ntotalbegin.QuadPart) / (double)(nfreq.QuadPart);
		printf("It takes %10.3f seceond(s) to excute the whole process.\n", time_test);
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
