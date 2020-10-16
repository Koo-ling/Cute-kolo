#include< stdlib.h>
#include <stdio.h>

typedef int Status;
typedef long ElemType;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE  100
#define LISTINCREAMENT 10

typedef struct {                      
	ElemType* elem;             
	int length;
	int listsize;
}Sqlist;

Status InitList(Sqlist& L) {
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)  exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}//��ʼ�����Ա�

Status GetElem(Sqlist& L, int i, ElemType& e) {       //��������Ԫ�ط��ظ� e
	if (i<1 || i>L.length) return ERROR;
	e = *(L.elem + i - 1);
	return OK;
}//����Ԫ

void LocateElem(Sqlist& L, ElemType e) {
	//����Ԫ��
	ElemType* p = L.elem;
	ElemType q = 0;
	ElemType i = 1;
	if (*p == e) printf("�ڵ�1��λ��");
	while (i <= L.length && *p++ != e) {
		i++;
		if (*p == e)
		{
			q = *p;
			printf("�ڵ� %d��λ��\n", i);
		}
	}

	if ((i - 1) == L.length && q != e)
		printf("���Ա����޴�Ԫ��\n");

}
Status ListInsert(Sqlist& L, int i, ElemType e) {
	ElemType* q, * p;
	ElemType* newbase = NULL;
	if (i<1 || i>L.length + 1) // iֵ���Ϸ�
		return ERROR;
	if (L.length >= L.listsize)
	{
		// ��ǰ�洢�ռ�����,���ӷ��䣬������Ԫ��
		newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREAMENT) * sizeof(ElemType));

		if (!newbase)
			exit(OVERFLOW); // �洢����ʧ��
		L.listsize += 10; // ���Ӵ洢����
		q = &(L.elem[i - 1]);
		for (p = &(L.elem[L.length - 1]); p >= q; --p)
			*(p + 1) = *p;
		*q = e;        //����Ԫ��
		//printf("%ld  ,%ld", *q, e);
		++L.length;
	}

	//��Ϊ�洢�ռ��㹻�����
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
//	printf("%ld  ,%ld", *q, e);
	++L.length;
	return OK;
}




Status Input_List(Sqlist& L, int n) {
	if (n > L.listsize) return OVERFLOW;
	else
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%ld", &L.elem[i]);
			L.length++;
		}
		return OK;
	}
}

Status Output(Sqlist L) {
	for (int i = 0; i < L.length; i++) {
		printf("%ld  ", L.elem[i]);
	}
	printf(" \n");
	return OK;
}

Status InsertX(Sqlist& L,ElemType y,ElemType x) {
	ElemType* q, * p;
	
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i] == y) {
			q = &(L.elem[i]);
			for (p = &(L.elem[L.length - 1]); p >= q; --p)
				*(p + 1) = *p;
		//	*q = x;
		//	printf("%ld  ,%ld", *q, x);
			L.elem[i] = x;
			++L.length;
			return 1;
		}
		
	}
	return -1;
}

void traSort(Sqlist& L) {
	Sqlist newly;
	InitList(newly);
	Sqlist ou;
	InitList(ou);
	int j = 0,k=0,m=0;
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i] % 2 != 0) {
			ListInsert(newly, j+1, L.elem[i]);
			//printf("%ld  ", L.elem[i]);
			j++;
		}
		if (L.elem[i] % 2 == 0) {
			ListInsert(ou, k+1, L.elem[i]);
			//printf("%ld  ", L.elem[i]);
			k++;
		}
	}
	//Output(newly);
	//Output(ou);
	for (; j < L.length; j++) {
		ListInsert(newly, j+1, ou.elem[m]);
		m++;
	}
	Sqlist w=L;
	L = newly;
	delete[] w.elem;
	delete[] ou.elem;
}

int main(void) {
	printf("������5��Ԫ�ص����Ա�Ϊ���ԣ����Ա����������ɺ�������\n");
	Sqlist ts;
	InitList(ts);
	printf("������Ԫ��\n");
	Input_List(ts, 5);
	Output(ts);

	printf("������Ҫ y �Ͳ����Ԫ��x\n");
	long y;
	long x;
	scanf("%ld", &y);
	scanf("%ld", &x);
	//	printf("%ld ,%ld", y, x);
	InsertX(ts, y, x);
	Output(ts);
	
	printf("������������ǰ��ż����\n");
	traSort(ts);
	Output(ts);
	
	
	return 0;

}

