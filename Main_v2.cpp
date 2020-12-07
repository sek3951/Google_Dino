//[C/C++ game] very simple google dinosaur. (by. BlockDMask)
//2019.12.03 (v2.0)���� �߰�, �浹ó�� �߰�.
#include<cstdio>
#include<windows.h>
#include<conio.h>
#include<ctime>
#include<iostream>

using namespace std;

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//�ܼ� â�� ũ��� ������ �����ϴ� �Լ�
void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
	system("Final Project - 10Team");
}

//Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//������ �׸��� �Լ�
void DrawDino(int dinoY)
{
	GotoXY(0, dinoY);
	static bool legFlag = true;
	cout << "        $$$$$$$ \n";
	cout << "       $$ $$$$$$\n";
	cout << "       $$$$$$$$$\n";
	cout << "$      $$$      \n";
	cout << "$$     $$$$$$$  \n";
	cout << "$$$   $$$$$     \n";
	cout << " $$  $$$$$$$$$$ \n";
	cout << " $$$$$$$$$$$    \n";
	cout << "  $$$$$$$$$$    \n";
	cout << "    $$$$$$$$    \n";
	cout << "     $$$$$$     \n";
	if (legFlag)
	{
		cout << "     $    $$$    \n";
		cout << "     $$          ";
		legFlag = false;
	}
	else
	{
		cout << "     $$$  $     \n";
		cout << "          $$    ";
		legFlag = true;
	}
}

//������ �׸��� �Լ�
void DrawTree(int treeX)
{
	GotoXY(treeX, TREE_BOTTOM_Y);
	cout << "$$$$";
	GotoXY(treeX, TREE_BOTTOM_Y + 1);
	cout << " $$ ";
	GotoXY(treeX, TREE_BOTTOM_Y + 2);
	cout << " $$ ";
	GotoXY(treeX, TREE_BOTTOM_Y + 3);
	cout << " $$ ";
	GotoXY(treeX, TREE_BOTTOM_Y + 4);
	cout << " $$ ";
}

//(v2.0) �浹 ������ ���ӿ��� �׷���
void DrawGameOver(const int score)
{
	system("cls");
	int x = 18;
	int y = 8;
	GotoXY(x, y);
	cout << "===========================";
	GotoXY(x, y + 1);
	cout << "======G A M E O V E R======";
	GotoXY(x, y + 2);	
	cout << "===========================";
	GotoXY(x, y + 5);
	cout << "SCORE : "<< score;

	cout << "\n\n\n\n\n\n\n\n\n";
	system("pause");
}

//(v2.0) �浹������ true, �ƴϸ� false
bool isCollision(const int treeX, const int dinoY)
{
	//Ʈ���� X�� ������ ��ü�ʿ� ������,
	//������ ���̰� ������� �ʴٸ� �浹�� ó��
	GotoXY(0, 0);
	cout << "treeX : "<<treeX<<" dinoY : "<< dinoY; //�̷������� ������ X, Y�� ã���ϴ�.
	if (treeX <= 8 && treeX >= 4 &&
		dinoY > 8)
	{
		return true;
	}
	return false;
}

int main()
{
	SetConsoleView();

	while (true)		//(v2.0) ���� ����
	{
		//���� ���۽� �ʱ�ȭ
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;
		
		int dinoY = DINO_BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;
		
		int score = 0;
		clock_t start, curr;	//���� ���� �ʱ�ȭ
		start = clock();		//���۽ð� �ʱ�ȭ

		while (true)	//�� �ǿ� ���� ����
		{
			//(v2.0) �浹üũ Ʈ���� x���� ������ y������ �Ǵ�
			if(isCollision(treeX, dinoY))
				break;

			//zŰ�� ���Ȱ�, �ٴ��� �ƴҶ� ����
			if (GetKeyDown() == 'z' && isBottom)
			{
				isJumping = true;
				isBottom = false;
			}

			//�������̶�� Y�� ����, ������ �������� Y�� ����.
			if (isJumping)
			{
				dinoY -= gravity;
			}
			else
			{
				dinoY += gravity;
			}

			//Y�� ����ؼ� �����ϴ°� �������� �ٴ��� ����.
			if (dinoY >= DINO_BOTTOM_Y)
			{
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			//������ �������� (x����) �������ϰ�
			//������ ��ġ�� ���� �����ΰ��� �ٽ� ������ ������ ��ȯ.
			treeX -= 2;
			if (treeX <= 0)
			{
				treeX = TREE_BOTTOM_X;
			}

			//������ ������ ������ ������ ���� ��Ȳ.
			if (dinoY <= 3)
			{
				isJumping = false;
			}

			DrawDino(dinoY);		//draw dino
			DrawTree(treeX);		//draw Tree

			//(v2.0)
			curr = clock();			//����ð� �޾ƿ���
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)	// 1�ʰ� �Ѿ�����
			{
				score++;	//���ھ� UP
				start = clock();	//���۽ð� �ʱ�ȭ
			}
			Sleep(60);
			system("cls");	//clear

			//(v2.0) ��������� 1�ʸ��� ���ִ°��� �ƴ϶� �׻� ������ָ鼭, 1�ʰ� �������� ++ ���ݴϴ�.
			GotoXY(22, 0);	//Ŀ���� ��� �������� �ű��. �ܼ�â�� cols=100�̴ϱ� 2*x�̹Ƿ� 22���� �־���
			cout << "Score : "<< score;	//���� �������.
		}

		//(v2.0) ���� ���� �޴�
		DrawGameOver(score);
	}
	return 0;
}