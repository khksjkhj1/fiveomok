#include <windows.h>
#include <cstdlib>
#include <iostream>
#include "client.h"
using namespace std;

#define ROW 20
#define COLUMN 20
#define PLAYER1 8
#define PLAYER2 9

int usergameStart();	// 유저 VS 유저 게임 
int comgameStart();		// 유저 VS 컴퓨터 게임
void Output(int omok[][COLUMN]);	// 판 출력
int InputF(int omok[][COLUMN], int first, int second);	// 1P 입력
int InputW(int omok[][COLUMN], int first, int second);	// 2P 입력
void InputC(int omok[][COLUMN], int first, int second);	//	COMPUTER 입력
int	ComputePoint(int omok[][COLUMN]);	// 컴퓨터 입력할 좌표 설정
void GetAttackPos(int omok[][COLUMN], int* row, int* col);	// 컴퓨터 입력 좌표 GET
int	ISAnemyNear(int omok[][COLUMN], int row, int col, int curPlayer); // 가중치 재설정
int Bingo_1(int omok[][COLUMN]);	// 1P 5줄 확인
int Bingo_2(int omok[][COLUMN]);	// 2P (컴퓨터) 5줄 확인
int game(char id[]);	// 게임메뉴


void main(){
	int quit = 1;
	int menu;
	char id[50],name[50],pass[50];
	char check;


	while (quit)
	{

		cout << " menu " << endl;
		cout << "1. 회원가입 " << endl;
		cout << "2. 로그인 " << endl;
		cout << "3. 전적보기 " <<endl;
		cout << "4. exit" << endl;

		cin >> menu;

		if(menu==1)
		{
			for(;;){
				client temp("member.txt");
				cout << "회원가입"<<endl;
				cout << "성명 : ";
				cin >> name;
				cout << "ID : ";
				cin >> id;
				cout << "PASSWORD : ";
				cin >> pass;
				check = temp.insert(id,name,pass);
				if(check=='i') cout << " 이미 사용중인 아이디 입니다"<<endl;
				if(check=='o') {cout << " 가입완료 "<<endl;break;}
			}
		}
		if(menu==2)
		{
			for(;;){
				client temp("member.txt");
				cout << "로그인"<<endl;
				cout << "ID : ";
				cin >> id;
				cout << "PASSWORD : ";
				cin >> pass;
				check = temp.check(id,pass);
				if(check=='i') cout << " 아이디를 확인해주세요"<<endl;
				if(check=='o') {
					cout << " 로그인 성공"<<endl; 
					game(id);
					break;
				}
				if(check=='p') cout << " 비밀번호를 확인해주세요"<<endl;

			}
		}
		if(menu==3)
		{
			client temp("member.txt");
			temp.print();
		}
		if(menu==4) break;
	}
}


int game(char id[])	// 게임 메뉴
{
	int quit = 1;
	int menu;
	int result=0;

	while (quit)
	{

		cout << " menu " << endl;
		cout << "1. user vs user " << endl;
		cout << "2. user vs computer " << endl;
		cout << "3. exit" << endl;

		cin >> menu;

		switch (menu)
		{
		case 1:
			usergameStart();
			fflush(stdin);
			getchar();
			system("cls");
			break;

		case 2:{
			result = comgameStart();
			fflush(stdin);
			getchar();
			system("cls");
			client temp("member.txt");
			temp.result(id, result);
			temp.write();
			break;
			   }
		case 3:
			quit = 0;
			break;

		default :
			cerr << "Error: wrong input" << endl;
			break;
		}
	}
	return 0;
}


int usergameStart()		// 유저 VS 유저 게임 
{

	int omok[ROW][COLUMN];
	int first = 0;
	int second = 0;

	for (int i = 0; i<ROW; i++)
	{
		for (int j = 0; j<COLUMN; j++)
		{
			omok[i][j] = 0;
		}
	}
	for (int q = 0; q<ROW; q++)
	{
		for (int w = 0; w<COLUMN; w++)
		{
			system("cls");
			Output(omok);

			if(InputF(omok, first, second))
				return -1;
			system("cls");
			Output(omok);
			if (Bingo_1(omok))
			{
				cout << "1p win" << endl;

				return 0;
			}


			if(InputW(omok, first, second))
				return -1;
			system("cls");
			Output(omok);

			if (Bingo_2(omok))
			{
				cout << "2p win" << endl;

				return 0;
			}
		}
	}
	return 0;
}


