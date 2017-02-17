#include <cs50.h>
#include <stdio.h>
#include <string.h>

char shift(char c, int k);
void encode(string n, int k);

int main(int argc, string argv[])
{
    if (argc==2)
    {
        int k = atoi(argv[1]);
        printf("plaintext: ");
        string a=get_string();
        printf("ciphertext: ");
        encode(a,k);
        return 0;
    }
    else
    {
        printf("Oops!  Usage: ./caesar k\n");
        return 1;
    }
}

char shift(char c, int k)
{
    if ( c>='A' && c<='z') 
    {
        char start = (c>'Z') ? 'a':'A';
        int pos=((c-start)+k)%26+start;
        return (char)pos;
    }
    else return c;
}

void encode(string n, int k)
{
    for (int i=0;i<strlen(n); i++)
        printf("%c", shift(n[i],k));
    printf("\n");
}