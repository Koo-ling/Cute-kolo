#include<iostream>
#include<string>
using namespace std;
typedef struct {
	int number;  //����
	string sex;  //�Ա�
	string name;  //����


} node;   //�洢Ա����Ϣ�Ľṹ��

void selectSort(int a[], int n) {  //��ѡ������
	int min, temp;
	for (int i = 0; i <= n - 1; i++) {
		min = i;
		for (int j = i + 1; j <= n; j++) {
			if (a[j] < a[min])
				min = j;
		}
		if (i != min) {
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	
	}
}

int main() {
	int i;
	node employee[8] = {
		{23,"��","����"},
		{12,"��","�˷�"},
		{45,"Ů","��С��"},
		{18,"��","�"},
		{19,"Ů","��˼˼"},
		{77,"Ů","�ⷽ"},
		{4,"��","��һ��"},
		{96,"��","��ΰ"}
	};
	cout<<"Ա����Ϣ����"<<endl;
	cout << "����\t�Ա�\t����" << endl;
	for (i = 0; i < 8; i++) {
		cout << employee[i].number << "\t" << employee[i].sex << "\t" << employee[i].name << endl;
	}
	int traser[8];  
	for (i = 0; i < 8; i++) {
		traser[i] = employee[i].number;
	}
	selectSort(traser, 7);
	node employee2[8];
	int j = 0;
	int k = 0;
	for (i = 0; i < 8; i++) {
		while (traser[j] != employee[k].number) {
			k++;
		}
		employee2[i].number = employee[k].number;
		employee2[i].sex = employee[k].sex;
		employee2[i].name = employee[k].name;

		j++;
		k = 0;
	}

	cout<<"�������������Ϣ���£�"<<endl;
	cout << "����\t�Ա�\t����" << endl;
	for (i = 0; i < 8; i++) {
		cout << employee2[i].number << "\t" << employee2[i].sex << "\t" << employee2[i].name << endl;
	}
	return 0;

}