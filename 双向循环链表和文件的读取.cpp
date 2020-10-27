//链表和文件的读取
//从文件中读取学生信息，并赋给链表
/*错误总结
①忘记给结构体动态分配内存 
②读取文件后，没有用printf输出 
③fread是读取二进制文件
④*&不能乱用 
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
	STUDENT stu; //不需要分配动态内存 
	
	//从文本文件中读取学生信息到双向循环链表中 
	ReadStuMsg((char*)"Student_Info", L); //从文件中读取学生信息到pstu所指向的内存块中
	
	//显示排序前的学生信息
	printf("学生信息：\n"); 
	ShowStuMsg(L);  
	
	//对学生成绩进行快速排序（从高到低，如果成绩相同，则时间少的在前） 
	s = L->next;
	t = L->prior;
	QSort(s, t); 
	
	//显示学生信息 
	printf("按成绩从高到低排序：\n");
	ShowStuMsg(L); 
	/* 
	//增加学生信息
	printf("是否需要添加学生信息？(1-添加，0-不添加)\n");
	scanf("%d", &judge);
    while(judge){
        printf("Please input the student's information:(including number, name, score and time)\n");
		scanf("%s, %s, %d, %d", &stu.no, &stu.name, &stu.score, &stu.time);
		InsertDuLinkList(L, stu);
		printf("是否还需要添加学生信息？(1-添加，0-不添加)\n");
	    scanf("%d", &judge);
	}//while 
	
	//对学生成绩进行快速排序（从高到低，如果成绩相同，则时间少的在前） 
	s = L->next;
	t = L->prior;
	QSort(s, t); 
	
	//显示学生信息 
	printf("按成绩从高到低排序：\n");
	ShowStuMsg(L); 
	*/ 
	//销毁双向循环链表
	DestroyList(L); 
	
} 
//读取学生信息，并创建双向循环链表 
int ReadStuMsg(char *filename, DuLinkList &L)
{
	FILE *fp;
	InitList_DuL(L);
	DuLNode *s, *r;
	int i = 1;
	r = L;
	//打开文件 
	fp = fopen("Student_Info.txt", "rt");
	if(fp == NULL){
		printf("can't open Student_Info.txt\n");
	    exit(0);
	}//if
	//printf("%-10s%-12s%-6s%6s\n", "no", "name", "score", "time");
	//从文件中读取学生信息到pstu所指向的内存块中
	while(!feof(fp)){
		s = (DuLNode*)malloc(sizeof(DuLNode)); 
		fscanf(fp, "%7s %11s %d %d", &s->stu.no, &s->stu.name, &s->stu.score, &s->stu.time);
		s->No = i;
		i++;
		//检查程序 
		//printf("%-10s%-12s%-6d%6d\n", s->stu.no, s->stu.name, s->stu.score, s->stu.time);
		r->next = s;
		s->prior = r;
		r = s;
	}
	//形成循环链表 
	s->next = L;
	L->prior = s; 
	//关闭文件
	fclose(fp); 
	return 0;
 } //ReadFromFile
 
//在双向循环链表的末尾插入 
int InsertDuLinkList(DuLinkList &L, STUDENT stu)
{
	//提示输入学生信息（并写入到文件中，创建结点，放入学生信息） 
	FILE *fp;
	DuLNode *p;
	p = (DuLNode*) malloc (sizeof(DuLNode));   //为新创建的结点分配动态存储空间 
	//打开文件
	fp = fopen("Student_Info.txt","at");
	if(fp == NULL)
	{
		printf("can't open Student_Info.txt\n");
		exit(-1);
	 }//if 
	//输入学生信息
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
	L = (DuLNode*)malloc(sizeof(DuLNode));             //创建头结点 
	L->prior = L->next = NULL;   //前后指针域置为NULL 
	L->No = 0;
	L->stu.score = 0;
	L->stu.time = 0;
	return 0;
 } // InitList_DuL

//显示学生信息 
int ShowStuMsg(DuLinkList L)
{
	DuLNode *s = L->next;
	printf("学生序号  %-10s%-12s%-6s%6s\n", "no", "name", "score", "time");
	while(s != L){
		printf("序号%d:   %-10s%-12s%-6d%6d\n", s->No, s->stu.no, s->stu.name, s->stu.score, s->stu.time);
		s = s->next;
	}//while
	return 0;
}//ShowStuMsg
//对学生成绩进行快速排序（从高到低，如果成绩相同，则时间少的在前） 
int QSort(DuLNode *s, DuLNode *t)
{
	//对记录结点进行快速排序
	DuLNode *pivotloc;
	if(s->No < t->No){
		pivotloc = Partition(s, t);  //对a[s..t]进行一次划分，并返回枢轴位置
		QSort(s, pivotloc->prior);         //对低子序列递归排序
		QSort(pivotloc->next, t);         //对高子序列递归排序
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
		//printf("学生序号：%s, %s, %d, %d\n", s->stu.no, s->stu.name, s->stu.score, s->stu.time); 
		//printf("学生序号：%s, %s, %d, %d\n", t->stu.no, t->stu.name, t->stu.score, t->stu.time); 
		while((s->No < t->No) && (s->stu.score >= key_score)){
			if(s->stu.score == key_score && s->stu.time >= key_time)   break;
			s = s->next;
		}
		swap(s, t);
		//printf("学生序号：%s, %s, %d, %d\n", s->stu.no, s->stu.name, s->stu.score, s->stu.time); 
		//printf("学生序号：%s, %s, %d, %d\n", t->stu.no, t->stu.name, t->stu.score, t->stu.time); 
	}//while
	return s;
}
//交换结点的stu数据 
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
//销毁双向循环链表 
int DestroyList(DuLinkList &L)
{
	L->prior->next = NULL;
	DuLNode *pre = L, *p = L->next;   //pre指向结点p的前驱节点 
	while(p != NULL){                 //扫描单链表L 
		//free(pre->stu); 
		free(pre);                    //释放pre结点 
		pre = p;                      //pre、p同步后移一个结点 
		p = pre->next;
	}//while
	free(pre);                        //循环结束时p为NULL，pre指向尾结点，释放它 
}//DestroyList 












