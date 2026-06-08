#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<queue>
#define random(a,b) (rand()%(b-a+1)+a)
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define HAN HANDLE
#define COO COORD
#define GET() GetStdHandle(STD_OUTPUT_HANDLE)
#define SET SetConsoleCursorPosition
#define red 12
#define blue 11
#define purple 13
#define white 15
#define green 10
#define yellow 14
#define kuang "□"
#define kuai "■"
using namespace std;
bitset<30>down;
bitset<30>pre;
typedef unsigned short int us; //能怎么省空间我就怎么省
typedef void vv; //惰性动物

map<us,us> color;//颜色对应
map<us,string> nb;//数字对应

const int card1=314;//牌堆1的总数
int rond=1;//回合数
int way=1;//出牌顺序方向 

vv null(){
	return;
} 

struct settings { //设置
	us cdmode;//牌堆模式
	us gmmode;//游戏模式
	us prs;//玩家数
	us cds;//开局手牌数
} sets[100];

vv begin1() {
	nb[0]="◎";
	nb[1]="①";
	nb[2]="②";
	nb[3]="③";
	nb[4]="④";
	nb[5]="⑤";
	nb[6]="⑥";
	nb[7]="⑦";
	nb[8]="⑧";
	nb[9]="⑨";
	nb[10]="×";
	nb[11]="+2";
	nb[12]="≒";
	nb[13]="¤";
	nb[14]="+4";
	color[1]=red;
	color[2]=green;
	color[3]=blue;
	color[4]=yellow;
	sets[1].prs=4;
	sets[1].cds=5;

}

vv SC /*变色！<<<<<9深蓝10绿11浅蓝12红13紫14黄15白>>>>>*/ (us ForeColor=15,us BackGroundColor=0) {
	HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
}
vv SP(int words_xx=30,int words_yy=108) { //设置光标位置，符合习惯，前参数为行，后参数为列，从1开始
	HAN h;
	COO c;
	c.X=words_yy-1;
	c.Y=words_xx-1;
	h=GET();
	SET(h,c);
}

struct button{//按钮 
	string name;
	vv (*p)();
	button(string xn,vv (*d)()=null):name(xn),p(d){
	}
	vv pt(int xx,int yy,bool ch){
		SP(xx,yy);
		if(ch)SC(0,240);
		else SC(15);
		cout<<name;
		SC();
		SP();
		return;
	}
	vv press(){
		p();
		return;
	}
};

struct card {
	us cr;//color颜色 1红 2绿 3蓝 4黄 0黑
	us num;//number数字 10为禁止 11为+2 12为转向 13万能 14+4
	bool put(int x,int y,bool f) { //显示函数 以xy为轴心3*3显示，f表示是否选中
		SP(x-1,y-2);
		string ct="□";//输出的方块
		if(f)ct="■";
		if(cr==0) {
			SC(red);
			cout<<ct;
			SC(15);
			cout<<ct;
			SC(green);
			cout<<ct;
			SP(x,y-2);
			SC(15);
			cout<<ct<<nb[num]<<ct;
			SP(x+1,y-2);
			SC(blue);
			cout<<ct;
			SC(15);
			cout<<ct;
			SC(yellow);
			cout<<ct;
		} else {
			SC(color[cr]);
			cout<<ct;
			cout<<ct;
			cout<<ct;
			SP(x,y-2);
			cout<<ct<<nb[num]<<ct;
			SP(x+1,y-2);
			cout<<ct;
			cout<<ct;
			cout<<ct;
		}
		SC(15);
		return 0;
	}
} cd[114514],lc/*上一张牌*/;

struct player {
	int cn;//cardnum 手牌数
	int noc;//no count 禁止回合数
	vector<card> c;//card 手牌
	int now;//now 选中哪张牌
	vv cls(){
		c.clear();
		cn=0;
		noc=0;
		now=0;	}
} pr/*玩家*/,ai[7];

vv putt() {
	for(int ix=0; ix<pr.cn; ix++) {
		card ee=pr.c[ix];
		ee.put(20,6*ix+3,ix==pr.now?1:0);
	}
}

us mp[30][200];
bool vs[30][200];
int wy[2][4]={{+1,0,-1,0},{0,+1,0,-1}};
struct dian{ //点 
	int x,y;
	dian(int xx,int yy):x(xx),y(yy){
	}
};

