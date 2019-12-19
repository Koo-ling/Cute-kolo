#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<string.h>;
using namespace std;

#define N 27//��Ȩֵ��Ҷ�ӽڵ�����������Ҫ������ַ���
#define M 2*N-1//n��Ҷ�ӽڵ㹹��Ĺ���������2n-1�����
#define MAX 10000
typedef char TElemType;
//��̬��������洢�ṹ
typedef struct {

    int weight;
	int parent;
	int lchild;
	int rchild;

}HTNode;//, *HuffmanTree;

typedef struct node {

	int data;
	node* lelem;
	node* relem;

}node, * bnode;
bnode ai = (bnode)malloc((M+1) * sizeof(node));
typedef HTNode HuffmanTree[M + 1];//0�ŵ�Ԫ��ʹ��
typedef char* HuffmanCode[N + 1];//�洢ÿ���ַ��Ĺ������������һ���ַ�ָ�����飬ÿ������Ԫ����ָ���ַ�ָ���ָ��

void select(HuffmanTree HT, int k, int& s1, int& s2) {

	//����s1��Ӧ��Ȩֵ����<=s2��Ӧ��Ȩֵ

	unsigned int tmp = MAX, tmpi = 0;
	for (int i = 1; i <= k; i++) {
		if (!HT[i].parent) {//parent����Ϊ0
			if (tmp > HT[i].weight) {
				tmp = HT[i].weight;//tmp���Ϊ��С��weight
				tmpi = i;
			}
		}
	}
	s1 = tmpi;
	tmp = MAX;
	tmpi = 0;
	for (int i = 1; i <= k; i++) {
		if ((!HT[i].parent) && i != s1) {//parentΪ0
			if (tmp > HT[i].weight) {
				tmp = HT[i].weight;
				tmpi = i;
			}
		}
	}
	s2 = tmpi;
}

//�����������

