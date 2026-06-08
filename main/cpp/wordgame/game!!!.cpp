#include<Windows.h>//V0.9.45不太究极内测版
#include<bits/stdc++.h>
#include<string>
#include<cstdlib>
#include<ctime>
#define random(a,b) (rand()%(b-a+1)+a)
int ban;
//版本修改日志：
//V0.1.00更新：新增地图系统（暂时没用）；新增一键通关功能；
//V0.2.00更新：新增性别系统；
//V0.2.10:修复了一些小bug；地图投入使用；
//V0.3.00：更新：新增基础技能系统；
//V0.3.10:可以在商店购买技能了；
//V0.4.00：更新：新增一键遗忘技能功能；
//V0.4.10：修复了遗忘技能不清空属性的bug；
//V0.5.00:更新：优化技能学习结构；
//V0.5.20:现在属性面板会显示基础值和技能加成了；
//V0.5.30:地图显示优化；
//V0.5.40:技能增加，学习技能时间减少；
//V0.5.50:修复了技能栏显示bug；
//V0.6.00:更新：新增暴击效果；
//V0.6.10:再次优化技能学习时间，新增遗忘技能确认开关；
//V0.7.00：更新：怪物属性及成长值确认（就快上线啦！！！；
//V0.8.00：更新：战斗系统上线！！(目前只能逃跑和自杀；
//V0.8.10：修复了战斗时间无限循环的bug；
//V0.8.20：可以在战斗时战斗了（笑；
//V0.8.30：修复了伤害与实际不符的bug和伤害叠加的bug；
//V0.8.40：优化战斗结构，优化等级加成；
//V0.9.00：更新：关卡推进效果加入；
//V0.9.10：通关条件加入；
//V0.9.20：暴击可以实现了；
//V0.9.30：新增开发者模式；
//V0.9.35：修改龙闪效果，修复了只能触发一次的bug；
//V0.9.45：修复了技能错位bug，修复了逃跑胜利bug；
//V0.9.50：龙闪削弱； 
using namespace std;
int j_shop=0,j_color=0,j_gift=0,j_c2=0,j_map=0,j_sex,j_skill=0,j_sk,j_sk2,j_guan,m_level,j_battle,j_huihe=1,f_battle,zisha,longshan=1;//各种计数器
                                                //技能栏计数器、技能学习界面开关
int j_win,suiji1,suiji2;
int n_d_m=0,n_d_p=0;
int e_Hp,e_Mp,e_Ak,e_De,e_De2;
double e_Cl,e_Bat,e_Cl_e;//额外属性（对应基本属性）指可以变动的属性(现在专指技能了！）
int da_mage_m=0,hup_m=0,da_mage_p=0,hup_p=0,s_Mp;//核心属性！
int e_sk[16];
int m_ap[20]= {1,0,0,0,0,0,0,0,0,0,
               1,0,0,0,0,0,0,0,0,0
              };
