#include< stdlib.h>
#include <stdio.h>

typedef int Status;
typedef int ElemType;
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

Status GetElem(Sqlist& L, int i, ElemType& e) {
	if (i<1 || i>L.length) return ERROR;
	e = *(L.elem + i - 1);
	return OK;
}//����Ԫ

void LocateElem(Sqlist& L, ElemType e) {
	//����Ԫ��
	ElemType* p = L.elem;
	ElemType q =0;
	ElemType i = 1;
	if (*p == e) printf("�ڵ�1��λ��");
	while (i <= L.length && *p++ != e) {
		i++;
		if (*p == e)
		{
			q = *p;
			printf("�ڵ� %d ��λ��\n", i);
		}
	}
	
	if ((i-1) == L.length && q != e)
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
			* (p + 1) = *p;
		*q = e;        //����Ԫ��
		++L.length;
	}

	//��Ϊ�洢�ռ��㹻�����
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		* (p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}




Status Input_List(Sqlist& L, int n) {
	if (n > L.listsize) return OVERFLOW;
	else
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &L.elem[i]);
			L.length++;
		}
		return OK;
	}
}

Status Output(Sqlist L) {
	for (int i = 0; i < L.length; i++) {
		printf("%d  ", L.elem[i]);
	}
	printf(" \n");
	return OK;
}
void sort(Sqlist& L) {
	int i, j;
	for (i = 0; i <= L.length - 1; i++) {
		for (j = 0; j < L.length - 1 - i; j++) {

			if (L.elem[j] > L.elem[j + 1]) {
				int tmp = L.elem[j];
				L.elem[j] = L.elem[j + 1];
				L.elem[j + 1] = tmp;
			}
		}
	}
}
Status ListDelete(Sqlist& L, int i) {
	if ((i < 1) || (i > L.length)) return ERROR;
	ElemType* p = &(L.elem[i - 1]);
	ElemType* q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		* (p - 1) = *p;
	--L.length;
	return OK;
}
void Inverse(Sqlist& L) {
	int i;
	ElemType* p, temp;
	p = L.elem;
	for (i = 0; i < (L.length) / 2; i++) {
		temp = *(L.elem + i);
		*(L.elem + i) = *(L.elem + L.length - i - 1);
		*(L.elem + L.length - i - 1) = temp;
	}
}
int max(Sqlist& L) {
	int i = 0;
	int k = L.elem[i];
	for (; i < L.length - 1; i++) {
		if (k < L.elem[i + 1])
			k = L.elem[i + 1];
	}
	return k;
}
int min(Sqlist& L) {
	int i = 0;
	int k= L.elem[i];
	for (; i < L.length - 1; i++) {
		if (k > L.elem[i + 1])
			k = L.elem[i+1];
	}
	return k;
}
void Merge(Sqlist La, Sqlist Lb, Sqlist& Lc) {
	ElemType* pa = La.elem;
	ElemType* pb = Lb.elem;
	int i, j;
	i = 1;
	j = 1;
	ElemType* pc;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
	if (!Lc.elem)  exit(OVERFLOW);
	ElemType* pa_last = La.elem + La.length - 1;
	ElemType* pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa < *pb)
		{
			*pc++ = *pa++;
			++i;
		}
		if (*pa == *pb)
		{
			*pc++ = *pa++;
			++pb;
			Lc.length--;
		}
		else {
			*pc++ = *pb++;
			++j;
		}
	}
	while (pa <= pa_last)* pc++ = *pa++;
	while (pb <= pb_last)* pc++ = *pb++;


}
int main(void) {
	printf("�������ĸ�Ԫ�ص����Ա�Ϊ���ԣ����Ա����������ɺ�������\n");
	Sqlist ts;
	InitList(ts);
	printf("�������ĸ�Ԫ��\n");
	Input_List(ts, 4);
	Output(ts);

	ElemType x;
	printf("������û2���Ԫ��\n");
	LocateElem(ts, 2);

	printf("�������ƺ�\n");
	Inverse(ts);
	Output(ts);



	sort(ts);
	printf("������������\n");
	Output(ts);

	printf("��������%d \n", max(ts));
	printf("��С������%d \n", min(ts));
	int k;
	printf("������Ҫ��ȡ��Ԫ��λ��\n");
	scanf("%d",&k);

	GetElem(ts, k, x);
	printf("��%d��Ԫ����%d\n", k, x);

	Sqlist tpps;
	InitList(tpps);
	printf("�������ĸ�Ԫ��\n");
	Input_List(tpps, 4);

	printf("�ڵ�����λ�ò���8\n");
	ListInsert(tpps, 3, 8);
	Output(tpps);

	printf("ɾ��������Ԫ��\n");
	ListDelete(tpps, 3);
	Output(tpps);

	Sqlist dc;
	Merge(ts, tpps, dc);
	printf("�ϲ�������");
	Output(dc);
	return 0;

}