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
    while (pHead!= NULL)//���pheadָ��ṹ�廹������
    {
        del = pHead;
        pHead = pHead->_next;
        free(del);
    }
}
void  Joseph(pLinkNode pHead,int  Length)
{
    assert(pHead);//ѭ������
    pLinkNode cur = pHead, del;
    while (1)
    {
        if (cur->_next == cur)
        {
            assert(cur->_data = 4);
            printf("��ʣ���%d\n", cur->_data);
            return;
        }
             
        int times = Length - 1;
        while (times--)
        {
            cur = cur->_next;
        }
        del = cur->_next;
        cur->_data = cur->_next->_data;//����cur����һ���������ݣ�ɾ����
        cur->_next = del->_next;
        free(del);
  