#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//動態分配記憶體大小，參考chatgpt
double *allocateMatrix(int rows, int cols) {
    return (double *)malloc(rows * cols * sizeof(double));
}

double *transpose(double *mar,int rows,int cols){
    double *temp=allocateMatrix(rows,cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[j*rows+i]=mar[i*cols+j];
        }
        
    }
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%0.lf ",temp[i*rows+j]);
        }
        printf("\n");
    }
}

int main(){
    int rowsA,colsA,rowsB,colsB;
    printf("rowsA colsA rowsB colsB\n");
    scanf("%d %d %d %d",&rowsA,&colsA,&rowsB,&colsB);
    double *marA=allocateMatrix(rowsA,colsA);
    double *marB=allocateMatrix(rowsB,colsB);
    printf("MatrixA:\n");
    for (int  i = 0; i < rowsA; i++)
    {
        double in1[colsA];
        for (int j = 0; j < colsA; j++)
        {
            scanf("%lf",&in1[j]);
            marA[i*colsA+j]=in1[j];
        }
    }
    printf("MatrixB:\n");
    for (int  i = 0; i < rowsB; i++)
    {
        double in1[colsB];
        for (int j = 0; j < colsB; j++)
        {
            scanf("%lf",&in1[j]);
            marB[i*colsB+j]=in1[j];
        }
    }
    printf("MatrixA to transpose:\n");
    transpose(marA,rowsA,colsA);
    printf("MatrixB to transpose:\n");
    transpose(marB,rowsB,colsB);
}