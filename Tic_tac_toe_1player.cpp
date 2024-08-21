#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define size 3
char board[size][size] = { {' ', ' ',' '}, {' ', ' ',' '}, {' ', ' ',' '} };
int player = 1;
bool isGameOver = false;
bool isTie = false;


void printBoard() {
    cout << "-------------" << endl;
    for (unsigned int i = 0; i < size; i++)
	    {
        for (unsigned int j = 0; j < size; j++)
		{
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
        cout << "-------------" << endl;
    }
}

void playerTurn() {
    int a, b;
    do
	{
        cout << "Please input your choice: ";
        cin >> a >> b;
    } while (a > 2 || b > 2 || board[a][b] != ' ');
    board[a][b] = 'X';
}

bool checkBoard();
int minimax (bool isMaximizing)
{
    if (checkBoard())
	{
        if (player == 1) return -1;
        if (player == 2) return 1;
    }

    if (isMaximizing)
	{
        int bestScore = -1000;
        for (int i = 0; i < size; i++)
		{
            for (int j = 0; j < size; j++)
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
        for (int i = 0; i < size; i++)
		{
            for (int j = 0; j < size; j++)
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
    for (int i = 0; i < size; i++)
	{
        for (int j = 0; j < size; j++)
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
    cout << "Computer choose position: " << moveA << " " << moveB << endl;
}

bool checkBoard()
{
    for (int i = 0; i < size; i++)
	{
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true;
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    bool tie = true;
    for (int i = 0; i < size; i++)
	{
        for (int j = 0; j < size; j++)
		{
            if (board[i][j] == ' ')
			{
                tie = false;
                break;
            }
        }
        if (!tie) break;
    }
    return tie;
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
            player = 2;
        }
		else
		{
            computerTurn();
            player = 1;
        }
        isGameOver = checkBoard();
        if (isGameOver)
		{
            printBoard();
            if (isTie)
                cout << "It's a tie" << endl;
            else if (player == 1)
                cout << "Computer wins!" << endl;
            else
                cout << "Player wins!" << endl;
        }
    }
    return 0;
}  

