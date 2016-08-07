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
// 保存适配器
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
// 单例模式
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
// 配置管理
enum ConifgOptions
{
	NONE = 0,
	PERFORMANCE_PROFILER_EE = 1, // 开启效率剖析
	PERFORMANCE_PROFILER_RS = 2, // 开启资源剖析
	SAVE_TO_CONSOLE = 4,		 // 保存到控制台
	SAVE_TO_FILE = 8,			 // 保存到文件
	SORT_BY_CALL_COUNT = 16,	 // 结果按调用次数排序
	SORT_BY_COST_TIME = 32,		 // 结果按花费时间排序 
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
		// 读取配置文件，设置选选项
	}

	int _flag;
};

/////////////////////////////////////////////////////////////////////////
// 剖析段信息

static int GetThreadId()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#else
	return thread_self();
#endif // _WIN32

}

// PerformanceProfiler
// 剖析段节点信息
struct PPNode
{
	string _filename;	// 文件名
	string _function;	// 函数名
	size_t _line;		// 行号
	string _desc;		// 附加项描述

	PPNode(const char* filename = "", const char* function = ""
		, size_t line = 0, const char* desc = "")
		:_filename(filename)
		, _function(function)
		, _line(line)
		, _desc(desc)
	{}

	bool operator < (const PPNode& node) const;
};

// 剖析段
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




