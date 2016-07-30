#include<iostream>
#include<stdarg.h>
using namespace std;


#define __DEBUG__
static string GetFileName(const string& path)
{
	char ch = '/';
#ifdef _WIN32
	ch = '\\';
#endif
	size_t pos = path.rfind(ch);
	if (pos == string::npos)
		return path;
	else
		return path.substr(pos + 1);
} 
// ���ڵ���׷�ݵ�trace log
inline static void __trace_debug(const char* function,
const char * filename, int line, char* format, ...)
{
#ifdef __DEBUG__
		// ������ú�������Ϣ
		fprintf(stdout, "��%s:%d�� %s", GetFileName(filename).c_str(), line, function);
	// ����û����trace��Ϣ
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
#endif
} 
#define __TRACE_DEBUG(...) \
__trace_debug(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);
typedef void(*MallocAllocHandler)();
template <int inst>
class MallocAllocTemplate
{
protected:
	static	MallocAllocHandler _handler;
	static void* Oom_Malloc(size_t n)
	{
		MallocAllocHandler handler = NULL;
		void* ret = NULL;
		while (1)
		{
			handler = _handler;
			if (handler == NULL)
			{
				cout << "out of memory" << endl;
				//exit(1);
			}
			(*handler)();
			ret = malloc(n);
			if (ret)
				return ret;
		}
	}
public:
	static void * Allocate(size_t n)
	{
		void *result = malloc(n);
		if (0 == result) result = Oom_Malloc(n);
		__TRACE_DEBUG("����һ���ռ������������ڴ棺ptr:%p,size:%u\n", result,n);
		return result;
	}

