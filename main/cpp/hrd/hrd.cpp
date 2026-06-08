#include<bits/stdc++.h>
#include<Windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#define random(a,b) (rand()%(b-a+1)+a)
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;

bitset<30>down;
bitset<30>pre;
int mp[36]={99,99,99,99,99,99,99,1,2,3,4,99,99,5,6,7,8,99,99,9,10,11,12,99,99,13,14,15,0,99,99,99,99,99,99,99};
int mp2[36]={99,99,99,99,99,99,99,1,2,3,4,99,99,5,6,7,8,99,99,9,10,11,12,99,99,13,14,15,0,99,99,99,99,99,99,99};
bool cop(int xx[],int yy[]){
	for(int q=0;q<36;q++)
	{
		if(xx[q]!=yy[q])
		return false;
	}
	return true;
}
int main(){
	srand((unsigned)time(NULL));
	int k=1,sp=0,spx=100000,j_color;
	char c_color;
	int ch1=0,ch2=0,jj=1;
	cout<<"数~~字~~华~~容~~道~~（超级劣质版/省流版）"<<"请按任意键开始游戏";
	int cc,dd;
	cc=getch();
	system("cls");
	cout<<"正式开始游戏前，请选择一个心仪的颜色吧！"<<endl<<"(提示，输入一个字母（a~f)，哪个对应哪个自己猜，选好后输入'x'即可继续下一步)"<<endl;
    j_color=1;
    while(j_color==1) {
        cin>>c_color;
        switch(c_color) {
            case 'a':
                system("color a");
                break;
            case 'b':
                system("color b");
                break;
            case 'c':
                system("color c");
                break;
            case 'd':
                system("color d");
                break;
            case 'e':
                system("color e");
                break;
            case 'f':
                system("color f");
                break;
            case 'x':
                j_color=0;
                break;
            default:
                cout<<"“别瞎输啊喂！”"<<endl;
        }
    }
	while(k)
	{
		if(jj==1)
		{
		for(int ddd=0;ddd<1000;ddd++){
		switch (random(1,4))
             {
             case 1: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&l>6&&mp[l-6]==0)
			 	{
			 	swap(mp[l],mp[l-6]);
			 	break;}
			 }break;
             case 2: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&l<30&&mp[l+6]==0){
			 	swap(mp[l],mp[l+6]);
			 	break;}
			 }break;
             case 3: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&l%6>0&&mp[l-1]==0)
			 	{
			 	swap(mp[l],mp[l-1]);break;}
			 }break;
             case 4: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&mp[l+1]==0){
			 	swap(mp[l],mp[l+1]);break;}
			 }break;
		}
	}
	jj=0;
	}
		system("cls");
	for(int i=0;i<36;i++)
	{
		if(mp[i]==99)
		cout<<"□";
		else if(mp[i]<10&&mp[i]!=0)
		cout<<mp[i]<<" ";
		else if(mp[i]!=0)
		{
			char c=mp[i]+55;
		cout<<c<<" ";
		}
		else
		cout<<"  ";
		if(i%6==5)
		cout<<endl;
	}
	cout<<"当前步数: "<<sp<<endl;
	if(spx==100000)
	cout<<"历史最快：无记录！"<<endl;
	else
	cout<<"历史最快："<<spx<<endl;
	cout<<"按下方向键移动方块;按回车键结束游戏";
	if (ch1=getch())
          {
             ch2=getch();
             switch (ch2)
             {
             case 72: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&l>6&&mp[l-6]==0)
			 	{sp++;
			 	swap(mp[l],mp[l-6]);
			 	break;}
			 }break;
             case 80: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&l<30&&mp[l+6]==0){sp++;
			 	swap(mp[l],mp[l+6]);
			 	break;}
			 }break;
             case 75: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&l%6>0&&mp[l-1]==0)
			 	{sp++;
			 	swap(mp[l],mp[l-1]);break;}
			 }break;
             case 77: for(int l=0;l<36;l++)
			 {
			 	if (mp[l]!=99&&mp[l]!=0&&mp[l+1]==0){sp++;
			 	swap(mp[l],mp[l+1]);break;}
			 }break;
			 case 13:k=0;break;
             default: cout<<"未知输入？";
             Sleep(1000);
                 break;
             }
             
          }
    if(cop(mp,mp2))
    {
    	system("cls");
	for(int i=0;i<36;i++)
	{
		if(mp[i]==99)
		cout<<"□";
		else if(mp[i]<10&&mp[i]!=0)
		cout<<mp[i]<<" ";
		else if(mp[i]!=0)
		{
			char c=mp[i]+55;
		cout<<c<<" ";
		}
		else
		cout<<"  ";
		if(i%6==5)
		cout<<endl;
	}
	cout<<"恭喜过关！本局所用步数："<<sp<<endl;
	if(sp<spx)
	spx=sp;
	cout<<"历史最快："<<spx<<endl;
	if(sp<spx)
	cout<<"恭喜！打破了自己的记录！"<<endl<<"按任意键开始下一局游戏";
	else if(sp==spx)
	cout<<"创造了一个新纪录！"<<endl;
	else
    cout<<"可惜，没能打破自己的记录呢！"<<endl<<"按任意键开始下一局游戏";
	cc=getch();
	sp=0;
	jj=1;}
	}
}
