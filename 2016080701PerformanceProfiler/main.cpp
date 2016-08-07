//#include "PerformanceProfiler.h"
//
//void Test()
//{
//	PPSection* section = PerformanceProfiler::GetInstance()\
//		->CreateSection(__FILE__, __FUNCTION__, __LINE__, "第一个代码段");
//
//	section->Begin();
//
//	//...
//	Sleep(2000);
//
//	section->End();
//}

void Test()
{
	PERFORMANCE_PROFILER_EE_BEGIN(sql, "数据库");
	//...数据库
	Sleep(100);

	PERFORMANCE_PROFILER_EE_END(sql);

	PERFORMANCE_PROFILER_EE_BEGIN(network, "网络");
	//...
	Sleep(200);

	PERFORMANCE_PROFILER_EE_END(network);
}

void TestPP1()
{
	int n = 3;
	while (n--)
	{
		Test();
	}
}

// 多线程 == 加锁
// 递归 == 引用计数

LongType Fib(size_t n)
{
	PERFORMANCE_PROFILER_EE_BEGIN(fib, "递归内部");

	LongType ret = n;
	if (n < 2)
	{
		ret = n;
	}
	else
	{
		ret = Fib(n - 1) + Fib(n - 2);
	}

	PERFORMANCE_PROFILER_EE_END(fib);

	return ret;
}

void TestPP2()
{
	PERFORMANCE_PROFILER_EE_BEGIN(fib, "fib");

	Fib(30);

	PERFORMANCE_PROFILER_EE_END(fib);
}

void ThreadRun(int count)
{
	cout << this_thread::get_id() << endl;
	while (count--)
	{
		//cout << this_thread::get_id() << endl;
		PERFORMANCE_PROFILER_EE_BEGIN(ThreadRun, "ThreadRun");

		this_thread::sleep_for(std::chrono::milliseconds(100));

		PERFORMANCE_PROFILER_EE_END(ThreadRun);
	}
}

void TestMutilThread()
{
	cout << this_thread::get_id() << endl;

	thread t1(ThreadRun, 15);
	thread t2(ThreadRun, 10);
	thread t3(ThreadRun, 5);

	t1.join();
	t2.join();
	t3.join();
}

// 可配置

int main()
{
	SET_CONFIG_OPTIONS(PERFORMANCE_PROFILER_EE | SAVE_TO_FILE);
	//TestPP1();
	//TestPP2();
	TestMutilThread();

	return 0;
}