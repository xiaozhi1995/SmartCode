#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include<assert.h>
using namespace std;
#define _CRT_SECURE_NO_DEPRECATE 1

#define _CRT_NONSTDC_NO_DEPRECATE 1
typedef long long LongType;
struct CharInfo
{
	char _ch;
	LongType _count;
	string _code;
	CharInfo(LongType count = 0)
		:_count(count)
	{}
	bool operator<(const CharInfo& info)const
	{
		return _count < info._count;
	}
	CharInfo operator+(const CharInfo& info)const
	{
		return CharInfo(_count + info._count);
	}
	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}
};
template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	T _weight;//权重
	HuffmanTreeNode<T>(T& weight)
		: _left(NULL)
		, _right(NULL)
		, _weight(weight)
	{}
};
template<class T, class Comp = Less<int>>
class Heap
{
public:
	//vector调用自己的构造函数
	Heap()
	{}
	Heap(T* a, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
			_array.push_back(a[i]);
		//size-1是数组最大下标，再减1除二是父节点下标
		for (int i = (_array.size() - 1 - 1) / 2; i >= 0; --i)
		{
			AdjustDown(i);
		}
	}
	void Push(const T& x)
	{
		_array.push_back(x);
		AdjustUp(_array.size() - 1);
	}
	void Pop()
	{
		if (_array.size()>0)
		{
			swap(_array[_array.size() - 1], _array[0]);
			_array.pop_back();
			AdjustDown(0);
		}
	}
	int Size()
	{
		return _array.size();
	}
	T Top()
	{
		if (Size() > 0)
		{
			return _array[0];
		}
	}
protected:
	void AdjustDown(int prtIndex)
	{
		int leftIndex = 0;
		while (prtIndex<_array.size())
		{
			leftIndex = prtIndex * 2 + 1;
			//此处应对称方法，传递的参数，比较大小：
			if (leftIndex + 1 < _array.size() && _com(_array[leftIndex + 1], _array[leftIndex]))
				leftIndex = leftIndex + 1;
			if (leftIndex<_array.size() && _com(_array[leftIndex], _array[prtIndex]))
			{
				swap(_array[prtIndex], _array[leftIndex]);
				prtIndex = leftIndex;
			}
			else
				break;
		}
	}
	void AdjustUp(int  chiIndex)
	{
		int parIndex = (chiIndex - 1) / 2;
		while (chiIndex > 0)//父节点不会小于0，（0-1）/2等于0，此处应用chiIndex来判断
		{
			if (_com(_array[chiIndex], _array[parIndex]))
			{
				swap(_array[parIndex], _array[chiIndex]);
				chiIndex = parIndex;
				parIndex = (chiIndex - 1) / 2;
			}
			else
				break;
		}
	}
protected:
	vector<T> _array;
	Comp _com;
};


template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree(T* a, int size, T& invalid)
		:_root(NULL)
	{
		struct HuffmanCompare
		{
			bool operator()(Node*& l, Node*&  r)
			{
				return l->_weight < r->_weight;
			}
		};
		Heap<Node*, HuffmanCompare> minHeap;
		for (int i = 0; i < size; ++i)
		{
			if (a[i] != invalid)
				minHeap.Push(new Node(a[i]));
		}
		Node    *left, *right, *parent;//指针定义，*和名字在一起
		while (minHeap.Size()>1)
		{
			left = minHeap.Top();
			minHeap.Pop();
			right = minHeap.Top();
			minHeap.Pop();
			parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			minHeap.Push(parent);
		}
		_root = minHeap.Top();
		minHeap.Pop();
	}
	Node* GetRoot()
	{
		return _root;
	}

private:
	Node* _root;
};

