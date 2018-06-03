#include<Windows.h>
//抽象类
class flyer
{
public:
	virtual void erase(int, int) = 0;//抹去图像
	virtual void draw(COORD) = 0;//绘制图像
};
//大炮类
class Cannon : protected flyer
{
public:
	COORD pos[2];
	Cannon()
	{
		pos[0].X=24;
		pos[0].Y=24;
		pos[1].X=24;
		pos[1].Y=23;
	}
	void moveCannon(char x);//移动大炮图像
	void erase(int, int);
	void draw(COORD);
};
//炮弹类
class shell : protected flyer
{
public:
	COORD pos[30];
	shell();
	void moveShell();//移动炮弹图像
	void erase(int, int);
	void erasethis(COORD a);
	void draw(COORD a);
};
//陨石类
class Meteor : protected flyer
{
protected:
	bool turn;
	int Lboundary;
	int Rboundary;
public:
	COORD pos;
	Meteor()
	{
		pos.X=1;
		pos.Y=1;
		turn = true;
		Lboundary = 1;
		Rboundary = 16;
	}
	Meteor(int i, int j)
	{
		pos.X=i;
		pos.Y=j;
		turn = true;
	}
	Meteor(Meteor& a);//拷贝构造函数
	Meteor operator +(const int&);//重载运算符
	Meteor operator =(const Meteor&);
	void moveMeteor();//移动陨石图像
	void erase(int, int);
	void draw(COORD);
};
//游戏控制类
class game
{
protected:
	int meteor_amount;//陨石数量
public:
	int shell_flag;
	int meteor_flag;
	game()
	{
		meteor_amount = 3;
		shell_flag = meteor_flag = 0;
	}
	bool judgeGame(COORD a, COORD b, COORD c);
	void judgeMeteor(COORD S, Meteor& M);
	void fire(COORD C, shell& S);
	void opening();
	void ending(bool);
};