	static void Deallocate(void *p, size_t n)
	{
		free(p);
		__TRACE_DEBUG("����һ���ռ��������ͷ��ڴ棺ptr:%p,size:%u\n", p, n);
	}
	static void(*SetMallocHandler(MallocAllocHandler f))()
	{
		void(*old)() = _handler;
		_handler = f;
		return(old);
	}
};
template<int inst> MallocAllocHandler MallocAllocTemplate<inst>::_handler = NULL;
template <bool threads, int inst>
class DefaultAllocTemplate
{
	enum { ALIGN = 8 };
	enum { MAX_BYTES = 128 };
	enum { NFREELISTS = MAX_BYTES / ALIGN };
	union Obj {
		union Obj * _freeListLink;
		char _clientData[1];    /* The client sees this.        */
	};
	static Obj * volatile _freeList[NFREELISTS];//ָ������
	static char *_startFree;
	static char *_endFree;
	static size_t _heapSize;
	static  size_t FreeListIndex(size_t bytes) {
		return (((bytes)+ALIGN - 1) / ALIGN - 1);
	}
	static size_t RoundUp(size_t bytes) {
		return (((bytes)+ALIGN - 1) & ~(ALIGN - 1));
	}
	static char* chunkAlloc(size_t n, int& nobjs)
	{
		char* ret = NULL;
		size_t totalBytes = n*nobjs;
		size_t freeLeft = _endFree - _startFree;
		if (freeLeft >= totalBytes)
		{
			ret = _startFree;
			_startFree += totalBytes;
			__TRACE_DEBUG("�ڴ���㹻����ռ䣺ptr:%p,size:%u\n", ret, totalBytes);
			return(ret);
		}
		else if (freeLeft >= n)
		{
			nobjs = freeLeft / n;
			totalBytes = n*nobjs;
			ret = _startFree;
			_startFree += totalBytes;
			__TRACE_DEBUG("�ڴ��ֻ�пռ䣺ptr:%p,size:%u\n", ret, totalBytes);
			return(ret);
		}
		else
		{
			size_t bytesOfGet = 2 * totalBytes + RoundUp(_heapSize >> 4);
			//��ʣ�µ�С���ڴ����
			if (freeLeft > 0)
			{
				Obj* myFreeList = _freeList[FreeListIndex(freeLeft)];
				((Obj*)_startFree)->_freeListLink = myFreeList;
				_freeList[FreeListIndex(freeLeft)] = (Obj*)_startFree;
			}
			_startFree =(char*) malloc(bytesOfGet);
			if (_startFree == NULL)
			{
				Obj* myFreeList, *p;
				for (int i = n; i < MAX_BYTES; i += ALIGN)
				{
					myFreeList = _freeList[FreeListIndex(i)];
					if (myFreeList != NULL)
					{
						p = myFreeList;
						myFreeList = myFreeList->_freeListLink;
						_startFree = (char*)p;
						_endFree = _startFree + i;
						return chunkAlloc(n, nobjs);//�����else if
					}
				}
				//���������ޱ�n����ڴ�
				_endFree = NULL;//��ֹ_startFree����0����_endFreeΪһ���ܴ��ֵ������Ϊ���ڴ���ڴ�ɷ���
				_startFree = (char*)MallocAllocTemplate<0>::Allocate(bytesOfGet);
			}
			_heapSize += bytesOfGet;
			_endFree = _startFree + bytesOfGet;
			return chunkAlloc(n, nobjs);//���if
		}
	}
	static void* Refill(size_t n)
	{
		int nobjs = 20;
		char * chunk = chunkAlloc(n, nobjs);
		Obj* volatile * myFreeList;
		Obj* ret;
		Obj * currentObj=NULL, *nextObj=NULL;
		int i;
		if (1 == nobjs)  return(chunk);
		myFreeList = _freeList + FreeListIndex(n);
		ret = (Obj *)chunk;
		*myFreeList = nextObj = (Obj *)(chunk + n);
		/*for (i = 1;; i++) {
			currentObj = nextObj;
			nextObj = (Obj *)((char *)nextObj + n);
			if (nobjs - 1 == i)
			{
				currentObj->freeListLink = 0;
				break;
			}
			else
			{
				currentObj->freeListLink = nextObj;
			}
		}*/
		//
		for (i = 0; i < nobjs - 1; ++i)
		{
			currentObj = nextObj;
			nextObj = nextObj + 1;
			currentObj->_freeListLink = nextObj;
		}
		__TRACE_DEBUG("���ؿռ䵽��������\n");
		currentObj->_freeListLink = NULL;
		return ret;
	}
public:
	static void Deallocate(void* p, size_t size)
	{
		if (size > MAX_BYTES)
		{
			MallocAllocTemplate<0>::Deallocate(p, size);
			__TRACE_DEBUG("����һ���ռ��������ͷ��ڴ棺ptr:%p,size:%u\n",p,size);
		}
		else
		{
			Obj * myFreeList = _freeList[FreeListIndex(size)];
			((Obj*)p)->_freeListLink = myFreeList;
			_freeList[FreeListIndex(size)] = (Obj*)p;
			__TRACE_DEBUG("���ص����������ͷ��ڴ棺ptr:%p,size:%u\n", p, size);
		}
	}
	static void * Allocate(size_t n)
	{
		Obj * volatile * myFreeList;
		Obj * result;
		if (n > MAX_BYTES)
		{
			return(MallocAllocTemplate<1>::Allocate(n));
		}
		myFreeList = _freeList + FreeListIndex(n);
		result = *myFreeList;
		if (result == NULL)
		{
			void* ret = Refill(RoundUp(n));
			__TRACE_DEBUG("����ռ䣺ptr:%p\n", ret);

			return ret;
		}
		*myFreeList = result->_freeListLink;
		__TRACE_DEBUG("����������ֱ��ȡ��ptr:%p,size:%u\n", result,n);

		return result;
	}
};
template<bool threads,int inst> 
typename DefaultAllocTemplate<threads, inst>::Obj*  volatile DefaultAllocTemplate<threads, inst>::_freeList[DefaultAllocTemplate<0, 0>::NFREELISTS] = { 0 };//ָ������
template<bool threads,int inst>
char* DefaultAllocTemplate<threads, inst>::_startFree = NULL;
template<bool threads, int inst>
char* DefaultAllocTemplate<threads, inst>::_endFree = NULL;
template<bool threads, int inst>
size_t DefaultAllocTemplate<threads, inst>::_heapSize = 0;
# ifdef __USE_MALLOC

