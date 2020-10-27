//������ļ��Ķ�ȡ
//���ļ��ж�ȡѧ����Ϣ������������
/*�����ܽ�
�����Ǹ��ṹ�嶯̬�����ڴ� 
�ڶ�ȡ�ļ���û����printf��� 
��fread�Ƕ�ȡ�������ļ�
��*&�������� 
*/ 
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct student_info{
	char no[7];
	char name[10];
	int score;
	int time; 
}STUDENT;
typedef struct DuLNode{
	STUDENT stu;
	int No;
	struct DuLNode *next, *prior;
}DuLNode, *DuLinkList; 
int InitList_DuL(DuLinkList &L);
int ReadStuMsg(char *filename, DuLinkList &L);
int ShowStuMsg(DuLinkList L);
int QSort(DuLNode *s, DuLNode *t);
DuLNode *Partition(DuLNode *s, DuLNode *t);
int swap(DuLNode *s, DuLNode *t);
int DestroyList(DuLinkList &L);
int InsertDuLinkList(DuLinkList &L, STUDENT stu);
int main()
{
	DuLinkList L;
	DuLNode *s, *t;
	int judge;
	STUDENT stu; //����Ҫ���䶯̬�ڴ� 
	
	//���ı��ļ��ж�ȡѧ����Ϣ��˫��ѭ�������� 
	ReadStuMsg((char*)"Student_Info", L); //���ļ��ж�ȡѧ����Ϣ��pstu��ָ����ڴ����
	
	//��ʾ����ǰ��ѧ����Ϣ
	printf("ѧ����Ϣ��\n"); 
	ShowStuMsg(L);  
	
	//��ѧ���ɼ����п������򣨴Ӹߵ��ͣ�����ɼ���ͬ����ʱ���ٵ���ǰ�� 
	s = L->next;
	t = L->prior;
	QSort(s, t); 
	
	//��ʾѧ����Ϣ 
	printf("���ɼ��Ӹߵ�������\n");
	ShowStuMsg(L); 
	/* 
	//����ѧ����Ϣ
	printf("�Ƿ���Ҫ���ѧ����Ϣ��(1-��ӣ�0-�����)\n");
	scanf("%d", &judge);
    while(judge){
        printf("Please input the student's information:(including number, name, score and time)\n");
		scanf("%s, %s, %d, %d", &stu.no, &stu.name, &stu.score, &stu.time);
		InsertDuLinkList(L, stu);
		printf("�Ƿ���Ҫ���ѧ����Ϣ��(1-��ӣ�0-�����)\n");
	    scanf("%d", &judge);
	}//while 
	
	//��ѧ���ɼ����п������򣨴Ӹߵ��ͣ�����ɼ���ͬ����ʱ���ٵ���ǰ�� 
	s = L->next;
	t = L->prior;
	QSort(s, t); 
	
	//��ʾѧ����Ϣ 
	printf("���ɼ��Ӹߵ�������\n");
	ShowStuMsg(L); 
	*/ 
	//����˫��ѭ������
	DestroyList(L); 
	
} 
//��ȡѧ����Ϣ��������˫��ѭ������ 
int ReadStuMsg(char *filename, DuLinkList &L)
{
	FILE *fp;
	InitList_DuL(L);
	DuLNode *s, *r;
	int i = 1;
	r = L;
	//���ļ� 
	fp = fopen("Student_Info.txt", "rt");
	if(fp == NULL){
		printf("can't open Student_Info.txt\n");
	    exit(0);
	}//if
	//printf("%-10s%-12s%-6s%6s\n", "no", "name", "score", "time");
	//���ļ��ж�ȡѧ����Ϣ��pstu��ָ����ڴ����
	while(!feof(fp)){
		s = (DuLNode*)malloc(sizeof(DuLNode)); 
		fscanf(fp, "%7s %11s %d %d", &s->stu.no, &s->stu.name, &s->stu.score, &s->stu.time);
		s->No = i;
		i++;
		//������ 
		//printf("%-10s%-12s%-6d%6d\n", s->stu.no, s->stu.name, s->stu.score, s->stu.time);
		r->next = s;
		s->prior = r;
		r = s;
	}
	//�γ�ѭ������ 
	s->next = L;
	L->prior = s; 
	//�ر��ļ�
	fclose(fp); 
	return 0;
 } //ReadFromFile
 
