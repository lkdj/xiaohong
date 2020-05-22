#include"block.h"
Game::Game()
{
	char x;
	time = 0;////////????                                                                        半成品                G1
	tip[0] = "准备好了嘛？OvO";
	tip[1] = "////////////////游戏结束 QAQ /////////////////";
	tip[2] = "||||||||暂停||||||||";
	cout << tip[0] << endl;
	this->stop();
	x=_getch();
	system("cls");
}
void Game::stop() //全局暂停                                                                                   G2
{
	system("pause");
}
void Game::PRINT(int x)//打印骚话？                                                                     G3
{
	cout << tip[x] << endl;
	this->stop();
}
//---------------------------------------------------------------------------方块类------------------------------------------------------------------
void Block::Create()  //////////生成下一个（调用旋转）                                         B1
{
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			nextBlock[i][j] = ' ';
		}
	}
	int x;
	x = rand() % 7;
	if (!x) { ////长条
		stateNext = 4;
		for (int i = 0;i < 4;i++) {
			nextBlock[2][i] = P;
		}
	}
	else if (x == 1) { /////田字块
		stateNext = 4;
		nextBlock[1][1] = P;
		nextBlock[1][2] = P;
		nextBlock[2][1] = P;
		nextBlock[2][2] = P;
	}
	else {
		stateNext = 3;
		if (x == 2) {////凸
			nextBlock[1][0] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
			nextBlock[2][1] = P;
		}
		if (x == 3) {///左瞄枪
			nextBlock[1][1] = P;
			nextBlock[1][0] = P;
			nextBlock[1][2] = P;
			nextBlock[0][2] = P;
		}
		if (x == 4) {//////右瞄枪
			nextBlock[0][0] = P;
			nextBlock[1][0] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
		}
		if (x == 5) {////↗台阶
			nextBlock[0][0] = P;
			nextBlock[0][1] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
		}
		if (x == 6) {//////↖台阶
			nextBlock[0][1] = P;
			nextBlock[1][0] = P;
			nextBlock[1][1] = P;
			nextBlock[0][2] = P;
		}
	}
	x = rand() % 4;
	while (x--) {
		this->transform(2);
	}
}
Block::Block()/////////////第一次生成下一个方块                                                B2
{
	this->Create();
}
void Block::createNow(int a,int b)//把下一个移到当前块，生成下一个,pos初始化                   B3
{
	x = a;
	y = b;
	stateNow = stateNext;
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			block[i][j] = nextBlock[i][j];
		}
	}
	this->Create();
}

