#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//動態分配記憶體大小，參考chatgpt
double *allocateMatrix(int rows, int cols) {
    return (double *)malloc(rows * cols * sizeof(double));
}

double *dump(double *mar,int rows,int cols){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%0.lf ",mar[i*cols+j]);
        }
        printf("\n");
    }
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
    int temp2=cols;
    cols =rows;
    rows=temp2;
    dump(temp,rows,cols);
}

double *add(double *marA,double *marB,int rowsA,int colsA,int rowsB,int colsB){
    if (rowsA==rowsB && colsA==colsB)
    {
        double *temp=allocateMatrix(rowsA,colsB);
        for (int i = 0; i < rowsA ; i++)
        {
            for (int j = 0; j < colsA; j++)
            {
                temp[i*colsA+j]=marA[i*colsA+j]+marB[i*colsA+j];
            }
        }
        dump(temp,rowsA,colsA);
    }
    else printf("err\n");
    
}

double *multiply(double *marA,double *marB,int rowsA,int colsA,int rowsB,int colsB){
    if (rowsA==rowsB && colsA==colsB){
        double *temp=allocateMatrix(rowsA,colsB);
        for (int i = 0; i < rowsA ; i++)
        {
            for (int j = 0; j < colsA; j++)
            {
                temp[i*colsA+j]=marA[i*colsA+j]*marB[i*colsA+j];
            }
        }
        dump(temp,rowsA,colsA);
    }
    else printf("err\n");
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
    printf("Transposed MatrixA:\n");
    transpose(marA,rowsA,colsA);
    printf("Transposed MatrixB:\n");
    transpose(marB,rowsB,colsB);
    printf("The added matrix:\n");
    add(marA,marB,rowsA,colsA,rowsB,colsB);
    printf("The multiplied matrix:\n");
    multiply(marA,marB,rowsA,colsA,rowsB,colsB);
}