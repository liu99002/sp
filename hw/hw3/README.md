1: #include<stdio.h>
2: int power(int x ,int n){
3:     int a;
4:     a=1;
    ENT  1
    LLA  -1
    PSH 
    IMM  1
    SI
5:     while (n>0)
    LLA  2
    LI
    PSH
    IMM  0
    GT
6:     {
    BZ   0
7:         a=a*x;
    LLA  -1
    PSH
    LLA  -1
    LI
    PSH
    LLA  3
    LI
    MUL
    SI
8:         n=n-1;
    LLA  2
    PSH
    LLA  2
    LI
    PSH
    IMM  1
    SUB
    SI
9:     }
10:     return a;
    JMP  -757268264
    LLA  -1
    LI
    LEV
11: }
    LEV
12:
13: int main(){
14:     printf("%d",power(2,10));
    ENT  0
    IMM  -757006176
    PSH
    IMM  2
    PSH
    IMM  10
    PSH
    JSR  -757268328
    ADJ  2
    PSH
    PRTF
    ADJ  2
15:     return 0;
    IMM  0
    LEV