#include<bits/stdc++.h>/*Made By DHOJ 只会整烂活的qpr*/
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
#define cls system("cls")
using namespace std;
bitset<30>down;
bitset<30>pre;
typedef unsigned short int us; //能怎么省空间我就怎么省
typedef void vv; //惰性动物
us level[3]={10,8,6};//空隙行数
us lv=0;//难度级数 
bool mp[35][60],mpp[35][60];//地图（炮 
int bd=15,bdd=15;//鸟鸟的位置和上一个位置 
us bdc=15;//鸟鸟的颜色 
us upt;//剩余上升时间(max=3) 
us tim;//时间进度
int sc;//分数
int addk; 
bool xu,www,lzx,cxk,nd;//作弊按钮 
us dnt;//下降速度，因为是加速度，所以会变大，max=4 
us f[3]={50,40,30};
us ff; 
string bird="鸟";

vv SC /*变色！<<<<<9深蓝10绿11浅蓝12红13紫14黄15白>>>>>*/ (us ForeColor=15,us BackGroundColor=0) {
	HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
}
vv SP(int words_xx=30,int words_yy=110) { //设置光标位置，符合习惯，前参数为行，后参数为列，从1开始
	HAN h;
	COO c;
	c.X=words_yy-1;
	c.Y=words_xx-1;
	h=GET();
	SET(h,c);
}

