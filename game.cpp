#include"game.h"
#include<fstream>
#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
//////*******定义坐标函数*******//////
void setpos(COORD w)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, w);
}
void setpos(int x, int y)
{
	COORD a = { x, y };
	setpos(a);
}
//////*****定义game类函数*******////////
void game::fire(COORD C, shell& S)
{
	for (int i = 0; i<=29; i++)
	{
		if (S.pos[i].Y == 23)
		{
			S.pos[i].X = C.X;
			S.pos[i].Y = 22;
			break;
		}
	}
}
void game::judgeMeteor(COORD S, Meteor& M)
{
	if (S.X == M.pos.X&&S.Y == M.pos.Y)
	{
		meteor_amount--;
		M.pos.Y = 0;
	}
}
void game::opening()
{
	fstream file;
	file.open("opening.txt", ios::in);
	if (!file)
	{
		cout << "文件打开失败！" << endl;
		exit(0);
	}
	char temp[81];
	while (!file.eof())
	{
		file.getline(temp, 81);
		if (file.fail())
			break;
		cout << temp << endl;
	}
	file.close();
}
void game::ending(bool a)
{
	if (a)
	{
		system("cls");
		setpos(23, 10);
		cout << "YOU    WIN"<<endl<<endl<<endl<<endl<<endl;
	}
	else
	{
		system("cls");
		setpos(23, 10);
		cout << "YOU    LOSE"<<endl<<endl<<endl<<endl<<endl;
	}
}
bool game::judgeGame(COORD a, COORD b, COORD c)
{
	if (meteor_amount == 0)
	{
		ending(true);
		return true;
	}
	else
	{
		if (a.Y == 23 || b.Y == 23 || c.Y == 23)
		{
			ending(false);
			return true;
		}
		else return false;
	}
}
//////*****大炮类函数***********///////////
void Cannon::moveCannon(char x)
{
	if (x == 'a')
	{
		if (pos[0].X != 1)
		{
			pos[0].X -= 4;
			pos[1].X -= 4;
			erase(pos[0].X + 4,pos[0].Y);
			erase(pos[1].X + 4,pos[1].Y);
			draw(pos[0]);
		}
	}
	if (x == 'd')
	{
		if (pos[0].X != 48)
		{
			pos[0].X += 4;
			pos[1].X += 4;
			erase(pos[0].X - 4, pos[0].Y);
			erase(pos[1].X - 4, pos[1].Y);
			draw(pos[0]);
		}
	}
}
void Cannon::draw(COORD a)
{
	setpos(a);
	cout << "U";
	setpos(a.X, a.Y-1);
	cout << "|";
}
void Cannon::erase(int i, int j)
{
	COORD a = { i, j };
	setpos(a);
	cout << " ";
}
/////*****炮弹类函数******/////////
shell::shell()
{
	for (int i = 0;i<=29; i++)
	{
		pos[i].X = 1;
		pos[i].Y = 23;
	}
}
void shell::moveShell()
{
	for (int i = 0;i<=29 ;i++)
	{
		if (pos[i].Y != 23)
		{
			if (pos[i].Y != 1)
			{
				pos[i].Y -= 1;
				erase(pos[i].X, pos[i].Y + 1);
				draw(pos[i]);
			}
			else
			{
				erasethis(pos[i]);
				pos[i].Y = 23;
			}
		}
	}
}
void shell::erasethis(COORD a)
{
	setpos(a);
	cout << " ";
}
void shell::erase(int x, int y)
{
	COORD a = { x, y };
	setpos(a);
	cout << " ";
}
void shell::draw(COORD a)
{
	setpos(a);
	cout << "@";
}
//////////*******陨石类*******///////////
Meteor::Meteor(Meteor& right)
{
	pos = right.pos;
	turn = right.turn;
	Lboundary = right.Lboundary;
	Rboundary = right.Rboundary;
}
Meteor Meteor::operator+(const int&a)
{
	Meteor temp;
	temp.Lboundary = Lboundary+a;
	temp.Rboundary = Rboundary+a;
	temp.pos.X = pos.X+a;
	return temp;
}
Meteor Meteor::operator =(const Meteor& right)
{
	Lboundary = right.Lboundary;
	Rboundary = right.Rboundary;
	pos.X = right.pos.X;
	return *this;
}
void Meteor::moveMeteor()
{
	if (pos.Y != 0)
	{
		if (pos.X == Lboundary)turn = false;
		if (pos.X == Rboundary)turn = true;
		if (turn)
		{
			pos.X -= 1;
			pos.Y += 1;
			erase(pos.X + 1, pos.Y - 1);
			draw(pos);
		}
		else
		{
			pos.X += 1;
			pos.Y += 1;
			erase(pos.X - 1, pos.Y - 1);
			draw(pos);
		}
	}
}
void Meteor::draw(COORD a)
{
	setpos(a);
	cout << "U";
}
void Meteor::erase(int x, int y)
{
	COORD a = { x, y };
	setpos(a);
	cout << " ";
}