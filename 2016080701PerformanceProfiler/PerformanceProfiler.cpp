#include "PerformanceProfiler.h"

///////////////////////////////////////////////////
// 配置管理
int ConifgManager::SetOption(int flag)
{
	int old = _flag;
	_flag = flag;
	return old;
}

int ConifgManager::GetOptions()
{
	return _flag;
}

void ConifgManager::AddOption(int flag)
{
	_flag |= flag;
}

void ConifgManager::DelOption(int flag)
{
	_flag &= (~flag);
}

/////////////////////////////////////////////////////////////////////////
// 剖析段信息

// PerformanceProfiler
// 剖析段节点信息

inline bool PPNode::operator < (const PPNode& node) const
{
	return _line < node._line
		|| _filename < node._filename
		|| _function < node._function;
}

// 剖析段
void PPSection::Begin(int id)
{
	lock_guard<mutex> lock(_mtx);

	if (_refCountMap[id]++ == 0)
	{
		_beginTimeMap[id] = clock();
	}

	_callCountMap[id]++;
}

void PPSection::End(int id)
{
	lock_guard<mutex> lock(_mtx);

	if (--_refCountMap[id] == 0)
	{
		LongType costTime = (clock() - _beginTimeMap[id]);
		_totalCostTime += costTime;
		_costTimeMap[id] += costTime;
	}
}

PPSection* PerformanceProfiler::CreateSection(const char* filename,
	const char* function, size_t line, const char* desc)
{
	PPNode node(filename, function, line, desc);
	PPSection*& section = _ppMap[node];
	if (section == NULL)
		section = new PPSection;

	return section;
}

void PerformanceProfiler::OutPut()
{
	int flag = ConifgManager::GetInstance()->GetOptions();
	if (flag & SAVE_TO_CONSOLE)
	{
		ConsoleSaveAdapter csa;
		_OutPut(csa);
	}

	if (flag & SAVE_TO_FILE)
	{
		FileSaveAdapter fsa("PerformanceProfilerReport.txt");
		_OutPut(fsa);
	}
}

void PerformanceProfiler::_OutPut(SaveAdapter& sa)
{
	vector<PPMap::iterator> vInfos;

	int num = 1;
	PPMap::iterator ppIt = _ppMap.begin();
	while (ppIt != _ppMap.end())
	{
		vInfos.push_back(ppIt);

		/*const PPNode& node = it->first;
		PPSection* section = it->second;
		sa.Save("NO.%d, Desc:%s\n", num++, node._desc.c_str());
		sa.Save("Filename:%s, Function:%s, Line:%u\n",
			node._filename.c_str(), node._function.c_str(), node._line);

		LongType totalCostTime = 0;
		LongType totalCallCount = 0;
		int id = 0;
		LongType costTime = 0;
		LongType callCount = 0;
		StatisticsMap::iterator timeIt = section->_costTimeMap.begin();
		while (timeIt != section->_costTimeMap.end())
		{
			id = timeIt->first;
			costTime = timeIt->second;
			callCount = section->_callCountMap[id];
			totalCostTime += costTime;
			totalCallCount += callCount;

			sa.Save("ThreadId:%d, CostTime:%.2f, CallCount:%lld\n",
				id, (double)costTime / 1000, callCount);

			++timeIt;
		}
		sa.Save("TotalCostTime:%.2f, TotalCallCount:%lld\n\n",
			(double)totalCostTime / 1000, totalCallCount);*/

		++ppIt;
	}

	struct SortByCostTime
	{
		bool operator()(PPMap::iterator left,
		PPMap::iterator right)
		{
			return left->second->_totalCostTime > right->second->_totalCostTime;
		}
	};

	sort(vInfos.begin(), vInfos.end(), SortByCostTime());

	vector<PPMap::iterator>::iterator it = vInfos.begin();
	while (it != vInfos.end())
	{
		const PPNode& node = (*it)->first;
		PPSection* section = (*it)->second;
		sa.Save("NO.%d, Desc:%s\n", num++, node._desc.c_str());
		sa.Save("Filename:%s, Function:%s, Line:%u\n",
			node._filename.c_str(), node._function.c_str(), node._line);

		LongType totalCostTime = 0;
		LongType totalCallCount = 0;
		int id = 0;
		LongType costTime = 0;
		LongType callCount = 0;
		StatisticsMap::iterator timeIt = section->_costTimeMap.begin();
		while (timeIt != section->_costTimeMap.end())
		{
			id = timeIt->first;
			costTime = timeIt->second;
			callCount = section->_callCountMap[id];
			totalCostTime += costTime;
			totalCallCount += callCount;

			sa.Save("ThreadId:%d, CostTime:%.2f, CallCount:%lld\n",
				id, (double)costTime / 1000, callCount);

			++timeIt;
		}
		sa.Save("TotalCostTime:%.2f, TotalCallCount:%lld\n\n",
			(double)totalCostTime / 1000, totalCallCount);

		++it;
	}
}


