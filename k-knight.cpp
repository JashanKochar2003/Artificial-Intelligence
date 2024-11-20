#include <iostream>
#include <ctime>
using namespace std;

int rows, cols;
int counts = 0;

void display(int **board)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool isPlaceAvailable(int **board, int x, int y)
{
  int knightMoves[8][2] = {
      {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

  for (int i = 0; i < 8; i++)
  {
    int X = x + knightMoves[i][0];
    int Y = y + knightMoves[i][1];

    if (X >= 0 && X < rows && Y >= 0 && Y < cols)
    {
      if (board[X][Y] == 1)
      {
        return false;
      }
    }
  }
  return true;
}

void solve(int **board, int KnightsLeft, int x, int y)
{
  if (KnightsLeft == 0)
  {
    counts++;
    cout << "Solution Number  " << counts << ":" << endl;
    display(board);
    return;
  }

  if (x >= rows)
    return;

  if (y >= cols)
  {
    solve(board, KnightsLeft, x + 1, 0);
    return;
  }

  int availableCells = (rows * cols) - (x * cols + y);
  if (availableCells < KnightsLeft)
    return;

  if (isPlaceAvailable(board, x, y))
  {
    board[x][y] = 1;
    solve(board, KnightsLeft - 1, x, y + 1);
    board[x][y] = 0;
  }

  solve(board, KnightsLeft, x, y + 1);
}

int main()
{
  double start, end, totalTime;
  cout << "Enter number of rows and columns in a board: ";
  cin >> rows >> cols;

  int **board = new int *[rows];
  for (int i = 0; i < rows; i++)
  {
    board[i] = new int[cols];
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      board[i][j] = 0;
    }
  }

  cout << "Enter the number of knights to place: ";
  int knights;
  cin >> knights;

  start = (double)clock();
  solve(board, knights, 0, 0);
  end = (double)clock();
  totalTime = (end - start) / CLOCKS_PER_SEC;

  if (counts == 0)
  {
    cout << "No solutions exist!" << endl;
  }
  else
  {
    cout << "Total number of solutions are : " << counts << endl;
  }
  cout << "Total time taken: " << totalTime << " seconds" << endl;

  for (int i = 0; i < rows; i++)
  {
    delete[] board[i];
  }
  delete[] board;

  return 0;
}