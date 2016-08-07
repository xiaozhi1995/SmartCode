#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <assert.h>
#include <stdarg.h>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <mutex>

#ifdef _WIN32
	#include <windows.h>
#else
#include <pthread.h>
#endif // _WIN32

using namespace std;

typedef long long LongType;

////////////////////////////////////////////////////////////////////
// ����������
class SaveAdapter
{
public:
	virtual void Save(const char* fmt, ...) = 0;
};

class ConsoleSaveAdapter : public SaveAdapter
{
public:
	virtual void Save(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		vfprintf(stdout, fmt, args);
		va_end(args);
	}
};

class FileSaveAdapter : public SaveAdapter
{
public:
	FileSaveAdapter(const char* filename)
	{
		_fout = fopen(filename, "w");
		assert(_fout);
	}

	virtual void Save(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		vfprintf(_fout, fmt, args);
		va_end(args);
	}

	~FileSaveAdapter()
	{
		if (_fout)
		{
			fclose(_fout);
		}
	}

protected:
	FileSaveAdapter(const FileSaveAdapter&);
	FileSaveAdapter& operator=(FileSaveAdapter&);

protected:
	FILE* _fout;
};

////////////////////////////////////////////////////////////////////
// ����ģʽ
template<class T>
class Singleton
{
public:
	static T* GetInstance()
	{
		assert(_sInstance);
		return _sInstance;
	}

protected:
	static T* _sInstance;
};

template<class T>
T* Singleton<T>::_sInstance = new T;

///////////////////////////////////////////////////////////////////////
// ���ù���
enum ConifgOptions
{
	NONE = 0,
	PERFORMANCE_PROFILER_EE = 1, // ����Ч������
	PERFORMANCE_PROFILER_RS = 2, // ������Դ����
	SAVE_TO_CONSOLE = 4,		 // ���浽����̨
	SAVE_TO_FILE = 8,			 // ���浽�ļ�
	SORT_BY_CALL_COUNT = 16,	 // ��������ô�������
	SORT_BY_COST_TIME = 32,		 // ���������ʱ������ 
};

class ConifgManager : public Singleton<ConifgManager>
{
	friend class Singleton<ConifgManager>;

public:
	int SetOption(int flag);
	int GetOptions();
	void AddOption(int flag);
	void DelOption(int flag);

protected:
	ConifgManager()
		:_flag(NONE)
	{
		// ��ȡ�����ļ�������ѡѡ��
	}

	int _flag;
};

/////////////////////////////////////////////////////////////////////////
// ��������Ϣ

static int GetThreadId()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#else
	return thread_self();
#endif // _WIN32

}

// PerformanceProfiler
// �����νڵ���Ϣ
struct PPNode
{
	string _filename;	// �ļ���
	string _function;	// ������
	size_t _line;		// �к�
	string _desc;		// ����������

	PPNode(const char* filename = "", const char* function = ""
		, size_t line = 0, const char* desc = "")
		:_filename(filename)
		, _function(function)
		, _line(line)
		, _desc(desc)
	{}

	bool operator < (const PPNode& node) const;
};

// ������
typedef map<int, LongType> StatisticsMap;
struct PPSection
{
public:
	PPSection()
	{}

	void Begin(int id);

	void End(int id);

	StatisticsMap _beginTimeMap;
	StatisticsMap _costTimeMap;
	StatisticsMap _callCountMap;
	StatisticsMap _refCountMap;
	LongType _totalCostTime;

	mutex _mtx;
};

class PerformanceProfiler : public Singleton<PerformanceProfiler>
{
	friend class Singleton<PerformanceProfiler>;
	typedef map<PPNode, PPSection*> PPMap;
public:
	PPSection* CreateSection(const char* filename,
		const char* function, size_t line, const char* desc);
	void OutPut();
	void _OutPut(SaveAdapter& sa);
protected:
	PerformanceProfiler()
	{}
	PerformanceProfiler(const PerformanceProfiler&);
	PerformanceProfiler& operator=(const PerformanceProfiler&);

protected:
	PPMap _ppMap;
};

struct Release
{
	~Release()
	{
		PerformanceProfiler::GetInstance()->OutPut();
	}
};

static Release gR;

#define PERFORMANCE_PROFILER_EE_BEGIN(sign, desc)	\
	PPSection* sign##section = NULL;				\
	int sign##flag = ConifgManager::GetInstance()->GetOptions(); \
	if (sign##flag & PERFORMANCE_PROFILER_EE)	\
	{											\
		sign##section = PerformanceProfiler::GetInstance()	\
		->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc); \
		sign##section->Begin(GetThreadId());	\
	}

#define PERFORMANCE_PROFILER_EE_END(sign) \
	if (sign##flag & PERFORMANCE_PROFILER_EE)\
		sign##section->End(GetThreadId());

#define SET_CONFIG_OPTIONS(flag)	\
	ConifgManager::GetInstance()->SetOption(flag);




