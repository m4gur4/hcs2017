#include <cs50.h>
#include <stdio.h>

const int gap=2;

void drow_line(int a, int b);

int normal_input(void);

int main(void)
{
 int lines = normal_input();
  if (lines>0)
  {
        for (int i = 0; i<lines; i++)
        {
            drow_line(i,lines);
        }
          //  printf("\n");
  } 
}

int normal_input(void)
{
  int result=-1;
  while ((result<0) || (result>23))
  {
     printf("Height: ");        
     result = get_int();
  } 
  return result;
}

void drow_line(int a, int b)
{
    for (int i=0; i<b+a+gap+1 ;i++)
    {
        if ((i<b+1-a-2) || ((i>b-1) && (i<b+gap) ) )
         printf(" ");
        else
        printf("#");
    }    
    printf("\n");
}