int comgameStart()		// 유저 VS 컴퓨터 게임
{

	int omok[ROW][COLUMN];
	int first = 0;
	int second = 0;

	for (int i = 0; i<ROW; i++)
	{
		for (int j = 0; j<COLUMN; j++)
		{
			omok[i][j] = 0;
		}
	}
	for (int q = 0; q<ROW; q++)
	{
		for (int w = 0; w<COLUMN; w++)
		{
			system("cls");
			Output(omok);

			if(InputF(omok, first, second))
				return -1;
			system("cls");
			Output(omok);
			if (Bingo_1(omok))
			{
				cout << "1p win" << endl;

				return 3;
			}

			Sleep(1000);
			cout << "computer is thinking..." << endl;

			InputC(omok, first, second);
			system("cls");
			Output(omok);

			if (Bingo_2(omok))
			{
				cout << "computer win" << endl;

				return 2;
			}
		}
	}
	return 0;
}


void Output(int omok[][COLUMN])	// 판 출력 함수
{
	int i,j,k = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COLUMN; j++)
		{


			if (omok[i][j] < PLAYER1)
				cout << "┼";
			else if (omok[i][j] == PLAYER1)
				cout << "●";
			else if (omok[i][j] == PLAYER2)
				cout << "○";
			//cout << omok[i][j] << " ";
			if (j == COLUMN-1)
				cout << " " << i+1 << endl;


		}
	}

	for(k=0;k<9;k++)
		cout << k+1 << " ";
	for(k=9;k<COLUMN;k++)
		cout << k+1;
	cout << endl;
}

int InputF(int omok[][COLUMN], int first, int second)	// 1P 돌 놓는 함수
{
	cout << "1P 좌표(m행n열)를 입력하세요:(input (0,0) to exit)";
	while (1)
	{
		cin >> first;
		cin >> second;

		if (first == 0 && second == 0)
			return -1;
		if (first < 1 || second < 1 || first > ROW || second > COLUMN)
			cout << " 잘못된 입력입니다. 다시 입력해주세요:" << endl;
		else if (omok[first-1][second-1] != PLAYER1 && omok[first-1][second-1] != PLAYER2)
		{
			omok[first-1][second-1] = PLAYER1;
			break;
		}
		else
			cout << "입력하신 좌표엔 돌이 이미 있습니다. 다시 입력해주세요:" << endl;

	}
	return 0;
}

int InputW(int omok[][COLUMN], int first, int second)	// 2P 돌 놓는 함수
{
	cout << "2P 좌표(m행n열)를 입력하세요(input (0,0) to exit)";
	while (1)
	{
		cin >> first;
		cin >> second;

		if (first == 0 && second == 0)
			return -1;
		if (first < 1 || second < 1 || first > ROW || second > COLUMN)
			cout << " 잘못된 입력입니다. 다시 입력해주세요:" << endl;
		else if (omok[first-1][second-1] != PLAYER1 && omok[first-1][second-1] != PLAYER2)
		{
			omok[first - 1][second - 1] = PLAYER2;
			break;
		}
		else
			cout << "입력하신 좌표엔 돌이 이미 있습니다. 다시 입력해주세요:" << endl;

	}
	return 0;
}

void InputC(int omok[][COLUMN], int first, int second)	// 컴퓨터가 돌 놓는 함수
{
	int row, col = 0;

	ComputePoint(omok);

	GetAttackPos(omok, &row, &col);

	omok[row][col]=PLAYER2;

}


int Bingo_1(int omok[][COLUMN]) // 1P 5줄 체크
{
	int i, j;

	for (i = 0; i<ROW; i++)
		for (j = 0; j<COLUMN; j++)
			if (omok[i][j] == PLAYER1 && omok[i][j + 1] == PLAYER1 && omok[i][j + 2] == PLAYER1 && omok[i][j + 3] == PLAYER1 && omok[i][j + 4] == PLAYER1)
			{

				return 1;
			}
			else if (omok[i][j] == PLAYER1 && omok[i + 1][j] == PLAYER1 && omok[i + 2][j] == PLAYER1 && omok[i + 3][j] == PLAYER1 && omok[i + 4][j] == PLAYER1)
			{

				return 1;
			}
			else if (omok[i][j] == PLAYER1 && omok[i + 1][j + 1] == PLAYER1 && omok[i + 2][j + 2] == PLAYER1 && omok[i + 3][j + 3] == PLAYER1 && omok[i + 4][j + 4] == PLAYER1)
			{

				return 1;
			}
			else if (omok[i][j] == PLAYER1 && omok[i + 1][j - 1] == PLAYER1 && omok[i + 2][j - 2] == PLAYER1 && omok[i + 3][j - 3] == PLAYER1 && omok[i + 4][j - 4] == PLAYER1)
			{

				return 1;
			}
			return 0;
}