vv begin2() {
	int cnt=1;
	for(int i=1; i<=4; i++) {
		for(int j=0; j<=12; j++) {
			cd[cnt].cr=i;
			cd[cnt++].num=j;
		}
	}
	cd[cnt].cr=0;
	cd[cnt++].num=13;
	cd[cnt].cr=0;
	cd[cnt].num=14;
	queue<dian> qq;
	dian now(1,1);
	mp[1][1]=1;
	vs[1][1]=1;
	qq.push(now);
	while(!qq.empty()){
		dian neww=qq.front();
		qq.pop();
		for(int i=0;i<4;i++){
			int nx=neww.x+wy[0][i];
			int ny=neww.y+wy[1][i];
			if(nx>0&&nx<=10&&ny>0&&ny<=55&&(!vs[nx][ny])){
				mp[nx][ny]=mp[neww.x][neww.y]+1;
				if(mp[nx][ny]>4)mp[nx][ny]=1;
				vs[nx][ny]=1;
				dian nows(nx,ny);
				qq.push(nows);
			}
		}
	}
}

vector<card> cdt;//临时牌堆
queue<card> ctt;//牌堆

vv pk(int xx,int yy,bool co,int sb,player bsb){//显示玩家 
	SP(xx-2,yy-2);
	cout<<"         ";
	SP(xx+2,yy-2);
	cout<<"         ";
	if(co)SC(13);
	else if(bsb.cn==1)SC(14);
	else SC(15);
	SP(xx-1,yy-2);
	cout<<"□□□";
	SP(xx,yy-2);
	cout<<"□"<<nb[sb]<<"□";
	SP(xx+1,yy-2);
	cout<<"□□□";
	SP(xx-2,yy-2);
	cout<<bsb.cn;
	SP(xx+2,yy-2);
	if(bsb.noc>0)cout<<nb[10]<<" "<<bsb.noc;
	SC(15);
}

vv pini(){//状态
	pk(7,3,rond==2?1:0,2,ai[1]);
	pk(3,50,rond==3?1:0,3,ai[2]);
	pk(7,97,rond==4?1:0,4,ai[3]);
	if(pr.noc>0){
		SP(18,80);
		cout<<nb[10]<<" "<<pr.noc;
	}	
	else{
		SP(18,80);
		cout<<"                ";
	}
}

vv setc(us x) { //set card 建立牌堆
	for(us i=1; i<=54; i++) {
		card nee=cd[i];
		us nt;
		if(cd[i].num<10)nt=3;
		else if(cd[i].cr==0)nt=5;
		else nt=2;
		while(nt--) {
			cdt.push_back(nee);
		}
	}
	for(int i=0; i<cdt.size(); i++) {
		us a=random(0,cdt.size()-1),b=random(0,cdt.size()-1);
		card k=cdt[a];
		cdt[a]=cdt[b];
		cdt[b]=k;
	}
	for(int i=0; i<cdt.size(); i++) {
		ctt.push(cdt[i]);
	}
	return;
}

bool pan(player l){
	bool x=1;
	if(l.cn==0)return 0;
	for(int i=0;i<l.cn;i++){
		if(l.c[i].num<10)x=0;
	}
	return x;
}

bool judge(player &jp){
	return jp.cn;
}

vv ch(player &jp){//抽卡
	 //给角色发手牌
	 	Sleep(150);
	 	putt();
	 	pini();
		jp.c.push_back(ctt.front());
		jp.cn++;
		ctt.pop();
		putt();
	 	pini();
}



vv clr(){//清空一切没用的地方 
	SP(19,1);
	cout<<"                                                                                                                                      ";
	SP(20,1);
	cout<<"                                                                                                                                      ";
	SP(21,1);
	cout<<"                                                                                                                                      ";
	SP(22,1);
	cout<<"                                                                                                                                      ";
	}

vv princ(card e){ //显示打出的牌
	SP(7,49);
	if(way==-1){
		cout<<"-->";
	}
	else cout<<"<--";
	e.put(9,50,1);
}

bool check(card ck){//检查牌是否合法
	if(ck.cr==lc.cr||ck.num==lc.num||ck.cr==0||lc.cr==0)
	return 1;
	return 0;
}

