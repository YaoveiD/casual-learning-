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
//定义商品类型
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
//定义售出暂时状态商品类型
map <int,bool> have;
//商品编号是否存在的map
int goodid;
//商品种类数量
typedef struct Lnode{
    GoodType good;
    Lnode *nex;
}*GoodList;
//商品链表
typedef struct Snode{
	shopgood good;
	Snode *nex;
}*ShopList;
//商品出售暂时状态的链表
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
//初始化从文件中读入商品
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
//将操作完后的数据写入文件中保存
GoodList LocateGood(GoodList L, int id)
{
	GoodList p = L->nex;
	while (p != NULL && p->good.id != id){
		p = p->nex;
	}
	return p;
}
//根据编号定为节点
GoodList LocateGoodByName(GoodList L, char s[])
{
	GoodList p = L->nex;
	while (p != NULL && strcmp(s,p->good.name) != 0){
		p = p->nex;
	}
	return p;
}
//根据名字定位节点
int CmpOut(const GoodType &a, const GoodType &b)
{
	return a.out > b.out;
}
int CmpSales(const GoodType &a, const GoodType &b)
{
	return a.sales > b.sales;
}
//根据销售量的比较函数
void show_by_vector(vector<GoodType> vec)
{
    printf("商品信息如下:\n");
    printf("%-16s %-10s %-10s %-10s %-10s %-10s\n", "名称", "编号", "库存量","售出" ,"价格","销售额");
    for (int i = 0; i < vec.size(); ++i){
        GoodType good = vec[i];
        printf("%-16s %-10d %-10d %-10d %-10.1f %-10.1f\n", good.name, good.id, good.left, good.out, good.price, good.sales);
    }
}
//显示商品信息，参数为排好序的vector
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
//根据销售额显示
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
//根据销售量显示
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
//获取时间
void showtime()
{
	string T = gettime();
	cout<<T<<endl;
}
void Writetorecord(string op)
{
    FILE *fr = fopen("record.txt", "a");
    fprintf(fr, "%s: 操作员：%s 时间：%s\n", op.c_str(), user.name, gettime().c_str());
    fclose(fr);
}
//显示时间
inline void showoutline()
{
	printf("%-16s %-10s %-10s %-10s\n", "名称", "编号", "库存量", "价格");
}
//低权限显示
void show_all(GoodList L)
{
    printf("商品信息如下:\n");
    printf("%-16s %-10s %-10s %-10s %-10s %-10s\n", "名称", "编号", "库存量","售出" ,"价格","销售额");
    GoodList node = L->nex;
    while (node){
        printf("%-16s %-10d %-10d %-10d %-10.1f %-10.1f\n",node->good.name,node->good.id,node->good.left,node->good.out,node->good.price,node->good.sales);
        node = node ->nex;
    }
}
//高权限商品信息显示
void show_one(GoodList node)
{
    printf("商品信息如下:\n");
    printf("%-16s %-10s %-10s %-10s %-10s %-10s\n", "名称", "编号", "库存量","售出" ,"价格","销售额");
    printf("%-16s %-10d %-10d %-10d %-10.1f %-10.1f\n",node->good.name,node->good.id,node->good.left,node->good.out,node->good.price,node->good.sales);
}
//高权限显示一个商品的信息
void show2(GoodList L)
{
	show(商品信息如下：)
	showoutline();
	GoodList p = L->nex;
	while (p != NULL){
		cout(p);
		p = p->nex;
	}
}
//低权限显示所有商品的信息
void show1(GoodList &L)
{
	ShopList Head = new Snode;
	Head->nex = NULL;
	show2(L);
	double tot = 0;
	while (true){
		printf("输入商品编号 (输入 0 结账): \n");
		int id,num,newleft;
		GoodList p;
		cin >> id;
		if (id == 0){//结账
			printf("总计 ￥：%.1f 输入收款金额: \n",tot);
			double getmoney;
			putmoney: cin >> getmoney;
			if (getmoney < tot){
				printf("金额不足 请重新输入\n");
				goto putmoney;
			}
			FILE *fp = fopen("bill.txt","w");
			printf("------------------------------------------------------\n");
			fprintf(fp,"%s","------------------------------------------------------\n");
			fprintf(fp,"%-16s %-10s %-10s %-10s\n","商品名称", "单价", "数量", "总价");
			printf("%-16s %-10s %-10s %-10s\n","商品名称", "单价", "数量", "总价");
			ShopList p = Head->nex;
			//结账成功后才能修改数据，所以先用head 开头的链表存了下来
			while (p != NULL){
				GoodList cur = LocateGood(L, p->good.id);
				cur->good.left -= p->good.num;
				cur->good.out += p->good.num;
				cur->good.sales += p->good.sum;
				printf("%-16s %-10.1f %-10d %-10.1f\n",p->good.name,p->good.price,p->good.num,p->good.sum);
				fprintf(fp, "%-16s %-10.1f %-10d %-10.1f\n",p->good.name,p->good.price,p->good.num,p->good.sum);
				p = p->nex;
			}
			printf("应收: ￥：%10.1f\n", tot);
			printf("实收: ￥：%10.1f   找零: ￥：%10.1f\n", getmoney, getmoney - tot);
			printf("------------------------------------------------------\n");
			showtime();
			printf("收银员: %s\n", user.name);
			printf("------------------------------------------------------\n");
			fprintf(fp, "应收: ￥：%10.1f\n", tot);
			fprintf(fp, "实收: ￥：%10.1f   找零: ￥：%10.1f\n", getmoney, getmoney - tot);
			fprintf(fp, "%s", "------------------------------------------------------\n");
			fprintf(fp, "%s\n", gettime().c_str());
			fprintf(fp, "收银员: %s\n", user.name);
			fprintf(fp, "%s", "------------------------------------------------------\n");
			fclose(fp);
			Writetorecord("销售记录");
			while (Head->nex != NULL){
				ShopList tmp = Head->nex;
				Head->nex = Head->nex->nex;
				delete tmp;
			}
			//本次销售完后临时链表的空间释放
	//		WritetoFile(L);
			break;
		}
		if ( (p = LocateGood(L,id))== NULL){
			printf("该商品信息为空\n");
			continue;
		}
		showoutline();
		cout(p);
		//显示这件商品
		printf("输入购买数量:\n");
		cin >> num;
		if (num <=0 ){
			printf("购买数量小于零，出现错误\n");
			continue;
		}
		newleft = p->good.left - num;
		if (newleft < 0){
			printf("库存量不足，出现错误\n");
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
		//存下购买信息，以进行打印操作
	}
}
void show3(GoodList &L)
{
	show2(L);
	int id;
	while (true){
		printf("按 1 添加 ， 按 0 退出\n");
		char op;
		cin >> op;
		cls;
		if (op != '1') nexline;
		if (op == '0') break;
		else if (op != '1'){
			show(请按提示输入);
			continue;
		}
		show(输入所添加商品的信息格式如下：)
		printf("%-16s %-10s %-10s %-10s\n", "名称", "编号", "库存量", "价格");
		printf("例如：\n%-16s %-10d %-10d %-10.1f\n", "好果汁", 1, 100, 5.0);
		GoodList node = new Lnode;
		scanf("%s%d%d%lf", &node->good.name, &node->good.id, &node->good.left, &node->good.price);
		if (have.count(node->good.id)){
			show(已经有该编号，轻重新输入)
			continue;
		}
		if (node->good.id < 0){
			show(编号小于零，请重新输入)
			continue;
		}
		node->good.out = node->good.sales = 0;
		node->nex = L->nex;
		L->nex = node;
		have[node->good.id] = true;
		++goodid;
		printf("添加成功\n");
		Writetorecord("添加记录");
	}
}
void show4(GoodList &L)
{
	int id;
	while (true){
        show2(L);
		show(输入商品编号删除 (按 0 退出));
		cin >> id;
		cls;
		if (id == 0) break;
		if (!have.count(id)){
			show(不存在该商品，请重新输入);
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
		printf("删除成功\n");
		Writetorecord("删除记录");
	}
}
void show5(GoodList &L)
{
	show2(L);
	int id;
	while (true){
		show(输入商品编号进行修改 (按 0 退出));
		cin >> id;
		cls;
		if (id == 0) break;
		if (!have.count(id)){
			show(不存在该商品，请重新输入);
			continue;
		}
		GoodList tmp = LocateGood(L,id);
		showoutline();
		cout(tmp);
		show(1: 修改名称)
		show(2: 修改价格)
		show(3: 修改库存)
		char op;
		cin >> op;
		cls;
		switch (op){
			case '1' :
				show(输入更改后的名称)
				char ChangedName[20];
				scanf("%s", ChangedName);
				strcpy(tmp->good.name, ChangedName);
				show(更改成功)
				Writetorecord("名称更改记录\n");
				break;
			case '2' :
				show(输入更改后的价格)
				double ChangedPrice;
				cin >> ChangedPrice;
				if (ChangedPrice < 0){
					show(价格不能小于 0，请重新输入)
					continue;
				}
				tmp->good.price = ChangedPrice;
				show(更改成功)
				Writetorecord("价格更改记录");
				break;
			case '3' :
				show(输入更改后的库存)
				int ChangedLeft;
				cin >> ChangedLeft;
				if (ChangedPrice < 0){
					show(库存不能小于 0，请重新输入);
					continue;
				}
				tmp->good.left = ChangedLeft;
				show(更改成功)
				Writetorecord("库存更改记录");
				break;
			default :
				printf("没有该操作！\n");
		}
	}
}
void show6(GoodList L)
{
    GoodList node;

    while (true){
        nexline;
        printf("输入 1 按名称检索商品信息 \n输入 2 按编号检索商品信息\n输入 3 显示所有商品信息\n");
        printf("输入 4 按销售额降序显示商品信息\n输入 5 按销售量降序显示商品信息\n输入 0 退出\n");
        printf("请输入操作:\n");
        char op;
        cin >> op;
        cls;
        if (op == '0') break;
        if (1 <= op && op <=5) {
            Writetorecord("数据分析记录");
        }
        switch (op){
            case '1':
                printf("输入商品名称:\n");
                char s[105];
                scanf("%s",s);
                node = LocateGoodByName(L,s);
                if (node == NULL){
                    printf("没有该商品\n");
                    continue;
                }
                show_one(node);
                break;
            case '2':
                printf("输入商品编号:\n");
                int idx;
                cin >> idx;
                node = LocateGood(L,idx);
                if (node == NULL){
                    printf("没有该商品\n");
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
                printf("请正确输入操作\n");
        }
    }

}
void show0_1(GoodList &L)
{
    while (true) {
        show(-------\t功能列表-------)
        show(\t1: 超市收银)
        show(\t2: 退出登陆)
        show(请输入功能:)
        int op;
        cin >> op;
        cls;
        if (op == 1) {
            show1(L);
        }
        else if (op == 2) {
            printf("退出成功\n");
            break;
        }
        else {
            printf("输入正确操作┗|｀O′|┛ 嗷~~\n");
        }
        WritetoFile(L);
    }
}
void show0_2(GoodList &L)
{   while (true) {
        show(-------\t功能列表-------)
        show(\t1: 查询商品)
        show(\t2: 添加商品)
        show(\t3: 删除商品)
        show(\t4: 修改商品)
        show(\t5: 退出登陆)
        show(输入操作)
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
                show(正确输入操作┗|｀O′|┛ 嗷~~)
        }
        WritetoFile(L);
    }

}
void show0_3(GoodList &L)
{   in_show0_3:
    show(-------\t功能列表-------)
    show(\t1: 销售分析)
    show(\t2: 退出登陆)
    show(输入操作)
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
        show(好好输入，不然没有你滴好果汁吃)
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
    printf("1: 超市收银员\n");
    printf("2: 货物管理员\n");
    printf("3: 销售分析员\n");
    printf("选择注册类型:\n");
    char s[105];
    scanf("%s", s);
    int len = strlen(s);
    if (len != 1 || s[0] < '0' || s[0] > '9'){
        printf("重新输入\n");
        goto reg;
    }
    newid.type = s[0] - '0';
    cls;
	printf("输入用户名:\n");
	scanf("%s", newid.name);
    while (fread(cmp, sizeof(account), 1, fp)) {
        if (strcmp(cmp->name, newid.name) == 0){
            printf("改用户名已被注册\n");
            fclose(fp);
            return;
        }
    }
    reset :printf("输入密码\n");
    char tmp[30];
    scanf("%s", tmp);
    printf("请重新确认密码\n");
    scanf("%s", newid.password);
    if (strcmp(newid.password, tmp) != 0) {
        printf("两次密码不一样，请重新设置密码\n");
        cls;
        goto reset;
    }
    cls;
    FILE *fr = fopen("record.txt", "a");
    fprintf(fr, "注册: %s %s\n", newid.name, gettime().c_str());
    fclose(fr);
    printf("注册成功\n");
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
    printf("\t假装是个登陆界面:\n");
    printf("输入用户名:\n");
    scanf("%s", tmp.name);
    putpassword:
    printf("输入密码:\n");
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
        	//退回一格用空格覆盖前一个输出再退回到空格位置准备读入下一个输入 
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
            printf("\n密码错误, 请重新输入\n");
            goto putpassword;
        }
        else {
            printf("\n该用户名不存在\n");
        }
    }
    return 0;
}
void Log(int &check)
{
    check = 0;
    //Logselect:
	printf("**********************\n");
	printf("1: 登录\n");
	printf("2: 注册\n");
	printf("3: 退出\n");
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
            fprintf(fp, "登陆: %s %s\n", user.name, gettime().c_str());
            fclose(fp);
            cls;
            printf("登陆成功\n");
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
            Writetorecord("退出登陆");
            WritetoFile(GoodHead);
        }
	}
    return 0;
}