vv null(){
	return;
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

vv mov(){
	for(int i=1;i<=55;i++){
		if(mp[1][i]){
			for(int j=1;j<=30;j++){
				if(mp[j][i]){
				mp[j][i-1]=1;
				mp[j][i]=0;}
			}
		}
	}
}

vv add(){
	addk=random(2,18);
	if(lzx)bd=addk+level[lv]/2;
	for(int i=1;i<=addk;i++){
		mp[i][54]=mp[i][55]=1;
	}
	for(int i=addk+level[lv];i<=30;i++){
		mp[i][54]=mp[i][55]=1;
	}
}

int xjz;
string xhz[7]= {"你~~干~~嘛~~哼哼~~~~",
				"鲲鲲勇敢飞爱鲲永相随",
				"哥哥下的蛋你们一个也不许吃",
				"鸡你实在是太美",
				"厉不厉害你鸡哥",
				"第一次鸦片战争养的我",
				"看我怎么欺负人~"};

char pc[3][60]={{"title Fly Bird:Easy"},{"title Fly Bird:Normal"},{"title Fly Bird:Hard"}};


vv putsc(){
	SP(5,12);
	if(cxk) {
		cout<<"                         ";
		SP(5,12);
		cout<<xhz[xjz];
	}
	else if(!lzx)
	printf("当前: %d",sc);
	else printf("当前：∞"); 
}


vv putmp(){
	for(int i=1;i<=30;i++){
		for(int j=1;j<=54;j++){
			if(mp[i][j]&&mp[i][j]!=mpp[i][j])SP(i,j*2-1),printf(kuai);
			if((!mp[i][j])&&mp[i][j]!=mpp[i][j])SP(i,j*2-1),printf("  ");
		}
	}
}

vv putbird(){
	SP(bd,54);
	SC(bdc);
	cout<<bird; 
	SC(); 
}

vv copymp(){
	for(int i=1;i<=30;i++)
		for(int j=1;j<=54;j++)
			mpp[i][j]=mp[i][j];
}

vv game(){
	memset(mp,0,sizeof mp);
	bd=15;
	bdd=15;
	cls;
	putbird();
	putsc();
	sc=0;
	tim=0;
	upt=0;
	dnt=1;
	SP(18,40);
	cout<<"按任意键以开始飞行";
	getch();
	SP(18,40);
	cout<<"                  ";
	copymp();
	while(1){
		SP(bdd,54);
		printf("   ");
		putmp();
		copymp();
		putbird();
		bdd=bd;
		putsc();
		if(mp[bd][27]&&!xu){
			SP(15,50);
			cout<<"GAME OVER!";
			getch();
			return;
		}
		if(bd==30&&!xu&&!nd){
			SP(15,50);
			cout<<"GAME OVER!";
			getch();
			return;
		}
		if(tim==0)add();
		if(kbhit()){
			getch(),upt=3;
			if(www)bd=random(2,29);
		}
		if(nd==0){
			if(upt>0&&!lzx)upt--,bd--,dnt=1;
			else if(!lzx)bd+=dnt/7+1,dnt++;
			}
		else{
			if(upt>0)upt--,bd++,dnt=1;
			else bd-=dnt/7+1,dnt++;
		}
		if(dnt>21)dnt=20;
		if(bd<=0&&!nd)bd=1;
		else if(bd<=0&&nd)bd=30;
		if(bd>30&&!nd)bd=30;
		else if(bd>30&&bd)bd=1;
		mov();
		tim++;
		if(tim>=60)tim=0;
		if(xu){
			bdc=random(9,14);
		}
		if(cxk&&tim==28){
			xjz++;
			if(xjz>6)xjz=0;
		}
		if(tim==28)sc++;
		if(xu)sc+=random(50,100);
		Sleep(tim<10?ff/2:ff);
	}
}

string nam[10]={{"经典"},{"[鲲]"},{"绿色"},{"炜文"},{"祖安"},{"挂比"},"[神]","顿牛"};
string tt[10]={{"鸟"},{"鸡"},{"鸟"},{"鹅"},{"马"},{"许"},"LZX","鳥"};
string tip[10]={{"Fly Bird"},{"小黑子卤出鸡脚了吧"},{"护 眼"},{"鹅哥与小天才的故事"},"“敢这么和我讲话，你的马是批发的吗？”","-littleblacky-","“IOI金牌不是随便拿？”","转反力重"};

vv setskin(){//设定皮肤	
	cls;
	int noo=0;
	SP(15,50);
	cout<<"←";
	SP(15,58);
	cout<<"→";
	while(1){
		bird=tt[noo];
		if(noo==7)nd=1;else nd=0;
		if(noo==1)cxk=1;else cxk=0;
		if(noo==5)xu=1;else xu=0;
		if(noo==3)www=1;else www=0;
		if(noo==2)bdc=10;
		else bdc=15;
		if(noo==6)lzx=1;else lzx=0;
		SP(13,53);
		cout<<"                ";
		SP(13,53);
		cout<<nam[noo];
		SP(15,54);
		cout<<"   ";
		SP(15,54);
		SC(bdc);
		cout<<tt[noo];
		SC();
		SP(17,46);
		cout<<"                                                     ";
		SP(17,46);
		cout<<tip[noo];
		switch(getch()){
			case 224:{
				switch(getch()){
					case 75:{
						if(noo==0)noo=8;
						noo--;
						break;
					}
					case 77:{
						noo++;
						if(noo==8)noo=0;
						break;
					}
				}
				break;
			}
			default:{
				return;
			}
		}
	} 
}


vv menu_2(){
	button easy("|   E a s y   |",game);
	button norm("| N o r m a l |",game);
	button hard("|   H a r d   |",game);
	button skin("|   S k i n   |",setskin);
	vector<button> vb;
	vb.push_back(easy);
	vb.push_back(norm);
	vb.push_back(hard);
	vb.push_back(skin);
	us nowc=0;
	while(1){
		system("title Fly Bird");
		for(int i=0;i<vb.size();i++){
			vb[i].pt(13+i*2,46,nowc==i);
		}
		switch(getch()){
			case 224:{
				switch(getch()){
					case 72:{
						if(nowc==0)nowc=4;
						nowc--;
						break;
					}
					case 80:{
						nowc++;
						if(nowc==4)nowc=0;
						break;
					}
				}
				break;
			}
			default:{
				system(pc[nowc]);
				lv=nowc;
				ff=f[nowc];
				vb[nowc].press();
				cls;
				break;
			}
		}
	}
}

vv menu_1(){
	bool stch=0;
	button stb("PleasePressAnyKey");
	while(1){
		stb.pt(15,44,stch);
		if(kbhit()){
			getch();break;
		}
		stch^=1;
		Sleep(120);
	}
	system("cls");
	menu_2();
	return;
} 

int main(){
	srand((unsigned)time(NULL));
	system("mode con cols=110 lines=30");
	system("title Fly Bird");
	system("cls");
	menu_1();
}
