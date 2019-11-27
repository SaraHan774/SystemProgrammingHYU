#include "pch.h"
#include <stdio.h>
//윈도우 화면 제어할 수 있도록 
#include <Windows.h>
//화면 콘솔 제어
#include <conio.h>

using namespace std; 

//top left (0, 0) y가 증가하면 아래로. x가 증가하면 오른쪽. 
#define DINOSAUR_DISTANCE_FROM_TOP_Y 12 
#define TREE_DISTANCE_FROM_TOP_Y 20
#define TREE_DISTANCE_FROM_RIGHT_X 45


//TODO : 점수 트래킹 & 트리 밟으면 죽는 것 구현하기 (다음주까지)

//구현할 함수들 
//선언시에는 자료형만 써줘도 됨 
void InitConsoleConfig(void); 
void GotoXY(int, int); 
int GetKeyDown(void); 
void DrawDinosaur(int, bool&); 
void DrawTree(int); 
void showScore(int&);

static int score = 5; 

int main(int argc, char* argv[]) {

	InitConsoleConfig(); 

	bool jumping = false; //점핑 하고 있다 
	bool working = true; //땅을 밟고 있다 
	bool legDraw = true; 
	
	static const int gravity = 2; //올라갈 때, 떨어질때를 3씩 제어하도록 
	
	int dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y; 
	int treeX = TREE_DISTANCE_FROM_RIGHT_X; 


	while (true) {

		showScore(score); 

		if (32 == GetKeyDown() && working) { //space -> jump 
			//working true 일때만, false 이면 이중점프 
			jumping = true; 
			working = false; 
		}

		if (jumping) {
			dinosaurY -= gravity;
		}
		else {
			dinosaurY += gravity; 
		}

		if (dinosaurY <= 0) {
			//jump 해서 천장에 부딪혔을 경우 
			jumping = false; 
		}

		if (DINOSAUR_DISTANCE_FROM_TOP_Y <= dinosaurY) {
			//바닥보다 아래에 위치하게 되면 
			dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y; 
			working = true; 
		}

		treeX -= 2; 

		if (treeX <= 0) {
			// 새롭게 트리를 생성해준다. 
			treeX = TREE_DISTANCE_FROM_RIGHT_X; 
		}

		
		DrawDinosaur(dinosaurY, legDraw); 
		DrawTree(treeX); 

		if (treeX == 11 && score > 0) {
			--score;
			GotoXY(30, 4);
			printf("YOU HIT THE TREE!");
			Sleep(1000); 
		}

		if (score <= 0) {
			break;
		}

		system("cls");
		Sleep(50); 
	}

	GotoXY(30, 30); 
	printf("GAME OVER"); 

	return 0; 
}

void InitConsoleConfig(void)
{
	//행이 열보다 적게 느껴질수도 ? 
	system("mode con:cols=100 lines=100");
}

void GotoXY(int x, int y) 
{
	COORD position; 
	position.X = x; 
	position.Y = y; 

	//커서의 위치를 바꿔주는 구조체 (인자로 넘어온 xy 대로 바꿔준다)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}


int GetKeyDown(void)
{
	if (0 != _kbhit()){
		return _getch(); 
	}

	return 0;
}



void DrawDinosaur(int dinosaurY, bool &legDraw)
{

	GotoXY(0, dinosaurY); 

	printf("        &&&&&&& \n");
	printf("       && &&&&&&\n");
	printf("       &&&&&&&&&\n");
	printf("&      &&&      \n");
	printf("&&     &&&&&&&  \n");
	printf("&&&   &&&&&     \n");
	printf(" &&  &&&&&&&&&& \n");
	printf(" &&&&&&&&&&&    \n");
	printf("  &&&&&&&&&&    \n");
	printf("    &&&&&&&&    \n");
	printf("     &&&&&&     \n");

	if (legDraw) {
		printf("     &    &&&     \n");
		printf("     &&           ");
		legDraw = false;
	}
	else {
		printf("     &&&  &       \n");
		printf("          &&      ");
		legDraw = true;
	}

	printf("Dinosaur position : %d", dinosaurY); 
}

void DrawTree(int treeX)
{
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y);
	printf(" $$$$$$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 1);
	printf(" $$$$$$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 2);
	printf("   $$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 3);
	printf("   $$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 4); //24
	printf("   $$");

	printf("Tree Position : %d", treeX);
}

void showScore(int& score) {
	GotoXY(25, 0);
	printf("Score :  %d / 5", score);
}



