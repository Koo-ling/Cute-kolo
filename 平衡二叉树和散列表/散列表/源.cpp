# include <malloc.h>
# include <stdlib.h>
#include<iostream>
using namespace std;
# define max 80
typedef struct
{
    int key;
    char data;
}ElemType;     //����������

typedef struct          //����̽�ⷨ  ���ݽṹ
{
    ElemType elems[max];
    int len;
}HashTable;      //����ɢ�б�����

int stored[max];  //��־����

typedef struct ElemNode {   //������ʱ���õĴ洢�ṹ
    int key;
    ElemType data;
    struct ElemNode* next;
}ElemNode;

typedef struct {
    ElemNode* first;
    int len;
}ElemHeader, hashtable[max];


HashTable initHashTable(int n)     //ht:ɢ�б�   n:ɢ�б���
{
    int i;
    HashTable ht;
    ht.len = n;
    for (i = 0; i < n; i++)
        stored[i] = 0;
    return ht;
}

int Hash(HashTable ht, int k)
{
    return k % ht.len;
}

HashTable insert(HashTable ht, int x)   //ht:ɢ�б�   ele:������   ����̽�ⷨ�����ͻ
{
    int i, add;
    i = Hash(ht, x);
    if (stored[i] == 0)
    {
        ht.elems[i].key = x;
        stored[i] = 1;
    }
    else {
        add = i; i = (i + 1) % ht.len;
        while (i != add && stored[i] == 1)  i = (i + 1) % ht.len;
        if (stored[i] == 0)
        {
            ht.elems[i].key = x; stored[i] = 1;
        }
        else 
            cout<<"error!"<<endl;
    }
    return ht;
}

void InitHashTable(hashtable ht2, int n) {  //�������ĳ�ʼ����ϣ��
    int i;
    ht2->len = n;
    for (i = 0; i < max; i++)
        ht2[i].first = NULL;
}

int hash2(hashtable ht2, int x) {
    return x % ht2->len;
}

void Insert(hashtable ht2, int x) {
    int i; ElemNode* p;
    i = hash2(ht2, x);
    p = (ElemNode*)malloc(sizeof(ElemNode));
    p->key = x;
    p->next = ht2[i].first;
    ht2[i].first = p;
}


void display1(HashTable ht) {
    int i;
    for (i = 0; i < ht.len; i++)
        cout << i << "   ";
    printf("\n");
    for (i = 0; i < ht.len; i++)
        if (stored[i] == 1)
        
                cout << ht.elems[i].key <<"  ";
        else cout <<  "  ";
    cout << endl;
}

void display2(hashtable ht2) {
    int i; ElemNode* p;
    for (i = 0; i < ht2->len; i++) {
        p = ht2[i].first;
        if (p != NULL) {
           
            cout << i << " ";
            while (p != NULL)
            {
                cout << p->key << " ";
                p = p->next;
            }
            cout << endl;
        }
        else
            cout << i << endl;
    }
}


void main()
{
    HashTable ht; hashtable ht2; ElemNode* p;
    int i, j, n, x, t;
    p = (ElemNode*)malloc(sizeof(ElemNode));
    cout<<"������ɢ�б�ĳ��ȣ�";
    cin >> n;
    InitHashTable(ht2, n);
    ht = initHashTable(n);
    cout << "���������ݣ�������"<<n<<"�����Ը���������";
    cin >> x;
    while (x >= 0)
    {
        ht = insert(ht, x);
        Insert(ht2, x); 
        cin>>x;
    }
        cout << "����̽�ⷨ������                            \n";
        display1(ht);        
        cout << "������������                            \n";
        display2(ht2);
           

        return;
        
    
}

