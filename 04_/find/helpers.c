/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
   bool pos=false;
   int left = 0;
   int right = n - 1;
   int half = (left+right)/2;
   
   if (n>=0) 
   {
      while (left <= right) {
          if (values[half] < value)
                 left = half + 1;    
            else if (values[half] == value) {
                    pos=true;
                    break;
                    }
            else
            right = half - 1;
       half = (left + right)/2;
        }
     if (left > right)
             pos=false;        
   }
    return pos;
}

void swap(int *el1, int *el2 )
{
    int buf;
    buf = *el1;
    *el1 = *el2;
    *el2 = buf;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // Insertion
     for (int i = 1 ; i <= n - 1; i++) {
    int j = i;
    while ( j > 0 && values[j] < values[j-1]) {
        swap(values+j,values+j-1);
      j--;
    }
  }
    
    
    return;
} 