#include <iostream>
#include <algorithm>

using namespace std;

#define SIZE 3
char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int player = 1;
bool isGameOver = false;

void printBoard() {
    cout << "-------------" << endl;
    for (int i = 0; i < SIZE; i++)
	{
        for (int j = 0; j < SIZE; j++)
		{
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
        cout << "-------------" << endl;
    }
}

void playerTurn()
{
    int a, b;
    do
	{
        cout << "Please input your choice: ";
        cin >> a >> b;
    }
	while (a < 0 || a >= SIZE || b < 0 || b >= SIZE || board[a][b] != ' ');
    board[a][b] = 'X';
}

bool checkWin(char p)
{
    for (int i = 0; i < SIZE; i++)
	{
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p)
            return true;
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p)
            return true;
    }
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p)
        return true;
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p)
        return true;

    return false;
}

bool checkTie() {
    for (int i = 0; i < SIZE; i++)
	{
        for (int j = 0; j < SIZE; j++)
		{
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

int minimax(bool isMaximizing)
{
    if (checkWin('O')) return 1;
    if (checkWin('X')) return -1;
    if (checkTie()) return 0;

    if (isMaximizing)
	{
        int bestScore = -1000;
        for (int i = 0; i < SIZE; i++)
		{
            for (int j = 0; j < SIZE; j++)
			{
                if (board[i][j] == ' ')
				{
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
	else
	{
        int bestScore = 1000;
        for (int i = 0; i < SIZE; i++)
		{
            for (int j = 0; j < SIZE; j++)
			{
                if (board[i][j] == ' ')
				{
                    board[i][j] = 'X';
                    int score = minimax(true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void computerTurn()
{
    int bestScore = -1000;
    int moveA = -1;
    int moveB = -1;
    for (int i = 0; i < SIZE; i++)
	{
        for (int j = 0; j < SIZE; j++)
		{
            if (board[i][j] == ' ')
			{
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore)
				{
                    bestScore = score;
                    moveA = i;
                    moveB = j;
                }
            }
        }
    }
    board[moveA][moveB] = 'O';
    cout << "Computer chose position: " << moveA << " " << moveB << endl;
}


int main()
{
    cout << "\t TIC TAC TOE ver C++" << endl;
    cout << "PLAYER 1 = [X]  COMPUTER = [O]" << endl;

    while (!isGameOver)
	{
        printBoard();

        if (player == 1)
		{
            playerTurn();
            if (checkWin('X'))
			{
                printBoard();
                cout << "Player wins!" << endl;
                isGameOver = true;
            } 
			else if (checkTie())
			{
                printBoard();
                cout << "It's a tie!" << endl;
                isGameOver = true;
            } 
			else 
			{
                player = 2;
            }
        } 
		else 
		{
            computerTurn();
            if (checkWin('O'))
			{
                printBoard();
                cout << "Computer wins!" << endl;
                isGameOver = true;
            } 
			else if (checkTie())
			{
                printBoard();
                cout << "It's a tie!" << endl;
                isGameOver = true;
            }
			else
			{
                player = 1;
            }
        }
    }
    return 0;
}

