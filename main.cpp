#include<iostream>
using namespace std;
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include"game.h"
void hidecursor()//���ع��
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
	Play.opening();//��Ϸ��ʼ˵��
	cout <<endl<<endl<<endl<<endl<< "���������ʼ\n";
	getch();
	system("cls");
	hidecursor();//���ع��
	Bigdog.draw(Bigdog.pos[0]);
	One.draw(One.pos);
	Two.draw(Two.pos);
	Three.draw(Three.pos);
	//��Ϸ����
	while (1)
	{
		Sleep(20);
		if (_kbhit())//����м�������
		{
			char w = _getch();//����������Ϣ
			if (w == 'a' || w == 'd')
			{
				Bigdog.moveCannon(w);//���ƴ���
			}
			else if (w == 'k')
				Play.fire(Bigdog.pos[1],Shell);//����
		}
		if (Play.shell_flag == 5)
		{
			Shell.moveShell();//�����ڵ�
			Play.shell_flag = 0;
		}
		if (Play.meteor_flag ==5)
		{
			One.moveMeteor();
			Two.moveMeteor();
			Three.moveMeteor();//������ʯ
			Play.meteor_flag = 0;
		}
		for (int i = 0; i<=29; i++)
		{
			Play.judgeMeteor(Shell.pos[i], One);
			Play.judgeMeteor(Shell.pos[i], Two);
			Play.judgeMeteor(Shell.pos[i], Three);//�ж��Ƿ��е�
		}
		Play.shell_flag++;
		Play.meteor_flag++;
		if (Play.judgeGame(One.pos, Two.pos, Three.pos))
		{
			break;
		}//�ж��Ƿ�ֳ�ʤ��
	}
	system("pause");
	return 0;
}