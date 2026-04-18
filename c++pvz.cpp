#include <cmath>
#include <iostream>
#include <graphics.h>
#include <time.h>
#define FILLRECTANGLE(A,B,C,D) fillrectangle(int(100+(A) + j * 100), int(i * 100 + 200+(B)), int(100+(C) + j * 100),int( i * 100 + 200+(D)))
#define FILLCIRCLE(A,B,R) fillcircle(int(100+(A) + j * 100), int(i * 100 + 200+B), R)
#define RANGE(A,X,Y) (((A)>=(X))&&((A)<=(Y)))
const int MAX = 200; const int MAXB = 200;
const int SUNSHINEDOWN = 250;	 //阳光自然落下间隔
const int SUNSHINE = 50;		 //初始阳光
const int SUNSHINEGENERATE = 700;//阳光生产间隔
const int INIENEMYTICK = 6000;
const int attackfrequency = 80;
int cd[14] =			   { 50   ,50  ,50   ,50  ,250  ,250  ,1500 ,1200 ,1800 ,1500 ,1000 ,600  ,250 ,3000 };
const int maxcd[14] =	   { 250  ,250 ,1200 ,1500,250  ,250  ,1500 ,1200 ,1800 ,1500 ,1000 ,600  ,250 ,3000 };
const int cost[14] =	   { 100  ,50  ,50   ,25  ,175  ,150  ,100  ,125  ,225  ,125  ,450  ,175  ,50  ,150  };
const char scost[14][10] = { "100","50","50" ,"25","175","150","100","125","225","125","450","175","50","150" };
const char sname[14][30] = { "豌豆射手","向日葵","坚果","土豆雷","寒冰射手","火龙草","飓风甘蓝","南瓜保护罩","樱桃炸弹","高坚果","机枪射手","火炬树桩","大蒜","寒冰菇" };
const int plantmhp[14] = { 200,200,3000,200 ,200,200,99999,4000,99999,8000,200,200  ,25  ,99999 };
const int enemymaxspeed[10] = { 1,1,1,1,3,1 };
const int enemymaxhp[10] = { 200,600,1700,4000,400,3200 };
ExMessage msg;
int enemytick ;
unsigned char ch = msg.vkcode;
int guangbiao, gametime, enemyindex, bulletindex, chooseplant, sunshine;
class enemy;
class block;
class bullet;
class block
{
public:
	int isplanted;
	int planttype;
	int hp;
	int time;
	int row;
	int line;
	int isprotected;
	int prohp;
	void run(int type, int i, int j);
	void initialize()
	{
		isplanted = isprotected = 0;
		planttype = 0;
		prohp = hp = 0;
		time = 0;
		row = line = 0;
	}
	void plant(int type, int row_, int line_)
	{
		if (type != 8)
		{
			if (sunshine >= cost[type - 1] && cd[type - 1] <= 0 && isplanted == 0)
			{
				time = 0;
				isplanted = 1;
				row = row_;
				line = line_;
				planttype = type;
				cd[type - 1] = maxcd[type - 1];
				sunshine -= cost[type - 1];
				hp = plantmhp[type - 1];
			}
		}
		if (type == 8)
		{
			if (sunshine >= cost[type - 1] && cd[type - 1] <= 0 && isprotected == 0)
			{//放南瓜保护罩
				time = 0;
				isprotected = 1;
				row = row_;
				line = line_;
				//planttype = type;
				cd[type - 1] = maxcd[type - 1];
				sunshine -= cost[type - 1];
				prohp = plantmhp[type - 1];
			}
		}
	}
	void show(int i, int j)
	{

		{
			if (isplanted)
			{
				time++;
				enemytick++;
				switch (planttype)
				{
				case 1:
					setfillcolor(GREEN);
					FILLRECTANGLE(20, 20, 70, 80);
					FILLRECTANGLE(70, 40, 90, 60);
					enemytick++;
					break;
				case 2:
					setfillcolor(YELLOW);
					FILLRECTANGLE(20, 20, 80, 80);
					FILLRECTANGLE(70, 40, 90, 60);
					FILLRECTANGLE(10, 40, 30, 60);
					FILLRECTANGLE(40, 10, 60, 30);
					FILLRECTANGLE(40, 70, 60, 90);
					FILLRECTANGLE(1, 100 - time % SUNSHINEGENERATE * 100 / SUNSHINEGENERATE, 3, 100);
					if ((time + 1) % SUNSHINEGENERATE == 0)
					{
						sunshine += 25; enemytick += 30;
					}
					break;
				case 3:
					setfillcolor(BROWN);
					FILLRECTANGLE(30, 40, 70, 90);
					if (hp < 1500)
					{
						setfillcolor(WHITE);
						FILLRECTANGLE(40, 50, 60, 70);
					}
					break;
				case 4:
					if (time < 600)
					{
						setfillcolor(RED);
						FILLCIRCLE(50, 80, 10);
					}
					else
					{
						setfillcolor(RED);
						FILLCIRCLE(50, 60, 10);
						setfillcolor(BROWN);
						FILLRECTANGLE(10, 70, 90, 95);
					}
					break;
				case 5:
					setfillcolor(BLUE);
					FILLRECTANGLE(20, 20, 70, 80);
					setfillcolor(GREEN);
					FILLRECTANGLE(70, 40, 90, 60);
					enemytick+=2;
					break;
				case 6:
					setfillcolor(RED);
					FILLRECTANGLE(20, 20, 70, 80);
					setfillcolor(GREEN);
					FILLRECTANGLE(70, 40, 90, 60);
					enemytick+=2;
					break;
				case 7:
					setfillcolor(BLUE);
					FILLCIRCLE(50, 49, 20);
					FILLCIRCLE(50, 20, 10);
					FILLCIRCLE(72, 68, 10);
					FILLCIRCLE(28, 68, 10);
					run(planttype, i, j);
					break;
				case 9:
					setfillcolor(RED);
					FILLRECTANGLE(20, 40, 40, 60);
					FILLRECTANGLE(60, 40, 80, 60);
					setfillcolor(GREEN);
					FILLRECTANGLE(40, 30, 60, 50);
					run(planttype, i, j);
					break;
				case 10:
					setfillcolor(BROWN);
					FILLRECTANGLE(20, 20, 80, 90);
					if (hp < 4000)
					{
						setfillcolor(WHITE);
						FILLRECTANGLE(40, 40, 60, 70);
					}
					break;
				case 11:
					setfillcolor(GREEN);
					FILLRECTANGLE(20, 20, 70, 80);
					FILLRECTANGLE(70, 40, 90, 60);
					setfillcolor(BLACK);
					FILLCIRCLE(50, 50, 10);
					enemytick += 4;
					break;
				case 12:
					setfillcolor(BROWN);
					FILLRECTANGLE(30, 40, 70, 90);
					setfillcolor(RED);
					FILLCIRCLE(50, 25, 15);
					break;
				case 13:
					setfillcolor(0xEEEEEE);
					FILLRECTANGLE(20, 80, 80, 40);
					break;
				case 14:
					setfillcolor(0x880000);
					FILLRECTANGLE(20, 80, 80, 40);
					run(planttype, i, j);
					break;
				}
			}
			if (isprotected)
			{
				enemytick++;
				setfillcolor(BROWN);
				setlinecolor(BROWN);
				FILLRECTANGLE(0, 0, 10, 100);
				FILLRECTANGLE(90, 0, 100, 100);
				FILLRECTANGLE(0, 0, 100, 10);
				FILLRECTANGLE(0, 90, 100, 100);
				setlinecolor(WHITE);
			}

		}

	}
	void attacked(int enemytype);

};
class block block[7][14];
class enemy
{
public:
	int row = 0;
	int x = 1500;
	int isalive = 0;
	int enemytype = 0;
	int hp = 0;
	int speed = 1;
	int time = 0;
	int slowtime = 0;
	int stoptime = 0;