//��˫��ѭ�������ĩβ���� 
int InsertDuLinkList(DuLinkList &L, STUDENT stu)
{
	//��ʾ����ѧ����Ϣ����д�뵽�ļ��У�������㣬����ѧ����Ϣ�� 
	FILE *fp;
	DuLNode *p;
	p = (DuLNode*) malloc (sizeof(DuLNode));   //Ϊ�´����Ľ����䶯̬�洢�ռ� 
	//���ļ�
	fp = fopen("Student_Info.txt","at");
	if(fp == NULL)
	{
		printf("can't open Student_Info.txt\n");
		exit(-1);
	 }//if 
	//����ѧ����Ϣ
	fprintf(fp, "%s &s %d &d", stu.no, stu.name, stu.score, stu.time);
	p->stu = stu;
	p->No = L->prior->No + 1;
	p->prior = L->prior;
	p->next = L;
	L->prior->next = p;
	L->prior = p;
	 
	return 0; 
}//InsertDuLinkList

int InitList_DuL(DuLinkList &L)
{
	L = (DuLNode*)malloc(sizeof(DuLNode));             //����ͷ��� 
	L->prior = L->next = NULL;   //ǰ��ָ������ΪNULL 
	L->No = 0;
	L->stu.score = 0;
	L->stu.time = 0;
	return 0;
 } // InitList_DuL

//��ʾѧ����Ϣ 
int ShowStuMsg(DuLinkList L)
{
	DuLNode *s = L->next;
	printf("ѧ�����  %-10s%-12s%-6s%6s\n", "no", "name", "score", "time");
	while(s != L){
		printf("���%d:   %-10s%-12s%-6d%6d\n", s->No, s->stu.no, s->stu.name, s->stu.score, s->stu.time);
		s = s->next;
	}//while
	return 0;
}//ShowStuMsg
//��ѧ���ɼ����п������򣨴Ӹߵ��ͣ�����ɼ���ͬ����ʱ���ٵ���ǰ�� 
int QSort(DuLNode *s, DuLNode *t)
{
	//�Լ�¼�����п�������
	DuLNode *pivotloc;
	if(s->No < t->No){
		pivotloc = Partition(s, t);  //��a[s..t]����һ�λ��֣�����������λ��
		QSort(s, pivotloc->prior);         //�Ե������еݹ�����
		QSort(pivotloc->next, t);         //�Ը������еݹ�����
	} //if
	return 0;
}//QSort
DuLNode *Partition(DuLNode *s, DuLNode *t)
{
	//static int i = 1;
	int key_score, key_time;
	key_score = s->stu.score;
	key_time = s->stu.time;
	printf("key_score = %d\n", key_score);
	printf("key_score = %d\n", key_score);
	while(s->No < t->No){
		//printf("%d\n", i++);
		while((s->No < t->No) && (t->stu.score <= key_score)){
			if(t->stu.score == key_score && t->stu.time <= key_time)   break;
		    t = t->prior;	
		}//while
		swap(s, t);
		//printf("ѧ����ţ�%s, %s, %d, %d\n", s->stu.no, s->stu.name, s->stu.score, s->stu.time); 
		//printf("ѧ����ţ�%s, %s, %d, %d\n", t->stu.no, t->stu.name, t->stu.score, t->stu.time); 
		while((s->No < t->No) && (s->stu.score >= key_score)){
			if(s->stu.score == key_score && s->stu.time >= key_time)   break;
			s = s->next;
		}
		swap(s, t);
		//printf("ѧ����ţ�%s, %s, %d, %d\n", s->stu.no, s->stu.name, s->stu.score, s->stu.time); 
		//printf("ѧ����ţ�%s, %s, %d, %d\n", t->stu.no, t->stu.name, t->stu.score, t->stu.time); 
	}//while
	return s;
}
//��������stu���� 
int swap(DuLNode *s, DuLNode *t)
{
	DuLNode *p;
	p = (DuLNode*) malloc (sizeof(DuLNode));
    //DuLinkList tmp = new DuLNode;
    p->stu = s->stu;
    s->stu = t->stu;
    t->stu = p->stu;

	return 0;
}
//����˫��ѭ������ 
int DestroyList(DuLinkList &L)
{
	L->prior->next = NULL;
	DuLNode *pre = L, *p = L->next;   //preָ����p��ǰ���ڵ� 
	while(p != NULL){                 //ɨ�赥����L 
		//free(pre->stu); 
		free(pre);                    //�ͷ�pre��� 
		pre = p;                      //pre��pͬ������һ����� 
		p = pre->next;
	}//while
	free(pre);                        //ѭ������ʱpΪNULL��preָ��β��㣬�ͷ��� 
}//DestroyList 












