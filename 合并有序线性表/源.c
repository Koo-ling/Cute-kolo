#include <stdio.h>
#include <stdlib.h>
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define list_init_size 80 //��ʼ����洢�ռ�
#define listincreament 10 //�洢�ռ��������

typedef char ElemType;
typedef char Belem;
typedef struct node {
	//�ṹ�嶨��
	Belem data;
	node* lelem;
	node* relem;

}node, * bnode;


void creat(bnode p) {   //�����������������
	char ch;
	scanf(" %c", ch);
	if (ch == '#')
		p = NULL;
	else {
		p = new node;
		p->data = ch;
		creat(p->lelem);
		creat(p->relem);
	}
}


void PrePut(bnode p) {

	if (p)
	{
		cout << p->data << " ";
		PrePut(p->lelem);
		PrePut(p->relem);

	}
}

//����ǵݹ��������X�Ľ��
void Midsort(bnode root,char x) {
	bnode p = root;
	if (p == NULL)
		return;
	int count=0;
	stack<bnode> s;
	while (!s.empty() || p) {
		while (p) {

			s.push(p);
			p = p->lelem;

		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			if (p->data == x) {
				printf(" %c ", p->data);
				count++;
			}

			p = p->relem;
		}
	}
	printf("һ���ҵ�ֵΪ %c �Ľڵ��� %d ��\n"��x, count);

}


void FindXLevel(bnode p,char x, int level) {
	if (p) {
		if (p->data == x) {
			printf("�����ڵ� %d �� ", level);

		}
		FindXLevel(p->lelem, x, level + 1);
		FindXLevel(p->relem, x, level + 1);
	}
}

//ABD##E##CF##G##
int main(void) {
	bnode test;
	creat(test);
	PrePut(test);
	printf("������Ҫ���ҵ�Xֵ %c\n");
	char x;
	scanf(" %c", x);
	Midsort(test,x);
	FindXLevel(test,x,0);
	return 0;

}
