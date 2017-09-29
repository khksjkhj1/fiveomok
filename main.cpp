#include <windows.h>
#include <cstdlib>
#include <iostream>
#include "client.h"
using namespace std;

#define ROW 20
#define COLUMN 20
#define PLAYER1 8
#define PLAYER2 9

int usergameStart();	// ���� VS ���� ���� 
int comgameStart();		// ���� VS ��ǻ�� ����
void Output(int omok[][COLUMN]);	// �� ���
int InputF(int omok[][COLUMN], int first, int second);	// 1P �Է�
int InputW(int omok[][COLUMN], int first, int second);	// 2P �Է�
void InputC(int omok[][COLUMN], int first, int second);	//	COMPUTER �Է�
int	ComputePoint(int omok[][COLUMN]);	// ��ǻ�� �Է��� ��ǥ ����
void GetAttackPos(int omok[][COLUMN], int* row, int* col);	// ��ǻ�� �Է� ��ǥ GET
int	ISAnemyNear(int omok[][COLUMN], int row, int col, int curPlayer); // ����ġ �缳��
int Bingo_1(int omok[][COLUMN]);	// 1P 5�� Ȯ��
int Bingo_2(int omok[][COLUMN]);	// 2P (��ǻ��) 5�� Ȯ��
int game(char id[]);	// ���Ӹ޴�


