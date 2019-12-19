#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
typedef struct AVLNode* Tree;
typedef int ElementType;
struct AVLNode
{
    int depth; //��ȣ��������ÿ��������ȣ�ͨ����ȵıȽϿɵó��Ƿ�ƽ��
    Tree parent; //�ý��ĸ��ڵ㣬�������
    ElementType val; //���ֵ   ���
    string bookname;
    string aditor;
    int xian;    //�ִ���
    int  total;   //�ܿ����
    Tree lchild;
    Tree rchild;
    AVLNode(int val = 0) //Ĭ�Ϲ��캯��
    {
        parent = NULL;
        depth = 0;
        lchild = rchild = NULL;
        this->val = val;
    }
};
typedef struct bookborrow {
    int shuhao;
    string booknames;
    struct bookborrow* next;
    long int data;
}bookborrow,*zhixiang;
typedef struct borrower {
    long int borrowNumber;
    bookborrow* xia;
}borrower,*bookjie;
Tree insert_val(Tree&, Tree, Tree);
Tree remove(Tree&, ElementType);
Tree remove_val(Tree&, Tree&);
void update_depth(Tree);
Tree AVLTree(Tree&, Tree);
Tree LL_rotate(Tree);
Tree RL_rotate(Tree);
Tree RR_rotate(Tree);
Tree LR_rotate(Tree);
int  get_balance(Tree);
int  is_balance(Tree);
Tree* Find_Min(Tree&);
//��AVL���в���val
//������������������value
//����:�¸����
Tree Insert(Tree& root, ElementType val,string a,string b, int c,int d)
{
    Tree temp = NULL;
    Tree node = new AVLNode(val);
    node->bookname = a;
    node->aditor = b;
    node->xian = c;
    node->total = d;
    //������
    temp = insert_val(root, node, NULL); //���������Ĳ��뺯��  16  ��3
    if (temp)
    {
        update_depth(temp);
        root = AVLTree(root, temp);  //������Ƿ�õ���
    }
    else //������룬�ͷŽ��
        delete temp;
    return root;
}
//���뺯��
//���������ڵ㣬�����㣬������ĸ��ڵ�
//���أ�������
Tree insert_val(Tree& root, Tree node, Tree parent)   //16����
{
    if (root == NULL)
    {
        root = node;        //������ڵ�Ϊ�գ������Ľڵ��Ϊ��
        node->parent = parent;    //���õ�ǰ���ĸ���㣬����һ�������˫��Ϊ��   16Ϊ3�ĵ�
        return root;              //���ز�����   ����3
    }
    if (node->val < root->val) //��������
        return insert_val(root->lchild, node, root);
    else if (node->val > root->val) //��������
        return insert_val(root->rchild, node, root);
    else //�Ѵ��ڸý�㣬ֹͣ�������������NULL
        return NULL;
}
//AVL����������
//����������㣬������
//���أ�������ĸ����
Tree AVLTree(Tree& root, Tree node)
{
    int balance = 0; //ƽ������
    while (node != NULL) //����������Ƿ���Ҫ����������
    {
        update_depth(node);     //���µ�ǰ���ĸ߶���Ϣ
        balance = is_balance(node);    //��ȡ��ǰ����ƽ���������
        if (balance > 1 || balance < -1) //ƽ�����ӳ���
        {
            if (balance > 1) //��������
            {
                if (is_balance(node->lchild) > 0) //LL��
                    node = LL_rotate(node);
                else  //LR��
                    node = LR_rotate(node);
            }
            else //��������
            {
                if (is_balance(node->rchild) < 0) //RR��
                    node = RR_rotate(node);
                else //RL��
                    node = RL_rotate(node);
            }
            if (node->parent == NULL) //��������
            {
                root = node; //�����µĸ����
                break; //�˳�
            }
        }
        node = node->parent; //�����ҵ��丸�ڵ�
    }
    return root; //�����¸�
}
//������С���
Tree* Find_Min(Tree& root)
{
    if (root->lchild)
    {
        return Find_Min(root->lchild);
    }
    return &root;
}
//ɾ������
//������������Ҫɾ���Ľ��
//����ֵ: ����ɾ�����ĸ��ڵ�
Tree remove_val(Tree& root, Tree& node)
{
    Tree parent = node->parent;
    Tree temp = NULL;
    //ֻ������
    if (node->rchild == NULL && node->lchild != NULL)
    {
        temp = node;
        node = node->lchild; //ָ������
        node->parent = temp->parent;
        delete temp;       //�ͷŽ��
        update_depth(node); //���µ�ǰ�����Ϣ
    }
    else if (node->lchild == NULL && node->rchild != NULL) //ֻ���Һ���
    {
        temp = node;
        node = node->rchild; //ָ���ҽ��
        node->parent = temp->parent;
        delete temp;       //�ͷŽ��
        update_depth(node); //���µ�ǰ�����Ϣ
    }
    else if (node->rchild == NULL && node->lchild == NULL) //Ҷ�ӽ��
    {
        parent = node->parent; //�ҵ��丸�ڵ�
        if (parent) //������ڵ����
        {
            delete node;
            node = NULL;
            update_depth(parent); //���¸��ڵ�߶���Ϣ
        }
        else //ɾ�����Ǹ�
        {
            delete root;
            root = NULL;
        }
    }
    else //��������Ҳ���Һ��ӣ�����Ϊ��
    {
        Tree* tmp = Find_Min(node->rchild); //�ҵ����Ԫ�أ�tempΪҶ�ӽ��
        node->val = (*tmp)->val;         //����ֵ
        //�жϵ�ǰҶ�ӽ�������ӻ����Һ��ӡ�
        parent = (*tmp)->parent;
        /*
        if (parent->lchild==temp)
        {
            parent->lchild=0;
            delete temp;
        }
        else
        {
            parent->rchild=0;
            delete temp;
        }
         */
        delete* tmp;
        *tmp = NULL;
        update_depth(parent);
    }
    return parent;
}
//�ҵ�ɾ���Ľ�㣬ִ��ɾ���������������������AVL��
//������������Ҫɾ����val
//���أ��ҵ�ɾ����������򷵻��¸������򷵻�NULL
Tree remove(Tree& root, ElementType val)
{
    static Tree* temp = NULL;
    if (root == NULL)
    {
        temp = NULL;
        return NULL;
    }
    else if (root->val < val) //������������
        remove(root->rchild, val);
    else if (root->val > val) //������������
        remove(root->lchild, val);
    else   //�ҵ��ˣ����һ��
        temp = &root;
    if (temp)
    {
        if (!root->parent) //����Ѿ����ص����һ�Σ�Ҳ����root��������������
        {
            Tree tmp = NULL;
            tmp = remove_val(root, *temp);  //ִ��ɾ������
            return AVLTree(root, tmp); //����AVL��
        }
        return *temp;
    }
    return NULL;
}
//��ȡ��ǰ�������
int get_balance(Tree node)
{
    if (node == NULL)
        return 0;
    return node->depth;
}
//���ص�ǰƽ������
int is_balance(Tree node)
{
    if (node == NULL)
        return 0;
    else
        return get_balance(node->lchild) - get_balance(node->rchild);
}
//RR�͵�������
//�����¸��ڵ�
Tree RR_rotate(Tree node)
{
    //nodeΪ�������������ʧ��Ľ��
    Tree parent = NULL, son;
    //��ȡʧ����ĸ��ڵ�
    parent = node->parent;
    //��ȡʧ������Һ���
    son = node->rchild;
    //����son������ӵĸ�ָ��
    if (son->lchild != NULL)
        son->lchild->parent = node;
    //ʧ������Һ��ӱ��Ϊson������
    node->rchild = son->lchild;
    //����ʧ����ĸ߶���Ϣ
    update_depth(node);
    //ʧ������son������
    son->lchild = node;
    //����son�ĸ����Ϊԭʧ����ĸ����
    son->parent = parent;
    //���ʧ���㲻�Ǹ���㣬��ʼ���¸��ڵ�
    if (parent != NULL)
    {
        //������ڵ��������ʧ���㣬ָ�����ڸ��º���º���son
        if (parent->lchild == node)
            parent->lchild = son;
        else //���ڵ���Һ�����ʧ����
            parent->rchild = son;
    }
    //����ʧ����ĸ���
    node->parent = son;
    //����son���ĸ߶���Ϣ
    update_depth(son);
    return son;
}
//LL�͵�������
//����:�¸��ڵ�
Tree LL_rotate(Tree node)
{
    //nodeΪ�������������ʧ��Ľ��
    Tree parent = NULL, son;
    //��ȡʧ����ĸ��ڵ�
    parent = node->parent;
    //��ȡʧ���������
    son = node->lchild;
    //����son����Һ��ӵĸ�ָ��
    if (son->rchild != NULL)
        son->rchild->parent = node;
    //ʧ��������ӱ��Ϊson���Һ���
    node->lchild = son->rchild;
    //����ʧ����ĸ߶���Ϣ
    update_depth(node);
    //ʧ������son���Һ���
    son->rchild = node;
    //����son�ĸ����Ϊԭʧ����ĸ����
    son->parent = parent;
    //���ʧ���㲻�Ǹ���㣬��ʼ���¸��ڵ�
    if (parent != NULL)
    {
        //������ڵ��������ʧ���㣬ָ�����ڸ��º���º���son
        if (parent->lchild == node)
            parent->lchild = son;
        else //���ڵ���Һ�����ʧ����
            parent->rchild = son;
    }
    //����ʧ����ĸ���
    node->parent = son;
    //����son���ĸ߶���Ϣ
    update_depth(son);
    return son;
}
//LR�ͣ�������ת��������ת
//���أ��¸��ڵ�
Tree LR_rotate(Tree node)
{
    RR_rotate(node->lchild);
    return LL_rotate(node);
}
//RL�ͣ�������ת��������ת
//����:�¸��ڵ�
Tree RL_rotate(Tree node)
{
    LL_rotate(node->rchild);
    return RR_rotate(node);
}
int max(int a, int b) {
    if (a >= b)  return a;
    else    return b;
}
//���µ�ǰ���
void update_depth(Tree node)
{
    if (node == NULL)
        return;
    else
    {
        int depth_Lchild = get_balance(node->lchild); //�������
        int depth_Rchild = get_balance(node->rchild); //�Һ������
        node->depth = max(depth_Lchild, depth_Rchild) + 1;
    }
}

