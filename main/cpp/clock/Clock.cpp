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
#define kuang "□"
#define kuai "■"
using namespace std;
bitset<30>down;
bitset<30>pre;
typedef unsigned short int us;
void SC /*变色！<<<<<9深蓝10绿11浅蓝12红13紫14黄15白>>>>>*/ (us ForeColor=15,us BackGroundColor=0) {
	HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
}
void SP(int words_xx=30,int words_yy=108) { //设置光标位置，符合习惯，前参数为行，后参数为列，从1开始
	HAN h;
	COO c;
	c.X=words_yy-1;
	c.Y=words_xx-1;
	h=GET();
	SET(h,c);
}

int mp[10][10];
int nx=1,ny=1;
unsigned long long score,step,combo,high;

void putsc(){
	SP(1,5);
	cout<<"SCORE:"<<score;
	SP(1,20);
	cout<<"HIGHEST:"<<high;
	SP(2,5);
	cout<<"STEPS:"<<step;
	return;
}

void putcom(){
	SP(2,15);
	if(combo>50)cout<<"COMBO"<<combo<<"!!!";
 	else if(combo>15)cout<<"COMBO"<<combo<<"!!";
 	else if(combo>5)cout<<"COMBO"<<combo<<"!";
 	else if(combo)cout<<"COMBO"<<combo;
 	else cout<<"                          ";
 	return;
}

void putc(int rx,int ry,int xx,int yy,bool f){
	SP(xx-1,yy-2);
	if(f)cout<<"■■■";
	else cout<<"□□□";
	SP(xx,yy-2);
	if(f)cout<<"■";
	else cout<<"□";
	switch(mp[rx][ry]){
		case 0:{
			cout<<"↑";
			break;
		}
		case 1:{
			cout<<"→";
			break;
		}
		case 2:{
			cout<<"↓";
			break;
		}
		case 3:{
			cout<<"←";
			break;
		}
	}
	if(f)cout<<"■";
	else cout<<"□";
	SP(xx+1,yy-2);
	if(f)cout<<"■■■";
	else cout<<"□□□";
	return;
}

void putmp(){
	for(int i=1;i<=6;i++){
		for(int j=1;j<=5;j++){
			putc(i,j,1+i*3,1+j*6,(nx==i&&ny==j));
		}
	}
}

void mv(int ix,int iy){
	if(ix<1||iy<1||ix>6||iy>5)return;
	combo++;
	putcom();
	score+=90;
	putsc();
	mp[ix][iy]++;
	if(mp[ix][iy]>3)mp[ix][iy]=0;
	putc(ix,iy,ix*3+1,iy*6+1,1);
	Sleep(combo>30?200:500-combo*10);
	putc(ix,iy,ix*3+1,iy*6+1,0);
	switch(mp[ix][iy]){
		case 0:{
			mv(ix-1,iy);
			break;
		}
		case 1:{
			mv(ix,iy+1);
			break;
		}
		case 2:{
			mv(ix+1,iy);
			break;
		}
		case 3:{
			mv(ix,iy-1);
			break;
		}
	}
}

int main(){
	freopen("Record.dat","r",stdin);
	cin>>high;
	putsc();
	putmp();
	while(1){
		if(step>=15){
			freopen("Record.dat","w",stdout);
			cout<<score;
			return 0;
		}
		combo=0;
		putcom();
		putmp();
		putsc();
		switch(getch()){
			case 224:{
				switch(getch()){
					case 72:{
						nx--;
						if(nx<1)nx=6;
						break;
					}
					case 80:{
						nx++;
						if(nx>6)nx=1;
						break;
					}
					case 75:{
						ny--;
						if(ny<1)ny=5;
						break;
					}
					case 77:{
						ny++;
						if(ny>5)ny=1;
						break;
					}
				}
				break;
			}
			case 32:{
				step++;
				mv(nx,ny);
				break;
			}
		}
	}
}
