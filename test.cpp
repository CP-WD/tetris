# include <iostream>
# include <random>
# include <chrono>
# include <thread>
# include <stdlib.h>
# include <windows.h>
# include <conio.h>

# define HEIGHT (22) // 1+20+1
# define WIDTH (12)  // 1+10+1

# define SPEED (100)


int stage[HEIGHT][WIDTH];
int next[7];


int randint (int min, int max);
int landing (void);
int operation (int kind);
int landing (void);
int deleteLine(void);
void drop (void);
void clear (void);
void moveMino (int dx, int dy);
void stageInit (void);
void decisionNext (void);
void writeStage (void);
void writeStageNum (void);
void oneToZero (void);
void changeStatic (void);
void sleep (int s);
void moveMino (void);
void placeMino(int kind);
int turnMino(int lr);




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





int main (void)
{
    int end = 0;

    stageInit ();
    writeStageNum();
    decisionNext();

    //while(end != 1)
    while(1)
    {
        for (int i=0;i<7;i++)
        {
            end = operation(next[i]);

            for (int j=0;j<4;++j)
            {
                deleteLine();
            }
        }
        decisionNext();
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


int randint(int min, int max)
{
    std::random_device rnd;
    std::mt19937 mt(rnd ());
    std::uniform_int_distribution<> rand100 (min, max);
    return rand100 (mt);
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
    for (int i=1;i<HEIGHT;++i)
    {
        for (int j=0;j<WIDTH;++j)
        {
            //std::cout << stage[i][j];
            switch (stage[i][j])
            {
                case 0:
                    std::cout << "  ";
                    break;

                case 1:
                    std::cout << "[]";
                    break;

                default:
                    std::cout << "::";
                    break;

            }
        }
        std::cout << std::endl;
    }
}


void writeStageNum (void)
{
    for (int i=0;i<HEIGHT;++i)
    {
        for (int j=0;j<WIDTH;++j)
        {
            std::cout << stage[i][j];
        }
        std::cout << std::endl;
    }
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
    //std::this_thread::sleep_for(std::chrono::milliseconds(s));
    Sleep(s);
}


void moveMino(int dx, int dy)
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
                stage[y][x] = 0;
                count += 2;
            }
        }
    }

    
    oneToZero();

    
    stage[coordinate[0]][coordinate[1]] = 1;
    stage[coordinate[2]][coordinate[3]] = 1;
    stage[coordinate[4]][coordinate[5]] = 1;
    stage[coordinate[6]][coordinate[7]] = 1;
}


int operation (int kind)
{
    placeMino(kind);
    clear();
    writeStageNum();
    sleep(SPEED);

    while(1)
    {
        if (landing())
        {
            changeStatic();
            clear();
            writeStageNum();
            break;
        }



        clear();
        moveMino(0, 1);

        writeStageNum();
        sleep(SPEED);

        if(kbhit())
        {
            int key = getch();

			if (key == 108)//L
            {
				moveMino(1, 0);
                clear();
                writeStageNum();

			}

            else if (key == 106)//J
            {
                moveMino(-1, 0);
                clear();
                writeStageNum();
            }

            else if (key == 107)//K
            {
                //drop();
                turnMino(1);
                clear();
                writeStageNum();
            }
		}
    }
    
    return 0;
}


void placeMino(int kind)
{
    switch (kind)
    {
        case I_MINO:
            stage[1][4]=1, stage[1][5]=1, stage[1][6]=1, stage[1][7]=1;
            break;
        
        case O_MINO:
            stage[1][5]=1, stage[1][6]=1, stage[2][5]=1, stage[2][6]=1;
            break;
        
        case S_MINO:
            stage[1][6]=1, stage[1][7]=1, stage[2][5]=1, stage[2][6]=1;
            break;

        case Z_MINO:
            stage[1][5]=1, stage[1][6]=1, stage[2][6]=1, stage[2][7]=1;
            break;

        case J_MINO:
            stage[1][5]=1, stage[1][6]=1, stage[1][7]=1, stage[2][7]=1;
            break;

        case L_MINO:
            stage[1][5]=1, stage[1][6]=1, stage[1][7]=1, stage[2][5]=1;
            break;

        case T_MINO:
            stage[1][5]=1, stage[1][6]=1, stage[1][7]=1, stage[2][6]=1;
            break;
    }
}


void clear(void)
{
    //std::system("clear");
    system("cls");
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
                    break;
                }
            }
        }
    }

    return 0;
}


void drop (void)
{
    int coordinate[8] = {0,0,0,0,0,0,0,0}, count;
    int dx=0, dy=1;

    while (1)
    {
        count = 0;
        if (landing())
        {
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
    }
}


int deleteLine(void)
{
    int i, j, k, l, m, count;


    for (i=0;i<HEIGHT;++i)
    {
        for (j=0;j<WIDTH;++j)
        {
            if (stage[i][j] == 2)
            {
                count+=1;
            }
        }


        if (count == 10)
        {
            for (m=1;m<WIDTH-1;++m)
            {
                stage[i][m] = 0;
            }


            for (k=i;k>0;--k)
            {
                for (l=1;l<WIDTH-1;++l)
                {
                    if (stage[k-1][l] == 2) stage[k][l] = 2;
                    else if (stage[k-1][l] = 0) stage[k][l] = 0;
                }
            }

        }

        count = 0;
    }

    return 0;
}


int turnMino(int lr)
{
    int maxI=0, minI = 100, maxJ=0, minJ=100;
    int dx=0, dy=0;
    int tempWidth=0;


    for (int i=0;i<HEIGHT;++i)
    {
        for (int j=0;j<WIDTH;++j)
        {
            if (stage[i][j] == 1)
            {
                if (i > maxI) maxI = i;
                else if (i < minI) minI = i;
                
                if (j > maxJ) maxJ = j;
                else if (j < minJ) minJ = j;
            }
        }   
    }


    if (maxI-minI > maxJ-minJ) tempWidth = maxI-minI+1;
    else tempWidth = maxJ-minJ+1;

    int tempStage[tempWidth][tempWidth];

    for (int i=0;i<tempWidth;++i)
    {
        for (int j=0;j<tempWidth;++j)
        {
            tempStage[i][j] = 0;
        }
    }

	dy = minI - tempWidth + 1, dx = minJ - tempWidth + 1;

    
    for (int y=0;y<tempWidth;++y)
    {
        for (int x=0;x<tempWidth;++x)
        {
			tempStage[y][x] = stage[WIDTH-1-x+dx][y+dy];
        }
    }


    for (int y=0;y<tempWidth;++y)
    {
        for (int x=0;x<tempWidth;++x)
        {
            stage[y+dy][x+dx] = tempStage[y][x];
        }
    }
    return 0;
}