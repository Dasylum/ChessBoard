#include <iostream>
#include <string.h>

using namespace std;

bool winner = false;
int player1 = 1;
int player2 = 2;
int currentPlayer = player1;

// 1 Pawn, 2 Rook, 3 Knight, 4 Bishop, 5 Queen, 6 King
int chessBoard[8][8] = {
    {2, 3, 4, 5, 6, 4, 3, 2},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {2, 3, 4, 5, 6, 4, 3, 2}};

// 1 for black and 2 for white
int blackAndWhiteTracker[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2}};

void displayChessBoard()
{

    for (int i = 0; i < 8; i++)
    {

        for (int j = 0; j < 8; j++)
        {

            cout << chessBoard[i][j];
        }

        cout << endl;
    }
}

void turnTheBoard()
{

    int temp;

    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 8; j++)
        {

            temp = chessBoard[i][j];
            chessBoard[i][j] = chessBoard[7 - i][j];
            chessBoard[7 - i][j] = temp;
        }
    }

    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 8; j++)
        {

            temp = blackAndWhiteTracker[i][j];
            blackAndWhiteTracker[i][j] = blackAndWhiteTracker[7 - i][j];
            blackAndWhiteTracker[7 - i][j] = temp;
        }
    }

    displayChessBoard();
}

int swapFunc(int x, int y, int locationX, int locationY)
{

    chessBoard[locationX][locationY] = chessBoard[x][y];
    chessBoard[x][y] = 0;

    blackAndWhiteTracker[locationX][locationY] = blackAndWhiteTracker[x][y];
    blackAndWhiteTracker[x][y] = 0;

    player1 = player2;
    player2 = currentPlayer;
    currentPlayer = player1;

    turnTheBoard();

    cout << endl
         << currentPlayer << "'s turn" << endl;

    return 0;
};

