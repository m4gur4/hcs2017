#include <cs50.h>
#include <stdio.h>

long int normal_input(void);

int size_of_num(long num);
int sum_parn(long num);
int getdigit(int num);
int sum_neparn(long num);
bool is_valid_number(long int num);
void get_vendor(long int a);


int main(void)
{
 long int number = normal_input();
 if (is_valid_number(number)==1) {   get_vendor(number); }
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

int sum_parn(long num)
{
    int sum=0;
    int numdigits=size_of_num(num);
    for(int i=0; i<numdigits; i+=2){
        sum+=num%10;
        num/=100;
    }
    return sum;
}

int getdigit(int num){
return ((num-num%10)/10)+num%10;
}

int sum_neparn(long num)
{
    int numdigits=size_of_num(num)-1;
    int sum=0;
    num/=10;
    for(int i=0;i<numdigits;i+=2)
        {
            sum+=getdigit((int)(2*(num % 10)));
            num/=100;
        }
    return sum;
}

bool is_valid_number(long int num)
{
  //  printf("~%d : %d \n",sum_parn(num),sum_neparn(num));
    if ((sum_parn(num)+sum_neparn(num))%10==0) return 1;
    else return 0;
}

void get_vendor(long int a)
{
 long int buf = a;
 while (buf >= 10)   //get first digit
 {
    buf /= 10;
 }
 if (buf==4) 
    printf("VISA\n");
 else
 {  //not VISA
    buf = a;
    while (buf >= 100) //get 2 first digit's
    {
        buf /= 10;
     }
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