vv chan(int r){
	Sleep(500);
	princ(lc);
	if(r!=1){
		for(int i=0;i<ai[r-1].cn;i++){
			if(ai[r-1].c[i].num==lc.num){
				int p=r+way;
				if(p>sets[1].prs)p=1;
				if(p<1)p=sets[1].prs;
				lc=ai[r-1].c[i];
				ai[r-1].cn--;
				ai[r-1].c.erase(ai[r-1].c.begin()+i);
				way*=-1; /*核心*/
				chan(p);
				return;
			}
		}
	}
	else{
		while(1){
			putt();
			SP(22,1);
			cout<<"是否传递该功能牌到下一家？";
			switch(getch()){
				case 'a':{
				pr.now--;
				if(pr.now<0) pr.now=pr.cn-1;
				break;
			}
			case 'd':{
				pr.now++;
				if(pr.now>=pr.cn) pr.now=0;
				break;
			}
			case 's':{ //跳过回合
				return;
				break;
			}
			case 224:{
				switch(getch()){
					case 75:{
						pr.now--;
						if(pr.now<0) pr.now=pr.cn-1;
						break;
					}
					case 77:{
						pr.now++;
						if(pr.now>=pr.cn) pr.now=0;
						break;
					}
				}
				break;
			}
			case 32:{
				if(pr.c[pr.now].num==lc.num){
					SP(12,1);
					cout<<"                       ";
					lc=pr.c[pr.now];
					pr.cn--;
					vector<card>::iterator ite;
					ite=pr.c.begin();
					for(int j=0;j<pr.now;j++){
						++ite;
					}
					pr.c.erase(ite);
					pr.now=0;
					clr();
					putt();
					princ(lc);
					SP(22,1);
					int p=r+way;
					if(p>sets[1].prs)p=1;
					if(p<1)p=sets[1].prs;
					way*=-1; /*核心*/
					chan(p);
					return;
				}
				else{
					SP(12,1);
					cout<<"不能这么出！";
				}
				break;
			} 
		}
	}
}
}

vv ban(int r,int cnt){
	Sleep(500);
	princ(lc);
	if(r!=1){
		for(int i=0;i<ai[r-1].cn;i++){
			if(ai[r-1].c[i].num==lc.num){
				int p=r+way;
				if(p>sets[1].prs)p=1;
				if(p<1)p=sets[1].prs;
				lc=ai[r-1].c[i];
				ai[r-1].cn--;
				ai[r-1].c.erase(ai[r-1].c.begin()+i); 
				/*核心*/
				ban(p,cnt+1);
				return;
			}
		}
		if(r!=1)
		ai[r-1].noc+=cnt;
		else pr.noc+=cnt;
		return;
	}
	else{
		while(1){
			putt();
			SP(22,1);
			cout<<"是否传递该功能牌到下一家？";
			switch(getch()){
				case 'a':{
				pr.now--;
				if(pr.now<0) pr.now=pr.cn-1;
				break;
			}
			case 'd':{
				pr.now++;
				if(pr.now>=pr.cn) pr.now=0;
				break;
			}
			case 's':{ //跳过回合
				pr.noc+=cnt;
				return;
				break;
			}
			case 224:{
				switch(getch()){
					case 75:{
						pr.now--;
						if(pr.now<0) pr.now=pr.cn-1;
						break;
					}
					case 77:{
						pr.now++;
						if(pr.now>=pr.cn) pr.now=0;
						break;
					}
				}
				break;
			}
			case 32:{
				if(pr.c[pr.now].num==lc.num){
					SP(12,1);
					cout<<"                       ";
					lc=pr.c[pr.now];
					pr.cn--;
					vector<card>::iterator ite;
					ite=pr.c.begin();
					for(int j=0;j<pr.now;j++){
						++ite;
					}
					pr.c.erase(ite);
					pr.now=0;
					clr();
					putt();
					princ(lc);
					SP(22,1);
					int p=r+way;
					if(p>sets[1].prs)p=1;
					if(p<1)p=sets[1].prs;
					 /*核心*/
					ban(p,cnt+1);
					return;
				}
				else{
					SP(12,1);
					cout<<"不能这么出！";
				}
				break;
			} 
		}
	}
}
}

