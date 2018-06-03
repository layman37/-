#include<Windows.h>
//������
class flyer
{
public:
	virtual void erase(int, int) = 0;//Ĩȥͼ��
	virtual void draw(COORD) = 0;//����ͼ��
};
//������
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
	void moveCannon(char x);//�ƶ�����ͼ��
	void erase(int, int);
	void draw(COORD);
};
//�ڵ���
class shell : protected flyer
{
public:
	COORD pos[30];
	shell();
	void moveShell();//�ƶ��ڵ�ͼ��
	void erase(int, int);
	void erasethis(COORD a);
	void draw(COORD a);
};
//��ʯ��
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
	Meteor(Meteor& a);//�������캯��
	Meteor operator +(const int&);//���������
	Meteor operator =(const Meteor&);
	void moveMeteor();//�ƶ���ʯͼ��
	void erase(int, int);
	void draw(COORD);
};
//��Ϸ������
class game
{
protected:
	int meteor_amount;//��ʯ����
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