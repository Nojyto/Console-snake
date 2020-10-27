#include <time.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int boardY = 15;
const int boardX = 20;
std::vector<int> snakeX, snakeY;
int movementDirection = KEY_LEFT;

void showCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void editSnake(const int& x, const int& y)
{
    snakeX.insert(snakeX.begin(), x);
    snakeX.pop_back();
    snakeY.insert(snakeY.begin(), y);
    snakeY.pop_back();
}

void moveSnake(const int& mvDir)
{
    if(snakeX.front() >= boardX) editSnake(1, snakeY.front());
    else if(snakeX.front() == 0) editSnake(boardX - 1, snakeY.front());
    else if(snakeY.front() >= boardY) editSnake(snakeX.front(), 1);
    else if(snakeY.front() == 0) editSnake(snakeX.front(), boardY - 1);
    else switch(mvDir){
        case KEY_UP: editSnake(snakeX.front(), snakeY.front() - 1); break;
        case KEY_DOWN: editSnake(snakeX.front(), snakeY.front() + 1); break;
        case KEY_LEFT: editSnake(snakeX.front() - 1, snakeY.front()); break;
        case KEY_RIGHT: editSnake(snakeX.front() + 1, snakeY.front()); break;
        default: moveSnake(movementDirection); return;
    }
    movementDirection = mvDir;
}

void printScreen(const int& points, const int& fruitX, const int& fruitY)
{
    system("cls");
    printf("Score: %i.\n", points);

    char board[boardY][boardX];

    for(int i = 0; i < boardY; i++){
        for(int j = 0; j < boardX; j++){
            if(i == 0 || i == boardY - 1 || j == 0 || j == boardX - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
        }
    }

    board[fruitY][fruitX] = '*';
    for(unsigned int i = 1; i < snakeX.size(); i++)
        board[snakeY[i]][snakeX[i]] = 'o';
    board[snakeY[0]][snakeX[0]] = 'x';

    for(int i = 0; i < boardY; i++){
        for(int j = 0; j < boardX; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    showCursor(false);
    int points = 0, fruitX = rand() % (boardX - 2) + 1, fruitY = rand() % (boardY - 2) + 1;
    bool game = true;

    for(int i = 0; i < 8; i++){
        snakeX.push_back(boardX/2 + i);
        snakeY.push_back(boardY/2);
    }

    while(game){
        !_kbhit() ? moveSnake(movementDirection) : moveSnake(getch());
        printScreen(points, fruitX, fruitY);

        for(unsigned int i = 1; i < snakeX.size(); i++)
            if(snakeX.front() == snakeX[i] && snakeY.front() == snakeY[i])
                game = false;

        if(snakeX.front() == fruitX && snakeY.front() == fruitY){
            fruitX = rand() % (boardX - 2) + 1;
            fruitY = rand() % (boardY - 2) + 1;
            snakeX.push_back(snakeX.back());
            snakeY.push_back(snakeY.back());
            points+= 10;
        }
        Sleep(80);
    }

    printf("\nGame Over!\n");
}
