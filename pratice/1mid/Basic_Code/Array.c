#include<stdio.h>
#include<stdlib.h>

int main(){
    //1D array
    /*
    int *grade;
    grade = (int*)malloc(5*sizeof(int));
    for(int i=0 ; i<5 ; i++){
        grade[i] = 5;
    }
    for(int i=0 ; i<5 ; i++){
        printf("%d\n" , grade[i]);

    }
    free(grade);
    */

    //2D array
    int row =4 , col =3;
    int **market = (int**)malloc(row*sizeof(int*));
    for(int i=0 ; i<row ; i++){
        market[i] = (int*)malloc(col*sizeof(int));
    }
    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<col ; j++){
            market[i][j] = i+j;
           
        }
    }
    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<col ; j++){
            printf("%d " , market[i][j]);
        }
        printf("\n");
    }
    for(int i=0 ; i<row ; i++){
        free(market[i]);
    }
    free(market);

    
}