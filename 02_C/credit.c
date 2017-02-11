#include <cs50.h>
#include <stdio.h>

long normal_input(void);
int size_of_num(long num);
int sum_odd(long num); // нечетные
int get_digit(int num);
int sum_even(long num); // четные
bool is_valid_number(long num);
long get_prefix(long num, int cnt);
void get_vendor(long int a);

int main(void)
{
 long int number = normal_input();
 if (is_valid_number(number)) 
    {   get_vendor(number); }
  else
    { printf("INVALID\n");}
}

long int normal_input(void) 
{
  long int num=0;
  printf("Number: ");        
  num = get_long_long();
  return num;
}


int size_of_num(long num)
{
    int cnt=0;
    while(num!=0){
        num/=10;
        cnt++;
    }
    return cnt;
}

int sum_odd(long num)
{
    int sum=0;
    int cnt_digits=size_of_num(num);
    for(int i=0; i<cnt_digits; i+=2){
        sum+=num%10;
//        printf("%ld - %ld\n",num,num%10);
        num/=100;
    }
    return sum;
}

int get_digit(int num)
{
    return ((num-num%10)/10)+num%10;
}

int sum_even(long num)
{
    int cnt_digits=size_of_num(num)-1;
    int sum=0;
    num/=10;
    for(int i=0; i<cnt_digits; i+=2)
        {
            sum+=get_digit((int)(2*(num % 10)));
            num/=100;
        }
    return sum;
}

bool is_valid_number(long int num)
{
    if ((sum_odd(num)+sum_even(num))%10==0) return 1;
    else return 0;
}

long get_prefix(long num, int cnt)
{
    long digits=10;
    for (int i=1;i<cnt;i++) digits *=10;
    long buf = num;
    while (buf >= digits)   //get first CNT digit's
     {
        buf /= 10;
     }       
    return buf;
}

void get_vendor(long num)
{
    long int buf = get_prefix(num, 1);
 if (buf==4) 
    printf("VISA\n");
 else
 {  //not VISA
    buf = get_prefix(num, 2);
     switch (buf)
    {
        case 34:
        case 37:
            printf("AMEX\n");
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            printf("MASTERCARD\n");
            break;
        default:
            printf("INVALID\n");
            break;  
    }
 }
}