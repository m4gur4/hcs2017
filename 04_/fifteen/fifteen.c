/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            printf("CONGRATS YOU ARE WIN!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
          //  usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    printf("===========================\n");
    printf("======== GAME RULES =======\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    for (int i=0;i<d*d;i++)
    {
        board[i/d][i%d]=d*d-i-1;
        // "even" dimensions
        if ( (d*d)%2==0) {
             if (board[i/d][i%d]==1) 
                    board[i/d][i%d]=2; 
                else
                  if (board[i/d][i%d]==2) 
                        board[i/d][i%d]=1; 
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for (int i=0;i<d;i++)
        {
        for (int j=0;j<d;j++)
        {
           if (board[i][j]!=0)
                printf (" %2i",board[i][j]);
            else           
                printf ("   ");
        }
        printf("\n");
        }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    bool rez=false;
    // TODO
    if (tile<d*d) {
        //find coords
        int Nx,Ny,Tx,Ty;
       for (int i=0;i<d;i++)
        for (int j=0;j<d;j++)
        {
          if (board[i][j]==0) { 
              Nx=i;
              Ny=j;    
            }
          if (board[i][j]==tile) { 
              Tx=i;
              Ty=j;    
            }            
        }    
         // is @tile@ around d*d
          if ( (abs(Tx-Nx)==1 && Ty==Ny) ^ (abs(Ty-Ny)==1 && Tx==Nx)) 
          {
           // swipe values
           board[Nx][Ny]=tile;
           board[Tx][Ty]=0; 
           rez=true;
          }
    }
    else rez=false;
    
    return rez;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{  
    bool rez=true;
      for (int i=0;i<d*d-1;i++)
          if (board[i/d][i%d]!=i+1) 
                rez=false;
   return rez;
}