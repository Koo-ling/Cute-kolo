#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

typedef struct sortTree {
	sortTree* lchild;
	sortTree* rchild;
	int val;//�ڵ�ֵ
}sortTree,*tree;

void InsertBST(tree &t, int val) {
	if (t == nullptr)
	{
		t = new sortTree;
		t->val = val;
		t->lchild = nullptr;
		t->rchild = nullptr;
	}
	
    if (val > t->val) {
			InsertBST(t->rchild, val);
		}
	if (val < t->val) {
			InsertBST(t->lchild, val);
		}
	
}

void CreatBST(tree &t,int a[],int n) {
	
	//t = nullptr;
	int i = 0;
	while (i < n) {
	//	cout << a[i];
		InsertBST(t, a[i]);
		i++;
	}
}
void Traverse(tree t) {
	//cout << "v f da";
	//�����������
	if (t == NULL) {
		//cout << "gsdfg";
		return;

	}
	else {
		Traverse(t->lchild);
		cout << (*t).val << " ";
		Traverse(t->rchild);
	}
}
int main() {
	cout << "����������������Ľڵ���" << endl;
	int x;
	tree test=NULL;
	cin >> x;
	int* s = new int[x];
	cout << "������������ڵ��ֵ" << endl;
	for (int i = 0; i < x; i++) {
		cin >> s[i];	
	}
	CreatBST(test,s,x);
	Traverse(test);
}


