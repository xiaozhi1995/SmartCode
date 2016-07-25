#pragma once
#include<iostream>
#include<vector>
using namespace std;
class BitMap//将数据存储在对应的位，用位来存储数据
{
public:
	BitMap(size_t len)
	{
		int size = len >> 5;
		if (len % 32)
			_array.resize(size + 1);
		else
			_array.resize(size);
	}
	BitMap(size_t minLen, size_t maxLen)//如果用这种，求下标时(num-minLen)/32
	{
		int size = (maxLen - minLen + 1) >> 5;
		if ((maxLen - minLen + 1) % 32)
			_array.resize(size + 1);
		else
			_array.resize(size);
	}
	void Set(size_t num)
	{
		size_t index = num >> 5;
		size_t count = num % 32;
		_array[index] |= (1 << count);//将_array[index]第count位置为1,此处存储和大小端有关系
	}
	void ReSet(size_t num)
	{
		size_t index = num >> 5;
		size_t count = num % 32;
		_array[index] &= (!(1 << count));//将_array[index]第count位置为1,此处存储和大小端有关系
	}
	bool Test(size_t num)
	{
		size_t index = num >> 5;
		size_t count = num % 32;
		return  _array[index] & (1 << count);
	}
private:
	vector<int> _array;//用vector<char>不能存储相同的数，有限制，因为它只有0，1两个不同的位
};
class HashFunc1
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}

public:
	size_t operator()(string key)
	{
		return BKDRHash(key.c_str());
	}
};
class HashFunc2
{
	size_t SDBMHash(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}

public:
	size_t operator()(string key)
	{
		return SDBMHash(key.c_str());
	}
};
class HashFunc3
{
	size_t RSHash(const char* str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}

		return hash;
	}

public:
	size_t operator()(string key)
	{
		return RSHash(key.c_str());
	}
};
class HashFunc4
{
	size_t APHash(const char* str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}

		return hash;
	}

public:
	size_t operator()(string key)
	{
		return APHash(key.c_str());
	}
};
class HashFunc5
{
	size_t JSHash(const char* str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}

		return hash;
	}

public:
	size_t operator()(string key)
	{
		return JSHash(key.c_str());
	}
};
template<class K, class Func1 = HashFunc1,
class Func2 = HashFunc2,
class Func3 = HashFunc3,
class Func4 = HashFunc4,
class Func5 = HashFunc5>
class BloomFilter
{
public:
	BloomFilter(size_t cap = 100)
		:_bitmap(cap)
		, _capacity(cap)
	{}
	void Set(const K& key)
	{
		size_t index1 = Func1()(key);
		_bitmap.Set(index1%_capacity);
		size_t index2 = Func2()(key);
		_bitmap.Set(index2%_capacity);
		size_t index3 = Func3()(key);
		_bitmap.Set(index3%_capacity);
		size_t index4 = Func4()(key);
		_bitmap.Set(index4%_capacity);
		size_t index5 = Func5()(key);
		_bitmap.Set(index5%_capacity);
		cout << index1 << " " << index2 << " " << index3
			<< " " << index4 << " " << index5 << endl;
	}
	bool Test(const K& key)
	{
		if (!_bitmap.Test(Func1()(key)%_capacity))
			return false;
		if (!_bitmap.Test(Func2()(key) % _capacity))
			return false;
		if (!_bitmap.Test(Func3()(key) % _capacity))
			return false;
		if (!_bitmap.Test(Func4()(key) % _capacity))
			return false;
		if (!_bitmap.Test(Func5()(key) % _capacity))
			return false;
		return true;
	}
protected:
	BitMap _bitmap;
	size_t _capacity;
};
void Test1()
{
	BloomFilter<string> b;
	b.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html");
	b.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528154.html");
	b.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528155.html");
	b.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528156.html");
	b.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528157.html");
	cout << b.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html") << endl;
	cout << b.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528154.html") << endl;
	cout << b.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528155.html") << endl;
	cout << b.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528156.html") << endl;
	cout << b.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528157.html") << endl;
	cout << b.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528158.html") << endl;
}
#include"BloomFilter.h"
int main()
{
	Test1();
	system("pause");
	return 0;
}