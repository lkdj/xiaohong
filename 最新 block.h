#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#define P 'O'
#define H 25
#define W 17
#define B 'H'
#define CB 7
#define T 1000000
using namespace std;
void setPos(int i, int j);
void setColor(int t);

class Block;
class Player {
	string name;
	char map[H][W];
	Block* ptr;
	int posx, posy;////光标打印位置的辅助////
	char s, x, z, y;//////（区分玩家）操作方式
	/////判断能不能向下/////
	bool checkDown();
	///////判断能不能向左//////
	bool checkLeft();
	/////判断能不能向右/////
	bool checkRight();
	/////判断能不能变形/////
	bool checkTransform();
	/////左移(调用->清屏+打印,pos变动)//////
	void moveLeft();
	/////右移（调用->清屏+打印,pos变动）//////
	void moveRight();
	/////下移（调用->清屏+打印,pos变动）/////
	void moveDown();
public:
	/////初始化地图+指针指方块+生成方块+初始化方块所在位置+光标辅助位置//////
	Player(string n, Block* a, char b, char c, char d, char e, int px, int py);
	/////接受键盘操作(调用以下函数)/////
	void getMessage(char m);
	/////判断有无消行并消行（返回所消行数）/////
	int CheckAndReplace();
	/////底下随机增加一行////
	void Add();
	////判断是否输了////
	bool checkLose();
	/////打印地图////
	void Print();
	/////方块到底后将方块贴入地图(利用pos后)//////
	void blockIn();
};
class Block {
private:
	int x, y;/////位置/////
	char block[4][4];//当前块//
	char nextBlock[4][4];//下一块//
	int stateNext;///////////4代表长条或田字块（特殊处理），3代表其他
	int stateNow;///////当前方块状态
	int color;//颜色
	////生成方块////
	void Create();
	///////////把下一个贴到当前，再生成下一个
	void createNow(int a, int b);
	/////逆时针旋转变形/////
	void transform(int a = 1);
	////打印下一个////
	void printNext(int px, int py);
public:
	///////随机生成下一个方块/////////
	Block();
	////////玩家类是方块类的friend////////
	friend Player;
};
class Game {        /////全局/////                 
private:
	////切换单人1/双人模式2////
	int mode;
	////提示语////？？
	string tip[9];
	////玩家////
	Player* p1, * p2;
	////方块////
	Block* a, * b;
	////难度////
	int hard;
public:
	////初始化提示////
	Game();
	/////全局暂停（按任意键继续）/////
	void stop();
	////打印提示语////
	void PRINT(int x);
	////打印游戏过程////
	void printGame();
	////选择难度////
	void selectHard();
	////游戏运行////
	void Run();
};
///////////////////////////////////////////？？？渲染？？？///////////////////////////////////////////////
//class /////还没呢
