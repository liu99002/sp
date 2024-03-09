#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//動態分配記憶體大小
double *allocateMatrix(int rows, int cols) {
    return (double *)malloc(rows * cols * sizeof(double));
}

int main(){
    int rowsA,colsA,rowsB,colsB;
    printf("rowsA colsA rowsB colsB\n");
    scanf("%d %d %d %d",&rowsA,&colsA,&rowsB,&colsB);
    double *marA=allocateMatrix(rowsA,colsA);
    double *marB=allocateMatrix(rowsB,colsB);
    printf("MatrixA:\n");
    int count=0;
    for (int  i = 0; i < rowsA; i++)
    {
        double in1=0,in2=0,in3=0;
        scanf("%lf %lf %lf",&in1,&in2,&in3);
        for (int j = 0; j < colsA; j++)
        {
            switch (j)
            {
                case 0:
                    marA[count]=in1;
                    break;
                case 1:
                    marA[count]=in2;
                    break;
                case 2:
                    marA[count]=in3;
                    break;
            }
            printf("%f\n",marA[count]);
            count++;
        }
    }
}