#include<iostream>
#include<queue>
using namespace std;
int c = 0;
#define MAX_SIZE 20
typedef struct ArcNode {
	int  adjvex;      //ָ��Ľṹ
	struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode {  //����ṹ
	char data;
	ArcNode* firstarc;
}VNode,AdjList[MAX_SIZE];

typedef enum {FALSE,TRUE} Boolean;
Boolean visited[MAX_SIZE];
Boolean bvisited[MAX_SIZE];

typedef struct {
	AdjList vertics;
	int vexnum, arcnum; //������,����
}ALGraph;

int bianji1[MAX_SIZE];    //�����������¼���ʵ�˳�����ڱ߼����ռ���ӡ
int bianji2[MAX_SIZE];
void CreateGraph(ALGraph* G) {
	int i, j, k;
	ArcNode* s;
	cout<<"�����붥�����ͱ��� �ԣ�������������)����"<<endl;
	cin >>G->vexnum;
	cin>>G->arcnum;
	cout << "�����붥����Ϣ"<<endl;
	for (i = 0; i < G->vexnum; i++) {
		cout << i << " ";
		cin >> G->vertics[i].data;
		G->vertics[i].firstarc = NULL;

	}
	cout << "������ߵ���Ϣ/n"<<endl;
	for (k = 0; k < G->arcnum; k++){
		cin >>i>>j;
		s = new ArcNode;
		s->adjvex = j;
		s->nextarc = G->vertics[i].firstarc;
		G->vertics[i].firstarc = s;
		s = new ArcNode;
		s->adjvex = i;
		s->nextarc = G->vertics[j].firstarc;
		G->vertics[j].firstarc = s;
		//��������ͼ���ڽӱ���
	}
}
		
void DFS(ALGraph *G,int n, int qe[MAX_SIZE]){
	cout << "��ǰ�õ��� "<< G->vertics[n].data << endl;
	
	qe[c] = n;
	c++;
	visited[n] = TRUE;
	ArcNode* p;
	p = G->vertics[n].firstarc;
	
	while (p) {
		if (!visited[p->adjvex])    //��δ�����ʣ��ݹ����
			DFS(G, p->adjvex,qe);    
		p = p->nextarc;          //�ѷ��ʹ����޿ɼ�����ȱ���ʱ��ָ������ļ���
		
	}

}

void DFStraver(ALGraph* G, int n, int qe[MAX_SIZE]) {
	int i = 0;
	for (; i < G->vexnum; i++) {
		visited[i] = FALSE;
	}
	for (i = n; i < G->vexnum; i++) {
		if (!visited[i]) {
			DFS(G, i,qe);
		}
		//cout << "��ǰ�õ���" << G->vertics[i].data<<endl;
		//visited[i] = TRUE;
	}
	for (i = 0; i < n; i++) {
		if (!visited[i]) {
			cout << visited[i];
			DFS(G, i,qe);
		}
	}
}

void BFS(ALGraph* G, int n,int qe[MAX_SIZE]) {
	int i = 0;
	int temp;
	queue<int> mkmk;
	mkmk.push(n);
	char shuchu;
	ArcNode* pp;
	int cc = 0;
	while (!mkmk.empty()) {
		temp = mkmk.front();
		mkmk.pop();

		cout << "��ǰ���ʵ��� " << G->vertics[temp].data << endl;
		qe[cc] = temp;
		//cout << qe[cc]<<" ";
		++cc;
		bvisited[temp] = TRUE;

		pp = G->vertics[temp].firstarc;
		while (pp) {
			if (bvisited[pp->adjvex] == FALSE) {
				mkmk.push(pp->adjvex);
				bvisited[pp->adjvex] = TRUE;
			}
			pp = pp->nextarc;
		}

	}

}


//	pp = G->vertics[n-1].firstarc;  ��ϴ�����д��ʱ��������
	//k.push(G->vertics[n-1].data);
	//while (!k.empty()) {
	//	shuchu = k.front();
	//	k.pop();
/*		cout << "��ǰ�õ���" << shuchu << endl;
		if (pp||zhuixia) {
			if (visited[pp->adjvex] == TRUE) {
				zhuixia = G->vertics[pp->adjvex].firstarc;
				if (zhuixia&&visited[zhuixia->adjvex]==FALSE) {
					
				}
				pp = pp->nextarc;
			}
			else {
				we = G->vertics[pp->adjvex].data;
				visited[pp->adjvex] = TRUE;
				k.push(we);
				pp = pp->nextarc;
			}
		}
	}*/


void BFStraver(ALGraph* G, int n,int qe[MAX_SIZE]) {
	int d;
	for (int t = 0; t < G->vexnum; t++) {
		bvisited[t] == FALSE;
	}
	for ( d = n; d < G->vexnum; d++) {
		if(bvisited[d]==FALSE)
		BFS(G, d,qe);
	}
	for (int i = 0; i < n; i++) {
		if (bvisited[i] == FALSE)
		BFS(G, i,qe);
	}
}
void outputb(int qe[MAX_SIZE]) {        //��ӡ�������ı߼�
	int z = 0;
	int kao = 0;
	int s;
	bool zero=FALSE;   //�����������С�0����Ҫ����һ��׷���жϣ�����Int���������һ��ҲΪ0�����ͻ�ж�
	cout << "�����������ı߼�����" << endl;
	for (;qe[z+1]!=NULL||qe[z+2]!=NULL; z++) {
		if (qe[z] == 0&&qe[z+1]!=NULL) {
			zero = TRUE;
		}
		cout << qe[z] << " " << qe[z + 1]<<endl;
	}
	//cout << z;
	if(zero==FALSE)
		cout << qe[z] << " " << qe[z+1] << endl;
}
int main() {
	int u;
	ALGraph G;
	CreateGraph(&G);
	cout << "��ѡ����� (�����±꣩" << endl;
	cin >> u;
	cout << "��ȱ�������" << endl;
	DFStraver(&G,u,bianji1);
	cout << endl;
	outputb(bianji1);
	cout << "��ȱ�������" << endl;
	BFStraver(&G, u,bianji2);
	cout << endl;
	outputb(bianji2);


}