// maze.cpp
// ʵ���˶�ջ��һЩ��������
// Ҳʵ�����Թ���·��Ѱ�Һʹ��
#include <stdio.h>
#include "maze.h"

extern int maze[MAXLEN][MAXLEN];
extern item move[4];
// ��̬����һ����̬��ջ
SeqStack *InitSeqStack()
{
	SeqStack *s;
	s=new SeqStack;
	s->top=-1;
	return s;
}
// ������ջ
int Push(SeqStack *s,dataType x)
{
	if(s->top==MAXLEN-1)
		return 0;
	else
	{
		s->top++;
		s->data[s->top]=x;
		return 1;
	}
}
// �ж϶�ջ�Ƿ�û������
int StackEmpty(SeqStack *s)
{
	if(s->top==-1)
		return 1;
	else
		return 0;
}
// �������ݳ�ջ
int Pop(SeqStack *s,dataType *x)
{
	if(StackEmpty(s))
		return 0;
	else
	{
		*x=s->data[s->top];
		s->top--;
		return 1;
	}
}
// ��ӡ���Թ�����
void printS1(int x,int y)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
			printf("%3d",maze[i][j]);
		printf("\n");
	}
}
// ��ջ�д洢���Թ�����
void printS2(SeqStack *s)
{
	int i = 0;
	printf("�ǵݹ��㷨���Թ�·��Ϊ:\n");
	for(;i<s->top;i++)
	{
		printf("(%d,%d,%d)->",s->data[i].x,s->data[i].y,s->data[i].d);
	}
	printf("(%d,%d,%d)->",s->data[i].x,s->data[i].y,s->data[i].d);
}
// �ǵݹ���Թ�·��Ѱ��
int findPath(int maze[MAXLEN][MAXLEN],item move[4],item begin,item end )
{
	
	SeqStack *s=InitSeqStack();
	dataType temp;
	int x,y,d,i,j;
	
	temp.x=1;
	temp.y=1;
	temp.d=-1;
	Push(s,temp);
	
	while(!StackEmpty(s))
	{
		Pop(s,&temp);
		x=temp.x;
		y=temp.y;
		d=temp.d+1;
		while(d<4)
		{
			i=x+move[d].x;
			j=y+move[d].y;
			if(maze[i][j]==0)
			{
				temp.x=x;
				temp.y=y;
				temp.d=d;
				Push(s,temp);
				x=i;
				y=j;
				maze[x][y]=-1;
				if(x==end.x&&y==end.y)
				{
					printS2(s);
					printf("\n");
					return 1;
				}
				else
					d=0;
			}
			else
				d++;
		}
	}
return 0;	
}
// �ݹ���Թ�·��Ѱ��
int mazePath(int maze[MAXLEN][MAXLEN], item move[4], int x1, int y1, item end) 
{ 
int k,g,h; 
for (k = 0; k < 4; k++)
{ 
	g = x1 + move[k].x; 
	h = y1 + move[k].y; 
	if (g==end.x&&h==end.y)//&&maze[g][h]==0) 
	{ 
		printf("�ݹ��㷨���Թ���·��Ϊ:");
		printf("\n"); 
		printf("(%d,%d) <- ",end.x,end.y); 
		printf("(%d,%d,%d) <- ",x1,y1,k); 
		return 1; 
	} 
	if(maze[g][h] == 0) 
	{ 
		maze[g][h] = -1; 
		mazePath(maze, move, g, h, end);
		
			printf("(%d,%d,%d) <- ",x1,y1,k); 
			return 1;
		}
	}
return 0; 
}/*
int mazePath(int maze[MAXLEN][MAXLEN],item move[4],int x,int y,item end)
{
	if(maze[x][y]==0)
	{
		if(x==end.x&&y==end.y)
		{
			printf("(%d,%d) <--",x,y);
			return 1;
		}
		else if(mazePath(maze,move,x+move[0].x,y+move[0].y,end)==1)
		{
			printf("(%d,%d,0) <--",x,y);
			return 1;
		}
		else if(mazePath(maze,move,x+move[1].x,y+move[1].y,end)==1)
		{
			printf("(%d,%d,1) <--",x,y);
			return 1;
		}
		else if(mazePath(maze,move,x+move[2].x,y+move[2].y,end)==1)
		{

			printf("(%d,%d,2) <--",x,y);
			return 1;
		}
		else if(mazePath(maze,move,x+move[3].x,y+move[3].y,end)==1)
		{
			printf("(%d,%d,3) <--",x,y);
			return 1;
		}
	}
	return 0;
}*/
// ʹ�Թ������ݻָ�Ϊ����ʱ��ԭ����
void Restore(int maze[MAXLEN][MAXLEN],int m,int n)
{
	int i,j;
	for(i=1;i<m-1;i++)
		for(j=1;j<n-1;j++)
		{
			if(maze[i][j]==-1)
				maze[i][j]=0;
		}
}