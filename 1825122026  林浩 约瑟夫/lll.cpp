#include<iostream>
#include<malloc.h>
using namespace std;
struct node {
	int sq;
	int code;
	node* next;
};
int main() {
	int m, n, i, j;
	node* p=NULL, * q, * first=NULL;
	cout << "���������� m�� ";
	cin >> m;
	cout << "���������� n�� ";
	cin >> n;
	for (i = 1; i <= n; i++) {  //�ڴ���ѭ������Ĺ���������ÿ���ڵ������
		if (i == 1)             //β�巨
		{
			first = p = (node*)malloc(sizeof(node));
			if (!p)
				return 0;
		}
		else
		{
			q = (node*)malloc(sizeof(node));
			if (!q)
				return 0;
			p->next = q;     //��q����p�ڵ�֮��
			p = q;           //�ڽ����q�ڵ���Ϊp��ʵ�ֲ��ϵ�β��

		}
		cout << "�������" << i << "���˵�����";
		cin >> (p->code);
		p->sq = i;
	}
	p->next = first;
	p = first;     //ͷ�ڵ�ɾ��
	cout << "����˳��Ϊ";
	for (j = 1; j <= n; j++)      //n���ˣ���ѭ��n�γ���
	{
		for (i = 1; i < m; i++, p = p->next);
		m = p->code;
		cout << p->sq << " ";
		p->sq = p->next->sq;
		p->code = p->next->code;
		q = p->next;
		p->next = p->next->next;
		free(q);

	}
	cout << endl;
	return 0;

}