void createHuffmanTree(HuffmanTree& HT, int* w, int n) {
	int i = 1;
	if (n <= 1)
		return;
	//��������ֵ

	for (; i <= n; i++) {//HTǰn�������洢Ҷ�ӽڵ㣬���Ǿ�����Ȩֵ

		HT[i].weight = w[i];
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	for (; i <= M; i++) {//HT��m-n�������洢�м��㣬���һ��������Ȼ���������ĸ��ڵ�
		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	//��ʼ��������������������HT�ĺ�m-n�����Ĺ��̣�ֱ�����������ڵ㡣�ù������㷨
	for (i = n + 1; i <= M; i++) {
		int s1, s2;
		select(HT, i - 1, s1, s2);//��HT[1...i-1]��ѡ��parentΪ0����Ȩֵ��С��2��㣬����ŷֱ�Ϊs1,s2��parent��Ϊ0˵���ý���Ѿ����빹���ˣ��ʲ����ٿ���
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
void decodingHuffmanCode(HuffmanTree HT, char* ch, char testDecodingStr[], int len, char* result) {

	int p = M;//HT�����һ���ڵ��Ǹ��ڵ㣬ǰn���ڵ���Ҷ�ӽڵ�
	int i = 0;//ָʾ���Դ��еĵ�i���ַ�
	//char result[30];//�洢�����Ժ���ַ���
	int j = 0;//ָʾ������еĵ�j���ַ�
	while (i < len) {
		if (testDecodingStr[i] == '0') {
			p = HT[p].lchild;
		}
		if (testDecodingStr[i] == '1') {
			p = HT[p].rchild;
		}
		if (p <= N) {//p<=N�����pΪҶ�ӽڵ�,��Ϊ�ڹ����������HTʱ��HT��m���ڵ���ǰn���ڵ�ΪҶ�ӽڵ�
			result[j] = ch[p];
			j++;
			p = M;//p����ָ����ڵ�
		}
		i++;
	}
	result[j] = '\0';	
}

//Ϊÿ���ַ������������룬��Ҷ�ӵ����������ÿ���ַ��Ĺ���������

void encodingHuffmanCode(HuffmanTree HT, HuffmanCode& HC) {

	//char *tmp = (char *)malloc(n * sizeof(char));//��ÿһ���ַ���Ӧ�ı��������ʱ�����ռ�tmp�ÿ���ַ��ı��볤�Ȳ��ᳬ��n
	char tmp[N];
	tmp[N - 1] = '\0';//����Ľ�����
	int start, c, f;
	for (int i = 1; i <= N; i++) {//���ڵ�i���������ַ�����i����Ȩֵ��Ҷ�ӽڵ�
		start = N - 1;//���������Ժ�start��ָ��������ʼλ��
		c = i;
		f = HT[i].parent;
		while (f) {//f!=0,��f���Ǹ��ڵ�ĸ��ڵ�
			if (HT[f].lchild == c) {
				tmp[--start] = '0';
			}
			else {//HT[f].rchild == c,ע��:���ڹ���������ֻ����Ҷ�ӽڵ�Ͷ�Ϊ2�Ľڵ㣬���Գ���Ҷ�ӽڵ㣬�ڵ�һ��������2����֧
				tmp[--start] = '1';
			}
			c = f;
     		f = HT[f].parent;
		}
		HC[i] = (char*)malloc((N - start) * sizeof(char));//ÿ��tmp�ĺ�n-start��λ���б������
		strcpy(HC[i], &tmp[start]);//��tmp�ĺ�n-start��Ԫ�طָ�H[i]ָ��ĵ��ַ���
	}
}

void encode(char dd[],char ch[],HuffmanCode HC,string &aa)  //���ļ�ToBeTran�е����Ľ��б��룬Ȼ�󽫽�������ļ�CodeFile��
{
	int i;
	for (int k = 0; dd[k]!=NULL; k++) {
		i = 1;
		while (dd[k] != ch[i])
		{
			++i;
			
		}
		aa += HC[i];
	}
	
}


//��ӡ����������
void printHuffmanTree(HuffmanTree HT, char ch[]) {
	printf("\n");
	printf("data, weight, parent, lchild, rchild\n");
	for (int i = 1; i <= M; i++) {
		if (i > N)
		{
			printf("  -, %5d, %5d, %5d, %5d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
		}
		else {

			printf("  %c, %5d, %5d, %5d, %5d\n", ch[i], HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);

		}

	}

	printf("\n");

}
/*
void printHelp(HTNode &p, string ss,HTNode * as)
{
	if (p.weight==0)
		return;
	ss += " ";
	int x = p.rchild-1;
	HTNode rr = as[x];
	printHelp(rr, ss, as);	
	cout << ss << p.weight << endl;
	int y = p.lchild-1;
	printHelp(as[y], ss, as);
	
}
void printha(HTNode &root, HTNode* as) {

			string ss = " ";
			printHelp(root, ss, as);
		}
	*/	
/*
void create(bnode q,HTNode *p,HuffmanTree zz){
	if (!p) {
		q = NULL;
		return;
	}
	else
		q = new node;
	cout << &p;
	q->data = p->weight;
	p = &zz[p->lchild];
	create(q->lelem, p, zz);

	p = &zz[p->rchild];
	create(q->relem, p, zz);

 }
 */
void printHelp(bnode p, string ss, ofstream& www)
{
	if (p == NULL)
		return;
	ss += " ";
	printHelp(p->relem, ss,www);
	cout << ss << p->data << endl;
	www<<ss<< p->data << endl;
	printHelp(p->lelem, ss,www);
}
void printa(bnode root,ofstream &www) {
	string ss = " ";
	printHelp(root, ss,www);
}


int main() {
	HuffmanTree HT;
	HTNode e;
	TElemType ch[N + 1];
	int w[N + 1];
	cout << "������" << N << "���ַ������Ӧ��Ȩֵ" << endl;
	
	
	for (int i = 1; i <= N; i++) {
		cin >> ch[i];
		cin >> w[i];
	}
	createHuffmanTree(HT, w, N);

	//�������õĹ��������洢���ļ�hfmTree��
	ofstream outFile("hfmTree.dat", ios::out | ios::binary);
	for (int i = 1; i <= M; i++) {
		e = HT[i];
		outFile.write((char*)& e, sizeof(HTNode));

	}
	outFile.close();
	/*   �����Ƿ�д��ɹ�
	ifstream inFile("hfmTree.dat", ios::in | ios::binary);
	if (!inFile) {
		cout << "error" << endl;
		return 0;
	}
	while (inFile.read((char*)& s, sizeof(s))) { //һֱ�����ļ�����
			cout <<s.weight<< " " <<s.parent << " " <<s.lchild<<" "<<s.rchild<< endl;
	}
	inFile.close();
	return 0;
	*/
	ifstream ppp;
	ppp.open("ToBeTran.txt");    //��ToBeTran.txt�����ı���
	char kkk[100];
	

	char cha;
	cin.unsetf(ios::skipws);

	int r = 0;
	do
	{   
		ppp.get(cha);
		
		if (cha == ' ') {
			kkk[r] = '^';
		
		}
		else {
			kkk[r] = cha;
			
		}
		++r;
	} while (!ppp.eof());

	ppp.close();
	kkk[r-1] = NULL;
	cout << kkk << endl;
	HuffmanCode HC;
	encodingHuffmanCode(HT, HC);
	string chk;
	encode(kkk, ch, HC, chk);
	cout << chk;
	ofstream  cxk;
	cxk.open("CodeFile.txt");       //����������ļ�CodeFile��
	cxk << chk;
	cxk.close();
	char www[500];
	ifstream ttt;
	ttt.open("CodeFile.txt");   //���ļ�CodeFile�еĴ����������
	ttt >> www;
	ttt.close();
	char* testDecodingStr = www;
	int testDecodingStrLen = chk.length();
	char result[1000];//�洢�����Ժ���ַ���
	decodingHuffmanCode(HT, ch, testDecodingStr, testDecodingStrLen, result);//���루���룩��ͨ��һ�θ����ı��뷭��ɶ�Ӧ���ַ���
	ofstream  sss;
	sss.open("TextFile.txt");   //������������ļ�TextFile��
	sss << result;
	sss.close();

	//���ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�ÿ��50�����롣
	//ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin�С�
	char daying[1000];
	ifstream print;
	print.open("CodeFile.txt");
	ofstream tofile;
	tofile.open("CodePrin.txt");
	print >> daying;
	int p = 0;
	for (int i = 0; ; i++) {
		if (daying[i] == NULL)  break;
		cout << daying[i];
		tofile << daying[i];
		++p;
		if (p % 50 == 0)
		{
			cout << endl;
			tofile << endl;
		}
	}
	//����������ֱ�۵ش�ӡ����д���ļ�TreePrint��
	printHuffmanTree(HT, ch);
	/*	bnode jiayou=NULL ;
		for(int i=0;i<=M;i++)
		cout<<&HT[i]<<endl;
		HTNode *chong =&HT[M];
		cout << &chong;
		create(jiayou, chong, HT);
		printa(jiayou);
		*/
	for (int i = 1; i <= M; i++) {
		ai[i].data = HT[i].weight;
		if (HT[i].lchild == 0) {
			ai[i].lelem = NULL;
		}

		if (HT[i].lchild != 0) {
			int t;
			t = HT[i].lchild;
			ai[i].lelem = &ai[t];
		}
		if (HT[i].rchild == 0) {
			ai[i].relem = NULL;
		}
		if (HT[i].rchild != 0) {
			int t;
			t = HT[i].rchild;
			ai[i].relem = &ai[t];
		}

	}
	//for (int i = 1; i <= M; i++) {
	//	cout << &ai[i] << endl;
	
	bnode root = &ai[M];
	ofstream lalala;
	lalala.open("TreePrint.txt");
	printa(root,lalala);
	/*cout << &ai[M] << endl;
	cout << &(*root->relem) << endl;
	cout << root->relem << endl;
	cout << &(root->relem)<<endl;//  ͨ����һ�β������ڷ�������
	bnode kk = root->relem;   // ԭ����ָ�����⻹�ǲ���λ

	cout << kk->data;//*/  
	
	return 0;
}