vv add(int r,int cnt,int cntt){
	Sleep(500);
	princ(lc);
	if(r!=1){
		for(int i=0;i<ai[r-1].cn;i++){
			if(ai[r-1].c[i].num==lc.num){
				int p=r+way;
				if(p>sets[1].prs)p=1;
				if(p<1)p=sets[1].prs;
				lc=ai[r-1].c[i];
				ai[r-1].cn--;
				ai[r-1].c.erase(ai[r-1].c.begin()+i); 
				/*核心*/
				add(p,cnt+cntt,cntt);
				return;
			}
		}
		if(r!=1){
		ai[r-1].noc++;
		for(int i=1;i<=cnt;i++){
			ch(ai[r-1]);
		}}
		else{
			pr.noc++;
			for(int i=1;i<=cnt;i++){
			ch(pr);
		}
		}
		return;
	}
	else{
		while(1){
			putt();
			SP(22,1);
			cout<<"是否传递该功能牌到下一家？";
			switch(getch()){
				case 'a':{
				pr.now--;
				if(pr.now<0) pr.now=pr.cn-1;
				break;
			}
			case 'd':{
				pr.now++;
				if(pr.now>=pr.cn) pr.now=0;
				break;
			}
			case 's':{ //跳过回合
				pr.noc++;
				while(cnt--)
				ch(pr);
				return;
				break;
			}
			case 224:{
				switch(getch()){
					case 75:{
						pr.now--;
						if(pr.now<0) pr.now=pr.cn-1;
						break;
					}
					case 77:{
						pr.now++;
						if(pr.now>=pr.cn) pr.now=0;
						break;
					}
				}
				break;
			}
			case 32:{
				if(pr.c[pr.now].num==lc.num){
					SP(12,1);
					cout<<"                       ";
					lc=pr.c[pr.now];
					pr.cn--;
					vector<card>::iterator ite;
					ite=pr.c.begin();
					for(int j=0;j<pr.now;j++){
						++ite;
					}
					pr.c.erase(ite);
					pr.now=0;
					clr();
					putt();
					princ(lc);
					SP(22,1);
					int p=r+way;
					if(p>sets[1].prs)p=1;
					if(p<1)p=sets[1].prs;
					 /*核心*/
					add(p,cnt+cntt,cntt);
					return;
				}
				else{
					SP(12,1);
					cout<<"不能这么出！";
				}
				break;
			} 
		}
	}
}
}

vv func(card ne){
	switch(ne.num){
		case 10:{
			int p=rond+way;
			if(p>sets[1].prs)p=1;
			if(p<1)p=sets[1].prs;
			ban(p,1);
			break;
		}
		case 11:{
			int p=rond+way;
			if(p>sets[1].prs)p=1;
			if(p<1)p=sets[1].prs;
			add(p,2,2);
			break;
		}
		case 12:{
			way*=-1;
			int p=rond+way;
			if(p>sets[1].prs)p=1;
			if(p<1)p=sets[1].prs;
			chan(p);
			break;
		}
		case 14:{
			int p=rond+way;
			if(p>sets[1].prs)p=1;
			if(p<1)p=sets[1].prs;
			add(p,4,4);
			break;
		}
	}
	return;
}

vv pd(card &pdc){
	if(rond==1){
	if(pdc.cr==0){
		princ(pdc);
		SC(15);
		SP(22,45);
		cout<<"请选择颜色:";
		SC(red);
		cout<<"1■";	
		SC(green);
		cout<<"2■";	
		SC(blue);
		cout<<"3■";	
		SC(yellow);
		cout<<"4■";
		char xxx=getch();
		while(xxx<'1'||xxx>'4'){
			SC(15);
			SP(23,45);
			cout<<"输入错误！"; 
			xxx=getch();
		}
		pdc.cr=(us)(xxx-'0');
		SP(23,45);
		cout<<"                           ";	
	}}
	else{
		princ(lc);
		Sleep(500);
		pdc.cr=random(1,4);
		princ(lc);
		return;
	}
}

