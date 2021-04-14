#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

# define HEIGHT (25) // 4+20+1
# define WIDTH (12)  // 1+10+1

# define MINO "■"
# define WALL "□"
# define STATIC "■"
# define SPACE "・"

# define DELETE_POINT (100)
# define DROP_POINT (10)

# define SPEED (100)


int stage[HEIGHT][WIDTH], next[7];
int swap[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int point = 0;

enum KIND_OF_MINO
{
    I_MINO,
    O_MINO,
    S_MINO,
    Z_MINO,
    J_MINO,
    L_MINO,
    T_MINO
};

int randint (int min, int max); // 乱数と言いつつ一定の値（dekita）
int landing (void);
int operation (int kind); // 接地した後一回更新するまで固定しないてきな
int landing (void);
int deleteLine (void); // 消え方の挙動がおかしい(多分直った)
void drop (void);
void clear (void);
int moveMino (int dx, int dy); // 横から壁やミノに刺せる(直った)
void stageInit (void);
void decisionNext (void);
void writeStage (void);
void writeStageNum (void);
void oneToZero (void);
void changeStatic (void);
void sleep (int s);
void placeMino (int kind);
int turnMino (void);
int swapMino (int kind); // 一度目のスワップで次のミノの取得ができるといいかも



int main (void)
{
    srand(time(NULL));
    int end = 0;


    stageInit ();
    writeStage ();
    decisionNext ();


    while (1)
    {
        int count = 0;


        for (int i=0;i<7;i++)
        {
            end = operation (next[i]);


            for (int i=1;i<WIDTH-1;++i)
            {
                if (stage[4][i] == 2)
                {
                    std::cout << "Game Over";
                    return 0;
                }
            }


            for (int j=0;j<4;++j)
            {
                count += deleteLine ();
            }

            point += pow(DELETE_POINT ,count);
        }
        
        decisionNext ();
    }
}



void stageInit (void)
{
    for (int i=0;i<HEIGHT-1;++i)
    {
        for (int j=0;j<WIDTH;++j)
        {
            switch (j)
            {
                case 0:
                    stage[i][j] = 3;
                    break;


                case WIDTH-1:
                    stage[i][j] = 3;
                    break;

                
                default:
                    stage[i][j] = 0;
                    break;

            }
        }
    }


    for (int j=0;j<WIDTH;++j)
    {
        stage[HEIGHT-1][j] = 4;
    }
}


int randint (int min, int max)
{
    int s = rand() % (max+1) + min;
    return s;
}


void decisionNext (void)
{
    int i, j, temp;
    int tempNumber[] = {0,1,2,3,4,5,6};


    for (i=0;i<7;++i)
    {
        temp = randint(0, 6-i);
        next[i] = tempNumber[temp];


        for (j=temp;j<6-i;++j)
        {
            tempNumber[j] = tempNumber[j+1];
        }
    }
}


void writeStage (void)
{
    int count = 0;
    for (int i=4;i<HEIGHT;++i)
    {
        for (int j=0;j<WIDTH;++j)
        {
            switch (stage[i][j])
            {
                case 0:
                    std::cout << SPACE;
                    break;


                case 1:
                    std::cout << MINO;
                    break;

                
                case 2:
                    std::cout << STATIC;
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


void oneToZero (void)
{
    for (int y=0;y<HEIGHT;++y)
    {
        for (int x=0;x<WIDTH;++x)
        {
            if (stage[y][x] == 1) stage[y][x] = 0;
        }
    }
}


void changeStatic (void)
{
    for (int y=0;y<HEIGHT;++y)
    {
        for (int x=0;x<WIDTH;++x)
        {
            if (stage[y][x] == 1)
            {
                stage[y][x] = 2;
            }
        }
    }
}


void sleep (int s)
{
    Sleep(s);
}


int moveMino (int dx, int dy)
{
    int coordinate[8] = {0,0,0,0,0,0,0,0}, count = 0;


    for (int y=0;y<HEIGHT;++y)
    {
        for (int x=0;x<WIDTH;++x)
        {
            if (stage[y][x] == 1)
            {

                coordinate[count] = y+dy;
                coordinate[count+1] = x+dx;

                count += 2;
            }
        }
    }


    for (int i=0;i<8;i+=2)
    {
        if (stage[coordinate[i]][coordinate[i+1]] != 1 && stage[coordinate[i]][coordinate[i+1]] != 0)
        {
            return 0;
        }
    }


    oneToZero();


    stage[coordinate[0]][coordinate[1]] = 1;
    stage[coordinate[2]][coordinate[3]] = 1;
    stage[coordinate[4]][coordinate[5]] = 1;
    stage[coordinate[6]][coordinate[7]] = 1;


    return 0;
}


int operation (int kind)
{

    placeMino (kind);
    clear ();
    writeStage ();
    sleep (SPEED);

    while(1)
    {
        if (landing ())
        {
            changeStatic ();
            clear ();
            writeStage ();
            break;
        }



        clear ();
        moveMino (0, 1);

        writeStage ();
        sleep (SPEED);

        if (kbhit ())
        {
            int key = getch ();

            if (key == 105) //I
            {
                drop ();
                clear ();
                writeStage ();
            }

			else if (key == 108) //L
            {
				moveMino (1, 0);
                clear ();
                writeStage ();

			}

            else if (key == 106) //J
            {
                moveMino (-1, 0);
                clear ();
                writeStage ();
            }

            else if (key == 107) //K
            {
                turnMino ();
                clear ();
                writeStage ();
            }

            else if (key == 32) //Space
            {
                swapMino(kind);
                clear ();
                writeStage ();
            }
		}
    }
    
    return 0;
}


void placeMino (int kind)
{
    switch (kind)
    {
        case I_MINO:
            stage[4][4]=1, stage[4][5]=1, stage[4][6]=1, stage[4][7]=1;
            break;

        
        case O_MINO:
            stage[4][5]=1, stage[4][6]=1, stage[5][5]=1, stage[5][6]=1;
            break;

        
        case S_MINO:
            stage[4][6]=1, stage[4][7]=1, stage[5][5]=1, stage[5][6]=1;
            break;


        case Z_MINO:
            stage[4][5]=1, stage[4][6]=1, stage[5][6]=1, stage[5][7]=1;
            break;


        case J_MINO:
            stage[4][5]=1, stage[4][6]=1, stage[4][7]=1, stage[5][7]=1;
            break;


        case L_MINO:
            stage[4][5]=1, stage[4][6]=1, stage[4][7]=1, stage[5][5]=1;
            break;


        case T_MINO:
            stage[4][5]=1, stage[4][6]=1, stage[4][7]=1, stage[5][6]=1;
            break;
    }
}


void clear (void)
{
    //std::system ("clear");
    system ("cls");
}


int landing (void)
{
    for (int i=0;i<HEIGHT;++i)
    {
        for (int j=0;j<WIDTH;++j)
        {
            if (stage[i][j] == 1)
            {
                if (stage[i+1][j] != 1 && stage[i+1][j] != 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}


void drop (void)
{
    int coordinate[8] = {0,0,0,0,0,0,0,0}, count, downCount=0;
    int dx=0, dy=1;


    while (1)
    {
        count = 0;
        if (landing ())
        {
            point += downCount*DROP_POINT;
            break;
        }


        for (int y=0;y<HEIGHT;++y)
        {
            for (int x=0;x<WIDTH;++x)
            {
                if (stage[y][x] == 1)
                {
                    coordinate[count] = y+dy;
                    coordinate[count+1] = x+dx;
                    stage[y][x] = 0;
                    count += 2;
                }
            }
        }

        
        stage[coordinate[0]][coordinate[1]] = 1;
        stage[coordinate[2]][coordinate[3]] = 1;
        stage[coordinate[4]][coordinate[5]] = 1;
        stage[coordinate[6]][coordinate[7]] = 1;

        downCount += 1;
    }
}


int deleteLine (void)
{
    int i, j, k, l, m, count, returnNum = 0;


    for (i=0;i<HEIGHT;++i)
    {
        for (j=1;j<WIDTH-1;++j)
        {
            if (stage[i][j] == 2)
            {
                count += 1;
            }
        }


        if (count == 10)
        {
            returnNum = 1;

            for (m=1;m<WIDTH-1;++m)
            {
                stage[i][m] = 0;
            }


            for (k=i;k>0;--k)
            {
                for (l=1;l<WIDTH-1;++l)
                {
                    stage[k][l] = stage[k-1][l];
                }
            }

        }

        count = 0;
    }

    return returnNum;
}


int turnMino (void)
{
    int maxI=0, minI = 100, maxJ=0, minJ=100;
    int dx=0, dy=0;
    int tempWidth=0;


    for (int i=0;i<HEIGHT;++i) // ミノの上下幅の取得
    {
        for (int j=0;j<WIDTH;++j)
        {
            if (stage[i][j] == 1)
            {
                if (i > maxI) maxI = i;
                if (i < minI) minI = i;
                
                if (j > maxJ) maxJ = j;
                if (j < minJ) minJ = j;
            }
        }   
    }



    if (maxI-minI > maxJ-minJ) tempWidth = maxI-minI+1; // tempStageのサイズの決定
    else tempWidth = maxJ-minJ+1;

    int tempStage[tempWidth][tempWidth];
    int tempStageTwo[tempWidth][tempWidth];

    dy = maxI - tempWidth + 1, dx = minJ; // tempStageの[0][0]の位置



    for (int y=0;y<tempWidth;++y) // 回転するミノの部分をtempStageにコピー
    {
        for (int x=0;x<tempWidth;++x)
        {
			tempStage[y][x] = stage[y+dy][x+dx];
        }
    }


    for (int y=0;y<tempWidth;++y) // 壁の巻き込みチェック
    {
        for (int x=0;x<tempWidth;++x)
        {
			if (tempStage[y][x] != 1 && tempStage[y][x] != 0) return 0;
        }
    }


    for (int y=0;y<tempWidth;++y) // tempStageを回転させtempStageTwoにコピー
    {
        for (int x=0;x<tempWidth;++x)
        {
			tempStageTwo[y][x] = tempStage[tempWidth-1-x][y];
        }
    }


    while (1) // 上昇防止
    {
        int cnt=0;

        for (int x=0;x<tempWidth;++x)
        {
            if (tempStageTwo[tempWidth-1][x] == 1) cnt += 1;
        }

        if (cnt != 0) break;

        for (int i=tempWidth-1;i>0;--i)
        {
            for (int j=0;j<tempWidth;++j)
            {
                tempStageTwo[i][j] = tempStageTwo[i-1][j];
            }
        }

        for (int j=0;j<tempWidth;++j)
        {
            tempStageTwo[0][j] = 0;
        }
    }


    for (int y=0;y<tempWidth;++y) // tempStageTwoをStageに戻す
    {
        for (int x=0;x<tempWidth;++x)
        {
            stage[y+dy][x+dx] = tempStageTwo[y][x];
        }
    }


    return 0;
}


int pow (int x, int y)
{
    int ans = 1;

    for (int i=0;i<y;i++)
    {
        ans *= x;
    }

    return ans;
}


int swapMino (int kind)
{
    int dx = 10, dy = 20;

    for (int y=0;y<HEIGHT;++y) // ミノの左上
    {
        for (int x=0;x<WIDTH;++x)
        {
            if (stage[y][x] == 1)
            {
                if(y<dy) dy=y;
                if(x<dx) dx=x;
            }
        }
    }


    int null = 1;


    for (int y=0;y<4;++y) // swapが空かどうか
    {
        for (int x=0;x<4;++x)
        {
            if (swap[y][x] != 0)
            {
                null = 0;
                break;
            }
        }
    }


    if (null) // 空のときの動作
    {
        for (int y=0;y<4;++y)
        {
            for (int x=0;x<4;++x)
            {
                swap[y][x] = stage[y+dy][x+dx];
            }
        }
        oneToZero();

        placeMino(kind);
    }


    else
    {
        int tempSwap[4][4];

        for (int y=0;y<4;++y) // stageのミノをtempSwapにコピー
        {
            for (int x=0;x<4;++x)
            {
                tempSwap[y][x] = stage[y+dy][x+dx];
            }
        }


        oneToZero();


        for (int y=0;y<4;++y) // swapの中身をstageにコピー
        {
            for (int x=0;x<4;++x)
            {
                stage[y+4][x+4] = swap[y][x];
            }
        }


        for (int y=0;y<4;++y) // tempSwapの中身をswapにコピー
        {
            for (int x=0;x<4;++x)
            {
                swap[y][x] = tempSwap[y][x];
            }
        }
    }
    return 0;
}