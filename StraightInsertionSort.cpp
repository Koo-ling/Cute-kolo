#include<iostream>
using namespace std;
void print(int a[], int n) {
	for (int i = 0; i <= n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void sort(int a[], int n) {
	int i, j;
	for (int i = 2; i <= n; i++) {
		if (a[i] <= a[i - 1]) {
			a[0] = a[i];
			for (j = i - 1; a[0] < a[j]; j--) {
				a[j + 1] = a[j];
				
			}
			a[j + 1] = a[0];
		}
		print(a, n);
	}
}
int main() {
	int a[9] = {0,49,38,65,97,76,13,27,49 };
	cout << "��ʼ�������£����е�һ��Ԫ����Ϊ�ڱ�" << endl;
	print(a, 8);
	cout << "�������ÿ������������" << endl;
	sort(a, 8);
	return 0;
}