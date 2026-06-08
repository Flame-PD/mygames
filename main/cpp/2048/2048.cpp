#include<bits/stdc++.h>
#include<Windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#define random(a,b) (rand()%(b-a+1)+a)
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define HAN HANDLE
#define COO COORD
#define GET() GetStdHandle(STD_OUTPUT_HANDLE)
#define SET SetConsoleCursorPosition
#define cls system("cls")
#define S(a) Sleep(a)
using namespace std;
typedef unsigned long long int ll;
typedef unsigned short int us;
typedef void vv;
ll scores = 0;//分数 12位应该够用
us scorn = 1;//记录分数位数方便补零
ll highestscores;//历史最高分
us hscorn = 1;//同上
ll step;//步数，隐藏变量，用于计算生存分
us backcolor = 15;//自定义背景颜色
us maxblock=1;//这是用来随机方块的一个小玩意 
bitset<30>down;
bitset<30>pre;
string mp[6] = {{"■■■■■■"},
				{"■        ■"},
				{"■        ■"},
				{"■        ■"},
				{"■        ■"},
				{"■■■■■■"}
};//背景地图
us rmp[9][9] = {0}; //游戏地图
float fc[9] = {1.0,1.05,1.2,1.5,1.8,2.0};//步数决定隐藏分数系数
us fcn = 0; //系数指示物 
const int sscore = 100;//基础分 
ll _score[20] = {0,1};	//合成分 
vv SC /*变色！<<<<<9深蓝10绿11浅蓝12红13紫14黄15白>>>>>*/ (us ForeColor = 15,us BackGroundColor = 0) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
	return;
}
vv SP(int xx,int yy) { //设置光标位置，xx为列，yy为行
	HAN h;
	COO c;
	c.X = xx;
	c.Y = yy;
	h = GET();
	SET(h,c);
	return;
}
vv hide() {
	SP(30,5);
}
vv iniscore(){
	for(int i = 2;i<=16;i++){
		_score[i] = _score[i-1]*2; 
	}
	return;
} 
struct block { //每个方块 目前来说15次方应该够用了
	char w; //对应字母（字母可比数字好输出多了
	us color;//颜色易区分
	vv putblock(int ix,int iy) {
		SP(ix,iy);
		SC(color);
		cout<<w<<w;
		return;
	}
} bk[16];
vv ini() { //初始化block
	for(us i = 1; i <= 14; i++) {
		bk[i].color = i+1;
		bk[i].w = 'A'+i-1;
	}
	return;
}
vv choscolor() { //开局自定义一下背景颜色
	printf("请选定您在本次游玩中希望使用的背景颜色\n按A/D进行切换，按S随机，其余任意键退出");
	bool pn = 1;
	while(pn) {
		SC(backcolor);
		SP(38,0);
		printf("■■");
		SP(38,1);
		printf("■■");
		switch(getch()) {
			case 'a': {
				backcolor --;
				break;
			}
			case 'd': {
				backcolor ++;
				break;
			}
			case 's': {
				backcolor = random(9,15);
				SC(backcolor);
				SP(38,0);
				printf("■■");
				SP(38,1);
				printf("■■");
				pn = 0;
				SP(0,2);
				printf("设置成功！按任意键继续……");
				getch();
				break;
			}
			default: {
				pn = 0;
				SP(0,2);
				printf("设置成功！按任意键继续……");
				getch();
				break;
			}
		}
		if(backcolor<9)backcolor = 15;
		if(backcolor>15)backcolor = 9;
	}
	return;
}
vv putmap() {
	SP(0,0);
	SC(backcolor);
	for(us i = 0; i < 5; i++)cout<<mp[i]<<endl;
	cout<<mp[5];
	SP(13,0);
	cout<<"     S C O R E";
	SP(13,1);
	cout<<"        NOW ";
	SP(13,3);
	cout<<"      HISTORY ";
	SP(13,5);
	cout<<"W/S/A/D移动 E退出";
	return;
}
vv putini() {
	scorn = 0;
	ll fscore = scores;
	while(fscore>0){
		scorn++;
		fscore/=10;
	}
	SC(backcolor);
	SP(15,2);
	for(int i = 14; i>scorn; i--)cout<<"0";
	cout<<scores;
	SP(15,4);
	for(int i = 12; i>hscorn; i--)cout<<"0";
	cout<<highestscores;
	hide();
	return;
}
vv putrmp() {
	SP(2,1);
	cout<<"        ";
	SP(2,2);
	cout<<"        ";
	SP(2,3);
	cout<<"        ";
	SP(2,4);
	cout<<"        ";
	for(int i = 1; i<=4; i++) {
		for(int j = 1; j<=4; j++) {
			if(rmp[i][j]!=0) {
				bk[rmp[i][j]].putblock(j*2,i);
			}
		}
	}
}
vv first() {
	SC(15);
	srand((unsigned)time(NULL));//初始化随机种子
	system("mode con cols=42 lines=3");
	system("title 2048(Beta)Basic_1.0(MadeBy Proo)");
	iniscore();
	ini();
	choscolor();
	system("mode con cols=31 lines=6");
	putmap();
	us fx = random(1,4);
	us fy = random(1,4);
	rmp[fx][fy] = 1;
	return;
}
bool xdigit(us vx){
	for(int j=1;j<=4;j++){
		if(rmp[vx][j]==0)return false;
	}
	return true;
}
bool ydigit(us vx,us vy){
	return rmp[vx][vy]==0?0:1;
}
vv randomm(){
	us xxx=random(1,4);
	us yyy=random(1,4);
	while(xdigit(xxx)){
		xxx=random(1,4);
	}
	while(ydigit(xxx,yyy)){
		yyy=random(1,4);
	}
	rmp[xxx][yyy]=random(1,maxblock);
	return;
}
vv score_plus(us vk){
	scores += _score[vk]*sscore*fc[fcn];
	return;
}
vv move_up() {
	for(int i=2; i<=4; i++) {
		for(int j=1; j<=4; j++) {
			if(rmp[i][j]!=0) {
				int ks=i-1;
				while(rmp[ks][j]==0&&ks>=1) {
					ks--;
				}
				ks++;
				swap(rmp[ks][j],rmp[i][j]);
			}
		}
	}
	for(int i=2; i<=4; i++) {
		for(int j=1; j<=4; j++) {
			if(rmp[i][j]!=0&&rmp[i][j]==rmp[i-1][j])
				score_plus(rmp[i][j]),rmp[i-1][j]++,rmp[i][j]=0;
		}
	}
	for(int i=2; i<=4; i++) {
		for(int j=1; j<=4; j++) {
			if(rmp[i][j]!=0) {
				int ks=i-1;
				while(rmp[ks][j]==0&&ks>=1) {
					ks--;
				}
				ks++;
				swap(rmp[ks][j],rmp[i][j]);
			}
		}
	}
	return;
}
vv move_left() {
	for(int i=1; i<=4; i++) {
		for(int j=2; j<=4; j++) {
			if(rmp[i][j]!=0) {
				int ks=j-1;
				while(rmp[i][ks]==0&&ks>=1) {
					ks--;
				}
				ks++;
				swap(rmp[i][ks],rmp[i][j]);
			}
		}
	}
	for(int i=1; i<=4; i++) {
		for(int j=2; j<=4; j++) {
			if(rmp[i][j]!=0&&rmp[i][j]==rmp[i][j-1])
				score_plus(rmp[i][j]),rmp[i][j-1]++,rmp[i][j]=0;
		}
	}
	for(int i=1; i<=4; i++) {
		for(int j=2; j<=4; j++) {
			if(rmp[i][j]!=0) {
				int ks=j-1;
				while(rmp[i][ks]==0&&ks>=1) {
					ks--;
				}
				ks++;
				swap(rmp[i][ks],rmp[i][j]);
			}
		}
	}
}
vv move_down() {
	for(int i=3; i>=1; i--) {
		for(int j=1; j<=4; j++) {
			if(rmp[i][j]!=0) {
				int ks=i+1;
				while(rmp[ks][j]==0&&ks<=4) {
					ks++;
				}
				ks--;
				swap(rmp[ks][j],rmp[i][j]);
			}
		}
	}
	for(int i=3; i>=1; i--) {
		for(int j=1; j<=4; j++) {
			if(rmp[i][j]!=0&&rmp[i][j]==rmp[i+1][j])
				score_plus(rmp[i][j]),rmp[i+1][j]++,rmp[i][j]=0;
		}
	}
	for(int i=3; i>=1; i--) {
		for(int j=1; j<=4; j++) {
			if(rmp[i][j]!=0) {
				int ks=i+1;
				while(rmp[ks][j]==0&&ks<=4) {
					ks++;
				}
				ks--;
				swap(rmp[ks][j],rmp[i][j]);
			}
		}
	}
}
vv move_right() {
	for(int i=1; i<=4; i++) {
		for(int j=3; j>=1; j--) {
			if(rmp[i][j]!=0) {
				int ks=j+1;
				while(rmp[i][ks]==0&&ks<=4) {
					ks++;
				}
				ks--;
				swap(rmp[i][ks],rmp[i][j]);
			}
		}
	}
	for(int i=1; i<=4; i++) {
		for(int j=3; j>=1; j--) {
			if(rmp[i][j]!=0&&rmp[i][j]==rmp[i][j+1])
				score_plus(rmp[i][j]),rmp[i][j+1]++,rmp[i][j]=0;
		}
	}
	for(int i=1; i<=4; i++) {
		for(int j=3; j>=1; j--) {
			if(rmp[i][j]!=0) {
				int ks=j+1;
				while(rmp[i][ks]==0&&ks<=4) {
					ks++;
				}
				ks--;
				swap(rmp[i][ks],rmp[i][j]);
			}
		}
	}
}
bool move() {
	switch(getch()) {
		case 224: {
			switch(getch()){
				case 72: {
					move_up();
					break;
				}
				case 80: {
					move_down();
					break;
				}
				case 75: {
					move_left();
					break;
				}
				case 77: {
					move_right();
					break;
				}
				default:{
					move();
					break;
				}
			}
			break;
		}
		case 'w': {
			move_up();
			break;
		}
		case 's': {
			move_down();
			break;
		}
		case 'a': {
			move_left();
			break;
		}
		case 'd': {
			move_right();
			break;
		}
		case 'e': {
			freopen("scores.sav","w",stdout);
			cout<<scores;
			return 1;
			break;
		} 
		default:{
			move();
			break;
		}
	}
	return 0;
}
vv stepcheck(){
	step++;
	if(step>25)maxblock=2;
	if(step==25||step==50||step==75||step==125||step==160)fcn++;
	return;
}
vv game() {
	while(1) {
		stepcheck();
		randomm();
		putrmp();
		putini();
		if(move())return;
	}
	return;
}

signed main() {
	freopen("scores.sav","r",stdin);
	cin>>highestscores;
	first();
	game();
//	system("pause");
}