//�������  ���ڲ���ƽ���������������ȷ
void InOrder(Tree root)
{
    if (root == NULL)
        return;
    InOrder(root->lchild);
   cout<<root->val<<"  "<<root->bookname<<endl;
    InOrder(root->rchild);
}
Tree find(Tree& root, int xx) {         //�����������Ĳ���
    if (root->val = xx)
        return root;
    if (root->val < xx)
         find(root->lchild, xx);
    if (root->val > xx)
         find(root->rchild, xx);
}
void aoutput(Tree& root,string kg) {      //������ӡ����ÿ���������֤
    if (root != NULL) {
        cout <<root->val << endl;
       
            if (root->lchild) {
                kg = kg + "  ";
                cout << kg<<"��:";
                aoutput(root->lchild, kg);
                if (root->rchild) {
                    cout << kg << "��:";
                    aoutput(root->rchild, kg);
                }
            }
            if (root->lchild==NULL&&root->rchild) {
                kg = kg + "  ";
                cout <<kg<< "��:";
                aoutput(root->rchild, kg);
            }
           
    }
   
}

bookjie findbro(long int temp,bookjie chaxun) {  //����ͼ��֤�Ų��ҽ����ߵ���Ϣ
    for (int j = 0; j <= 10; j++) {
       
        if (chaxun->borrowNumber != temp) {
            ++chaxun;
        }
        if (chaxun->borrowNumber == temp) {
            return chaxun;
            break;
        }
    }
    return NULL;
}
void outputbrorrowbook(bookjie dfd) {         //���Ҹý����ߵĽ�����Ϣ����ӡ����
    zhixiang sdsa;
    if(dfd->xia!= NULL) {
        cout << dfd->xia->shuhao << endl;
    }
    sdsa = dfd->xia->next;
    if (sdsa != NULL) {
        cout << sdsa->shuhao;
        sdsa = sdsa->next;
    }
}
void  reback(int xx, bookjie cv) {      //����
    zhixiang  vfvf,lll=NULL;
    vfvf = cv->xia;
    while (vfvf->shuhao != xx) {
        lll = vfvf;
        vfvf = vfvf->next;

    }
    lll->next = vfvf->next;
    free(vfvf);
}
int main()
{   
    cout << "ͼ����Ϣ����,���β���ƽ�������������" << endl;
    cout << "���   " << "����       " << "����     " << "�ֿ��   " << "�ܿ��   "<<endl;
    cout << "16     " << "JAVA����   " << "Nocdfv   " << "10       " << "10   " << endl;
    cout << "3      " << "Linux      " << "balala   " << "20       " << "20   " << endl;
    cout << "7      " << "����       " << "С��     " << "5        " << "5   " << endl;
    cout << "11     " << "��ѧ       " << "С��     " << "6        " << "6   " << endl;
    cout << "9      " << "Ӣ��       " << "С��     " << "2        " << "2   " << endl;
    cout << "26     " << "����       " << "С��     " << "1        " << "1   " << endl;
    cout << "18     " << "��ʷ       " << "С��     " << "3        " << "3   " << endl;
    cout << "14     " << "����       " << "С��     " << "4        " << "4   " << endl;
    cout << "15     " << "����       " << "koolas   " << "8        " << "8   " << endl;
    string kongge = " ";
    cout <<"����ÿ����һ����������ӡ"<< endl;
    Tree chazhao = NULL;
    Tree root = NULL;
    //�ɱ����
    root = Insert(root, 16,"JAVA����","Nocdfv",10,10);
    aoutput(root,kongge);
    cout << endl;
    root = Insert(root, 3,"Linux����ϵͳ","balala",20,20);
    aoutput(root, kongge);
    cout << endl;
    //����7��LR����
    root = Insert(root, 7, "����", "С��", 5, 5);
    aoutput(root, kongge);
    cout << endl;
    root = Insert(root, 11, "��ѧ", "С��", 6, 6);
    aoutput(root, kongge);
    cout << endl;
    //����9��LL����
    root = Insert(root, 9, "Ӣ��", "С��", 2, 2);
    aoutput(root, kongge);
    cout << endl;
    //����26��RR����
    root = Insert(root, 26, "����", "С��", 1, 1);
    aoutput(root, kongge);
    cout << endl;
    //����28��RL����
    root = Insert(root, 18, "��ʷ", "С��", 3, 3);
    aoutput(root, kongge);
    cout << endl;
    root = Insert(root, 14, "����", "С��", 4, 4);
    aoutput(root, kongge);
    cout << endl;
    //����15��LR����
    root = Insert(root, 15, "����", "koolas", 8, 8);
    aoutput(root, kongge);
    cout << endl;
    InOrder(root);
    //���Ĺ���
   
    bookjie  yi = (bookjie)malloc(10 * sizeof(borrower));     //����10�������ߵ�˳���
   
        cout << "���������Ľ���֤��" << endl;
        cin >> yi[0].borrowNumber;
        zhixiang sd = NULL;
        zhixiang sdaaa = NULL;
    for (int u = 0; u <= 10; u++) {
        
        cout << "����������������" << endl;
        int xx;
        cin >> xx;
        chazhao = find(root, xx);
        if (chazhao->xian >= 0) {
            cout << "�п�棬�ɽ���" << endl;
            zhixiang fg;
           
            fg = new bookborrow;
            fg->shuhao=chazhao->val;
            yi[0].xia = fg;
            

            yi[0].xia->next = sdaaa;             //˳����ӵ�������ʽ�洢�鼮��Ϣ
            sdaaa = yi[0].xia;
            
            //  cout << yi[0].xia->booknames << " " << yi[0].xia->shuhao;
            cout << "�����뻹������ ��20120101 ����ʽ" << endl;
            cin >> yi[0].xia->data;
            cout << "����ɹ���" << endl;
            chazhao->xian = chazhao->xian - 1;//���ĳɹ����ִ�����1
        }
        else
            cout << "��Ǹ�����޿��" << endl;

        cout << "�Ƿ��������?������������ 1 ���������� 0 " << endl;
        int vc;
        cin >> vc;
        if (vc == 0)  
            break;
    }
    cout << "�黹ͼ�����" << endl;
    cout << "��������Ľ���֤��" << endl;
    long int mm;
    cin >> mm;
    bookjie zhongzhuang;
    zhongzhuang = findbro(mm, yi);
    cout << "��ѯ�������ڳ��е����� "<< endl;
    outputbrorrowbook(zhongzhuang);
    cout << endl;
    cout << "��ѡ��Ҫ������,�������" << endl;
    int  xx;
    cin >> xx;
    cout << "�ѻ��ɹ���" << endl;
    reback(xx, yi);
    cout << "��ѯ�������ڳ��е����� " << endl;
    outputbrorrowbook(zhongzhuang);
    cout << "���������" << endl;
    cout << "��ѡ��Ҫɾ����������" << endl;
    int mop;
    cin >> mop;
    remove(root, mop);
    aoutput(root, kongge);
    cout << endl;
    cout << "��ѡ��Ҫɾ����������" << endl;
    cin >> mop;
    remove(root, mop);
    aoutput(root, kongge);
    

    return 0;
}
