#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

#include"AVLTree.h"

void Test()
{
	/*
	��ƽ�����������
			12             
		  /   \
		8	   15
	   / \    /  \
	  4	  10  14	17
	 / \     /    / \
	2   6	11   16	 27
					  \          { 16, 4, 8, 12, 10, 45, 17, 14, 15 ,2,6,11,27 };
				       45

		
	*/
	AVLTree<int, int> tree;
	int a[] = { 16, 4, 8, 12, 10,45, 17, 14, 15 ,2,6,11,27 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		tree.Insert(a[i], i);
	}
	
	cout << "����������� " << endl;
	tree.InOrder();
	

	cout << "height=" << tree.Height() << endl;
	bool ret = tree.IsBalance();
	if (ret == true)
		cout << "AVLTree ƽ��!" << endl;
	else
		cout << "AVLTree ��ƽ�� !" << endl;
}
void Test2()
{
	/*
	��ƽ�����������
			10
		  /   \
		4	   9
	   /      /
	  2	    8
	 	
					  


	*/
	AVLTree<int, int> tree;
	int a[] = { 2,4,10,9,8};
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		tree.Insert(a[i], i);
	}

	cout << "����������� " << endl;
	tree.InOrder();


	cout << "height=" << tree.Height() << endl;
	bool ret = tree.IsBalance();
	if (ret == true)
		cout << "AVLTree ƽ��!" << endl;
	else
		cout << "AVLTree ��ƽ�� !" << endl;
}

int main()
{
//	Test();
	Test2();
	return 0;
}