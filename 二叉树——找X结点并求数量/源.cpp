#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//typedef char Status;
typedef int Belem;
typedef struct node {
	//�ṹ�嶨��
	Belem data;
	node* lelem;
	node* relem;

}node, * bnode;


void creat(bnode& p) {   //�����������������
	int c;
	cin >> c;
	if (c == -1)
		p = NULL;
	else {
		p = new node;
		p->data = c;
		creat(p->lelem);
		creat(p->relem);
	}
}

void Preoutput(bnode& p) {  //����������
	if (p)
	{
		cout << p->data << " ";
		Preoutput(p->lelem);
		Preoutput(p->relem);

	}
}

int PresortFindX(bnode& root,int m)
{ //���÷ǵݹ������������ҵ�X�Ľڵ�����
	bnode p = root;
	if (p == NULL)
		return -1;
	stack<bnode> s;
	int count = 0;
	while (!s.empty() || p)
	{

		while (p) {

			//cout << p->data << " ";
			if (p->data == m)
				count++;
			s.push(p);
			p = p->lelem;
		}
		if (!s.empty()) {
			p = s.top();
			p = p->relem;
			s.pop();
		}
	}
	return count;
}




void Find_X_Child(bnode& root, int m)
{ //���÷ǵݹ������������ҵ�X�ĺ��ӽڵ㲢���
	bnode p = root;
	if (p == NULL)
		return;
	stack<bnode> s;
	//int count = 0;
	while (!s.empty() || p)
	{

		while (p) {

			//cout << p->data << " ";
			if (p->data == m)
				//count++;
			{
				if(p->lelem)
				cout << p->lelem->data<<" ";
				if(p->relem)
				cout << p->relem->data << " ";
			}
			s.push(p);
			p = p->lelem;
		}
		if (!s.empty()) {
			p = s.top();
			p = p->relem;
			s.pop();
		}
	}
	
}
int main() {
	node* root;
	cout << "�������������Ϊ���룬������Ϊ���á�-1����ʾ" << endl;
	creat(root);
	cout << "����������" << endl;
	Preoutput(root);
	cout << endl;
	cout << "��ѡ��Ҫ���ҵ�ֵ" << endl;
	int x;
	cin >> x;
	cout << "��ֵ�ڶ������ڵ�����Ϊ��" << endl;
	cout<<PresortFindX(root, x);
	cout << "��ֵ���ӽڵ��У�" << endl;
	Find_X_Child(root, x);


}