int Bingo_2(int omok[][COLUMN]) // 2P (COMPUTER) 5줄 체크
{
	int i, j;

	for (i = 0; i<ROW; i++)
		for (j = 0; j<COLUMN; j++)
			if (omok[i][j] == PLAYER2 && omok[i][j + 1] == PLAYER2 && omok[i][j + 2] == PLAYER2 && omok[i][j + 3] == PLAYER2 && omok[i][j + 4] == PLAYER2)
			{

				return 1;
			}
			else if (omok[i][j] == PLAYER2 && omok[i + 1][j] == PLAYER2 && omok[i + 2][j] == PLAYER2 && omok[i + 3][j] == PLAYER2 && omok[i + 4][j] == PLAYER2)
			{

				return 1;
			}
			else if (omok[i][j] == PLAYER2 && omok[i + 1][j + 1] == PLAYER2 && omok[i + 2][j + 2] == PLAYER2 && omok[i + 3][j + 3] == PLAYER2 && omok[i + 4][j + 4] == PLAYER2)
			{

				return 1;
			}
			else if (omok[i][j] == PLAYER2 && omok[i + 1][j - 1] == PLAYER2 && omok[i + 2][j - 2] == PLAYER2 && omok[i + 3][j - 3] == PLAYER2 && omok[i + 4][j - 4] == PLAYER2)
			{

				return 1;
			}
			return 0;
}



