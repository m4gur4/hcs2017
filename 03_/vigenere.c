#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool is_good_input(string a);
int get_shift_distance(string key_string,int pos);
char shift(char c, string k, int p);
void encode(string n, string k);


bool is_good_input(string a)
{
    bool rez=true;
    for (int i=0; i<strlen(a); i++)
    if (a[i]<'A' || a[i]>'z') rez=false;
    return rez;
}

int get_shift_distance(string key_string,int pos)
{
    int pz=pos%(strlen(key_string));
    char cc=key_string[pz];
    int start= (cc>'Z')? (int)cc-'a' : (int)cc-'A';
   return start;
}

char shift(char c, string k, int p)
{
    char start = (c>'Z') ? 'a':'A';
    int dif=get_shift_distance(k,p);
    int pos=((c-start)+dif)%26+start;
    return (char)pos;
}

void encode(string n, string k)
{
    char symbol;
    int not_alphabet_cnt=0;
    for (int i=0;i<strlen(n); i++)
    {  
        symbol = n[i];
        if ( symbol>='A' && symbol<='z') 
            symbol = shift(n[i],k,i-not_alphabet_cnt);
        else 
            not_alphabet_cnt++;
        printf("%c", symbol);
    }
    printf("\n");
}

int main(int argc, string argv[])
{
    if (argc==2 && is_good_input(argv[1]) )
    {
        printf("plaintext: ");
        string a=get_string();
        printf("ciphertext: ");
        encode(a,argv[1]);
        return 0;
    }
    else
    {
        printf("Oops!  Usage: ./caesar k\n");
        return 1;
    }
}