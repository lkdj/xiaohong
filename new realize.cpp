#include"block.h"
void setPos(int i, int j)			//设置光标位置（列， 行）
{
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setColor(int t)
{
	int n = 0x0F;
	switch (t){
		case 0: n = 0x08; break;  //灰色
		case 1: n = 0x0C; break;  //大红（浅）
		case 2: n = 0x0D; break;  //亮紫色
		case 3: n = 0x0E; break;  //浅黄色
		case 4: n = 0x0A; break;  //绿色
		case 5: n = 0x0F; break;  //亮白色
		case 6: n = 0x09; break;  //深蓝色
		case 7: n = 0x0B; break;  //青色
		case 8: n = 0x05; break;  //暗紫色
		case 9: n = 0x03; break;  //浅蓝色
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}
Game::Game()
{
	char x;                                                                //    半成品                G1
	tip[0] = "欢迎来到我罗斯椭圆!!! OvO";
	tip[7] = "扣1选择单人模式，扣2选择双人对战模式噢";
	tip[8] = "由于技术不精，闪屏和粗糙的做工可能会对你的眼睛造成伤害，但我们不负责。";
	tip[1] = "////////////////游戏结束 QAQ /////////////////";
	tip[2] = "||||||||暂停||||||||";
	tip[3] = "按空格暂停，按‘T’退出";
	tip[4] = "小红胜利！CONGRATULATIONS!";
	tip[5] = "小明胜利！CONGRATULATIONS!";
	tip[6] = "||||||||||||||已退出||||||||||||||";
	setPos(44, 11);
	setColor(3);
	cout << tip[0];
	setColor(7);
	setPos(38, 14);
	cout << tip[7] << endl;
	setPos(24, 25);
	setColor(0);
	cout << tip[8] << endl;
	x=_getch();
	while (x != '1' && x != '2') {
		x = _getch();
	}
	if (x == '1') {
		mode = 1;
		a = new Block();
		p1=new Player("小红", a, 'W', 'S', 'A', 'D', 45, 3);
	}
	else {
		mode = 2;
		a = new Block();
		p1 = new Player("小红", a, 'W', 'S', 'A', 'D', 1, 3);
		b = new Block();
		p2 = new Player("小明", b, 'I', 'K', 'J', 'L', 11 + W, 3);
	}
	system("cls");
	selectHard();
}
void Game::stop() //全局暂停                                                                                   G2
{
	system("pause");
}
void Game::PRINT(int x)//打印骚话？                                                                     G3
{
	setColor(4);
	cout << tip[x];
	if (x == 2)this->stop();
}
void Game::printGame()        //                                                                              G4
{
	if (mode == 1) {
		//setPos(W - 5, 0);
		system("cls");
		setPos(45, 0);
		PRINT(3);
		p1->Print();
		p1->CheckAndReplace();
		if (p1->checkLose()) {
			setPos(45, H);
			PRINT(1);
			stop();
			exit(0);
		}
	}
	else {
		int num1, num2;
		system("cls");
		p1->Print();
		setPos(W - 5, 0);
		PRINT(3);
		p2->Print();
		num1 = p1->CheckAndReplace();
		for (int i = 0;i < num1;i++) {
			p2->Add();
			if (p2->checkLose()) {
				system("cls");
				p1->Print();
				setPos(W - 5, 0);
				PRINT(3);
				p2->Print();
				setPos(W - 5, H);
				PRINT(4);
				setPos(W - 5, H + 1);
				PRINT(1);
				stop();
				exit(0);
			}
		}
		num2 = p2->CheckAndReplace();
		for (int i = 0;i < num2;i++) {
			p1->Add();
			if (p1->checkLose()) {
				system("cls");
				p1->Print();
				setPos(W - 5, 0);
				PRINT(3);
				p2->Print();
				setPos(W - 5, H);
				PRINT(5);
				setPos(W - 5, H + 1);
				PRINT(1);
				stop();
				exit(0);
			}
		}
		if (p1->checkLose()) {
			setPos(W - 6, H);
			PRINT(5);
			setPos(6, H + 1);
			PRINT(1);
			cout << endl;
			stop();
			exit(0);
		}
		if (p2->checkLose()) {
			setPos(W - 6, H);
			PRINT(4);
			setPos(6, H + 1);
			PRINT(1);
			cout << endl;
			stop();
			exit(0);
		}
	}
}
void Game::Run()  /////游戏运行                                                                                     G5
{
	char x;
	int i = 0;
	if (mode == 1) {
		setPos(45, 1);
		PRINT(3);
		p1->Print();
		while (1) {
			if (i >= T)i = 0;
			if (i % hard == 0) {
				p1->getMessage('S');
				printGame();
			}
			if (_kbhit()) {
				x = _getch();
				if (x == 'T') {
					system("cls");
					PRINT(6);
					cout << endl;
					stop();
					exit(0);
				}
				if (x == ' ') {
					setPos(45, H);
					PRINT(2);
					cout << endl;
				}
				else if (x == 'W' || x == 'S' || x == 'A' || x == 'D') {
					p1->getMessage(x);
					printGame();
				}
			}
			Sleep(10);
			i++;
		}
	}
	else {
		p1->Print();
		setPos(W - 5, 0);
		PRINT(3);
		p2->Print();
		while (1) {
			if (i >= T)i = 0;
			if (i % hard == 0) {
				p1->getMessage('S');
				p2->getMessage('K');
				printGame();
			}
			if (_kbhit()) {
				x = _getch();
				if (x == 'T') {
					system("cls");
					PRINT(6);
					cout << endl;
					stop();
					exit(0);
				}
				if (x == ' ') {
					setPos(W - 5, H);
					PRINT(2);
					cout << endl;
				}
				else {
					p1->getMessage(x);
					p2->getMessage(x);
					printGame();
				}
			}
			Sleep(10);   //停10毫秒
			i++;
		}
	}
}
void Game::selectHard()
{
	char x;
	setPos(50, 8);
	setColor(5);
	cout << "请选择难度：?";
	setPos(50, 9);
	cout << "~~~~~~~~~~~";
	setPos(50, 10);
	setColor(3);
	cout << "1:敌不动我不动 $";
	setPos(50, 11);
	cout << "~~~~~~~~~~~~~~";
	setPos(50, 12);
	setColor(7);
	cout << "2:你的反应慢慢慢 $$";
	setPos(50, 13);
	cout << "~~~~~~~~~~~~~~~~";
	setPos(50, 14);
	setColor(9);
	cout << "3: 平平淡淡才是真 $$$";
	setPos(50, 15);
	cout << "~~~~~~~~~~~~~~~~~";
	setPos(50, 16);
	setColor(1);
	cout << "4:速度与激情 $$$$";
	setPos(50, 17);
	cout << "~~~~~~~~~~~~";
	setPos(50, 19);
	setColor(4);
	cout << "抠对应数字选择难度";
	setPos(48, 20);
	cout << "难度越高椭圆下降越快噢";
	setPos(50, 21);
	x = _getch();
	while (x != '1' && x != '2' && x != '3' && x != '4') {
		x = _getch();
	}
	if (x == '1')hard = 70;
	if (x == '2')hard = 50;
	if (x == '3')hard = 30;
	if (x == '4')hard = 10;
	system("cls");
}
//---------------------------------------------------------------------------方块类------------------------------------------------------------------
void Block::Create()  //////////生成下一个（调用旋转）                                         B1
{
	srand((int)time(0));
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			nextBlock[i][j] = ' ';
		}
	}
	int x;
	x = rand() % 7;
	if (!x) { ////长条
		stateNext = 4;
		color = 1;
		for (int i = 0;i < 4;i++) {
			nextBlock[2][i] = P;
		}
	}
	else if (x == 1) { /////田字块
		stateNext = 4;
		color = 2;
		nextBlock[1][1] = P;
		nextBlock[1][2] = P;
		nextBlock[2][1] = P;
		nextBlock[2][2] = P;
	}
	else {
		stateNext = 3;
		if (x == 2) {////凸
			color = 3;
			nextBlock[1][0] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
			nextBlock[2][1] = P;
		}
		if (x == 3) {///左瞄枪
			color = 4;
			nextBlock[1][1] = P;
			nextBlock[1][0] = P;
			nextBlock[1][2] = P;
			nextBlock[0][2] = P;
		}
		if (x == 4) {//////右瞄枪
			color = 9;
			nextBlock[0][0] = P;
			nextBlock[1][0] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
		}
		if (x == 5) {////↗台阶
			color = 6;
			nextBlock[0][0] = P;
			nextBlock[0][1] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
		}
		if (x == 6) {//////↖台阶
			color = 7;
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
Block::Block()/////////////第一次生成下一个方块                                                                  B2
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

void Block::transform(int a) ////逆时针旋转                                                                         B4
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
void Block::printNext(int px, int py)                                                        //B5
{
	setPos(px, py);
	setColor(3);
	cout << "Next:";
	setPos(px, py + 1);
	for (int i = 0;i < stateNext + 2;i++)cout << "^";
	for (int i = 0;i < stateNext;i++) {
		setPos(px, py + 2 + i);
		setColor(3);
		cout << "^";
		setColor(color);
		for (int j = 0;j < stateNext;j++) {
			cout << nextBlock[i][j];
		}
		setColor(3);
		cout << "^";
	}
	setPos(px, py + 2 + stateNext);
	for (int i = 0;i < stateNext + 2;i++)cout << "^";
}
//------------------------------------------------------Player----------------------------------------------------------------
Player::Player(string n, Block* a, char b, char c, char d, char e, int px, int py)//初始化地图+生成方块+操作按键                            P1
{
	name = n;
	s = b;
	x = c;
	z = d;
	y = e;
	ptr = a;
	posx = px;
	posy = py;
	ptr->createNow(H - 5, (W - 3) / 2 - 1); 
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
			ptr->createNow(H - 5, (W - 3) / 2 - 1);
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
	setPos(posx + 10, posy - 1);
	setColor(3);
	cout << name;
	ptr->printNext(posx + W, posy);
	setPos(posx + W, posy + 10);
	setColor(3);
	cout << "操作方式:";
	setPos(posx + W + 1, posy + 13);
	cout << z;
	setPos(posx + W + 3, posy + 13);
	cout << x;
	setPos(posx + W + 3, posy + 12);
	cout << s;
	setPos(posx + W + 5, posy + 13);
	cout << y;
	setPos(posx, posy);
	setColor(CB);
	for (int i = 0;i < W - 1;i++)cout << B;
	for (int i = H-6;i >= 0;i--) {
		setPos(posx, posy + (H - 5 - i));
		for (int j = 0;j < W-1;j++) {
			if (i - ptr->x >= 0 && i - ptr->x < ptr->stateNow && j - ptr->y >= 0 && j - ptr->y < ptr->stateNow && ptr->block[i - ptr->x][j - ptr->y] == P) {
				setColor(ptr->color);
				cout << ptr->block[i - ptr->x][j - ptr->y];
			}
			else {
				setColor(CB);
				cout << map[i][j];
			}
		}
	}
}
