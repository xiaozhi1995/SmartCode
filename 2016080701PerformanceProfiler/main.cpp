//#include "PerformanceProfiler.h"
//
//void Test()
//{
//	PPSection* section = PerformanceProfiler::GetInstance()\
//		->CreateSection(__FILE__, __FUNCTION__, __LINE__, "��һ�������");
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
	PERFORMANCE_PROFILER_EE_BEGIN(sql, "���ݿ�");
	//...���ݿ�
	Sleep(100);

	PERFORMANCE_PROFILER_EE_END(sql);

	PERFORMANCE_PROFILER_EE_BEGIN(network, "����");
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

// ���߳� == ����
// �ݹ� == ���ü���

LongType Fib(size_t n)
{
	PERFORMANCE_PROFILER_EE_BEGIN(fib, "�ݹ��ڲ�");

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

// ������

int main()
{
	SET_CONFIG_OPTIONS(PERFORMANCE_PROFILER_EE | SAVE_TO_FILE);
	//TestPP1();
	//TestPP2();
	TestMutilThread();

	return 0;
}