class FileCompress
{
protected:
	CharInfo _infos[256];//存储所有字符
public:
	FileCompress()
	{
		for (int i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}
	}
	void Compress(const char* filename)
	{
		FILE* fout = fopen(filename, "r");
		assert(fout);//判断指针非空
		int ch = fgetc(fout);//读取到EOF
		while (ch != EOF)
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fout);
		}
		//建哈夫曼树
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);

		//生成哈夫曼编码
		string code;
		GenerateHuffmanCode(tree.GetRoot(), code);

		string compressFilename = filename;
		compressFilename += ".compress";
		FILE* fin = fopen(compressFilename.c_str(), "w");
		assert(fin);
		fseek(fout, 0, SEEK_SET);
		ch = fgetc(fout);
		int value = 0;
		int size = 0;
		while (ch != EOF)
		{
			string& _c_code = _infos[(unsigned char)ch]._code;
			for (int i = 0; i < _c_code.size(); ++i)
			{
				value <<= 1;
				if (_c_code[i] == '1')
					value |= 1;
				++size;
				if (size == 8)
				{
					fputc(value, fin);
					size = 0;
					value = 0;
				}
			}
			ch = getc(fout);
		}
		//不满8位，低位补0
		if (size)
		{
			value <<= (8 - size);
			fputc(value, fin);
		}
		//写配置文件
		string configName = filename;
		configName += ".config";
		FILE* fInconfig = fopen(configName.c_str(), "w");
		assert(fInconfig);
		for (int i = 0; i < 256; ++i)
		{
			string line;
			char _buf[20];
			if (_infos[i]._count>0)
			{
				memset(_buf, 0, sizeof(_buf));
				line += _infos[i]._ch;
				line += ',';
				line += _itoa(_infos[i]._count, _buf, 10);
				line += '\n';
				fputs(line.c_str(), fInconfig);
			}
		}

		fclose(fin);
		fclose(fout);
		fclose(fInconfig);
	}
	void UnCompress(const char* filename)
	{
		string compressFilename = filename;
		compressFilename += ".compress";
		FILE* fout = fopen(compressFilename.c_str(), "r");
		assert(fout);
		int ch = getc(fout);
		//重建哈夫曼树

		string configFilename = filename;
		configFilename += ".config";
		FILE* foutConfig = fopen(configFilename.c_str(), "r");
		assert(foutConfig);
		//解析配置文件
		string line;
		while (ReadLine(foutConfig, line))
		{
			if (line.empty())//空行
			{
				line += '\n';
			}
			else
			{
				//	_infos[(unsigned char)line[0]]._count = atoi(&line[2]);
				_infos[(unsigned char)line[0]]._count = atoi(line.substr(2).c_str());
				line.clear();
			}
		}
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		//解压缩不需要哈夫曼编码
		HuffmanTreeNode<CharInfo>* root = tree.GetRoot();
		HuffmanTreeNode<CharInfo>* cur = root;

		string uncompressFilename = filename;
		uncompressFilename += ".uncompress";
		FILE* fin = fopen(uncompressFilename.c_str(), "w");
		assert(fin);
		int pos = 7;
		while (ch != EOF)
		{
			if (ch&(1 << pos))
				cur = cur->_right;
			else
				cur = cur->_left;
			if (cur->_left == NULL&&cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fin);
				cur = root;
			}
			--pos;
			if (pos < 0)
			{
				ch = getc(fout);
				pos = 7;
			}
		}
	}
	bool ReadLine(FILE* fout, string& line)
	{
		int ch = fgetc(fout);
		while (ch != EOF&&ch != '\n')
		{
			line += ch;
			ch = fgetc(fout);
		}
		if (ch == '\n')
			return true;
		else
			return false;
	}
	void GenerateHuffmanCode(HuffmanTreeNode<CharInfo>* root, string code)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
			return;
		}
		GenerateHuffmanCode(root->_left, code + '0');
		GenerateHuffmanCode(root->_right, code + '1');
	}
};

void TestCompress()
{
	FileCompress f;
	f.Compress("input.txt");
}
void TestUnCompress()
{
	FileCompress f;
	f.UnCompress("input.txt");
}