	void show()
	{
		if (isalive)
		{
			if (x < 500)
				enemytick--;
			if (x < 300)
				enemytick-=2;
			switch (enemytype)
			{
			case 1:
				setfillcolor(RED);
				if (slowtime > 0)
					setfillcolor(BLUE);
				fillcircle(x, row * 100 + 260, 25);
				enemytick--;
				break;
			case 2:
				setfillcolor(RED);
				if (slowtime > 0)
					setfillcolor(BLUE);
				fillcircle(x, row * 100 + 260, 25);
				setfillcolor(YELLOW);
				fillcircle(x, row * 100 + 225, 10);
				enemytick--;
				break;
			case 3:
				setfillcolor(RED);
				if (slowtime > 0)
					setfillcolor(BLUE);
				fillcircle(x, row * 100 + 260, 25);
				setfillcolor(WHITE);
				fillcircle(x, row * 100 + 225, 13);
				enemytick -= 2;
				break;
			case 4:
				setfillcolor(RED);
				if (slowtime > 0)
					setfillcolor(BLUE);
				fillcircle(x, row * 100 + 250, 40);
				if (hp < 2000)
				{
					fillcircle(x, row * 100 + 250, 10);
				}
				enemytick -= 4;
				break;
			case 5:
				setfillcolor(RED);
				if (slowtime > 0)
					setfillcolor(BLUE);
				fillcircle(x, row * 100 + 255, 20);
				fillcircle(x, row * 100 + 255, 15);
				enemytick -= 2;
				break;
			case 6:
				setfillcolor(RED);
				fillcircle(x, row * 100 + 260, 25);
				setfillcolor(WHITE);
				fillrectangle(x - 45, row * 100 + 230, x - 25, row * 100 + 290);
				enemytick -= 3;
				break;
			}
		}

	}
	void generate(int type, int r)
	{
		if (type > 0)
		{
			
			time = 0;
			slowtime = 0;
			enemyindex++;
			enemyindex = enemyindex % MAX;
			row = r;
			enemytype = type;
			isalive = 1;
			x = 1499;
			hp = enemymaxhp[type - 1];
		}
	}
	void move()
	{
		if (isalive)
		{
			speed = enemymaxspeed[enemytype - 1];
			time++;
			if (slowtime > 0)
				slowtime--;
			if (stoptime > 0)
				stoptime--;
			if (hp <= 0)
			{
				isalive = 0;
			}
			if (x / 100 - 1 >= 0)
			{
				if (block[row][x / 100 - 1].isplanted || block[row][x / 100 - 1].isprotected)
				{
					speed = 0;
					if (stoptime <= 0)
					{
						if (slowtime > 0 && time % 2 == 0)
						{
							block[row][x / 100 - 1].attacked(enemytype);
							goto 大蒜换行;
						}
						if (slowtime <= 0)
						{
							block[row][x / 100 - 1].attacked(enemytype);
						大蒜换行:
							if (block[row][x / 100 - 1].planttype == 13 && (!block[row][x / 100 - 1].isprotected))
							{
								if (row == 0)
									row++;
								else if (row == 6)
									row--;
								else { row += rand() % 2 * 2 - 1; }
							}
						}
					}
				}
			}
			if (stoptime <= 0)
			{
				if (time % 2 == 0)
				{
					if (enemytype == 6)
						slowtime = 0;
					if (slowtime <= 0)
						x -= speed;
					if (slowtime > 0)
						if (time % 4 == 0)
							x -= speed;
				}
			}
			if (enemytype == 2 && hp <= enemymaxhp[0])//路障掉了
				enemytype = 1;
			if (enemytype == 3 && hp <= enemymaxhp[0])//铁桶掉了
				enemytype = 1;
			if (enemytype == 6 && hp <= enemymaxhp[0])//铁门掉了
				enemytype = 1;
			if (x < 80)//游戏结束
			{
				std::cout << "游戏结束，生存时间：" << gametime << std::endl;
				system("pause");
			}
		}
	}
};
class enemy enemy[MAX];
class bullet
{
public:
	int damage;
	int row;
	int x;
	int isalive;
	int type;
	int speed;
	int lifetime;
	void move()
	{
		int line = x / 100 - 1;
		if (x >= 1500)
			isalive = 0;
		x += speed;
		if (type == 3)
		{
			lifetime--;
			if (lifetime <= 0)
			{
				isalive = 0;
			}
		}
		if (type == 1 || type == 2)
		{
			if (line >= 0 && line < 14)
			{
				if (block[row][line].planttype == 12 && block[row][line].isplanted)
				{
					type += 3;
					damage *= 2;//豌豆变火球
				}
			}
		}
	}
	void hit()
	{
		int i;
		if (isalive)
		{
			for (i = 0; i < MAX && isalive; i++)
			{
				switch (type)
				{
				case 1:
					if (enemy[i].isalive && row == enemy[i].row && RANGE(x-enemy[i].x,-7,12))
					{
						isalive = 0;
						enemy[i].hp -= damage;
					}
					break;
				case 2://冰
					if (enemy[i].isalive && row == enemy[i].row && RANGE(x - enemy[i].x, -7, 12))
					{
						isalive = 0;
						enemy[i].hp -= damage;
						if (enemy[i].slowtime < 200)
							enemy[i].slowtime = 200;
					}
					break;
				case 3://火
					if (enemy[i].isalive && abs(row - enemy[i].row) <= 1 && RANGE(x - enemy[i].x, -7, 12))
					{
						enemy[i].hp -= damage;
					}
					break;
				case 4://火球
					if (enemy[i].isalive && row == enemy[i].row && RANGE(x - enemy[i].x, -7, 12))
					{
						isalive = 0;
						enemy[i].hp -= damage;
					}
					break;
				case 5://冰火球
					if (enemy[i].isalive && row == enemy[i].row && RANGE(x - enemy[i].x, -7, 12))
					{
						isalive = 0;
						enemy[i].hp -= damage;
						if (enemy[i].slowtime < 200)
							enemy[i].slowtime = 200;
					}
					break;
				}
			}
		}
	}
	void generate(int type_, int row_, int x_)
	{
		int isgenerate[10] = { 0 }, k;
		for (k = 0; k < MAX; k++)
		{//攻击范围判定
			if (enemy[k].isalive && enemy[k].row == row_ && enemy[k].x > x_)
				isgenerate[0] = 1;
			if (enemy[k].isalive && RANGE(enemy[k].row - row_,-1,1) && RANGE(enemy[k].x -x_,0,310))
				isgenerate[1] = 1;
		}
		switch (type_)
		{
		case 1:
		case 2:
			if (isgenerate[0])
			{//产生豌豆
				speed = 15;
				damage = 20;
				bulletindex++;
				bulletindex = bulletindex % MAXB;
				isalive = 1;
				x = x_;
				row = row_;
				type = type_;
			}
			break;
		case 3:
			if (isgenerate[1])
			{
				speed = 6;
				damage = 8;
				lifetime = 50;
				bulletindex++;
				bulletindex = bulletindex % MAXB;
				isalive = 1;
				x = x_;
				row = row_;
				type = type_;
			}
			break;
		}
	}
	void show()
	{
		if (isalive)
		{
			switch (type)
			{
			case 1:
				setfillcolor(GREEN);
				fillcircle(x, row * 100 + 250, 15);
				break;
			case 2:
				setfillcolor(BLUE);
				fillcircle(x, row * 100 + 250, 15);
				break;
			case 3:
				setfillcolor(RED);
				fillrectangle(x - 3, row * 100 + 130, x + 3, row * 100 + 370);
				break;
			case 4:
				setfillcolor(GREEN);
				fillcircle(x, row * 100 + 250, 15);
				setfillcolor(RED);
				fillcircle(x, row * 100 + 250, 10);
				break;
			case 5:
				setfillcolor(BLUE);
				fillcircle(x, row * 100 + 250, 15);
				setfillcolor(RED);
				fillcircle(x, row * 100 + 250, 10);
				break;
			}
		}
	}
};
class bullet bullet[MAXB];
void block::attacked(int enemytype)
{
	int i;
	if (isprotected)
	{
		enemytick -= 1;
		switch (enemytype)
		{
		case 1:
		case 2:
		case 3:
		case 6:
			prohp -= 1;
			break;
		case 4:
			prohp -= 5;
			break;
		case 5:
			prohp -= 2;
			break;
		}
	}
	if (!isprotected && isplanted)
	{
		enemytick -= 2;
		switch (enemytype)
		{
		case 1:
		case 2:
		case 3:
		case 6:
			hp -= 1;
			break;
		case 4:
			hp -= 5;
			break;
		case 5:
			hp -= 2;
			break;
		}
	}
	if (hp <= 0 && isplanted)
	{
		enemytick -= 3000;
		planttype = isplanted = 0;
	}
	if (prohp <= 0 && isprotected)
	{
		isprotected = 0;
		enemytick -= 3000;
	}
	if (planttype == 4 && time >= 600 && isplanted)
	{//土豆雷爆炸
		hp = planttype = isplanted = 0;
		for (i = 0; i < MAX; i++)
		{
			if (enemy[i].row == row && abs(enemy[i].x - line * 100 - 150) < 60)
				enemy[i].hp -= 2000;
		}
	}
}
void block::run(int type, int i, int j)
{
	int k;
	if (type == 7)
	{//飓风甘蓝
		if (time > 80)
		{
			isplanted = planttype = hp = 0;
		}
		for (k = 0; k < MAX; k++)
		{
			if (enemy[k].row == i)
			{
				enemy[k].x += int(0.02 * (1500 - enemy[k].x));
				enemy[k].slowtime = 400;
			}
		}
	}
	if (type == 9)//樱桃爆炸
	{
		if (time > 20)
		{
			isplanted = 0;
			for (k = 0; k < MAX; k++)
			{
				if (enemy[k].isalive && abs(enemy[k].row - i) <= 1 && abs(enemy[k].x - j * 100 - 150) < 155)
				{
					enemy[k].hp -= 2000;
				}
			}
		}
	}
	if (type == 14)//寒冰菇爆炸
	{
		if (time > 40)
		{
			isplanted = 0;
			for (k = 0; k < MAX; k++)
			{
				if (enemy[k].isalive)
				{
					enemy[k].slowtime = 600;
					enemy[k].stoptime = 300;
				}
			}
		}
	}

}

