#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

# define HEIGHT (25) // 4+20+1
# define WIDTH (12)  // 1+10+1

# define MINO "■"
# define WALL "□"
# define STATIC "■"
# define SPACE "・"

# define DELETE_POINT (100)
# define DROP_POINT (10)

# define SPEED (100)

#define co(y, x) ((y) * WIDTH + (x))


enum class Mino {
    I_MINO,
    O_MINO,
    S_MINO,
    Z_MINO,
    J_MINO,
    L_MINO,
    T_MINO,
    FRAME,
    EMPTY
};

enum class Status {
    MOVE,
    STOP,
    EMPTY,
    FRAME
};

struct Block {
    Mino kind;
    Status status;
};


void initStage (Block *stage) {

    for (int y = 0; y < HEIGHT - 1; ++y) {
        for (int x = 0; x < WIDTH; ++x) {

            switch (x) {
                case 0:
                    stage[co(y, x)].kind = Mino::FRAME;
                    stage[co(y, x)].status = Status::FRAME;
                    break;
                
                
                case WIDTH - 1:
                    stage[co(y, x)].kind = Mino::FRAME;
                    stage[co(y, x)].status = Status::FRAME;
                    break;

                
                default:
                    stage[co(y, x)].kind = Mino::EMPTY;
                    stage[co(y, x)].status = Status::EMPTY;
            }
        }
    }
}


int randint (int min, int max) {
    int s = rand() % (max + 1) + min;
    return s;
}


void decisionNext (Mino *next, int begin) {
    int temp, number[7] = {0, 1, 2, 3, 4, 5, 6};


    for (int i = 0; i < 7; ++i) {
        temp = randint(0, 6 - i);


        switch (number[temp]) {
            case 0: 
                next[i + begin] = Mino::I_MINO;
                break;

            case 1:
                next[i + begin] = Mino::O_MINO;
                break;

            case 2:
                next[i + begin] = Mino::S_MINO;
                break;

            case 3:
                next[i + begin] = Mino::Z_MINO;
                break;

            case 4:
                next[i + begin] = Mino::J_MINO;
                break;

            case 5:
                next[i + begin] = Mino::L_MINO;
                break;

            case 6:
                next[i + begin] = Mino::T_MINO;
                break;
        }


        for (int j = temp; j < 6 - i; ++j)
        {
            number[j] = number[j + 1];
        }
    }
}


void changeStop (Block *stage) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {

            if (stage[co(y, x)].status == Status::MOVE) stage[co(y, x)].status = Status::STOP;
        }
    }
}


void delMove (Block *stage) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {

            if (stage[co(y, x)].status == Status::MOVE) {
                stage[co(y, x)].status = Status::EMPTY;
                stage[co(y, x)].kind = Mino::EMPTY;
            }
        }
    }
}


int moveMino (Block *stage, int dy, int dx) //(y + dy, x + dx) に移動
{
    int tempCo[8], cCount = 0, kCount = 0;
    Mino tempKind[4];


    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (stage[co(y, x)].status == Status::MOVE)
            {

                tempCo[cCount] = y + dy;
                tempCo[cCount + 1] = x + dx;

                tempKind[kCount] = stage[co(y, x)].kind;

                cCount += 2;
                kCount ++;
            }
        }
    }


    for (int i = 0; i < 8; i += 2)
    {
        if (stage[co(tempCo[i], tempCo[i + 1])].status != Status::MOVE && stage[co(tempCo[i], tempCo[i + 1])].status != Status::EMPTY)
        {
            return 0;
        }
    }


    delMove(&stage[0]); 


    for (int i = 0; i < 4; ++i) {
        stage[co(tempCo[i * 2], tempCo[i * 2 + 1])].status = Status::MOVE;
        stage[co(tempCo[i * 2], tempCo[i * 2 + 1])].kind = tempKind[i];

    }


    return 0;
}


void placeMino (Block *stage, Mino argKind)
{
    switch ((int) argKind)
    {
        case (int) Mino::I_MINO:
            stage[co(4, 4)].status = Status::MOVE, stage[co(4, 5)].status = Status::MOVE;
            stage[co(4, 6)].status = Status::MOVE, stage[co(4, 7)].status = Status::MOVE;
            stage[co(4, 4)].kind = argKind, stage[co(4, 5)].kind = argKind;
            stage[co(4, 6)].kind = argKind, stage[co(4, 7)].kind = argKind;
            break;

        
        case (int) Mino::O_MINO:
            stage[co(4, 5)].status = Status::MOVE, stage[co(4, 6)].status = Status::MOVE;
            stage[co(5, 5)].status = Status::MOVE, stage[co(5, 6)].status = Status::MOVE;
            stage[co(4, 5)].kind = argKind, stage[co(4, 6)].kind = argKind;
            stage[co(5, 5)].kind = argKind, stage[co(5, 6)].kind = argKind;
            break;

        
        case (int) Mino::S_MINO:
            stage[co(4, 6)].status = Status::MOVE, stage[co(4, 7)].status = Status::MOVE;
            stage[co(5, 5)].status = Status::MOVE, stage[co(5, 6)].status = Status::MOVE;
            stage[co(4, 6)].kind = argKind, stage[co(4, 7)].kind = argKind;
            stage[co(5, 5)].kind = argKind, stage[co(5, 6)].kind = argKind;
            break;


        case (int) Mino::Z_MINO:
            stage[co(4, 5)].status = Status::MOVE, stage[co(4, 6)].status = Status::MOVE;
            stage[co(5, 6)].status = Status::MOVE, stage[co(5, 7)].status = Status::MOVE;
            stage[co(4, 5)].kind = argKind, stage[co(4, 6)].kind = argKind;
            stage[co(5, 6)].kind = argKind, stage[co(5, 7)].kind = argKind;
            break;


        case (int) Mino::J_MINO:
            stage[co(4, 5)].status = Status::MOVE, stage[co(4, 6)].status = Status::MOVE;
            stage[co(4, 7)].status = Status::MOVE, stage[co(5, 7)].status = Status::MOVE;
            stage[co(4, 5)].kind = argKind, stage[co(4, 6)].kind = argKind;
            stage[co(4, 7)].kind = argKind, stage[co(5, 7)].kind = argKind;
            break;


        case (int) Mino::L_MINO:
            stage[co(4, 5)].status = Status::MOVE, stage[co(4, 6)].status = Status::MOVE;
            stage[co(4, 7)].status = Status::MOVE, stage[co(5, 5)].status = Status::MOVE;
            stage[co(4, 5)].kind = argKind, stage[co(4, 6)].kind = argKind;
            stage[co(4, 7)].kind = argKind, stage[co(5, 5)].kind = argKind;
            break;


        case (int) Mino::T_MINO:
            stage[co(4, 5)].status = Status::MOVE, stage[co(4, 6)].status = Status::MOVE;
            stage[co(4, 7)].status = Status::MOVE, stage[co(5, 6)].status = Status::MOVE;
            stage[co(4, 5)].kind = argKind, stage[co(4, 6)].kind = argKind;
            stage[co(4, 7)].kind = argKind, stage[co(5, 6)].kind = argKind;
            break;
    }
}
