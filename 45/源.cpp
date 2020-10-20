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

typedef struct {                    //�������Ա�Ļ����ṹ *elem ��������Ĺؼ�  ���Ϊ�������Ա����ַ  ������ͨ�� L.elem[x]������
	ElemType* elem;             //˳����x��Ԫ��
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

void Remake(Sqlist &La, Sqlist Lb, Sqlist Lc) {
	ElemType temp[LIST_INIT_SIZE];
	//int time = (Lb.length < Lc.length ? Lb.length: Lc.length);
	
	int i = 0;
	//int j = 1;
	ElemType* pc = Lc.elem;
	ElemType* pb = Lb.elem;
	ElemType* pc_last = Lc.elem + Lc.length - 1;
	ElemType* pb_last = Lb.elem + Lb.length - 1;
	while (pc <= pc_last && pb <= pb_last) {
		if (*pb == *pc) {
			
			temp[i] = *pb;
			pb++;
			pc++;
			i++;

		}
		else {
			if (*pb < *pc)
				pb++;

			else
				pc++;
		}
		/*
		if (*pb == *pc) {
			pb++;
			pc++;
			temp[i] = *pb;
			i++;

		}
		*/
	}
	ElemType* pa = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	int ques=0;
	int pa_i = 0;
	for (int n = 0; n < La.length; n++) {
		for (int m = 0; m < i; m++) {
			if (La.elem[n] == temp[m]) {
				ques = 1;
			}
			
		}
		if (ques == 0) {
			pa[pa_i] = La.elem[n];
			pa_i++;
		}
		ques = 0;
	}
	free(La.elem);
	La.elem = pa;
	La.length = La.length - i;


}
int main() {
	printf("���������Ԫ�ص����Ա�Ϊ���ԣ����Ա�A\n");  //  1  3  5  7  9
	Sqlist A;                                            //12  15  24   35  69
	InitList(A);
	printf("���������Ԫ��\n");
	Input_List(A, 5);
	Output(A);

	printf("���������Ԫ�ص����Ա�Ϊ���ԣ����Ա�B\n");   //2  3   6  7   9
	Sqlist B;                                           //22    24    33   42  45
	InitList(B);
	printf("���������Ԫ��\n");
	Input_List(B, 5);
	Output(B);

	printf("���������Ԫ�ص����Ա�Ϊ���ԣ����Ա�C\n");  //3  7  8  10  11
	Sqlist C;                                             //1  7  24  28  29
	InitList(C);
	printf("���������Ԫ��\n");
	Input_List(C, 5);
	Output(C);

	Remake(A, B, C);
	printf("�����\n");
	Output(A);
}
