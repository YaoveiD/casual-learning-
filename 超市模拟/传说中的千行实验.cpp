#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
#define show(a) cout<<#a<<endl;
#define nexline cout<<"*******************************************************"<<endl;
#define cout(node) printf("%-16s %-10d %-10d %-10.1f\n",node->good.name,node->good.id,node->good.left,node->good.price)
#define cls system("cls")
typedef struct goodnode{
    char name[30];
    int id,left,out;
    double price,sales;
}GoodType;
//������Ʒ����
typedef struct shopgood{
	char name[30];
	int id,num;
	double price, sum;
}shopgood;
typedef struct account{
    char name[30],password[30];
    int type;
}account;
account user;
//�����۳���ʱ״̬��Ʒ����
map <int,bool> have;
//��Ʒ����Ƿ���ڵ�map
int goodid;
//��Ʒ��������
typedef struct Lnode{
    GoodType good;
    Lnode *nex;
}*GoodList;
//��Ʒ����
typedef struct Snode{
	shopgood good;
	Snode *nex;
}*ShopList;
//��Ʒ������ʱ״̬������
void Init(GoodList &L)
{
	L = new Lnode;
	L->nex = NULL;
	FILE *fp = fopen("information.txt","r");
	while (1){
		GoodList node = new Lnode;
		if (fscanf(fp,"%s%d%d%d%lf%lf", &node->good.name, &node->good.id, &node->good.left, &node->good.out, &node->good.price, &node->good.sales) == EOF) break;
		node->nex = L->nex;
		L->nex = node;
		++goodid;
		have[node->good.id] = true;
		//if (fgets(s,80,fp) == NULL) break;
	}
	fclose(fp);
}
//��ʼ�����ļ��ж�����Ʒ
void WritetoFile(GoodList L)
{
	FILE *fp = fopen("information.txt","w");
	GoodList node = L->nex;
	while (node != NULL){
		fprintf(fp,"%s %d %d %d %.1f %.1f\n", node->good.name, node->good.id, node->good.left, node->good.out, node->good.price, node->good.sales);
		node = node->nex;
	}
	fclose(fp);
}
//��������������д���ļ��б���
GoodList LocateGood(GoodList L, int id)
{
	GoodList p = L->nex;
	while (p != NULL && p->good.id != id){
		p = p->nex;
	}
	return p;
}
//���ݱ�Ŷ�Ϊ�ڵ�
GoodList LocateGoodByName(GoodList L, char s[])
{
	GoodList p = L->nex;
	while (p != NULL && strcmp(s,p->good.name) != 0){
		p = p->nex;
	}
	return p;
}
//�������ֶ�λ�ڵ�
int CmpOut(const GoodType &a, const GoodType &b)
{
	return a.out > b.out;
}
int CmpSales(const GoodType &a, const GoodType &b)
{
	return a.sales > b.sales;
}
//�����������ıȽϺ���
void show_by_vector(vector<GoodType> vec)
{
    printf("��Ʒ��Ϣ����:\n");
    printf("%-16s %-10s %-10s %-10s %-10s %-10s\n", "����", "���", "�����","�۳�" ,"�۸�","���۶�");
    for (int i = 0; i < vec.size(); ++i){
        GoodType good = vec[i];
        printf("%-16s %-10d %-10d %-10d %-10.1f %-10.1f\n", good.name, good.id, good.left, good.out, good.price, good.sales);
    }
}
//��ʾ��Ʒ��Ϣ������Ϊ�ź����vector
void show_by_sales(GoodList L){
    vector<GoodType> vec;
    GoodList p = L->nex;
    while (p) {
        vec.push_back(p->good);
        p = p->nex;
    }
    sort(vec.begin(), vec.end(),CmpSales);
    show_by_vector(vec);
    vec.clear();
    vector<GoodType> ().swap(vec);
}
//�������۶���ʾ
void show_by_out(GoodList L)
{
    vector<GoodType> vec;
    GoodList p = L->nex;
    while (p) {
        vec.push_back(p->good);
        p = p->nex;
    }
    sort(vec.begin(), vec.end(),CmpOut);
    show_by_vector(vec);
    vec.clear();
    vector<GoodType> ().swap(vec);
}
//������������ʾ
string gettime()
{
	time_t rawtime;
    struct tm * timeinfo;
    char buffer [128];

    time (&rawtime);
    //printf("%ld\n", rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", timeinfo);
    return buffer;
}
//��ȡʱ��
void showtime()
{
	string T = gettime();
	cout<<T<<endl;
}
void Writetorecord(string op)
{
    FILE *fr = fopen("record.txt", "a");
    fprintf(fr, "%s: ����Ա��%s ʱ�䣺%s\n", op.c_str(), user.name, gettime().c_str());
    fclose(fr);
}
//��ʾʱ��
inline void showoutline()
{
	printf("%-16s %-10s %-10s %-10s\n", "����", "���", "�����", "�۸�");
}
//��Ȩ����ʾ
void show_all(GoodList L)
{
    printf("��Ʒ��Ϣ����:\n");
    printf("%-16s %-10s %-10s %-10s %-10s %-10s\n", "����", "���", "�����","�۳�" ,"�۸�","���۶�");
    GoodList node = L->nex;
    while (node){
        printf("%-16s %-10d %-10d %-10d %-10.1f %-10.1f\n",node->good.name,node->good.id,node->good.left,node->good.out,node->good.price,node->good.sales);
        node = node ->nex;
    }
}
//��Ȩ����Ʒ��Ϣ��ʾ
void show_one(GoodList node)
{
    printf("��Ʒ��Ϣ����:\n");
    printf("%-16s %-10s %-10s %-10s %-10s %-10s\n", "����", "���", "�����","�۳�" ,"�۸�","���۶�");
    printf("%-16s %-10d %-10d %-10d %-10.1f %-10.1f\n",node->good.name,node->good.id,node->good.left,node->good.out,node->good.price,node->good.sales);
}
//��Ȩ����ʾһ����Ʒ����Ϣ
void show2(GoodList L)
{
	show(��Ʒ��Ϣ���£�)
	showoutline();
	GoodList p = L->nex;
	while (p != NULL){
		cout(p);
		p = p->nex;
	}
}
//��Ȩ����ʾ������Ʒ����Ϣ
void show1(GoodList &L)
{
	ShopList Head = new Snode;
	Head->nex = NULL;
	show2(L);
	double tot = 0;
	while (true){
		printf("������Ʒ��� (���� 0 ����): \n");
		int id,num,newleft;
		GoodList p;
		cin >> id;
		if (id == 0){//����
			printf("�ܼ� ����%.1f �����տ���: \n",tot);
			double getmoney;
			putmoney: cin >> getmoney;
			if (getmoney < tot){
				printf("���� ����������\n");
				goto putmoney;
			}
			FILE *fp = fopen("bill.txt","w");
			printf("------------------------------------------------------\n");
			fprintf(fp,"%s","------------------------------------------------------\n");
			fprintf(fp,"%-16s %-10s %-10s %-10s\n","��Ʒ����", "����", "����", "�ܼ�");
			printf("%-16s %-10s %-10s %-10s\n","��Ʒ����", "����", "����", "�ܼ�");
			ShopList p = Head->nex;
			//���˳ɹ�������޸����ݣ���������head ��ͷ�������������
			while (p != NULL){
				GoodList cur = LocateGood(L, p->good.id);
				cur->good.left -= p->good.num;
				cur->good.out += p->good.num;
				cur->good.sales += p->good.sum;
				printf("%-16s %-10.1f %-10d %-10.1f\n",p->good.name,p->good.price,p->good.num,p->good.sum);
				fprintf(fp, "%-16s %-10.1f %-10d %-10.1f\n",p->good.name,p->good.price,p->good.num,p->good.sum);
				p = p->nex;
			}
			printf("Ӧ��: ����%10.1f\n", tot);
			printf("ʵ��: ����%10.1f   ����: ����%10.1f\n", getmoney, getmoney - tot);
			printf("------------------------------------------------------\n");
			showtime();
			printf("����Ա: %s\n", user.name);
			printf("------------------------------------------------------\n");
			fprintf(fp, "Ӧ��: ����%10.1f\n", tot);
			fprintf(fp, "ʵ��: ����%10.1f   ����: ����%10.1f\n", getmoney, getmoney - tot);
			fprintf(fp, "%s", "------------------------------------------------------\n");
			fprintf(fp, "%s\n", gettime().c_str());
			fprintf(fp, "����Ա: %s\n", user.name);
			fprintf(fp, "%s", "------------------------------------------------------\n");
			fclose(fp);
			Writetorecord("���ۼ�¼");
			while (Head->nex != NULL){
				ShopList tmp = Head->nex;
				Head->nex = Head->nex->nex;
				delete tmp;
			}
			//�������������ʱ����Ŀռ��ͷ�
	//		WritetoFile(L);
			break;
		}
		if ( (p = LocateGood(L,id))== NULL){
			printf("����Ʒ��ϢΪ��\n");
			continue;
		}
		showoutline();
		cout(p);
		//��ʾ�����Ʒ
		printf("���빺������:\n");
		cin >> num;
		if (num <=0 ){
			printf("��������С���㣬���ִ���\n");
			continue;
		}
		newleft = p->good.left - num;
		if (newleft < 0){
			printf("��������㣬���ִ���\n");
			continue;
		}
		ShopList q = new Snode;
		q->good.id = p->good.id;
		strcpy(q->good.name, p->good.name);
		q->good.price = p->good.price;
		q->good.num = num;
		q->good.sum = q->good.price*num;
		tot += q->good.sum;
		q->nex = Head->nex;
		Head->nex = q;
		//���¹�����Ϣ���Խ��д�ӡ����
	}
}
void show3(GoodList &L)
{
	show2(L);
	int id;
	while (true){
		printf("�� 1 ��� �� �� 0 �˳�\n");
		char op;
		cin >> op;
		cls;
		if (op != '1') nexline;
		if (op == '0') break;
		else if (op != '1'){
			show(�밴��ʾ����);
			continue;
		}
		show(�����������Ʒ����Ϣ��ʽ���£�)
		printf("%-16s %-10s %-10s %-10s\n", "����", "���", "�����", "�۸�");
		printf("���磺\n%-16s %-10d %-10d %-10.1f\n", "�ù�֭", 1, 100, 5.0);
		GoodList node = new Lnode;
		scanf("%s%d%d%lf", &node->good.name, &node->good.id, &node->good.left, &node->good.price);
		if (have.count(node->good.id)){
			show(�Ѿ��иñ�ţ�����������)
			continue;
		}
		if (node->good.id < 0){
			show(���С���㣬����������)
			continue;
		}
		node->good.out = node->good.sales = 0;
		node->nex = L->nex;
		L->nex = node;
		have[node->good.id] = true;
		++goodid;
		printf("��ӳɹ�\n");
		Writetorecord("��Ӽ�¼");
	}
}
void show4(GoodList &L)
{
	int id;
	while (true){
        show2(L);
		show(������Ʒ���ɾ�� (�� 0 �˳�));
		cin >> id;
		cls;
		if (id == 0) break;
		if (!have.count(id)){
			show(�����ڸ���Ʒ������������);
			continue;
		}
		GoodList p = L;
		while (p ->nex != NULL && p->nex->good.id != id){
			p = p->nex;
		}
		p->nex = p->nex->nex;
		p = p->nex;
		--goodid;
		have.erase(id);
		printf("ɾ���ɹ�\n");
		Writetorecord("ɾ����¼");
	}
}
void show5(GoodList &L)
{
	show2(L);
	int id;
	while (true){
		show(������Ʒ��Ž����޸� (�� 0 �˳�));
		cin >> id;
		cls;
		if (id == 0) break;
		if (!have.count(id)){
			show(�����ڸ���Ʒ������������);
			continue;
		}
		GoodList tmp = LocateGood(L,id);
		showoutline();
		cout(tmp);
		show(1: �޸�����)
		show(2: �޸ļ۸�)
		show(3: �޸Ŀ��)
		char op;
		cin >> op;
		cls;
		switch (op){
			case '1' :
				show(������ĺ������)
				char ChangedName[20];
				scanf("%s", ChangedName);
				strcpy(tmp->good.name, ChangedName);
				show(���ĳɹ�)
				Writetorecord("���Ƹ��ļ�¼\n");
				break;
			case '2' :
				show(������ĺ�ļ۸�)
				double ChangedPrice;
				cin >> ChangedPrice;
				if (ChangedPrice < 0){
					show(�۸���С�� 0������������)
					continue;
				}
				tmp->good.price = ChangedPrice;
				show(���ĳɹ�)
				Writetorecord("�۸���ļ�¼");
				break;
			case '3' :
				show(������ĺ�Ŀ��)
				int ChangedLeft;
				cin >> ChangedLeft;
				if (ChangedPrice < 0){
					show(��治��С�� 0������������);
					continue;
				}
				tmp->good.left = ChangedLeft;
				show(���ĳɹ�)
				Writetorecord("�����ļ�¼");
				break;
			default :
				printf("û�иò�����\n");
		}
	}
}
void show6(GoodList L)
{
    GoodList node;

    while (true){
        nexline;
        printf("���� 1 �����Ƽ�����Ʒ��Ϣ \n���� 2 ����ż�����Ʒ��Ϣ\n���� 3 ��ʾ������Ʒ��Ϣ\n");
        printf("���� 4 �����۶����ʾ��Ʒ��Ϣ\n���� 5 ��������������ʾ��Ʒ��Ϣ\n���� 0 �˳�\n");
        printf("���������:\n");
        char op;
        cin >> op;
        cls;
        if (op == '0') break;
        if (1 <= op && op <=5) {
            Writetorecord("���ݷ�����¼");
        }
        switch (op){
            case '1':
                printf("������Ʒ����:\n");
                char s[105];
                scanf("%s",s);
                node = LocateGoodByName(L,s);
                if (node == NULL){
                    printf("û�и���Ʒ\n");
                    continue;
                }
                show_one(node);
                break;
            case '2':
                printf("������Ʒ���:\n");
                int idx;
                cin >> idx;
                node = LocateGood(L,idx);
                if (node == NULL){
                    printf("û�и���Ʒ\n");
                    continue;
                }
                show_one(node);
                break;
            case '3':
                show_all(L);
                break;
            case '4':
                show_by_sales(L);
                break;
            case '5':
                show_by_out(L);
                break;
            default :
                printf("����ȷ�������\n");
        }
    }

}
void show0_1(GoodList &L)
{
    while (true) {
        show(-------\t�����б�-------)
        show(\t1: ��������)
        show(\t2: �˳���½)
        show(�����빦��:)
        int op;
        cin >> op;
        cls;
        if (op == 1) {
            show1(L);
        }
        else if (op == 2) {
            printf("�˳��ɹ�\n");
            break;
        }
        else {
            printf("������ȷ������|��O��|�� �~~\n");
        }
        WritetoFile(L);
    }
}
void show0_2(GoodList &L)
{   while (true) {
        show(-------\t�����б�-------)
        show(\t1: ��ѯ��Ʒ)
        show(\t2: �����Ʒ)
        show(\t3: ɾ����Ʒ)
        show(\t4: �޸���Ʒ)
        show(\t5: �˳���½)
        show(�������)
        int op;
        cin >> op;
        cls;
        switch (op) {
            case 1:
                show2(L);
                break;
            case 2:
                show3(L);
                break;
            case 3:
                show4(L);
                break;
            case 4:
                show5(L);
                break;
            case 5:
                return;
            default:
                show(��ȷ���������|��O��|�� �~~)
        }
        WritetoFile(L);
    }

}
void show0_3(GoodList &L)
{   in_show0_3:
    show(-------\t�����б�-------)
    show(\t1: ���۷���)
    show(\t2: �˳���½)
    show(�������)
    int op;
    cin >> op;
    cls;
    if (op == 1){
        show6(L);
    }
    else if (op == 2) {
        return;
    }
    else {
        show(�ú����룬��Ȼû����κù�֭��)
        goto in_show0_3;
    }
}
int CheckId(FILE *fp, account it,int &findname)
{
    rewind(fp);
    account *cmp = new account;
    while (fread(cmp, sizeof(account), 1, fp)) {
        if (strcmp(cmp->name, it.name) == 0) {
            findname = 1;
            if (strcmp(cmp->password, it.password) == 0) {
                user = *cmp;
                return cmp->type;
            }
        }
    }
    return 0;
}
void IdRegister()
{
    FILE *fp = fopen("User.dat","a+");
    if (fp == NULL) {
        printf("file can't be opened\n");
        exit(0);
    }
    account newid, *cmp = new account;
    reg:
    printf("1: ��������Ա\n");
    printf("2: �������Ա\n");
    printf("3: ���۷���Ա\n");
    printf("ѡ��ע������:\n");
    char s[105];
    scanf("%s", s);
    int len = strlen(s);
    if (len != 1 || s[0] < '0' || s[0] > '9'){
        printf("��������\n");
        goto reg;
    }
    newid.type = s[0] - '0';
    cls;
	printf("�����û���:\n");
	scanf("%s", newid.name);
    while (fread(cmp, sizeof(account), 1, fp)) {
        if (strcmp(cmp->name, newid.name) == 0){
            printf("���û����ѱ�ע��\n");
            fclose(fp);
            return;
        }
    }
    reset :printf("��������\n");
    char tmp[30];
    scanf("%s", tmp);
    printf("������ȷ������\n");
    scanf("%s", newid.password);
    if (strcmp(newid.password, tmp) != 0) {
        printf("�������벻һ������������������\n");
        cls;
        goto reset;
    }
    cls;
    FILE *fr = fopen("record.txt", "a");
    fprintf(fr, "ע��: %s %s\n", newid.name, gettime().c_str());
    fclose(fr);
    printf("ע��ɹ�\n");
    cmp = &newid;
    fwrite(cmp, sizeof(account), 1, fp);
    fclose(fp);
    return;
}
int login()
{
    int res;
    FILE *fp = fopen("User.dat", "r");
    account tmp;
    printf("\t��װ�Ǹ���½����:\n");
    printf("�����û���:\n");
    scanf("%s", tmp.name);
    putpassword:
    printf("��������:\n");
    int idx = 0, idxs = 0;
    //scanf("%s", tmp.password);
    while (idx < 30) {
    	char ch = _getch();
    	if (ch == '\r') {
    		break;
    	}
        if (ch == '\b') {
        	if (idx > 0) --idx;
        	printf("\b \b");
        	//�˻�һ���ÿո񸲸�ǰһ��������˻ص��ո�λ��׼��������һ������ 
        }
        else{
        	tmp.password[idx++] = ch;
        	printf("*");	
        }
    }
    tmp.password[idx] = 0;
    int findname = 0;
    if (res = CheckId(fp,tmp,findname)) {
        return res;
    }
    else {
        if (findname) {
            printf("\n�������, ����������\n");
            goto putpassword;
        }
        else {
            printf("\n���û���������\n");
        }
    }
    return 0;
}
void Log(int &check)
{
    check = 0;
    //Logselect:
	printf("**********************\n");
	printf("1: ��¼\n");
	printf("2: ע��\n");
	printf("3: �˳�\n");
	printf("**********************\n");
    int op;
    cin >> op;
    cls;
    if (op == 1){
        check = login();
       // printf("login: check = %d\n",check);
    }
    else if (op == 2){
        IdRegister();
    }
    else {
        check = -1;
    }
    return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	GoodList GoodHead;
	Init(GoodHead);
	int check = 0;
	while (check != -1) {
        Log(check);
        //cout << "check = " << check << endl;
        if (check > 0) {
            FILE *fp = fopen("record.txt", "a");
            fprintf(fp, "��½: %s %s\n", user.name, gettime().c_str());
            fclose(fp);
            cls;
            printf("��½�ɹ�\n");
        }
        switch (check) {
            case 1:
                show0_1(GoodHead);
                break;
            case 2:
                show0_2(GoodHead);
                break;
            case 3:
                show0_3(GoodHead);
                break;
        }
        if(0 <check && check < 4) {
            Writetorecord("�˳���½");
            WritetoFile(GoodHead);
        }
	}
    return 0;
}
