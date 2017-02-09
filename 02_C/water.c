#include <cs50.h>
#include <stdio.h>

int main(void)
{
  printf("Minutes: ");    
  int minets = get_int();
  if (minets>0)
  {
    printf("Bottles: %d\n",minets*12);
  } 
}