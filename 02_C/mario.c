#include <cs50.h>
#include <stdio.h>

const int GAP=2; //GAP size

int normal_input(void);

void drow_line(int a, int b);

int main(void)
{
 int lines = normal_input();
  if (lines>0)
  {
        for (int i = 0; i<lines; i++)
        {
            drow_line(i,lines);
        }
  } 
}

int normal_input(void)
{
  int result=0;
 do
  {
     printf("Height: ");        
     result = get_int();
  }
  while (result<0 || result>23);
  return result;
}

void drow_line(int a, int b)
{
    for (int i=0, cur_lenght =b+a+GAP+1; i<cur_lenght ;i++)
    {
        if ((i<b-a-1) || ((i>b-1) && (i<b+GAP) ) )
            printf(" ");
        else
            printf("#");
    }    
    printf("\n");
}