int moveValidityChecker(int x, int y, int locationX, int locationY)
{
    //Validation for piece
    if (chessBoard[x][y] != 0)
    {

        cout << "Valid piece..." << endl;
        //Validation for location
        if ((blackAndWhiteTracker[locationX][locationY] != currentPlayer) && (blackAndWhiteTracker[x][y] == currentPlayer))
        {

            cout << "Location is empty..." << endl;

            //Validation for move
            int piece = chessBoard[x][y];
            switch (piece)
            {
            case 1:
                if (locationX == (x + 1))
                {

                    if (locationY == (y + 1))
                    {

                        if (blackAndWhiteTracker[locationX][locationY] == 2)
                        {

                            cout << "Valid move..." << endl;
                            swapFunc(x, y, locationX, locationY);
                            return 1;
                        }

                        else
                        {
                            cout << "Invalid move..." << endl;
                        }
                    }

                    if (locationY == (y - 1))
                    {

                        if (blackAndWhiteTracker[locationX][locationY] == 2)
                        {

                            cout << "Valid move..." << endl;
                            swapFunc(x, y, locationX, locationY);
                            return 1;
                        }

                        else
                        {
                            cout << "Invalid move..." << endl;
                        }
                    }

                    if (locationY == y)
                    {

                        cout << "Valid move..." << endl;
                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }
                }
                else
                {
                    cout << "Invalid move..." << endl;
                }
                break;
            case 2:
                if (x == locationX)
                {
                    //Check the path for obstructions
                    if (y > locationY)
                    {
                        for (int i = (locationY + 1); i < y; i++)
                        {

                            if (chessBoard[x][i] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }

                    else
                    {
                        for (int i = (y + 1); i < locationY; i++)
                        {
                            if (chessBoard[x][i] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }
                }

                if (y == locationY)
                {

                    if (x > locationX)
                    {
                        for (int i = (locationX + 1); i < x; i++)
                        {

                            if (chessBoard[i][y] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }

                    else
                    {
                        for (int i = (x + 1); i < locationX; i++)
                        {
                            if (chessBoard[i][y] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }
                }

                cout << "This piece doesn't move like that...";
                break;
            case 3:
                if (abs(locationX - x) == 2)
                {

                    if (abs(locationY - y) == 1)
                    {

                        swapFunc(x, y, locationX, locationY);
                    }

                    else
                    {

                        cout << "Not a valid move..." << endl;
                    }
                }

                else if (abs(locationY - y) == 2)
                {

                    if (abs(locationX - x) == 1)
                    {

                        swapFunc(x, y, locationX, locationY);
                    }

                    else
                    {

                        cout << "Not a valid move..." << endl;
                    }
                }

                else
                {

                    cout << "Not a valid move..." << endl;
                }

                break;
            case 4:
                if (abs(locationX - x) == abs(locationY - y))
                {

                    if ((locationX - x) > 0)
                    {

                        if ((locationY - y) > 0)
                        {
                            int j = y + 1;

                            for (int i = x + 1; i < locationX; i++)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j++;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }

                        if ((locationY - y) < 0)
                        {
                            int j = y - 1;

                            for (int i = x + 1; i < locationX; i++)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j--;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }
                    }

                    if ((locationX - x) < 0)
                    {

                        if ((locationY - y) > 0)
                        {
                            int j = y + 1;

                            for (int i = x - 1; i > locationX; i--)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j++;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }

                        if ((locationY - y) < 0)
                        {
                            int j = y - 1;

                            for (int i = x - 1; i > locationX; i--)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j--;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }
                    }
                }

                else
                {

                    cout << "Not a valid move..." << endl;
                }

                break;
            case 5: 
                if (abs(locationX - x) == abs(locationY - y))
                {

                    if ((locationX - x) > 0)
                    {

                        if ((locationY - y) > 0)
                        {
                            int j = y + 1;

                            for (int i = x + 1; i < locationX; i++)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j++;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }

                        if ((locationY - y) < 0)
                        {
                            int j = y - 1;

                            for (int i = x + 1; i < locationX; i++)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j--;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }
                    }

                    if ((locationX - x) < 0)
                    {

                        if ((locationY - y) > 0)
                        {
                            int j = y + 1;

                            for (int i = x - 1; i > locationX; i--)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j++;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }

                        if ((locationY - y) < 0)
                        {
                            int j = y - 1;

                            for (int i = x - 1; i > locationX; i--)
                            {
                                if (chessBoard[i][j] != 0) {

                                    cout << "Path obstructed..." << endl;
                                    return 0;
                                }
                                j--;
                            }
                            swapFunc(x, y, locationX, locationY);
                        }
                    }
                }
                if (x == locationX)
                {
                    //Check the path for obstructions
                    if (y > locationY)
                    {
                        for (int i = (locationY + 1); i < y; i++)
                        {

                            if (chessBoard[x][i] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }

                    else
                    {
                        for (int i = (y + 1); i < locationY; i++)
                        {
                            if (chessBoard[x][i] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }
                }

                if (y == locationY)
                {

                    if (x > locationX)
                    {
                        for (int i = (locationX + 1); i < x; i++)
                        {

                            if (chessBoard[i][y] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }

                    else
                    {
                        for (int i = (x + 1); i < locationX; i++)
                        {
                            if (chessBoard[i][y] != 0)
                            {

                                cout << "Invalid move..." << endl;
                                return 0;
                            }
                        }

                        swapFunc(x, y, locationX, locationY);
                        return 1;
                    }
                }
            case 6:
                
            }
        }

        else
        {

            cout << "You already have a piece there...";
        }
    }

    return 0;
};

int main()
{

    int defaultPlayer = 8;

    int x, y;

    displayChessBoard();

    while (!winner)
    {

        cout << "Enter the position of your piece" << endl;
        cin >> x;
        cin >> y;

        int locationX, locationY;

        cout << "Enter the location where you want to move the piece" << endl;
        cin >> locationX;
        cin >> locationY;

        moveValidityChecker(x, y, locationX, locationY);
    }

    return 0;
}