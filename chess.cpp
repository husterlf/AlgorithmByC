// chess.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//写一个对弈的三步棋程序
//VS2019编译通过，windows控制台程序
//采用极大极小策略加上α-β裁剪

#include<iostream>
#include<vector>

using namespace std;

typedef vector<vector<char>>* BoardType;


enum SCORES
{
	CompLoss=-1,
	Draw,
	CompWin
};

enum PLAYER
{
	Comp,
	Human
};

void FindHumanMove(BoardType Board, int* BestMove, int* Value , int Alpha, int Beta);
bool isWinned(BoardType Board, int loc, PLAYER P);

void print_chess(vector<vector<char>> &P)
{
	cout << "=================" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "-------------------" << endl;
		for (int j = 0; j < 3; j++)
		{
			cout <<" | "<< P[i][j]<<" |";
		}

		cout << endl;
	}
	cout << "-------------------" << endl;
	cout << "=================" << endl;
}

bool FullBoard(BoardType Board)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (Board->at(i)[j] == ' ')
				return false;

	return true;
}

//电脑执'X'子，人类执'O'子，空闲位置为' '
//位置由0-8的整型表示
bool ImmediateCompWin(BoardType Board,int *BestMove)
{
	int loc = *BestMove;
	if ((Board->at(0)[0] == 'X' && Board->at(0)[1] == 'X' && Board->at(0)[2] == 'X') ||
		(Board->at(1)[0] == 'X' && Board->at(1)[1] == 'X' && Board->at(1)[2] == 'X') ||
		(Board->at(2)[0] == 'X' && Board->at(2)[1] == 'X' && Board->at(2)[2] == 'X') ||
		(Board->at(0)[0] == 'X' && Board->at(1)[0] == 'X' && Board->at(2)[0] == 'X') ||
		(Board->at(0)[1] == 'X' && Board->at(1)[1] == 'X' && Board->at(2)[1] == 'X') ||
		(Board->at(0)[2] == 'X' && Board->at(1)[2] == 'X' && Board->at(2)[2] == 'X') ||
		(Board->at(0)[0] == 'X' && Board->at(1)[1] == 'X' && Board->at(2)[2] == 'X') ||
		(Board->at(0)[2] == 'X' && Board->at(1)[1] == 'X' && Board->at(2)[0] == 'X') 
		)
		return true;

	return false;
}

bool ImmediateHumanWin(BoardType Board, int* BestMove)
{
	int loc = *BestMove;
	if ((Board->at(0)[0] == 'O' && Board->at(0)[1] == 'O' && Board->at(0)[2] == 'O') ||
		(Board->at(1)[0] == 'O' && Board->at(1)[1] == 'O' && Board->at(1)[2] == 'O') ||
		(Board->at(2)[0] == 'O' && Board->at(2)[1] == 'O' && Board->at(2)[2] == 'O') ||
		(Board->at(0)[0] == 'O' && Board->at(1)[0] == 'O' && Board->at(2)[0] == 'O') ||
		(Board->at(0)[1] == 'O' && Board->at(1)[1] == 'O' && Board->at(2)[1] == 'O') ||
		(Board->at(0)[2] == 'O' && Board->at(1)[2] == 'O' && Board->at(2)[2] == 'O') ||
		(Board->at(0)[0] == 'O' && Board->at(1)[1] == 'O' && Board->at(2)[2] == 'O') ||
		(Board->at(0)[2] == 'O' && Board->at(1)[1] == 'O' && Board->at(2)[0] == 'O')
		)
		return true;

	return false;
}

bool IsEmpty(BoardType Board, int Location)
{
	int i = Location / 3;
	int j = Location % 3;
	if (Board->at(i)[j] == ' ')
			return true;

	return false;
}

void Place(BoardType Board, int Location,PLAYER P)
{
	if (Location >= 0 && Location <= 8)
	{
		char ch = P == Comp ? 'X' : 'O';
		int i = Location / 3;
		int j = Location % 3;
		Board->at(i)[j] = ch;
	}

}

void Unplace(BoardType Board,int Location)
{
	if (Location >= 0 && Location <= 8)
	{
		int i = Location / 3;
		int j = Location % 3;
		Board->at(i)[j] = ' ';
	}

}