void Block::transform(int a) ////逆时针旋转                                                    B4
{
	char temp[4][4];
	if (a == 1) {/////旋转now
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				temp[i][j] = block[i][j];
			}
		}
		for (int i = 0;i < stateNow;i++) {
			for (int j = 0;j < stateNow;j++) {
				block[j][stateNow - i - 1] = temp[i][j];
			}
		}
	}
	else {//旋转next
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				temp[i][j] = nextBlock[i][j];
			}
		}
		for (int i = 0;i < stateNext;i++) {
			for (int j = 0;j < stateNext;j++) {
				nextBlock[j][stateNext - i - 1] = temp[i][j];
			}
		}
	}
}
void Block::printNext()
{
	cout << "\t" << "Coming:";
	cout << endl << "\t";
	for (int i = 0;i < stateNext + 2;i++)cout << "+";
	for (int i = 0;i < stateNext;i++) {
		cout << endl << "\t+";
		for (int j = 0;j < stateNext;j++) {
			cout << nextBlock[i][j];
		}
		cout << "+";
	}
	cout << endl << "\t";
	for (int i = 0;i < stateNext + 2;i++)cout << "+";
	cout << endl;
}
//------------------------------------------------------Player----------------------------------------------------------------
Player::Player(string n, Block* a, char b, char c, char d, char e)//初始化地图+生成方块+操作按键                            P1
{
	name = n;
	s = b;
	x = c;
	z = d;
	y = e;
	ptr = a;
	ptr->createNow(25, 9);
	for (int i = 0;i < H;i++) {
		map[i][0] = B;
		map[i][W - 2] = B ;
		map[i][W - 1] = '\0';
	}
	for (int i = 0;i < H; i++) {
		for (int j = 1;j < W-2;j++) {
			if (!i) map[i][j] = B;
			else map[i][j] = ' ';
		}
	}
}
void Player::getMessage(char m)//接收操作信息                                                                                   P2
{
	if (m == s && checkTransform()) ptr->transform();
	if (m == z && checkLeft()) moveLeft();
	if (m == y && checkRight()) moveRight();
	if (m == x) {
		if (checkDown()) moveDown();
		else {
			blockIn();
			ptr->createNow(H-5, W/2);
		}
			
	}
}
bool Player::checkDown()                                                  //                                           P3
{
	for (int i = 0;i < ptr->stateNow;i++) {
		for (int j = 0;j < ptr->stateNow;j++) {
			if (ptr->block[i][j] == P && (ptr->x + i <= 1 || map[ptr->x + i - 1][ptr->y + j] != ' '))return false;
		}
	}
	return true;
}
bool Player::checkLeft()//                                                                                                                      P4
{
	for (int i = 0;i < ptr->stateNow;i++) {
		for (int j = 0;j < ptr->stateNow;j++) {
			if (ptr->block[i][j] == P && (ptr->y + j <= 1 || map[ptr->x + i][ptr->y + j - 1] != ' '))return false;
		}
	}
	return true;
}
bool Player::checkRight()//                                                                                                                      P5
{
	for (int i = 0;i < ptr->stateNow;i++) {
		for (int j = 0;j < ptr->stateNow;j++) {
			if (ptr->block[i][j] == P && (ptr->y + j >= W-3 || map[ptr->x + i][ptr->y + j + 1] != ' '))return false;
		}
	}
	return true;
}
bool Player::checkTransform()//                                                                                                             P6
{
	for (int i = 0;i < ptr->stateNow;i++) {
		for (int j = 0;j < ptr->stateNow;j++) {
			if (ptr->block[i][j] == P && ((ptr->x + j < 1 || ptr->y + ptr->stateNow - i - 1 < 1 || ptr->y + ptr->stateNow - i - 1 > W - 3) || map[ptr->x + j][ptr->y + ptr->stateNow - i - 1] != ' '))return false;
		}
	}
	return true;
}
void Player::moveDown()//                                                                                                                         P7
{
	(ptr->x)--;
}
void Player::moveLeft()//                                                                                                                           P8
{
	(ptr->y)--;
}
void Player::moveRight()//                                                                                                                          P9
{
	(ptr->y)++;
}
void Player::blockIn()//                                                                                                                              P10
{
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (ptr->block[i][j] == P) {
				map[ptr->x + i][ptr->y + j] = P;
			}
		}
	}
}
int Player::CheckAndReplace()//检查并消行，返回所消的行数                                                                      P11
{
	int cnt = 0, j;
	for (int i = 1;i < H-5;i++) {
		for (j = 1;j < W-2;j++) {
			if (map[i][j] == ' ')break;
		}
		if (j == W-2) {
			cnt++;
			for (int k = i;k < H-5;k++) {
				for (int l = 1;l < W-2;l++) {///
					map[k][l] = map[k + 1][l];
				}
			}
		}
	}
	return cnt;
}
void Player::Add()//底下加行，只一次                                                                                                         P12
{
	int x;
	if (ptr->x < H-5) (ptr->x)++;
	for (int i = H-5;i > 1;i--) {
		for (int j = 1;j < W-2;j++) {
			map[i][j] = map[i - 1][j];
		}
	}
	int y;
	y = rand() % 20 + 1;
	map[1][y] = ' ';
	for (int i = 0;i < W-2;i++) {
		if (i != y) {
			x = rand() % 2;
			if (x) map[1][i] = ' ';
			else map[1][i] = P;
		}
	}
}
bool Player::checkLose()// 输了返回真                                                                                                        P13
{
	for (int i = 1;i < W-2;i++) {
		if (map[H-5][i] != ' ')return true;
	}
	return false;
}
void Player::Print()               // 输出(清屏在主函数噢)                                                                           P14
{
	ptr->printNext();
	for (int i = 0;i < W - 1;i++)cout << B;
	cout << endl;
	for (int i = H-6;i >= 0;i--) {
		for (int j = 0;j < W-1;j++) {
			if (i - ptr->x >= 0 && i - ptr->x < ptr->stateNow && j - ptr->y >= 0 && j - ptr->y < ptr->stateNow && ptr->block[i - ptr->x][j - ptr->y] == P) {
				cout << ptr->block[i - ptr->x][j - ptr->y];
			}
			else cout << map[i][j];
		}
		cout << endl;
	}
}