int ComputePoint(int omok[][COLUMN]) // 컴퓨터가 놓을 자리 선정
{

	int row, col;
	int i=0;
	int count=1;
	int tempPlayer=0;

	// 가중치 1 세팅
	for(row=0;row<ROW;row++){
		for(col=0;col<COLUMN;col++){
			// LEFT →
			if( col < COLUMN-1 && omok[row][col+1]==PLAYER1 && omok[row][col]<1 )
				omok[row][col]=1;
			else	// RIGHT ← 
				if( col > 0 && omok[row][col-1]==PLAYER1  && omok[row][col]<1)
					omok[row][col]=1;
				else	// DOWN ↓
					if( row < ROW-1 && omok[row+1][col]==PLAYER1 && omok[row][col]<1)
						omok[row][col]=1;
					else	// UP ↑
						if( row > 0 && omok[row-1][col]==PLAYER1 && omok[row][col]<1)
							omok[row][col]=1;
						else // ↘
							if( (row < ROW-1 && col < COLUMN-1) && omok[row+1][col+1] == PLAYER1  && omok[row][col]<1)
								omok[row][col]=1;		
							else // ↖
								if( (row > 0 && col > 0) && omok[row-1][col-1] == PLAYER1  && omok[row][col]<1)
									omok[row][col]=1;
								else // ↗
									if( (row > 0 && col < COLUMN-1) && omok[row-1][col+1] == PLAYER1  && omok[row][col]<1)
										omok[row][col]=1;
									else // ↙
										if( (row < ROW-1 && col > 0) && omok[row+1][col-1] == PLAYER1  && omok[row][col]<1)
											omok[row][col]=1;
		}
	}


	//돌의 개수에 의한 일반 가중치 
	for(row=0;row<ROW;row++){
		for(col=0;col<COLUMN;col++){

			if( col < COLUMN && omok[row][col] < PLAYER1 && omok[row][col+1] >= PLAYER1 ){

				count=0;
				tempPlayer=omok[row][col+1] ;

				for(i=col+1; i<COLUMN;i++){
					if( omok[row][i] == tempPlayer )
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	 //주위에 상대돌이 있다면 
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// RIGHT ← 
			if( col > 0 && omok[row][col] < PLAYER1 && omok[row][col-1] >=PLAYER1){

				count=0;
				tempPlayer=omok[row][col-1] ;

				for(i=col-1; i>=0;i--){
					if( omok[row][i] == tempPlayer )
						count++;
					else
						break;
				}


				if(omok[row][col] < count){	//주위에 상대돌이 있다면
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}
			}
			// DOWN ↓
			if( row < ROW && omok[row][col] < PLAYER1 && omok[row+1][col] >= PLAYER1){

				count=0;
				tempPlayer=omok[row+1][col] ;

				for(i=row+1; i<ROW ;i++){
					if( omok[i][col] == tempPlayer )
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//주위에 상대돌이 있다면
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// UP ↑
			if( row > 0 && omok[row][col] < PLAYER1 &&  omok[row-1][col]>=PLAYER1){

				count=0;
				tempPlayer=omok[row-1][col] ;

				for(i=row-1; i>=0 ;i--){
					if( omok[i][col] == tempPlayer )
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//주위에 상대돌이 있다면
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ↘
			if( (row < ROW && col < COLUMN)  && omok[row][col] < PLAYER1 && omok[row+1][col+1] >=PLAYER1)
			{
				count=0;
				tempPlayer=omok[row+1][col+1] ;

				for(i=1;i<5;i++){
					if((row+i<ROW && col+i<COLUMN) && (omok[row+i][col+i]== tempPlayer))
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//주위에 상대돌이 있다면
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ↖
			if( (row > 0 && col > 0)  && omok[row][col] < PLAYER1 && omok[row-1][col-1] >=PLAYER1){

				count=0;
				tempPlayer=omok[row-1][col-1] ;

				for(i=1;i<5;i++){
					if((row-i>=0 && col-i>=0) && (omok[row-i][col-i]== tempPlayer))
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//주위에 상대돌이 있다면
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ↗
			if( (row > 0 && col < COLUMN)  && omok[row][col] < PLAYER1 && omok[row-1][col+1] >= PLAYER1)
			{
				count=0;
				tempPlayer=omok[row-1][col+1] ;

				for(i=1;i<10;i++){
					if((row-i>=0 && col+i<COLUMN) && (omok[row-i][col+i]== tempPlayer))
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//주위에 상대돌이 있다면
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ↙
			if( (row < ROW && col > 0)  && omok[row][col] < PLAYER1 && omok[row+1][col-1] >= PLAYER1)
			{
				count=0;
				tempPlayer=omok[row+1][col-1] ;

				for(i=1;i<5;i++){
					if((row+i<ROW && col-i>0) && (omok[row+i][col-i]== tempPlayer))
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//주위에 상대돌이 있다면 
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}

		}
	}


	//--------------다른 가중치 방법 구현 위치



	return 0;
}


void GetAttackPos(int omok[][COLUMN], int* row, int* col)	// 컴퓨터가 놓을 자리 GET
{

	int Max=0;

	for(int i=0;i< ROW; i++){
		for(int j=0;j< COLUMN; j++){

			if(omok[i][j] > Max && omok[i][j] < PLAYER1){
				Max = omok[i][j];
				*row =i;
				*col =j;
			}
		}
	}
}


int ISAnemyNear(int omok[][COLUMN], int row, int col, int curPlayer)	// 가중치 재설정
{
	int bTrue =0;


	// LEFT →
	if( col < COLUMN-1 && omok[row][col+1]>=PLAYER1 && omok[row][col+1] !=curPlayer )
		bTrue = 1;
	// RIGHT ← 
	if( col > 0 && omok[row][col-1]>=PLAYER1  && omok[row][col-1] != curPlayer)
		bTrue = 1;
	// DOWN ↓
	if( row < ROW-1 && omok[row+1][col]>=PLAYER1 && omok[row+1][col] != curPlayer)
		bTrue = 1;
	// UP ↑
	if( row > 0 && omok[row-1][col]>=PLAYER1 && omok[row-1][col] != curPlayer)
		bTrue = 1;
	// ↘
	if( (row < ROW-1 && col < COLUMN-1) && omok[row+1][col+1] >= PLAYER1  && omok[row+1][col+1] != curPlayer)
		bTrue = 1;		
	// ↖
	if( (row > 0 && col > 0) && omok[row-1][col-1] >= PLAYER1  && omok[row-1][col-1] != curPlayer)
		bTrue = 1;
	// ↗
	if( (row > 0 && col < COLUMN-1) && omok[row-1][col+1] >= PLAYER1  && omok[row-1][col+1] != curPlayer)
		bTrue = 1;
	// ↙
	if( (row < ROW-1 && col > 0) && omok[row+1][col-1] >= PLAYER1  && omok[row+1][col-1] != curPlayer)
		bTrue = 1;


	return bTrue;
}