void FindCompMove(BoardType Board, int* BestMove, int* Value, int Alpha, int Beta)
{
	int Dc, i, Response;
	//static int times = 0;
	//times++;
	//cout << "Comp depth:" << depth << "   Times:" << times << endl;
	if (FullBoard(Board))
		*Value = Draw;
	else if (ImmediateCompWin(Board, BestMove))
		*Value = CompWin;
	else
	{
		//*Value = CompLoss;
		*Value = Alpha;
		for (i = 0; i <= 8&&*Value<Beta; ++i)
		//for (i = 0; i <= 8; ++i)
		{
			if (IsEmpty(Board, i))
			{
				Place(Board, i, Comp);
				FindHumanMove(Board, &Dc, &Response,*Value,Beta);
				Unplace(Board, i);

				if (Response > *Value)
				{
					*Value = Response;
					*BestMove = i;
				}
			}
		}
	}
};


void FindHumanMove(BoardType Board, int* BestMove, int* Value, int Alpha, int Beta)
{
	int Dc, i, Response;

	if (FullBoard(Board))
		*Value = Draw;
	else if (ImmediateHumanWin(Board, BestMove))
		*Value = CompLoss;
	else
	{
		//*Value = CompWin;
		*Value = Beta;
		for (i = 0; i <= 8&&*Value>Alpha; ++i)
		//for (i = 0; i <= 8 ; ++i)
		{
			if (IsEmpty(Board, i))
			{
				Place(Board, i, Human);
				FindCompMove(Board, &Dc, &Response,Alpha,*Value);
				Unplace(Board, i);

				if (Response < *Value)
				{
					*Value = Response;
					*BestMove = i;
				}
			}
		}
	}
};

void reset(int& flag, vector<vector<char>>& board)
{
	flag = 0;
	for (auto& i : board)
		for (auto& j : i)
			j = ' ';

};

int main()
{

	vector<vector<char>> chess(3, vector<char>(3, ' '));// {' ', ' ', ' '}, { ' ',' ',' ' }, { ' ',' ',' ' }
	//int k = 0;
	//reset(k, chess);
	BoardType b = &chess;


	int pBestMove;
	int pValue;


	int flag = 0;

	for (;;)
	{
		if (flag == 0)
		{
			Place(b, rand() % 9, Comp);
			print_chess(chess);
			flag = 1;
			cout << "Input any data which is not a INT type to RESET GAME. " << endl;
		}
		
		int loc;
		
		cout << "Input your chess Loction(0-8):" << endl;
		if (cin >> loc)
		{
			if (loc >= 0 && loc <= 8)
			{
				//确认输入有效并判断人类方输赢
				int row = loc / 3;
				int col = loc % 3;
				if (chess[row][col] == ' ')
				{
					Place(b, loc, Human);
					print_chess(chess);
					if (ImmediateHumanWin(b, &loc))
					{
						cout << "Congradulation!You win!" << endl;
						system("pause");
					//	cin.clear();
					//	cin.ignore(1000, '\n');
						reset(flag, chess);
						system("cls");
						cout << "Game has been restarted!" << endl;
						continue;
					}
				}
				else
				{
					cout << "Your input location is not EMPTY!Please try other location." << endl;
					continue;
				}
				
			}	
			else
			{
				cout << "Input location must be in 0-8! Try again." << endl;
				continue;
			}
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			reset(flag, chess);
			system("cls");
			cout << "Game has been reset!" << endl;
			continue;
		}
			

		FindCompMove(b, &pBestMove, &pValue , -1, 1);
		Place(b, pBestMove, Comp);
		print_chess(chess);
		if (ImmediateCompWin(b, &pBestMove))
		{
			cout << "Computer Win!\n." << endl;
			system("pause");
			//	cin.clear();
			//	cin.ignore(1000, '\n');
			reset(flag, chess);
			system("cls");
			cout << "Game has been restarted!" << endl;
			continue;
		}
		
		if (FullBoard(b))
		{
			cout << "End in a draw!  Good For You!" << endl;
			system("pause");
			//	cin.clear();
			//	cin.ignore(1000, '\n');
			reset(flag, chess);
			system("cls");
			cout << "Game has been restarted!" << endl;
		}
	}

}


