#include<stdio.h>
#include<stdlib.h>
#include "maze.h"

// ȫ�ֱ���
int maze[MAXLEN][MAXLEN];		// ���ڴ洢һ���Թ���0���ߣ�1Ϊ�ϰ�
item move[4]={{0,1},{1,0},{0,-1},{-1,0}};	// ����ڵ�ǰ·������ϵ��ĸ�����ǰ �� �� ��

// ������
void main()
{
	item begin,end;
	int i,j, x, y;
	
	// �����Թ��ĳߴ�
	printf("�������Թ�������:");
	scanf("%d",&x);
	printf("�������Թ�������:");
	scanf("%d",&y);
	printf("\n");
	
	// �������
	begin.x=1;
	begin.y=1;
	// �յ�����
	end.x=x;
	end.y=y;
	// ¼��x*y���Թ����ݾ���
	for(i=1;i<=x;i++)
		for(j=1;j<=y;j++)
			scanf("%d",&maze[i][j]);
	// ���ҵ�ǽ�ڣ�10��ʾǽ
	for(i=0;i<x+2;i++)
	{
		maze[0][i]=10;		// ��
		maze[x+1][i]=10;	// ��
	}
	// ���µ�ǽ��
	for(j=0;j<y+2;j++)
	{
		maze[j][0]=10;		// ��
		maze[j][y+1]=10;	// ��
	}

	// ����Թ�����10Ϊ���ܵ�ǽ��0Ϊ���ߣ�1Ϊ�����ߵ��ϰ�
	printf("�������Թ��ṹ����:\n");
	printS1(x+2,y+2);
	  
	// �ݹ��·��������·���ڵݹ�������Ѵ��
	if(mazePath(maze, move, begin.x, begin.y, end)==0)
		printf("���Թ�û��ͨ·!\n");
	// �ָ��Թ�������
	Restore(maze,x,y);
	printf("\n");
	/*
	// �ǵݹ��·������
	if(findPath(maze,move,begin,end)==1)
	{
			// ��·��
			printf("�Թ�ͨ·�ķ�����ʽΪ(-1Ϊ�Թ����ߵ�·��):\n");
			printS1(x+2,y+2);
	}
	else
		printf("���Թ�û��ͨ·!\n");
	system("pause");  */
}
