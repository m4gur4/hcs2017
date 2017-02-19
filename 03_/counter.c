#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>   // for "isalpha"

const int ASCII_SIZE=256;

void init(int a[],int b[]);
void count(string n, int a[] );
void swap(int *el1, int *el2 );
void sort(int a[],int b[]);
void out(int a[],int b[]);

int main(int argc, string argv[])
{
    int counter[ASCII_SIZE];
    int symbols[ASCII_SIZE];
    string input_str;
    
    if (argc!=2 )
    {
       printf("Oops!  Usage: ./counter <word>\n");
       printf("or enter string NOW :");
       input_str=get_string();
    }
    else
        input_str=argv[1];

    init(counter,symbols);
    count(input_str,counter);
    sort(counter,symbols);
    out(counter,symbols);
    return 0;
}

void init(int a[],int b[])
{
    for (int i=0; i<ASCII_SIZE;i++) 
    {
        a[i]=0;
        b[i]=i;
    }
}

void count(string n, int a[] )
{
    for (int i=0; i<strlen(n);i++)  a[(int)n[i]]++;
}

void swap(int *el1, int *el2 )
{
    int buf;
    buf = *el1;
    *el1 = *el2;
    *el2 = buf;
}

// bubble sort
void sort(int a[],int b[])
{
  for (int i = 0 ; i < ( ASCII_SIZE - 1 ); i++)
    for (int j = 0 ; j < ASCII_SIZE - i - 1; j++)
      if (a[j] < a[j+1]) 
      {
        swap(a+j,a+j+1);
        swap(b+j,b+j+1);
      }
}

void out(int a[],int b[])
{
    int i=0;
    while (a[i]>0) 
    {
     if (isalpha(b[i]))
     printf("\"%c\" - %d\n",b[i],a[i]);
     i++;
    }
}