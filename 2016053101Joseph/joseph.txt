#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
typedef  int   DataType;
typedef struct  LinkNode
{
    DataType _data;
    struct   LinkNode *_next;
}LinkNode,*pLinkNode;
pLinkNode BuyNode(DataType x)
{
    pLinkNode tmp;
    tmp = (pLinkNode)malloc(sizeof(LinkNode));
    tmp->_data = x;
    tmp->_next = NULL;
    return  tmp;
}
void  InitNode(pLinkNode& pHead)
{
    pHead=NULL;
}
void  DestoryNode(pLinkNode& pHead)
{
    pLinkNode del=pHead;
    while (pHead!= NULL)//如果phead指向结构体还有数据
    {
        del = pHead;
        pHead = pHead->_next;
        free(del);
    }
}
void  Joseph(pLinkNode pHead,int  Length)
{
    assert(pHead);//循环链表
    pLinkNode cur = pHead, del;
    while (1)
    {
        if (cur->_next == cur)
        {
            assert(cur->_data = 4);
            printf("所剩最后：%d\n", cur->_data);
            return;
        }
             
        int times = Length - 1;
        while (times--)
        {
            cur = cur->_next;
        }
        del = cur->_next;
        cur->_data = cur->_next->_data;//拷贝cur的下一个结点的数据，删除它
        cur->_next = del->_next;
        free(del);
  