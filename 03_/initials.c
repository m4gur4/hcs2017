#include <cs50.h>
#include <stdio.h>
#include <string.h>

string get_input();
void make_initials(string n);
char to_upper(char c);

int main()
{
    make_initials(get_input());
}

string get_input()
{
    string s = get_string();
    return s;
}

char to_upper(char c)
{
    if (c>'Z') return c-('a'-'A');
    else return c;
}

void make_initials(string n)
{
    int i=0;
    int pre_space=-1;
    while (i<strlen(n)) 
    { 
        if (n[i]==' ') pre_space=i;
         else
            if (pre_space==(i-1)) printf("%c", to_upper(n[i]));
        i++;
    }
    printf("\n");
}