vv pc(){//玩家出牌
	if(pr.noc>0){ //被禁止就不能出牌
		pr.noc--;
		return;
	}
	bool flg=0;//记录玩家是否有能出的牌
	for(int i=0;i<pr.cn;i++){
		if(check(pr.c[i]))flg=1;
	}
	if(!flg) ch(pr);
	while(pan(pr)){
		ch(pr);
	}
	while(1){
		clr();
		princ(lc);
		putt();
		switch(getch()){
			case 'a':{
				pr.now--;
				if(pr.now<0) pr.now=pr.cn-1;
				break;
			}
			case 'd':{
				pr.now++;
				if(pr.now>=pr.cn) pr.now=0;
				break;
			}
			case 's':{ //跳过回合
				return;
				break;
			}
			case 224:{
				switch(getch()){
					case 75:{
						pr.now--;
						if(pr.now<0) pr.now=pr.cn-1;
						break;
					}
					case 77:{
						pr.now++;
						if(pr.now>=pr.cn) pr.now=0;
						break;
					}
				}
				break;
			}
			case 32:{
				if(check(pr.c[pr.now])){
					SP(12,1);
					cout<<"                       ";
					lc=pr.c[pr.now];
					pr.cn--;
					vector<card>::iterator ite;
					ite=pr.c.begin();
					for(int j=0;j<pr.now;j++){
						++ite;
					}
					pr.c.erase(ite);
					pr.now=0;
					if(lc.cr==0){
						pd(lc);
					}
					clr();
					putt();
					func(lc);
					princ(lc);
					while(pan(pr)){
					ch(pr);}
					return;
				}
				else{
					SP(12,1);
					cout<<"不能这么出！";
				}
				break;
			}
				
			
		}
	}
}

vv pcai(player &aii){//电脑出牌
	pini();
	Sleep(500);
	if(aii.noc>0){ //被禁止就不能出牌
		aii.noc--;
		return;
	}
	bool flg=0;//记录玩家是否有能出的牌
	for(int i=0;i<aii.cn;i++){
		if(check(aii.c[i]))flg=1;
	}
	if(!flg) ch(aii);
	while(pan(aii)){
		ch(aii);
	}
	flg=0;
	for(int i=0;i<aii.cn;i++){
		if(check(aii.c[i]))flg=1;
	}
	if(!flg) return;
	else
	while(1){
		vector<card>::iterator ite;
		ite=aii.c.begin();
		for(int j=0;j<aii.cn;j++){
			if(check(aii.c[j]))
			{
				aii.cn--;
				lc=aii.c[j];
				func(lc);
				aii.c.erase(ite);
				if(lc.cr==0){
					pd(lc);
				}
				Sleep(500);
				while(pan(aii)){
				ch(aii);
				}
				return;
			}
			++ite;
		}
	}

}

vv qcls(queue<card> &cq){
	while(!cq.empty()){
		cq.pop();
	}
}

vv clsall(){//全部初始化 
	pr.cls();
	for(int i=1;i<=7;i++)ai[i].cls();
	cdt.clear();
	qcls(ctt);
	rond=1;
	way=1;
}

vv game() { //经典模式 
	clsall();
	system("cls");
	setc(0);
	for(int i=1; i<=sets[1].cds; i++) { //给玩家发手牌
		ch(pr);
	}
	for(int j=1; j<=sets[1].prs-1; j++) {
		for(int i=1; i<=sets[1].cds; i++) { //给ai玩家发手牌
			ch(ai[j]);
		}
	}
	bool fi=1;//是否有人出完牌
	lc=ctt.front();
	ctt.pop();
	princ(lc);
	putt();
	while(fi){
		princ(lc);
		pini();
		if(rond>sets[1].prs)rond=1;
		if(rond<1)rond=sets[1].prs;
		if(rond==1)
		pc();
		else
		pcai(ai[rond-1]);
		if(rond==1)fi=judge(pr);
		else fi=judge(ai[rond-1]);
		rond+=way;
	}
	pini();
	princ(lc);
	SP(28,20);
	cout<<"玩家"<<(way==1?rond-1:rond+1)<<"获胜！";
	SP(29,20);
	cout<<"请按任意键……";
	getch();
	system("cls");
	return;
}
vv game2(){ //休闲模式 最大特点可以出对子 
	clsall();
	system("cls");
	setc(0);
	for(int i=1; i<=sets[1].cds; i++) { //给玩家发手牌
		ch(pr);
	}
	for(int j=1; j<=sets[1].prs-1; j++) {
		for(int i=1; i<=sets[1].cds; i++) { //给ai玩家发手牌
			ch(ai[j]);
		}
	}
	bool fi=1;//是否有人出完牌
	lc=ctt.front();
	ctt.pop();
	princ(lc);
	putt();
	while(fi){
		princ(lc);
		pini();
		if(rond>sets[1].prs)rond=1;
		if(rond<1)rond=sets[1].prs;
		if(rond==1)
		pc();
		else
		pcai(ai[rond-1]);
		if(rond==1)fi=judge(pr);
		else fi=judge(ai[rond-1]);
		rond+=way;
	}
	pini();
	princ(lc);
	SP(28,20);
	cout<<"玩家"<<(way==1?rond-1:rond+1)<<"获胜！";
	SP(29,20);
	cout<<"请按任意键……";
	getch();
	system("cls");
	return;
}

