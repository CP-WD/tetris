#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<fstream>

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

int point = 0;


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

    for (int i = 0; i < WIDTH; ++i) {

        stage[co(HEIGHT - 1, i)].kind = Mino::FRAME;
        stage[co(HEIGHT - 1, i)].status = Status::FRAME;

    }
}


int randint (int min, int max) {
    int s = rand() % (max + 1) + min;
    return s;
}


void decisionNext (Mino *next) {
    int temp, number[7] = {0, 1, 2, 3, 4, 5, 6};


    for (int i = 0; i < 7; ++i) {
        temp = randint(0, 6 - i);


        switch (number[temp]) {
            case 0: 
                next[i] = Mino::I_MINO;
                break;

            case 1:
                next[i] = Mino::O_MINO;
                break;

            case 2:
                next[i] = Mino::S_MINO;
                break;

            case 3:
                next[i] = Mino::Z_MINO;
                break;

            case 4:
                next[i] = Mino::J_MINO;
                break;

            case 5:
                next[i] = Mino::L_MINO;
                break;

            case 6:
                next[i] = Mino::T_MINO;
                break;
        }


        for (int j = temp; j < 6 - i; ++j) {
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


int moveMino (Block *stage, int dy, int dx) {//(y + dy, x + dx) に移動
    int tempCo[8], cCount = 0, kCount = 0;
    Mino tempKind[4];


    for (int y = 0; y < HEIGHT; ++y) {

        for (int x = 0; x < WIDTH; ++x) {

            if (stage[co(y, x)].status == Status::MOVE) {

                tempCo[cCount] = y + dy;
                tempCo[cCount + 1] = x + dx;

                tempKind[kCount] = stage[co(y, x)].kind;

                cCount += 2;
                kCount ++;
            }
        }
    }


    for (int i = 0; i < 8; i += 2) {

        if (stage[co(tempCo[i], tempCo[i + 1])].status != Status::MOVE && stage[co(tempCo[i], tempCo[i + 1])].status != Status::EMPTY) {

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


void placeMino (Block *stage, Mino argKind) {
    switch ((int) argKind) {

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


void clear (void) {
    system ("cls");
}


int landing (Block *stage) {
    for (int i = 0; i < HEIGHT; ++i) {

        for (int j = 0; j < WIDTH; ++j) {

            if (stage[co(i, j)].status == Status::MOVE) {

                if (stage[co(i + 1, j)].status != Status::MOVE && stage[co(i + 1, j)].status != Status::EMPTY) {

                    return 1;
                }
            }
        }
    }

    return 0;
}


void drop (Block *stage) {
    Mino tempKind[4];
    int coordinate[8], count = 0, downCount = 0;
    int dx = 0, dy = 1;


    while (1) {
        count = 0;
        if (landing (&stage[0])) {
            point += downCount * DROP_POINT;
            break;
        }

        moveMino(&stage[0], 1, 0);
        downCount += 1;
    }
}


int deleteLine (Block*stage) {
    int count, returnNum = 0;


    for (int i = 0; i < HEIGHT; ++i) {

        count = 0;

        for (int j = 0; j < WIDTH; ++j) {

            if (stage[co(i, j)].status == Status::STOP) {

                ++count;
            }
        }


        if (count == 10) {

            returnNum = 1;

            for (int m = 1; m < WIDTH - 1; ++m) {

                stage[co(i, m)].status = Status::EMPTY;
                stage[co(i, m)].kind = Mino::EMPTY;
            }


            for (int k = i; k > 0; --k) {

                for (int l = 1; l < WIDTH - 1; ++l) {

                    stage[co(k, l)] = stage[co(k - 1, l)];
                }
            }

        }
    }

    return returnNum;
}


int turnMino (Block *stage) {

    int maxI = 0, minI = 100, maxJ = 0, minJ = 100;
    int dx = 0, dy = 0;
    int tempWidth = 0;


    for (int i = 0; i < HEIGHT; ++i) {// ミノの上下幅の取得

        for (int j = 0; j < WIDTH; ++j) {

            if (stage[co(i, j)].status == Status::MOVE) {

                if (i > maxI) maxI = i;
                if (i < minI) minI = i;
                
                if (j > maxJ) maxJ = j;
                if (j < minJ) minJ = j;
            }
        }   
    }



    if (maxI - minI > maxJ - minJ) tempWidth = maxI - minI + 1; // tempStageのサイズの決定
    else tempWidth = maxJ - minJ + 1;

    Block tempStage[tempWidth][tempWidth];
    Block tempStageTwo[tempWidth][tempWidth];

    dy = maxI - tempWidth + 1, dx = minJ; // tempStageの[0][0]の位置

    if (dx + tempWidth >= WIDTH || dy + tempWidth >= HEIGHT) return 0;



    for (int y = 0; y < tempWidth; ++y) {// 回転するミノの部分をtempStageにコピー

        for (int x = 0; x < tempWidth; ++x) {

			tempStage[y][x] = stage[co(y + dy, x + dx)];
        }
    }

    delMove(&stage[0]);


    for (int y = 0; y < tempWidth; ++y) {// 壁の巻き込みチェック
        
        for (int x = 0; x < tempWidth; ++x) {

			if (tempStage[y][x].status != Status::MOVE && tempStage[y][x].status != Status::EMPTY) return 0;
        }
    }


    for (int y = 0; y < tempWidth; ++y) { // tempStageを回転させtempStageTwoにコピー

        for (int x = 0; x < tempWidth; ++x) {

			tempStageTwo[y][x] = tempStage[tempWidth - 1 - x][y];
        }
    }


    while (1) // 上昇防止
    {
        int cnt = 0;

        for (int x = 0; x < tempWidth; ++x) {

            if (tempStageTwo[tempWidth - 1][x].status == Status::MOVE) cnt += 1;
        }

        if (cnt != 0) break;

        for (int i = tempWidth - 1; i > 0; --i) {

            for (int j = 0; j < tempWidth; ++j) {

                tempStageTwo[i][j] = tempStageTwo[i - 1][j];
            }
        }

        for (int j = 0; j < tempWidth; ++j) {

            tempStageTwo[0][j].status = Status::EMPTY;
            tempStageTwo[0][j].kind = Mino::EMPTY;

        }
    }


    for (int y = 0; y < tempWidth; ++y) {// tempStageTwoをStageに戻す
        
        for (int x = 0; x < tempWidth; ++x) {

            stage[co(y + dy, x + dx)] = tempStageTwo[y][x];
        }
    }


    return 0;
}


int pow (int x, int y) {

    int ans = 1;

    for (int i = 0; i < y; i++) {
        ans *= x;
    }

    return ans;
}


void swapMino(Block *stage, Mino *next) {

    static Mino minoBuffer = Mino::EMPTY;
    Mino tempKind = Mino::EMPTY;


    for (int y = 0; y < HEIGHT; ++y) {

        for (int x = 0; x < WIDTH; ++x) {

            if (stage[co(x, y)].status == Status::MOVE) {

                tempKind = stage[co(x, y)].kind;
                break;
            }
        }
        if (tempKind != Mino::EMPTY) break;
    }


    delMove(&stage[0]);


    if (minoBuffer == Mino::EMPTY) {
        placeMino(&stage[0], next[0]);
        minoBuffer = tempKind;
    }

    else {
        placeMino(&stage[0], minoBuffer);
        minoBuffer = tempKind;
    }
}


void writeStage (Block *stage)
{
    int count = 0;
    for (int i = 4; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            switch ((int) stage[co(i, j)].kind)
            {
                case (int) Mino::EMPTY:
                    std::cout << SPACE;
                    break;


                case (int) Mino::I_MINO:
                    std::cout << "\033[36m" << MINO << "\033[m";
                    break;


                case (int) Mino::O_MINO:
                    std::cout << "\033[33m" << MINO << "\033[m";
                    break;

                case (int) Mino::S_MINO:
                    std::cout << "\033[32m" << MINO << "\033[m";
                    break;

                
                case (int) Mino::Z_MINO:
                    std::cout << "\033[31m" << MINO << "\033[m";
                    break;


                case (int) Mino::J_MINO:
                    std::cout << "\033[34m" << MINO << "\033[m";
                    break;


                case (int) Mino::L_MINO:
                    std::cout << "\033[37m" << MINO << "\033[m";
                    break;


                case (int) Mino::T_MINO:
                    std::cout << "\033[35m" << MINO << "\033[m";
                    break;


                default:
                    std::cout << WALL;
                    break;

            }
        }
        std::cout << std::endl;
    }
    std::cout << point << std::endl;
}


void slideNext (Mino *next) {

    for (int i = 0; i < 13; ++i) {

        next[i] = next[i + 1];
    }
}


int operation (Block *stage, Mino *next)
{

    placeMino (&stage[0], next[0]);
    slideNext(&next[0]);
    clear ();
    writeStage (&stage[0]);
    Sleep (SPEED);

    while(1) {

        if (landing (&stage[0]))
        {
            changeStop(&stage[0]);
            clear ();
            writeStage (&stage[0]);
            break;
        }



        clear ();
        moveMino (&stage[0], 1, 0);

        writeStage (&stage[0]);
        Sleep (SPEED);

        if (kbhit ())
        {
            int key = getch ();

            if (key == 105) //I
            {
                drop (&stage[0]);
            }

			else if (key == 108) //L
            {
				moveMino (&stage[0], 0, 1);
			}

            else if (key == 106) //Jc
            {
                moveMino (&stage[0], 0, -1);
            }

            else if (key == 107) //K
            {
                turnMino (&stage[0]);
            }

            else if (key == 32) //Space
            {
                swapMino(&stage[0], &next[0]);
            }
            clear ();
            writeStage (&stage[0]);
		}
    }
    
    return 0;
}


int main (void)
{
    std::ofstream outputfile("test.txt");
    srand(time(NULL));
    int end = 0;

    Block stage[HEIGHT * WIDTH];
    Mino next[14];


    initStage (&stage[0]);
    writeStage (&stage[0]);
    decisionNext (&next[0]);
    decisionNext (&next[7]);


    while (1)
    {
        int count = 0;


        for (int i = 0; i < 7; i++)
        {
            for(int f = 0; f < 14; ++f) {
                outputfile << (int) next[f] << " / ";
            }
            outputfile << std::endl;

            end = operation (&stage[0], &next[0]);


            for (int i = 1; i < WIDTH - 1; ++i)
            {
                if (stage[co(4, i)].status == Status::STOP)
                {
                    std::cout << "Game Over";
                    outputfile.close();
                    return 0;
                }
            }


            for (int j = 0; j < 4; ++j)
            {
                count += deleteLine(&stage[0]);
            }

            point += pow(DELETE_POINT ,count);

            //slideNext(&next[0]);
        }
        decisionNext (&next[7]);
    }
}
