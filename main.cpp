#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y,fx,fy,score;
int tailx[100],taily[100];
int ntail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fx = rand() % width;
    fy = rand() % height;
}

void Draw(){
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "*";
    cout << endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < height; j++){
            if (j == 0)
                cout << "*";
            if (i == y && j == x)
                cout << "A";
            else if (i == fy && j == fx)
                cout << "X";
            else{
                bool print = false;
                for (int k = 0; k < ntail; k++){

                    if (tailx[k] == j && taily[k] == i){
                        cout << 'a';
                        print = true;
                    }

                }
                if (!print)
                    cout << " ";

            }

            if (j == width - 1)
                cout << "*";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "*";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input(){
    if (_kbhit()){
        switch (_getch()){
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic(){
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++){
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir){
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if ( x > width || x < 0 || y < 0 || y > height)
        gameOver = true;
    for (int i = 0; i < ntail; i++){
        if (tailx[i] == x && taily[i] == y)
            gameOver = true;
    }
    if ( x == fx && y == fy){
        score += 10;
        ntail++;
        fx = rand() % width;
        fy = rand() % height;
    }
}

int main()
{
    //cout << "Hello world!" << endl;
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(30);
        if(gameOver){
            cout<< "Good try!" << endl;
        }
    }
    return 0;
}
