# include <iostream>
# include <random>

# define HEIGTH (24) //3+20+1
# define WIDTH (12) //1+10+1


int stage[HEIGTH][WIDTH];
int next[7];


int randint (int min, int max);
void stageInit (void);
void decisionNext (void);
void writeStage (void);



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



class Mino
{
    int kind;
    int direction;
    int shape[4][4];

public:
    int showKind()
    {
        return kind;
    }
    int showDirection()
    {
        return direction;
    }
    int showShape()
    {
        return shape;
    }
    void __init__(int kind);
};



void Mino::__init__(int orgKind)
{
    switch (orgKind)
    {
        case I_MINO:
            kind = 0;
            direction = 0;
            shape = {}
            break;

        case O_MINO:
            kind = 1;
            break;
        
        case S_MINO:
            kind = 2;
            break;
        
        case Z_MINO:
            kind = 3;
            break;
    
        case J_MINO:
            kind = 4;
            break;

        case L_MINO:
            kind = 5;
            break;

        case T_MINO:
            kind = 6;
            break;
    }
}





int main (void)
{
    stageInit ();
    writeStage ();
}



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
    for (int i=3;i<HEIGTH;++i)
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