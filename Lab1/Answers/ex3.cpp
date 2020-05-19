/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return the trace of the Laplacian of the weight matrix.
int traceLaplacian(int weight[][50], int size){
    int diagonal[size][size];int laplacian[size][size];unsigned int i,j;int trace=0;
    for(i=0;i<size;i++) {
        for (j=0;j<size;j++) {
            diagonal[i][j] = 0;
        }
    }
    if (size==0){return 0;}
    else{
        for(i=0;i<size;i++) {
            for (j=0;j<size;j++) {
                diagonal[i][i] += weight[i][j];
            }
        }
        for(i=0;i<size;i++) {
            for (j=0;j<size;j++) {
                laplacian[i][j] = diagonal[i][j]-weight[i][j];
            }
        }
        for(i=0;i<size;i++) {
            trace+=laplacian[i][i];
        }
        return  trace;

    }
}


int main(){
    int size, trace;
    int weight[50][50] = {};
    cin >> size;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            cin >> weight[i][j];
    trace = traceLaplacian(weight, size);
    cout << trace << endl;
}