typedef MallocAllocTemplate<0> Alloc;
typedef MallocAllocTemplate<0> Alloc;
# else
typedef DefaultAllocTemplate<0, 0> Alloc;
typedef DefaultAllocTemplate<0, 0> Alloc;
#endif

template<class T, class Alloc>
class SimpleAlloc
{
public:
	static T *Allocate(size_t n) { return 0 == n ? 0 : (T*)Alloc::Allocate(n*sizeof(T)); }
	static T *Allocate(void) { return (T*)Alloc::Allocate(sizeof(T)); }
	static void Deallocate(T* p, size_t n) { if (0 != n) Alloc::Deallocate(p, n*sizeof(T)); }
	static void Deallocate(T *p){ Alloc::Deallocate(p, sizeof(T)); }
	//�����ô��ݸ��������ĳ�Ա�����������ǵ�һ��Ҳ�����ǵڶ���
};
void Test1()
{
	//MallocAllocTemplate<1> d;
	////int *p=(int*)MallocAllocTemplate<1>::Allocate(sizeof(int));
	//int *p=(int*)d.Allocate(sizeof(int));
	//*p = 2;
	//cout << *p << endl;
	//d.Deallocate(p, sizeof(int));
	//DefaultAllocTemplate<0, 0> a;
	//int* p1 = (int*)a.Allocate(sizeof(int));
	//*p1 = 3;
	//cout << *p1 << endl;
	//typedef MallocAllocTemplate<0> Alloc;
	// ���Ե���һ�������������ڴ�
	cout << " ���Ե���һ�������������ڴ� " << endl;
	char*p1 = SimpleAlloc< char, Alloc>::Allocate(129);
	SimpleAlloc<char, Alloc>::Deallocate(p1, 129);
	// ���Ե��ö��������������ڴ�

	cout << " ���Ե��ö��������������ڴ� " << endl;
	char*p2 = SimpleAlloc< char, Alloc>::Allocate(128);
	char*p3 = SimpleAlloc< char, Alloc>::Allocate(128);
	char*p4 = SimpleAlloc< char, Alloc>::Allocate(128);
	char*p5 = SimpleAlloc< char, Alloc>::Allocate(128);
	SimpleAlloc<char, Alloc>::Deallocate(p2, 128);
	SimpleAlloc<char, Alloc>::Deallocate(p3, 128);
	SimpleAlloc<char, Alloc>::Deallocate(p4, 128);
	SimpleAlloc<char, Alloc>::Deallocate(p5, 128);
	for (int i = 0; i < 21; ++i)
	{
		printf(" ���Ե�%d�η��� \n", i + 1);
		char*p = SimpleAlloc< char, Alloc>::Allocate(128);
	}
}
// �������ⳡ��
void Test2()
{
	cout << " �����ڴ�ؿռ䲻������ " << endl;
	// 8*20->8*2->320
	char*p1 = SimpleAlloc< char, Alloc>::Allocate(8);
	char*p2 = SimpleAlloc< char, Alloc>::Allocate(8);
	cout << " �����ڴ�ؿռ䲻�㣬 ϵͳ�ѽ��з��� " << endl;
	char*p3 = SimpleAlloc< char, Alloc>::Allocate(12);
}
void Test3()
{
	cout << " ����ϵͳ���ڴ�ľ� " << endl;
	SimpleAlloc<char, Alloc>::Allocate(1024 * 1024 * 1024);
	//SimpleAlloc<char, Alloc>::Allocate(1024*1024*1024);
	SimpleAlloc<char, Alloc>::Allocate(1024 * 1024);
	// ���ò��ԣ� ˵��ϵͳ����С���ڴ���������Ǻ�ǿ�ġ�
	for (int i = 0; i < 100000; ++i)
	{
		char*p1 = SimpleAlloc< char, Alloc>::Allocate(128);
	}
}