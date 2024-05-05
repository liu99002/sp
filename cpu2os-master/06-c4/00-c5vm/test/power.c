#include<stdio.h>
int power(int x ,int n){
    int a;
    a=1;
    while (n>0)
    {
        a=a*x;
        n=n-1;
    }
    return a;
}

int main(){
    printf("%d",power(2,10));
    return 0;
} 