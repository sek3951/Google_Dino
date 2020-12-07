//[C/C++ game] very simple google dinosaur. (by. BlockDMask)
//2019.12.03 (v2.0)���� �߰�, �浹ó�� �߰�.
#include<cstdio>
#include<windows.h>
#include<conio.h>
#include<ctime>
#include<iostream>
#include "common.h"

using namespace std;

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
			if (IsCollision(treeX, dinoY))
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
			GoToXY(22, 0);	//Ŀ���� ��� �������� �ű��. �ܼ�â�� cols=100�̴ϱ� 2*x�̹Ƿ� 22���� �־���
			cout << "Score : " << score;	//���� �������.
		}

		//(v2.0) ���� ���� �޴�
		DrawGameOver(score);
	}
	return 0;
}