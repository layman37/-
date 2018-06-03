#include<iostream>
using namespace std;
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include"game.h"
void hidecursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
int main()
{
	game Play;
	Cannon Bigdog;
	shell Shell;
	Meteor One;
	Meteor Two = One, Three = One;
	Two = One + 16;
	Three = Two + 16; 
	Play.opening();//游戏开始说明
	cout <<endl<<endl<<endl<<endl<< "按任意键开始\n";
	getch();
	system("cls");
	hidecursor();//隐藏光标
	Bigdog.draw(Bigdog.pos[0]);
	One.draw(One.pos);
	Two.draw(Two.pos);
	Three.draw(Three.pos);
	//游戏过程
	while (1)
	{
		Sleep(20);
		if (_kbhit())//如果有键盘输入
		{
			char w = _getch();//接收输入信息
			if (w == 'a' || w == 'd')
			{
				Bigdog.moveCannon(w);//控制大炮
			}
			else if (w == 'k')
				Play.fire(Bigdog.pos[1],Shell);//开火
		}
		if (Play.shell_flag == 5)
		{
			Shell.moveShell();//控制炮弹
			Play.shell_flag = 0;
		}
		if (Play.meteor_flag ==5)
		{
			One.moveMeteor();
			Two.moveMeteor();
			Three.moveMeteor();//控制陨石
			Play.meteor_flag = 0;
		}
		for (int i = 0; i<=29; i++)
		{
			Play.judgeMeteor(Shell.pos[i], One);
			Play.judgeMeteor(Shell.pos[i], Two);
			Play.judgeMeteor(Shell.pos[i], Three);//判断是否中弹
		}
		Play.shell_flag++;
		Play.meteor_flag++;
		if (Play.judgeGame(One.pos, Two.pos, Three.pos))
		{
			break;
		}//判断是否分出胜负
	}
	system("pause");
	return 0;
}