void main(){
	int quit = 1;
	int menu;
	char id[50],name[50],pass[50];
	char check;


	while (quit)
	{

		cout << " menu " << endl;
		cout << "1. ȸ������ " << endl;
		cout << "2. �α��� " << endl;
		cout << "3. �������� " <<endl;
		cout << "4. exit" << endl;

		cin >> menu;

		if(menu==1)
		{
			for(;;){
				client temp("member.txt");
				cout << "ȸ������"<<endl;
				cout << "���� : ";
				cin >> name;
				cout << "ID : ";
				cin >> id;
				cout << "PASSWORD : ";
				cin >> pass;
				check = temp.insert(id,name,pass);
				if(check=='i') cout << " �̹� ������� ���̵� �Դϴ�"<<endl;
				if(check=='o') {cout << " ���ԿϷ� "<<endl;break;}
			}
		}
		if(menu==2)
		{
			for(;;){
				client temp("member.txt");
				cout << "�α���"<<endl;
				cout << "ID : ";
				cin >> id;
				cout << "PASSWORD : ";
				cin >> pass;
				check = temp.check(id,pass);
				if(check=='i') cout << " ���̵� Ȯ�����ּ���"<<endl;
				if(check=='o') {
					cout << " �α��� ����"<<endl; 
					game(id);
					break;
				}
				if(check=='p') cout << " ��й�ȣ�� Ȯ�����ּ���"<<endl;

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


int game(char id[])	// ���� �޴�
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


int usergameStart()		// ���� VS ���� ���� 
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


int comgameStart()		// ���� VS ��ǻ�� ����
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


void Output(int omok[][COLUMN])	// �� ��� �Լ�
{
	int i,j,k = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COLUMN; j++)
		{


			if (omok[i][j] < PLAYER1)
				cout << "��";
			else if (omok[i][j] == PLAYER1)
				cout << "��";
			else if (omok[i][j] == PLAYER2)
				cout << "��";
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

int InputF(int omok[][COLUMN], int first, int second)	// 1P �� ���� �Լ�
{
	cout << "1P ��ǥ(m��n��)�� �Է��ϼ���:(input (0,0) to exit)";
	while (1)
	{
		cin >> first;
		cin >> second;

		if (first == 0 && second == 0)
			return -1;
		if (first < 1 || second < 1 || first > ROW || second > COLUMN)
			cout << " �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���:" << endl;
		else if (omok[first-1][second-1] != PLAYER1 && omok[first-1][second-1] != PLAYER2)
		{
			omok[first-1][second-1] = PLAYER1;
			break;
		}
		else
			cout << "�Է��Ͻ� ��ǥ�� ���� �̹� �ֽ��ϴ�. �ٽ� �Է����ּ���:" << endl;

	}
	return 0;
}

int InputW(int omok[][COLUMN], int first, int second)	// 2P �� ���� �Լ�
{
	cout << "2P ��ǥ(m��n��)�� �Է��ϼ���(input (0,0) to exit)";
	while (1)
	{
		cin >> first;
		cin >> second;

		if (first == 0 && second == 0)
			return -1;
		if (first < 1 || second < 1 || first > ROW || second > COLUMN)
			cout << " �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���:" << endl;
		else if (omok[first-1][second-1] != PLAYER1 && omok[first-1][second-1] != PLAYER2)
		{
			omok[first - 1][second - 1] = PLAYER2;
			break;
		}
		else
			cout << "�Է��Ͻ� ��ǥ�� ���� �̹� �ֽ��ϴ�. �ٽ� �Է����ּ���:" << endl;

	}
	return 0;
}

void InputC(int omok[][COLUMN], int first, int second)	// ��ǻ�Ͱ� �� ���� �Լ�
{
	int row, col = 0;

	ComputePoint(omok);

	GetAttackPos(omok, &row, &col);

	omok[row][col]=PLAYER2;

}


int Bingo_1(int omok[][COLUMN]) // 1P 5�� üũ
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

int Bingo_2(int omok[][COLUMN]) // 2P (COMPUTER) 5�� üũ
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



int ComputePoint(int omok[][COLUMN]) // ��ǻ�Ͱ� ���� �ڸ� ����
{

	int row, col;
	int i=0;
	int count=1;
	int tempPlayer=0;

	// ����ġ 1 ����
	for(row=0;row<ROW;row++){
		for(col=0;col<COLUMN;col++){
			// LEFT ��
			if( col < COLUMN-1 && omok[row][col+1]==PLAYER1 && omok[row][col]<1 )
				omok[row][col]=1;
			else	// RIGHT �� 
				if( col > 0 && omok[row][col-1]==PLAYER1  && omok[row][col]<1)
					omok[row][col]=1;
				else	// DOWN ��
					if( row < ROW-1 && omok[row+1][col]==PLAYER1 && omok[row][col]<1)
						omok[row][col]=1;
					else	// UP ��
						if( row > 0 && omok[row-1][col]==PLAYER1 && omok[row][col]<1)
							omok[row][col]=1;
						else // ��
							if( (row < ROW-1 && col < COLUMN-1) && omok[row+1][col+1] == PLAYER1  && omok[row][col]<1)
								omok[row][col]=1;		
							else // ��
								if( (row > 0 && col > 0) && omok[row-1][col-1] == PLAYER1  && omok[row][col]<1)
									omok[row][col]=1;
								else // ��
									if( (row > 0 && col < COLUMN-1) && omok[row-1][col+1] == PLAYER1  && omok[row][col]<1)
										omok[row][col]=1;
									else // ��
										if( (row < ROW-1 && col > 0) && omok[row+1][col-1] == PLAYER1  && omok[row][col]<1)
											omok[row][col]=1;
		}
	}


	//���� ������ ���� �Ϲ� ����ġ 
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

				if(omok[row][col] < count){	 //������ ��뵹�� �ִٸ� 
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// RIGHT �� 
			if( col > 0 && omok[row][col] < PLAYER1 && omok[row][col-1] >=PLAYER1){

				count=0;
				tempPlayer=omok[row][col-1] ;

				for(i=col-1; i>=0;i--){
					if( omok[row][i] == tempPlayer )
						count++;
					else
						break;
				}


				if(omok[row][col] < count){	//������ ��뵹�� �ִٸ�
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}
			}
			// DOWN ��
			if( row < ROW && omok[row][col] < PLAYER1 && omok[row+1][col] >= PLAYER1){

				count=0;
				tempPlayer=omok[row+1][col] ;

				for(i=row+1; i<ROW ;i++){
					if( omok[i][col] == tempPlayer )
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//������ ��뵹�� �ִٸ�
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// UP ��
			if( row > 0 && omok[row][col] < PLAYER1 &&  omok[row-1][col]>=PLAYER1){

				count=0;
				tempPlayer=omok[row-1][col] ;

				for(i=row-1; i>=0 ;i--){
					if( omok[i][col] == tempPlayer )
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//������ ��뵹�� �ִٸ�
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ��
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

				if(omok[row][col] < count){	//������ ��뵹�� �ִٸ�
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ��
			if( (row > 0 && col > 0)  && omok[row][col] < PLAYER1 && omok[row-1][col-1] >=PLAYER1){

				count=0;
				tempPlayer=omok[row-1][col-1] ;

				for(i=1;i<5;i++){
					if((row-i>=0 && col-i>=0) && (omok[row-i][col-i]== tempPlayer))
						count++;
					else
						break;
				}

				if(omok[row][col] < count){	//������ ��뵹�� �ִٸ�
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ��
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

				if(omok[row][col] < count){	//������ ��뵹�� �ִٸ�
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}
			// ��
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

				if(omok[row][col] < count){	//������ ��뵹�� �ִٸ� 
					if(ISAnemyNear(omok, row, col, tempPlayer) == 1)
						omok[row][col]=count;
					else
						omok[row][col]=count+1;
				}

			}

		}
	}


	//--------------�ٸ� ����ġ ��� ���� ��ġ



	return 0;
}


void GetAttackPos(int omok[][COLUMN], int* row, int* col)	// ��ǻ�Ͱ� ���� �ڸ� GET
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


int ISAnemyNear(int omok[][COLUMN], int row, int col, int curPlayer)	// ����ġ �缳��
{
	int bTrue =0;


	// LEFT ��
	if( col < COLUMN-1 && omok[row][col+1]>=PLAYER1 && omok[row][col+1] !=curPlayer )
		bTrue = 1;
	// RIGHT �� 
	if( col > 0 && omok[row][col-1]>=PLAYER1  && omok[row][col-1] != curPlayer)
		bTrue = 1;
	// DOWN ��
	if( row < ROW-1 && omok[row+1][col]>=PLAYER1 && omok[row+1][col] != curPlayer)
		bTrue = 1;
	// UP ��
	if( row > 0 && omok[row-1][col]>=PLAYER1 && omok[row-1][col] != curPlayer)
		bTrue = 1;
	// ��
	if( (row < ROW-1 && col < COLUMN-1) && omok[row+1][col+1] >= PLAYER1  && omok[row+1][col+1] != curPlayer)
		bTrue = 1;		
	// ��
	if( (row > 0 && col > 0) && omok[row-1][col-1] >= PLAYER1  && omok[row-1][col-1] != curPlayer)
		bTrue = 1;
	// ��
	if( (row > 0 && col < COLUMN-1) && omok[row-1][col+1] >= PLAYER1  && omok[row-1][col+1] != curPlayer)
		bTrue = 1;
	// ��
	if( (row < ROW-1 && col > 0) && omok[row+1][col-1] >= PLAYER1  && omok[row+1][col-1] != curPlayer)
		bTrue = 1;


	return bTrue;
}

