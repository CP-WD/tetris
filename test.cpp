# include <iostream>
# include <chrono>
# include <thread>

# define HEIGTH 8
# define WIDTH 9

int stage[HEIGTH][WIDTH];
int tempStage[HEIGTH][WIDTH];


void stageInit (void)
{
    for (int i=0;i<HEIGTH-1;++i)
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
        stage[HEIGTH-1][j] = 4;
    }
}


void writeStage (void)
{
    int count = 0;
    for (int i=0;i<HEIGTH;++i)
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
    for (int i=0;i<HEIGTH;++i)
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
    for (int y=0;y<HEIGTH;++y)
    {
        for (int x=0;x<WIDTH;++x)
        {
            if (stage[y][x] == 1) stage[y][x] = 0;
        }
    }
}


void changeStatic (void)
{
    for (int y=0;y<HEIGTH;++y)
    {
        for (int x=0;x<WIDTH;++x)
        {
            if (stage[x][y] == 1) stage[x][y] = 2;
        }
    }
}


void sleep (int s)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(s));  
}


int landing (void)
{
    for (int i=0;i<HEIGTH;++i)
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


void moveMino(int dx, int dy)
{
    int coordinate[8] = {0,0,0,0,0,0,0,0}, count = 0;

    for (int y=0;y<HEIGTH;++y)
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


int operation (void)
{
    int x=0, y=0;
    stage[0+y][3+x]=1, stage[0+y][4+x]=1, stage[0+y][5+x]=1, stage[1+y][4+x]=1;
    std::system("clear");
    writeStage();
    sleep(1000);

    while(1)
    //for (int hoge=0;hoge<1;++hoge)
    {
        if (landing())
        {
            changeStatic();
            std::system("clear");
            writeStage();
            break;
        }


        ++y;

        std::system("clear");

        moveMino(0, 1);

        writeStage();
        sleep(1000);
    }
    
    return 0;
}


int placeMino (int kind)
{
    return 0;
}


int main(void)
{
    stageInit();
    operation();
    //writeStage();
}