# include <stdio.h>
# include <conio.h>
# include <stdlib.h>
# include <windows.h>

# define HEIGTH (24) //3+20+1
# define WIDTH (12) //1+10+1

# define W (119)
# define A (97)
# define S (115)
# define D (100)

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

/* memo
0 = balnk
1 = dynamic mino
2 = static mino
3 = wall
4 = floor
*/

int draw (int *stage);
int stage_init (int *stage);//done
int next (void);
int operation (int *stage, int mino);

int main (void)
{
    int stage[HEIGTH*WIDTH], next_mino[7], temp = 0;

    system("cls");
    
    while (temp == 0)
    {
        next_mino[0] = next();
        stage_init (stage);
        operation (stage ,4);
        draw (stage);
        printf("\n%d",temp);
        Sleep (1000);
        system ("cls");
        temp++;
    }
}

int draw (int *stage)
{
    int i, j, value;

    for (i=3;i<HEIGTH;i++)
    {
        for (j=0;j<WIDTH;j++)
        {
            value = stage[i*WIDTH + j];
            /*switch (value)
            {
                case 0:
                    printf ("　");
                    break;
                case 1:
                    printf ("■");
                    break;
                case 2:
                    printf ("■");
                    break;
                case 3:
                    printf ("■");
            }*/
            switch (value)
            {
                case 0:
                    printf ("  ");
                    break;
                case 1:
                    printf ("[]");
                    break;
                case 2:
                    printf ("::");
                    break;
                case 3:
                    printf ("::");
            }
        }
        printf("\n");
    }
}

int stage_init(int *stage)
{
    int i, j;

    for (i=0;i<HEIGTH-1;i++)
    {
        for (j=0;j<WIDTH;j++)
        {
            switch (j)
            {
                case 0:
                    stage[i*WIDTH + j] = 3;
                    break;
                case 11:
                    stage[i*WIDTH + j] = 3;
                    break;
                default:
                    stage[i*WIDTH + j] = 0;
                    break;
            }
        }
    }

    for (i=0;i<WIDTH;i++)
    {
        stage[WIDTH*(HEIGTH-1) + i] = 2;
    }
}

int next (void)
{
    int i,j,temp;
    int next_array[7];
    int num_array[7] = {0,1,2,3,4,5,6};

    for (i=1;i<7;i++)
    {
        srand((unsigned)time(NULL));
        temp = rand() % (7-i);
        next_array[i-1] = num_array[temp];

        for (j=temp;j<6;j++)
        {
            num_array[j] = num_array[j+1];
        }    
    }
    next_array[6] = num_array[0];
    
    return next_array[0];
}

