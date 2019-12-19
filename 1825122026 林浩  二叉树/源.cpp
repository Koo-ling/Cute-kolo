#include<iostream>
#include<stack>
#include<queue>
using namespace std;
typedef char Status;
typedef char Belem;
typedef struct node {

	Belem data;
	node* lelem;
	node* relem;

}node, * bnode;

void creat(bnode& p) {

	char c;
	cin >> c;
	if (c == '#')
		p = NULL;
	else {
		p = new node;
		p->data = c;
		creat(p->lelem);
		creat(p->relem);
	}
	
}

void Preoutput(bnode &p) {

	if (p)
	{
		cout << p->data << " ";
		Preoutput(p->lelem);
		Preoutput(p->relem);

	}
}

void Midoutput(bnode &p) {
	if (p)
	{
		Midoutput(p->lelem);
		cout << p->data << " ";
		Midoutput(p->relem);
	}
}

void Laoutpaut(bnode &p) {
	if (p)

	{
		Laoutpaut(p->lelem);
		Laoutpaut(p->relem);
		cout << p->data << " ";
	}
}

//�����Ƿǵݹ�ĺ���
void Presort(bnode& root) {
	bnode p = root;
	if (p == NULL)
		return;
	stack<bnode> s;

	while (!s.empty()||p)
	{  
		
		while (p) {
		
			cout << p->data << " ";
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




void Midsort(bnode& root) {
	bnode p = root;
	if (p == NULL)
		return;

	stack<bnode> s;
	while (!s.empty()||p) {
		while (p) {
			
			s.push(p);
			p = p->lelem;

		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			cout << p->data << " ";
			p = p->relem;
		}
	}

}
void lastsort(bnode& root) {
	bnode p = root;
	bnode lastvist = NULL;
	if (p == NULL)
		return;
	stack<bnode> s;
	
		while (p) {
			s.push(p);
			p = p->lelem;
		}
		while (!s.empty()) {
			p = s.top();
			s.pop();

			if (p->relem == NULL || p->relem == lastvist) {
				cout << p->data << " ";

				lastvist = p;

			}
			else {
				s.push(p);
				p = p->relem;
				while (p) {
					s.push(p);
					p = p->lelem;

				}
			}
		}
}
//�������
void LevelTraverse(bnode p) {
	if (p == NULL)  return;
	queue<bnode> k;
	k.push(p);

	while (!k.empty()) {
		bnode front = k.front();
		k.pop();

		cout << front->data;
		if (front->lelem != NULL) {
			k.push(front->lelem);
		}
		if (front->relem != NULL) {
			k.push(front->relem);
		}
	}

}
int main() {
	node* root;
	cout << "�������������Ϊ���룬������Ϊ���á�#����ʾ" << endl;
	creat(root);
	cout << "����������" << endl;
	Preoutput(root);
	cout << endl;
	cout << "����������" << endl;
	Midoutput(root);
	cout << endl;
	cout << "����������" << endl;
	Laoutpaut(root);
	cout << endl;
	cout << "�����Ƿǵݹ����" << endl;
	 
	
	cout << "ǰ�����" << endl;
	Presort(root);
	cout << endl;
	cout << "�������  " << endl;
	Midsort(root);
	cout << endl;
	cout << "�������" << endl;
	lastsort(root);
	cout << endl;
	cout << "�������" << endl;
	LevelTraverse(root);
	cout << endl;
	return 0;
}