void draw_map()
{
	int i, j;
	for (i = 0; i < 7; i++)
		for (j = 0; j < 14; j++)
			rectangle(100 + j * 100, i * 100 + 200, 200 + j * 100, i * 100 + 300);
	setfillcolor(BLUE);
	i = guangbiao / 14;
	j = guangbiao % 14;
	fillrectangle(100 + j * 100, i * 100 + 200, 200 + j * 100, i * 100 + 300);
	setfillcolor(YELLOW);
	fillrectangle(0, 0, gametime % SUNSHINEDOWN * 100 / SUNSHINEDOWN, 10);
	for (j = 0; j < 14; j++)
	{


		if (sunshine >= cost[j])
		{
			setfillcolor(WHITE);
			if (chooseplant == j + 1)
				setfillcolor(GREEN);
		}
		else {
			setfillcolor(RED);
			if (chooseplant == j + 1)
				setfillcolor(0x99FFFF);
		}

		setlinecolor(BLACK);
		fillrectangle(100 + j * 100, 50, 200 + j * 100, 150);
		setlinecolor(WHITE);
		float i = -1.5;
		switch (j + 1) {

		case 1:
			setfillcolor(GREEN);
			FILLRECTANGLE(20, 20, 70, 80);
			FILLRECTANGLE(70, 40, 90, 60);
			break;
		case 2:
			setfillcolor(YELLOW);
			FILLRECTANGLE(20, 20, 80, 80);
			FILLRECTANGLE(70, 40, 90, 60);
			FILLRECTANGLE(10, 40, 30, 60);
			FILLRECTANGLE(40, 10, 60, 30);
			FILLRECTANGLE(40, 70, 60, 90);
			break;
		case 3:
			setfillcolor(BROWN);
			FILLRECTANGLE(30, 40, 70, 90);
			break;
		case 4:
			setfillcolor(RED);
			FILLCIRCLE(50, 60, 10);
			setfillcolor(BROWN);
			FILLRECTANGLE(10, 70, 90, 95);
			break;
		case 5:
			setfillcolor(BLUE);
			FILLRECTANGLE(20, 20, 70, 80);
			setfillcolor(GREEN);
			FILLRECTANGLE(70, 40, 90, 60);
			break;
		case 6:
			setfillcolor(RED);
			FILLRECTANGLE(20, 20, 70, 80);
			setfillcolor(GREEN);
			FILLRECTANGLE(70, 40, 90, 60);
			break;
		case 7:
			setfillcolor(BLUE);
			FILLCIRCLE(50, 49, 20);
			FILLCIRCLE(50, 20, 10);
			FILLCIRCLE(72, 68, 10);
			FILLCIRCLE(28, 68, 10);
			break;
		case 8:
			setfillcolor(BROWN);
			setlinecolor(BROWN);
			FILLRECTANGLE(0, 0, 10, 100);
			FILLRECTANGLE(90, 0, 100, 100);
			FILLRECTANGLE(0, 0, 100, 10);
			FILLRECTANGLE(0, 90, 100, 100);
			setlinecolor(WHITE);
			break;
		case 9:
			setfillcolor(RED);
			FILLRECTANGLE(20, 40, 40, 60);
			FILLRECTANGLE(60, 40, 80, 60);
			setfillcolor(GREEN);
			FILLRECTANGLE(40, 30, 60, 50);
			break;
		case 10:
			setfillcolor(BROWN);
			FILLRECTANGLE(20, 20, 80, 90);
			break;
		case 11:
			setfillcolor(GREEN);
			FILLRECTANGLE(20, 20, 70, 80);
			FILLRECTANGLE(70, 40, 90, 60);
			setfillcolor(BLACK);
			FILLCIRCLE(50, 50, 10);
			break;
		case 12:
			setfillcolor(BROWN);
			FILLRECTANGLE(30, 40, 70, 90);
			setfillcolor(RED);
			FILLCIRCLE(50, 25, 15);
			break;
		case 13:
			setfillcolor(0xEEEEEE);
			FILLRECTANGLE(20, 80, 80, 40);
			break;
		case 14:
			setfillcolor(0x880000);
			FILLRECTANGLE(20, 80, 80, 40);
			break;
		}
		setfillcolor(BLACK);
		fillrectangle(100 + j * 100, 50, 200 + j * 100, 50 + 100 * cd[j] / maxcd[j]);
	}
	outtextxy(0, 20, _T("阳光:"));
	outtextxy(40, 20, '0' + sunshine / 1000 % 10);
	outtextxy(50, 20, '0' + sunshine / 100 % 10);
	outtextxy(60, 20, '0' + sunshine / 10 % 10);
	outtextxy(70, 20, '0' + sunshine % 10);
	outtextxy(0, 50, _T("时间:"));
	outtextxy(40, 50, '0' + gametime / 10000 % 10);
	outtextxy(50, 50, '0' + gametime / 1000 % 10);
	outtextxy(60, 50, '0' + gametime / 100 % 10);
	outtextxy(70, 50, '0' + gametime / 10%10);
	outtextxy(80, 50, '0' + gametime % 10);
	for (i = 0; i < 14; i++)
	{
		//需要使用多字节字符集，否则报错！
		outtextxy(100 * (i + 1), 150, scost[i]);
		outtextxy(100 * (i + 1), 30, sname[i]);
	}
}
void block_move()
{
	int i, j;
	for (i = 0; i < 7; i++)
		for (j = 0; j < 14; j++)
		{
			block[i][j].show(i, j);
		}
}
void enemy_move()
{
	int i, type, diff;
	const int smallkind[10][10] =
	{//小波敌人
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,1,2,5 },
	{ 0,0,0,0,0,1,1,1,2,5 },
	{ 0,0,0,0,0,1,2,2,3,5 },
	{ 0,0,0,0,1,1,2,3,5,6 }
	};
	const int kind[10][10] =
	{ //主要敌人
	{ 1,1,1,1,1,1,2,2,2,5},
	{ 1,1,1,2,2,2,3,4,5,6},
	{ 1,2,2,2,3,3,6,4,4,5},
	{ 6,2,3,3,3,3,4,4,4,5},
	{ 6,2,3,3,4,4,4,4,4,5},
	{ 6,2,3,4,4,4,4,4,4,5},
	};
	int tick[10] = { 0,2500,4000,6000,10000,4000,6000 };//每种敌人消耗tick数
	int smalltick[10] = { 0,200,300,400,500,300,400 };
	int enemygspeed[10] = { 5,12,20,35,65,90 };//出怪速度
	if (gametime < 5000)
		diff = 0;
	if (gametime >= 5000)
		diff = 1;
	if (gametime >= 10000)
		diff = 2;
	if (gametime >= 15000)
		diff = 3;
	if (gametime >= 20000)
		diff = 4;
	if (gametime >= 25000)
	{
		diff = 5;
		enemytick += (gametime - 25000) / 500;
	}
	enemytick += enemygspeed[diff];
	if (enemytick > 10000)
	{
		type = kind[diff][rand() % 10];
		enemy[enemyindex].generate(type, rand() % 7);
		enemytick -= tick[type];
	}

	if (gametime % 50 == 0 && enemytick > 5000)
	{
		type = smallkind[diff][rand() % 10];
		enemy[enemyindex].generate(type, rand() % 7);
		enemytick -= smalltick[type];
	}

	for (i = 0; i < MAX; i++)
	{
		enemy[i].move();
		enemy[i].show();
	}
}
void bullet_move()
{
	int i, j, t;
	for (i = 0; i < 7; i++)
		for (j = 0; j < 14; j++)
		{
			t = block[i][j].time;
			if (block[i][j].isplanted)
			{
				if (block[i][j].planttype == 1 && block[i][j].time % attackfrequency == 0)
				{
					bullet[bulletindex].generate(1, i, j * 100 + 150);
				}
				if (block[i][j].planttype == 5 && block[i][j].time % attackfrequency == 0)
				{
					bullet[bulletindex].generate(2, i, j * 100 + 150);
				}
				if (block[i][j].planttype == 6 && block[i][j].time % attackfrequency == 0)
				{
					bullet[bulletindex].generate(3, i, j * 100 + 150);
				}
				if (block[i][j].planttype == 11 && (t % attackfrequency == 1 || t % attackfrequency == 7 || t % attackfrequency == 13 || t % attackfrequency == 19))
				{
					bullet[bulletindex].generate(1, i, j * 100 + 150);
				}
			}
		}
	for (i = 0; i < MAXB; i++)
	{
		bullet[i].move();
		bullet[i].hit();
		bullet[i].show();
	}
}
void run_game()
{
	int i;
	block_move();
	enemy_move();
	bullet_move();
	gametime++;
	if (gametime % SUNSHINEDOWN == 0)
		sunshine += 25;
	for (i = 0; i < 14; i++)
		if (cd[i] > 0)
			cd[i]--;
}
void initialize()
{
	int i, j;
	for (i = 0; i < 7; i++)
		for (j = 0; j < 14; j++)
		{
			block[i][j].initialize();
		}
	guangbiao = gametime = enemyindex = bulletindex = 0, chooseplant = 0, enemytick = INIENEMYTICK, sunshine = SUNSHINE;
}
int main()
{
	int i, j;
	srand(time(0));
	initgraph(1600, 950);
	initialize();
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		draw_map();
		run_game();
		EndBatchDraw();
		if (peekmessage(&msg, -1))
		{
			ch = msg.vkcode;
			int gby = guangbiao / 14;
			int gbx = guangbiao % 14;
			if (msg.message == WM_KEYDOWN)
			{
				switch (ch)
				{
				case VK_DOWN:guangbiao += 14; break;
				case VK_UP:guangbiao -= 14; break;
				case VK_LEFT:guangbiao -= 1; break;
				case VK_RIGHT:guangbiao += 1; break;
				case VK_RETURN:block[gby][gbx].plant(chooseplant, gby, gbx); break;
				case VK_BACK:
					if (!block[gby][gbx].isplanted)
						block[gby][gbx].isprotected = 0;
					if (block[gby][gbx].isplanted)
						block[gby][gbx].isplanted = 0;
					break;
				case 0x31:chooseplant = 1; break;
				case 0x32:chooseplant = 2; break;
				case 0x33:chooseplant = 3; break;
				case 0x34:chooseplant = 4; break;
				case 0x35:chooseplant = 5; break;
				case 0x36:chooseplant = 6; break;
				case 0x37:chooseplant = 7; break;
				case 0x38:chooseplant = 8; break;
				case 0x39:chooseplant = 9; break;
				case 0x30:chooseplant = 10; break;
				case 0xBD:chooseplant = 11; break;
				case 0xBB:chooseplant = 12; break;
				case 0x51:chooseplant = 13; break;
				case 0x57:chooseplant = 14; break;
				}
				guangbiao = abs(guangbiao) % 98;
			}
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.y >= 50 && msg.y <= 150)
					chooseplant = msg.x / 100;
				for (i = 0; i < 14; i++)
					for (j = 0; j < 7; j++)
						if (msg.x > i * 100 + 100 && msg.x<i * 100 + 200 && msg.y>j * 100 + 200 && msg.y < j * 100 + 300)
						{
							guangbiao = i + 14 * j;
							gby = guangbiao / 14;
							gbx = guangbiao % 14;
							block[gby][gbx].plant(chooseplant, gby, gbx);
						}
			}
		}
		flushmessage(-1);
		Sleep(20);
	}
}