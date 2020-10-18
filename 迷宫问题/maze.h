// maze.h
#ifndef MAZE_H
#define MAZE_H
// ��������ֵ
#define MAXLEN 100
// ����
typedef struct
{
	int x;		
	int y;
}item;
// �Թ�·��������Ϣ
typedef struct
{
	int x;		// x����
	int y;		// y����
	int d;		// Ҫ�ߵķ���
}dataType;
// ��̬��ջ
typedef struct
{
	dataType data[MAXLEN];
	int top;
}SeqStack;


// ���õ��ĺ���ͷ

// ��̬����һ����̬��ջ
SeqStack *InitSeqStack();
// ������ջ
int Push(SeqStack *s,dataType x);
// �ж϶�ջ�Ƿ�û������
int StackEmpty(SeqStack *s);
// �������ݳ�ջ
int Pop(SeqStack *s,dataType *x);
// ��ӡ���Թ�����
void printS1(int x,int y);
// ��ջ�д洢���Թ�����
void printS2(SeqStack *s);
// �ǵݹ���Թ�·��Ѱ��
int findPath(int maze[MAXLEN][MAXLEN],item move[4],item begin,item end );
// �ݹ���Թ�·��Ѱ��
int mazePath(int maze[MAXLEN][MAXLEN], item move[4], int x1, int y1,item end) ;
// ʹ�Թ������ݻָ�Ϊ����ʱ��ԭ����
void Restore(int maze[MAXLEN][MAXLEN],int m,int n);



#endif // MAZE_H