int sk_2=0,sk_3=0;
int cHp,cMp,cAk,cDe,cCl,cBat,cCl_e;
int cMHp,cMMp,cMAk,cMDe,cMCl,cMBat,cMMoney,cMCl_e;
class AAA {
    public:
        int Hp;//生命值（确信
        int Mp;//魔法值（膜法
        int Ak;//攻击力（俺有很多AK
        int De;//防御力（因为太怕痛……
        double Cl;//玄学暴击
        double Bat;//吸血率
        int Money;//rt
        int sex;//性别
        int skill[10]= {0}; //技能栏
        float Cl_e;//暴击效果
        AAA() {
            Hp=100;
            Mp=100;
            Ak=20;
            De=5;
            Cl=0.00;
            Bat=0.00;
            Money=10;
            sex=0;
            Cl_e=2.0;
        }
};
class Monster {
    public:
        int MHp;//生命值（确信
        int MMp;//魔法值（膜法
        int MAk;//攻击力（俺有很多AK
        int MDe;//防御力（因为太怕痛……
        double MCl;//玄学暴击
        double MBat;//吸血率
        float MCl_e;//暴击效果(copy真爽
        int MMoney;//指怪物掉落金钱
        Monster() {
            MHp=80;
            MMp=50;
            MAk=14;
            MDe=8;
            MCl=0.00;
            MBat=0.00;
            MMoney=20;
            MCl_e=2.0;
        }
};
AAA p;
Monster mr;
class Skill {
    public:
        string sk_[15];//技能名称栏
        Skill(){
        sk_[0]="暂无技能！";//技能名称定义
        sk_[1]="【基本】精准:提升10点攻击力和2.5%暴击率";//目前设想技能分五个等级：基本、高级、秘传、宗师、神话，等级越高越dio；
        sk_[2]="【基本】定力:战斗中每回合回复5%最大生命值";
        sk_[3]="【宗师】渴血:暴击率降低25%,暴击伤害降低50%,但暴击会获得全额吸血效果";
        sk_[4]="【神话】天翔龙闪:(主动技能:消耗100魔法:每场战斗限一次)造成15次基于敌人最大生命值的伤害（可暴击）";
        sk_[5]="开发者模式已学会全技能";
        sk_[6]="【高级】鹰眼:暴击率提升20%，暴击效果提升25%";
        sk_[7]="【秘传】暴乱:每第二回合的攻击必定暴击";
        sk_[8]="【神话】无尽之锋:暴击伤害改为500%";
        sk_[9];
        sk_[10];
        sk_[11];
        sk_[12];
        }
};
void skill_learn(int skill_i){//技能学习函数
    j_sk2=1;
    system("cls");
    char c_sk;
    while(j_sk2){
    printf("学习中。 ");
    for(int iii=0;iii<10;iii++){
    Sleep(130);
    printf("。 ");}
    cout<<endl;
    printf("学习成功！\n");
    Sleep(1500);
    switch(skill_i){
        case 1:
            system("cls");
            p.skill[j_skill]=1;
            printf("学会了一个新的基本技能！\n");
            e_Ak+=10;
            e_Cl+=0.025;
            j_sk++;
            break;
        case 3:
            system("cls");
            p.skill[j_skill]=3;
            printf("学会了一个新的宗师技能！\n");
            e_Cl-=0.25;
            e_Cl_e-=0.5;
            e_sk[3]=1;
            j_sk++;
            break;
        case 4:
            system("cls");
            p.skill[j_skill]=4;
            printf("学会了一个新的神话技能！\n");
            e_sk[4]=1;
            j_sk++;
            break;
        case 6:
        	system("cls");
        	p.skill[j_skill]=6;
        	printf("学会了一个新的高级技能！\n");
        	e_sk[6]=1;
			e_Cl+=0.2;
			e_Cl_e+=0.25;
        	j_sk++;
        	break;
        case 7:
        	system("cls");
        	p.skill[j_skill]=7;
        	printf("学会了一个新的秘传技能！\n");
        	e_sk[7]=1;
        	j_sk++;
        	break;
    }
    j_skill++;
    printf("*按任意键返回上一级\n");
    cin>>c_sk;
    system("cls");
    j_sk2=0;
    }
}
void Battle(){
	j_win=0;
    j_huihe=1;
    f_battle=1;
    s_Mp=0;
    da_mage_m=da_mage_p=0;
    cHp=p.Hp+e_Hp,cMp=p.Mp+e_Mp,cAk=p.Ak+e_Ak,cDe=p.De+e_De,cCl=p.Cl+e_Cl,cBat=p.Bat+e_Bat;
    cMHp=mr.MHp,cMAk=mr.MAk,cMDe=mr.MDe,cMCl=mr.MCl;
    printf("您理所应当顺理成章地遭遇了与怪物的战斗！！\n");
    if(m_level<9) 
    printf("怪物等级 = %d\n",m_level+1);
    else
    printf("Boss等级 = Max!");
    Sleep(900);
    for(int mmm=0;mmm<=100;mmm++){
	printf("\r");
    cout<<"加载中";
    printf("%d%%",mmm);
    Sleep(5);}
    printf("正在开始战斗……\n");
    Sleep(1000);
    while(p.Hp+e_Hp-da_mage_m>0&&mr.MHp-da_mage_p>0&&f_battle){
    mr.MHp=80+24*m_level*m_level;
    mr.MMp=50+11*m_level;
    mr.MAk=14+3*m_level*m_level*1.3;
    mr.MDe=8+12*m_level*1.2;
    mr.MCl=0.00+0.04*m_level*m_level;
    mr.MBat=0.00+0.004*m_level*m_level;
    mr.MMoney=20+35*m_level*m_level;
    mr.MCl_e=2.0;
    system("cls");
    printf("回合  %d\n",j_huihe);
    printf("我方属性                  敌方属性\n");
    printf("生命值%d                  生命值%d\n",p.Hp+e_Hp-da_mage_m,mr.MHp-da_mage_p);
    printf("魔法值%d                  攻击力%d\n",p.Mp+e_Mp-s_Mp,mr.MAk);
    printf("攻击力%d                   防御力%d\n",p.Ak+e_Ak,mr.MDe);
    printf("防御力%d                    暴击率%0.1f%%\n",p.De+e_De,mr.MCl*100);
    printf("暴击率%0.1f%%                吸血值%0.2f%%\n",(p.Cl+e_Cl)*100,mr.MBat*100);
    printf("吸血值%0.2f%%\n",(p.Bat+e_Bat)*100);
    printf("输入1/2/3/4/5/6/7以攻击/防御/技能/逃跑/自杀/强化/闪避\n");
    char v_b;
    cin>>v_b;
    switch(v_b){
        case '1':
            n_d_m=da_mage_m,n_d_p=da_mage_p;
             suiji1=random(0,100);
            suiji2=random(0,100);
            if(suiji1<=p.Cl*100||e_sk[7]&&j_huihe%2==0){
            da_mage_m+=mr.MAk*(100-p.De)*1.0/100,da_mage_p+=(p.Ak+e_Ak)*(p.Cl_e+e_Cl_e)*(100-mr.MDe)*1.0/100;
            printf("敌方造成了%d点伤害！我方暴击造成了%d点伤害！\n",da_mage_m-n_d_m,da_mage_p-n_d_p);
            Sleep(1500);
            if(e_sk[3]){
                printf("触发技能【渴血】的效果！我方吸血回复了%d点生命！\n",da_mage_p-n_d_p);
                p.Hp+=da_mage_p-n_d_p;
                Sleep(1500);
            }
            }
            else{
            da_mage_m+=mr.MAk*(100-p.De)*1.0/100,da_mage_p+=(p.Ak+e_Ak)*(100-mr.MDe)*1.0/100;
            printf("敌方造成了%d点伤害！我方造成了%d点伤害！\n",da_mage_m-n_d_m,da_mage_p-n_d_p);
            Sleep(1500);}
            break;
        case '2':
            e_De2+=p.De;
            n_d_m=da_mage_m;
            da_mage_m+=mr.MAk-p.De-e_De2;
            printf("我方在本回合内提升了%d点防御力！敌方造成了%d点伤害！\n",e_De2,da_mage_m-n_d_m);
            e_De2=0;
            Sleep(2500);
            break;
        case '3':
			if(e_sk[4]&&longshan&&p.Mp+e_Mp-s_Mp>=100)
            {
            	s_Mp+=100;	
                n_d_m=da_mage_m,n_d_p=da_mage_p;
                longshan=0;
                printf("发动技能【龙闪】！\n");
                Sleep(1500);
                system("cls");

                for(int longl=0;longl<15;longl++){
                	suiji1=random(0,100);
                    n_d_m=da_mage_m,n_d_p=da_mage_p;
                if(suiji1<=(p.Cl+e_Cl)*100||e_sk[7]&&j_huihe%2==0){
                da_mage_p+=(((p.Ak+e_Ak)/2+(mr.MHp-da_mage_p)/100+1)*p.Cl_e)*(100-mr.MDe)*1.0/100;
                printf("【龙闪】暴击造成了%d点伤害！\n",da_mage_p-n_d_p);
                Sleep(0);
				if(e_sk[3]){
                printf("触发技能【渴血】的效果！我方吸血回复了%d点生命！\n",da_mage_p-n_d_p);
                p.Hp+=da_mage_p-n_d_p;
                Sleep(150);}}
                else{
                da_mage_p+=((p.Ak+e_Ak)/2+(mr.MHp-da_mage_p)/100+1)*(100-mr.MDe)*1.0/100;
                printf("【龙闪】造成了%d点伤害！\n",da_mage_p-n_d_p);
                Sleep(25);}}
                da_mage_m+=mr.MAk*(100-p.De)*1.0/100;
                printf("敌方造成了%d点伤害！\n",da_mage_m-n_d_m);
                Sleep(2500);}    
            else {
			printf("您未学习主动技能或魔法不足！\n");
			Sleep(1000);}
			break; 
        case '4':
        printf("逃跑了……\n");
        Sleep(1500);
        f_battle=0;
        break;
        case '5':
        system("cls");
        printf("您已自杀\n");
        f_battle=0;
        zisha=1;
}
if(p.Hp+e_Hp-da_mage_m<0)
zisha=1;
else if(mr.MHp-da_mage_p<0){
j_win=1;printf("怪物生命值：%d\n怪物已死亡！\n",mr.MHp-da_mage_p);}
j_huihe++;
}
}
Skill s_k;
int main() {
    srand((unsigned)time(NULL));
    system("color f");
    cout<<"正式开始游戏前，请选择一个心仪的颜色吧！"<<endl<<"(提示，输入一个字母（a~f)，哪个对应哪个自己猜，选好后输入'x'即可继续下一步)"<<endl;
    char a_m,a_shop,c_color,a_map;
    j_color=1;
    while(j_color==1) {
        cin>>c_color;
        switch(c_color) {
            case 'a':
                system("color a");
                printf("哇，居然变——绿啦！");
                j_c2++;
                break;
            case 'b':
                system("color b");
                printf("哇，居然变——蓝啦！");
                j_c2++;
                break;
            case 'c':
                system("color c");
                printf("哇，居然变——红啦！");
                j_c2++;
                break;
            case 'd':
                system("color d");
                printf("哇，居然变——紫啦！");
                j_c2++;
                break;
            case 'e':
                system("color e");
                printf("哇，居然变——黄啦！");
                j_c2++;
                break;
            case 'f':
                system("color f");
                if(j_c2==0)
                    printf("哇，居然——没变色！");
                else
                    printf("哇，居然——变回去啦！");
                break;
            case 'x':
                j_color=0;
                break;
            default:
                cout<<"“别瞎输啊喂！”"<<endl;
        }
    }
    int sex_i;
    system("cls");
    printf("请输入您的性别\n1————♂\n2————♀\n");
    scanf("%d",&sex_i);
    switch(sex_i) {
        case 1:
            p.sex=1;
            break;
        case 2:
            p.sex=2;
            break;
        default:
            system("cls");
            cout<<"未知性别QAQ"<<endl;
            Sleep(1300);
            p.sex=3;
            break;
    }
    system("cls");
    cout<<endl;//总是在上方留出一行，作为信息通知栏
    while(1) {
        if(j_guan==10){
                system("cls");
                cout<<"您已经通关游戏啦！！快去和小伙伴们炫耀吧！！";
                return 0;}
        if (p.Cl+e_Cl<0.00)
        p.Cl=0,e_Cl=0;
        cout<<"主菜单"<<endl;
        cout<<"输入1/2以查看属性面板/技能面板(输入'd'一键遗忘所有技能(无法撤回！慎重考虑！))"<<endl<<"输入's'前往商店！输入'x'以退出"<<endl;
        printf("输入'f以领取每日礼物！ （其实可以无限领取……）\n");
        printf("输入'9'开始战斗！！！");
        printf("输入'o'以领取新手礼包！ （其实是空的）\n");
        printf("输入't'以直接通关游戏！！！\n");
        cin>>a_m;
        switch(a_m) {
            case '1':
                system("cls");
                printf("生命值： %d  (基础值%d+技能加成%d)\n",(p.Hp+e_Hp),p.Hp,e_Hp);
                printf("魔法值： %d  (基础值%d+技能加成%d)\n",p.Mp+e_Mp,p.Mp,e_Mp);
                printf("攻击力： %d  (基础值%d+技能加成%d)\n",p.Ak+e_Ak,p.Ak,e_Ak);
                printf("防御力： %d  (基础值%d+技能加成%d)\n",p.De+e_De,p.De,e_De);
                if(p.Cl+e_Cl>0.00) {
                    printf("暴击率:  %.2f%%  （基础值%.2f%%+技能加成%.2f%%)\n",(p.Cl+e_Cl)*100,p.Cl*100,e_Cl*100);
                } else {
                    cout<<"暴击率 （暴击未启用） "<<p.Cl*100<<"%"<<endl;
                }
                printf("吸血率:  %.2f%% （基础值%.2f%%+技能加成%.2f%%)\n",(p.Bat+e_Bat)*100,p.Bat*100,e_Bat*100);
                printf("暴击效果(默认为双倍伤害)： %.0f%%\n",(p.Cl_e+e_Cl_e)*100);
                printf("当前金钱 ￥%d\n",p.Money);
                break;
            case '2':
                system("cls");
                cout<<"当前技能栏："<<endl;
                for(int u=0;u<10;u++)
                {

                    cout<<"["<<u+1<<"]:";
                    cout<<s_k.sk_[p.skill[u]];

                    cout<<";"<<endl;}

                break;
            case 'f':
                p.Money+=100;
                system("cls");
                printf("获得了今日的奖励：100金币！！感谢作者的大恩大德吧！\n");
                printf("当前金钱 ￥%d\n",p.Money);
                break;
            case 'd':
                system("cls");
                printf("确定吗？一经遗忘无法回退!\n坚持'1'/反悔'2'\n");
                char d_re;
                cin>>d_re;
                if (d_re=='1'){
                system("cls");
                printf("已遗忘所有技能，可以学习新技能了！\n");
                e_Hp=e_Mp=e_Ak=e_De=e_Cl=e_Bat=e_Cl_e=j_skill=0;
				for(int kkk=0;kkk<=15;kkk++)
				e_sk[kkk]=0;
                for(int bbb=0;bbb<10;bbb++){
                    p.skill[bbb]=0;
                }}
                else{
                system("cls");
                printf("就知道你肯定会反悔！\n");
                }
                break;
            case '8':
                break;
            case '9':                                           //map_begin
                j_map=1;
                while(j_map) {
                    system("cls");
                printf("当前位置：");
                    if(j_guan==0)
                        printf("新手村（只有一个人怎么算村啊？？）");
                    else if(j_guan==9)
                        printf("最终关");
                    else if(j_guan==10)
                        {
                        printf("已通关！");
                        break;}
                    else
                        printf("第 %d 关",j_guan+1);
                cout<<endl;
                for(int i=0; i<10; i++) {
                    if (m_ap[i]==1&&p.sex==1)
                        printf("   ♂   ");
                    else if(m_ap[i]==1&&p.sex==2)
                        printf("   ♀   ");
                    else if(m_ap[i]==1&&p.sex==3)
                        printf("    §  ");
                    else if(i!=9)
                        printf("   ◎   ");
                    else
                        printf("   卐   ");
                }
                for(int i=10; i<20; i++) {
                    if (m_ap[i]==1)
                        printf("|■■■|");
                    else
                        printf("|□□□|");
                }
                cout<<endl;
                printf("♂/♀/§：您当前的位置\n◎：普通关卡\n卐：最终BOSS关卡\n|■■■|:已探索过的关卡\n|□□□|未探索过的关卡\n");
                    cout<<"输入'x'以返回主菜单 'n'挺近下一关！"<<endl;
                    cin>>a_map;
                    switch(a_map) {
                        case 'x':
                            system("cls");
                            j_map=0;
                            break;
                        case 'n':
                            system("cls");
                            longshan=1;
                            Battle();
                            if(zisha)
                            {
                                system("color c");
                                printf("You are DEAD");
                                return 0;
                            }
                            else if(j_win){
                            printf("赢得了胜利！获得金币￥%d!\n",mr.MMoney);
                            p.Money+=mr.MMoney;
                            printf("当前金币：￥%d\n",p.Money);
                            m_ap[j_guan]=0;
                            j_guan++;
                            m_ap[j_guan]=1;
                            m_ap[j_guan+10]=1;
                            Sleep(2400);
                            m_level++;}
                            break;
                    }
                }
                break;                                                  //map_end
            case 'o':
                if(j_gift==0) {
                    system("cls");
                    cout<<"为什么不信我？你看着有东西吗？"<<endl;
                    j_gift++;
                } else {
                    system("cls");
                    cout<<"您已经领取过啦！"<<endl;
                }
                break;
            case 't':
                system("cls");
                cout<<"您已经通关游戏啦！！快去和小伙伴们炫耀吧！！";
                return 0;
            case 'k':
                system("cls");
                printf("已开启开发者选项\n");
                p.Hp=99999;
                p.Mp=99999;
                p.Ak=99999;
                p.De=99999;
                p.Cl=1.00;
                p.Bat=1.00;
                p.Money=999999;
                p.Cl_e=10.0;
                j_sk=10;
                for(int lll=0;lll<10;lll++){
                e_sk[lll]=1;
				p.skill[lll]=5;}
                break;
            case 's':
                j_shop=1;
                system("cls");
                cout<<endl;
                while(j_shop==1) {
                    cout<<"当前金币 ￥"<<p.Money<<endl;
                    printf("输入商品前[]内标码以购买\n商品列表：\n[1]变壮（提升攻击力）……[￥10]\n[2]变肉（提升生命值）……[￥10]\n[3]冥想（提升魔法值）……[￥10]\n[4]看蝙蝠侠（提升吸血率）……[￥10]\n[5]学习基础技能（一个神秘的基本等级技能！）……[￥25]\n[6]学习高级技能（一个神秘的高级等级技能！）……[￥50]\n[7]学习秘传技能（一个神秘的秘传等级技能！）……[￥90]\n[8]学习宗师技能（一个神秘的宗师等级技能！）……[￥145]\n[9]一键开挂（一个神秘的神话等级技能！）……[￥300]\ntips：输入'x'返回主菜单\n");
                    cin>>a_shop;
                    switch(a_shop) {
                        case '1':
                            if(p.Money<10) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            p.Ak+=5;
                            p.Money-=10;
                            system("cls");
                            printf("变厉害了！(攻击力上升了5！)\n");
                            printf("当前该数值为：%d\n",p.Ak);
                            break;
                        case '2':
                            if(p.Money<10) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            p.Hp+=20;
                            p.Money-=10;
                            system("cls");
                            printf("变厉害了！(生命值上升了20！)\n");
                            printf("当前该数值为：%d\n",p.Hp);
                            break;
                        case '3':
                            if(p.Money<10) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            p.Mp+=10;
                            p.Money-=10;
                            system("cls");
                            printf("变厉害了！(魔法值上升了10！)\n");
                            printf("当前该数值为：%d\n",p.Mp);
                            break;
                        case '4':
                            if(p.Money<10) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            p.Bat+=0.02;
                            p.Money-=10;
                            system("cls");
                            printf("变厉害了！(吸血率上升了2%！)\n");
                            printf("当前该数值为：%.2f%%\n",p.Bat);
                            break;
                        case '5':
                            if(p.Money<25) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            if(j_sk<=9){
                            p.Money-=25;
                            skill_learn(1);
                            }
                            else{
                            system("cls");
                            printf("技能槽已满！\n");}
                            break;
                        case '7':
                            if(p.Money<90) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            if(j_sk<=9){
                            p.Money-=90;
                            skill_learn(7);
                            }
                            else{
                            system("cls");
                            printf("技能槽已满！\n");}
                            break;
                        case '6':
                            if(p.Money<50) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            if(j_sk<=9){
                            p.Money-=50;
                            skill_learn(6);
                            }
                            else{
                            system("cls");
                            printf("技能槽已满！\n");}
                            break;
                        case '8':
                            if(p.Money<145) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            if(j_sk<=9){
                            p.Money-=145;
                            skill_learn(3);
                            }
                            else{
                            system("cls");
                            printf("技能槽已满！\n");}
                            break;
                        case '9':
                            if(p.Money<300) {
                                system("cls");
                                printf("“穷光蛋，滚！”\n");
                                continue;
                            }
                            if(j_sk<=9){
                            p.Money-=300;
                            skill_learn(4);
                            }
                            else{
                            system("cls");
                            printf("技能槽已满！\n");}
                            break;
                        case 'x':
                            system("cls");
                            printf("“穷光蛋，滚！”\n");
                            j_shop=0;
                            break;
                        default:
                            system("cls");
                            cout<<"“别瞎输啊喂！”"<<endl;
                    }
                }
                break;
            case 'x':
                system("cls");
                cout<<"“爱玩不玩，滚！”";
                return 0;
            default:
                system("cls");
                cout<<"“别瞎输啊喂！”"<<endl;
        }
    }
}