int operation (int *stage, int mino)
{
    int i = 0, x = 6;
    while (1)
    {
        switch (mino)
        {
            case I_MINO:
                stage[(0+i-1)*WIDTH + x] = 0, stage[(1+i-1)*WIDTH + x] = 0, stage[(2+i-1)*WIDTH + x] = 0, stage[(3+i-1)*WIDTH + x] = 0;
                stage[(0+i)*WIDTH + x] = 1, stage[(1+i)*WIDTH + x] = 1, stage[(2+i)*WIDTH + x] = 1, stage[(3+i)*WIDTH + x] = 1;
                break;
                
            case O_MINO:
                stage[(2+i-1)*WIDTH + x] = 0, stage[(2+i-1)*WIDTH + x+1] = 0, stage[(3+i-1)*WIDTH + x] = 0, stage[(3+i-1)*WIDTH + x+1] = 0;
                stage[(2+i)*WIDTH + x] = 1, stage[(2+i)*WIDTH + x+1] = 1, stage[(3+i)*WIDTH + x] = 1, stage[(3+i)*WIDTH + x+1] = 1;
                break;
            
            case S_MINO:
                stage[(2+i-1)*WIDTH + x] = 0, stage[(2+i-1)*WIDTH + x+1] = 0, stage[(3+i-1)*WIDTH + x-1] = 0, stage[(3+1-1)*WIDTH + x] = 0;
                stage[(2+i)*WIDTH + x] = 1, stage[(2+i)*WIDTH + x+1] = 1, stage[(3+i)*WIDTH + x-1] = 1, stage[(3+i)*WIDTH + x] = 1;
                break;
            
            case Z_MINO:
                stage[(2+i-1)*WIDTH + x-1] = 0, stage[(2+i-1)*WIDTH + x] = 0, stage[(3+i-1)*WIDTH + x] = 0, stage[(3+i-1)*WIDTH + x+1] = 0;
                stage[(2+i)*WIDTH + x-1] = 1, stage[(2+i)*WIDTH + x] = 1, stage[(3+i)*WIDTH + x] = 1, stage[(3+i)*WIDTH + x+1] = 1;
                break;
                
            case J_MINO:
                stage[(1+i-1)*WIDTH + x+1] = 0, stage[(2+i-1)*WIDTH + x+1] = 0, stage[(3+i-1)*WIDTH + x+1] = 0, stage[(3+i-1)*WIDTH + x] = 0;
                stage[(1+i)*WIDTH + x+1] = 1, stage[(2+i)*WIDTH + x+1] = 1, stage[(3+i)*WIDTH + x+1] = 1, stage[(3+i)*WIDTH + x] = 1;
                break;
            
            case L_MINO:
                stage[(1+i-1)*WIDTH + x] = 0, stage[(2+i-1)*WIDTH + x] = 0, stage[(3+i-1)*WIDTH + x] = 0, stage[(3+i-1)*WIDTH + x+1] = 0;
                stage[(1+i)*WIDTH + x] = 1, stage[(2+i)*WIDTH + x] = 1, stage[(3+i)*WIDTH + x] = 1, stage[(3+i)*WIDTH + x+1] = 1;
                break;

            case T_MINO:
                stage[(2+i-1)*WIDTH + x-1] = 0, stage[(2+i-1)*WIDTH + x] = 0, stage[(2+i-1)*WIDTH + x+1] = 0, stage[(3+i-1)*WIDTH + x] = 0;
                stage[(2+i)*WIDTH + x-1] = 1, stage[(2+i)*WIDTH + x] = 1, stage[(2+i)*WIDTH + x+1] = 1, stage[(3+i)*WIDTH + x] = 1;
                break;       
        }

        system ("cls");
        draw (stage);
        Sleep(200);

        if (i == 19)
            {
                system ("cls");

                switch (mino)
                {
                    case I_MINO:
                        stage[(0+i)*WIDTH + x] = 2, stage[(1+i)*WIDTH + x] = 2, stage[(2+i)*WIDTH + x] = 2, stage[(3+i)*WIDTH + x] = 2;
                        break;

                    case O_MINO:
                        stage[(2+i)*WIDTH + x] = 2, stage[(2+i)*WIDTH + x+1] = 2, stage[(3+i)*WIDTH + x] = 2, stage[(3+i)*WIDTH + x+1] = 2;
                        break;

                    case S_MINO:
                        stage[(2+i)*WIDTH + x] = 2, stage[(2+i)*WIDTH + x+1] = 2, stage[(3+i)*WIDTH + x-1] = 2, stage[(3+i)*WIDTH + x] = 2;
                        break;
                    case Z_MINO:
                        stage[(2+i)*WIDTH + x-1] = 2, stage[(2+i)*WIDTH + x] = 2, stage[(3+i)*WIDTH + x] = 2, stage[(3+i)*WIDTH + x+1] = 2;
                        break;
                    case J_MINO:
                        stage[(1+i)*WIDTH + x+1] = 2, stage[(2+i)*WIDTH + x+1] = 2, stage[(3+i)*WIDTH + x+1] = 2, stage[(3+i)*WIDTH + x] = 2;
                        break;

                    case L_MINO:
                        stage[(1+i)*WIDTH + x] = 2, stage[(2+i)*WIDTH + x] = 2, stage[(3+i)*WIDTH + x] = 2, stage[(3+i)*WIDTH + x+1] = 2;
                        break;

                    case T_MINO:
                        stage[(2+i)*WIDTH + x-1] = 2, stage[(2+i)*WIDTH + x] = 2, stage[(2+i)*WIDTH + x+1] = 2, stage[(3+i)*WIDTH + x] = 2;
                        break; 
                }
                break;
            }
            i++;
    }
}