vv opening(){//超他妈炫酷的开场动画 
	SC();
	for(int i=0;i<53;i++){
		SP(5,i*2+1);
		cout<<kuang;
		SP(16,109-i*2);
		cout<<kuang;
		Sleep(20);
	}
	SP(5,1);
	for(int i=0;i<55;i++)cout<<kuang;
	SP(16,1);
	for(int i=0;i<55;i++)cout<<kuang;
	vector<dian> opn;
	for(int i=1;i<=10;i++){
		for(int j=0;j<=54;j++){
			dian opni(i,j);
			opn.push_back(opni);
		}
	} 
	int ksl=opn.size();
	for(int i=0;i<ksl;i++){
		int e=random(0,opn.size()-1);
		SP(opn[e].x+5,opn[e].y*2+1);
		cout<<kuang;
		opn.erase(opn.begin()+e);
		Sleep(1);
	}

//	SP(5,1);
//	for(int i=0;i<55;i++)cout<<kuang;
//	SP(16,1);
//	for(int i=0;i<55;i++)cout<<kuang;
//	for(int i=1;i<=10;i++){
//		SP(5+i,1);
//		for(int j=1;j<=55;j++){
//			SC(color[mp[i][j]]);
//			cout<<kuang;
//		}
//	}
	SC();
}

vv showr(int ci){//讲解模式内容 
	SC();
	for(int i=0;i<7;i++){
		SP(7+i,40);
		cout<<"                                 ";
	}
	switch(ci){
		case 0:{
			SP(7,40);
			cout<<"·原汁原味的经典模式";
			SP(8,40);
			cout<<"·变色仅能指定颜色";
			SP(9,40);
			cout<<"·功能牌传递至下一家";
			SP(10,40);
			cout<<"·加牌后禁止";
			SP(11,40);
			cout<<"·无法出对子"; 
			break;
		}
		case 1:{
			SP(7,40);
			cout<<"·玩法多样的休闲模式";
			SP(8,40);
			cout<<"·变色多带一张";
			SP(9,40);
			cout<<"·功能牌可指定任意玩家（包括自己）";
			SP(10,40);
			cout<<"·加牌后不会禁止";
			SP(11,40);
			cout<<"·可以出对子甚至三连及更多"; 
			break;
		}
		case 2:{
			SP(7,40);
			cout<<"·退出";
			break;
		}
	}
	SC();
}

vv choose(){//选择游戏模式
	system("cls");
	button mode1("Classic Mode",game);
	button mode2("RelaxingMode");  
	button backs("Back");
	vector<button> bks;
	bks.push_back(mode1);
	bks.push_back(mode2);
	bks.push_back(backs);
	int ci=0;
	while(1){
		for(int ji=0;ji<=2;ji++){
			bks[ji].pt(7+ji*2,16,ci==ji);
		}
		showr(ci); 
		switch(getch()){
			case 224:{
				switch(getch()){
					case 72:{
						ci--;if(ci<0)ci=2;
						break;
					}
					case 80:{
						ci++;if(ci>2)ci=0;
						break;
					}
				}
				break;
			}
			case 32:{
				bks[ci].press();
				if(ci==2){
					system("cls");
					return;
				}
				break;
			}
		}
	}
}

vv start(){//开机画面 

	button stgame("StartGame",choose);
	button exgame("Exit Game");
	vector<button> bk;
	bk.push_back(stgame);
	bk.push_back(exgame);
	int in=0;
	while(1){
		bk[0].pt(17,48,in==0);
		bk[1].pt(19,48,in==1);
		switch(getch()){
			case 224:{
				in^=1;
				break;
			}
			case 32:{
				bk[in].press();
				if(in==1)return;
				break;
			}
		}
	}
}

int main() {
	srand((unsigned)time(NULL));
	system("mode con cols=110 lines=30");
	system("title UNO");
	system("cls");
	begin1();
	begin2();
	opening();
	start();
//	int ce,dd;

//	cout<<"sb";
//	for(int i=1;i<=10;i++){
//		pr.c.push_back(cd[random(0,42)]);
//		pr.cn++;
//	}
//	putt();
}
