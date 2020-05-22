#include"block.h"
Game::Game()
{
	char x;
	time = 0;////////????                                                                        ���Ʒ                G1
	tip[0] = "׼�������OvO";
	tip[1] = "////////////////��Ϸ���� QAQ /////////////////";
	tip[2] = "||||||||��ͣ||||||||";
	cout << tip[0] << endl;
	this->stop();
	x=_getch();
	system("cls");
}
void Game::stop() //ȫ����ͣ                                                                                   G2
{
	system("pause");
}
void Game::PRINT(int x)//��ӡɧ����                                                                     G3
{
	cout << tip[x] << endl;
	this->stop();
}
//---------------------------------------------------------------------------������------------------------------------------------------------------
void Block::Create()  //////////������һ����������ת��                                         B1
{
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			nextBlock[i][j] = ' ';
		}
	}
	int x;
	x = rand() % 7;
	if (!x) { ////����
		stateNext = 4;
		for (int i = 0;i < 4;i++) {
			nextBlock[2][i] = P;
		}
	}
	else if (x == 1) { /////���ֿ�
		stateNext = 4;
		nextBlock[1][1] = P;
		nextBlock[1][2] = P;
		nextBlock[2][1] = P;
		nextBlock[2][2] = P;
	}
	else {
		stateNext = 3;
		if (x == 2) {////͹
			nextBlock[1][0] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
			nextBlock[2][1] = P;
		}
		if (x == 3) {///����ǹ
			nextBlock[1][1] = P;
			nextBlock[1][0] = P;
			nextBlock[1][2] = P;
			nextBlock[0][2] = P;
		}
		if (x == 4) {//////����ǹ
			nextBlock[0][0] = P;
			nextBlock[1][0] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
		}
		if (x == 5) {////�J̨��
			nextBlock[0][0] = P;
			nextBlock[0][1] = P;
			nextBlock[1][1] = P;
			nextBlock[1][2] = P;
		}
		if (x == 6) {//////�Į��
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
Block::Block()/////////////��һ��������һ������                                                B2
{
	this->Create();
}
void Block::createNow(int a,int b)//����һ���Ƶ���ǰ�飬������һ��,pos��ʼ��                   B3
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

void Block::transform(int a) ////��ʱ����ת                                                    B4
{
	char temp[4][4];
	if (a == 1) {/////��תnow
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
	else {//��תnext
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
Player::Player(string n, Block* a, char b, char c, char d, char e)//��ʼ����ͼ+���ɷ���+��������                            P1
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
void Player::getMessage(char m)//���ղ�����Ϣ                                                                                   P2
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
int Player::CheckAndReplace()//��鲢���У���������������                                                                      P11
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
void Player::Add()//���¼��У�ֻһ��                                                                                                         P12
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
bool Player::checkLose()// ���˷�����                                                                                                        P13
{
	for (int i = 1;i < W-2;i++) {
		if (map[H-5][i] != ' ')return true;
	}
	return false;
}
void Player::Print()               // ���(��������������)                                                                           P14
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