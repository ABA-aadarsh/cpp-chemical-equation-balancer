#pragma once
#include <cmath>
#include <cstdlib>
#include<iostream>
using namespace std;

int findPivotColumn(int row, float ** table, int r, int c){
    int pivotColumn=-1;
    for(int i=0; i<c; i++){
        if(table[row][i]!=0){
            pivotColumn = i;
            break;
            std::string name = "Aadarsh";
        }
    }
    return pivotColumn;
}
void displayTable(float **table, int r, int c){
    cout << "\nTS..........\n";
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << table[i][j]<< "      ";
        }
        cout << "\n";
    }
    cout << "\nTE............\n";
}
void swapRows (int r1, int r2, float ** table, int r, int c){
    float temp;
    for(int i =0; i<c; i++){
        temp = table[r1][i];
        table[r1][i] = table[r2][i];
        table[r2][i] = temp;
    }
}
void divideRowByValue(int row, float value, float **table, int r, int c){
    for(int i=0; i<c; i++){
        table[row][i] /= value;
    }
}
void reduceRowByFactor(int row, int factorRow, float factor, float **table, int r, int c){
    // row -> row - factor * factorRow;
    for(int i =0; i<c; i++){
        table[row][i] -= factor * table[factorRow][i];
    }
}
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int notFloaty(float l[], int r) {
    int k = 1;
    float number = 0;
    for (int i =0; i< r; i++) {
        number = std::abs(l[i]);
        int denominator = 1;
        while (std::fmod(number * denominator, 1.0) != 0.0) {
            denominator *= 2;
        }
        k = lcm(k, denominator);
    }

    return k;
}

int nonFloaty2 (float l[], int r){
    int soln=1;
    for(int i =0; i<r; i++){
        if(abs(l[i])<1){
            soln = lcm(int(abs(1/l[i])), soln);
        }
        else{
            soln = lcm(abs(int(l[i])), soln);
        }
    }
    return soln;
}

void solver(float **table, float soln[], int r, int c){
    int tempInt, pivotColumn;
    // for(int i =0; i<r; i++){
    //     for(int j=0; j<c; j++){
    //         cout << table[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    float tempFloat, pivotValue, lastColumn[r];
    // displayTable(table, r, c);
    if(table[0][0]==0){
        for(int i=1; i<r; i++){
            if(table[i][0]!=0){
                tempInt=i;
                break;
            }
        }
        swapRows(0, tempInt, table, r, c);
        // displayTable(table, r, c);
    }
    for(int i =0; i<r; i++){
        // pivotColumn=findPivotColumn(i, table, r, c);
        // if(pivotColumn==-1){
        //     for(int it=i+1; it<r; it++){
        //         if(table[it][0]!=0){
        //             tempInt=it;
        //             break;
        //         }
        //     }
        //     swapRows(i, tempInt, table, r, c);
        //     displayTable(table, r, c);
        //     i--;
        //     continue;
        // }
        pivotColumn = i;
        if(table[i][i]==0){
            tempInt=-1;
            // cout << "i = " << i << " table[i][i] = "<< table[i][i] << endl;
            for(int it = i+1; it<r;it++){
                if(table[it][i]!=0){
                    tempInt=it;
                    break;
                }
            }
            if(tempInt==-1){
                cerr << "Cant Solve this equation\n";
                break;
            }else{
                swapRows(i, tempInt, table, r, c);
            }
        }
        pivotValue = table[i][pivotColumn];
        divideRowByValue(i, pivotValue, table, r, c);
        // displayTable(table, r, c);
        for(int j=0; j<r; j++){
            if(j==i) continue;
            tempFloat = table[j][pivotColumn];
            reduceRowByFactor(j, i, tempFloat, table, r, c);
            // displayTable(table, r, c);
        }
    }
    // for(int i =0; i<r; i++){
    //     for(int j=0; j<c; j++){
    //         cout << table[i][j] << "   ";
    //     }
    //     cout << endl;
    // }

    // displayTable(table, r, c);
    for(int i=0; i<r; i++){
        lastColumn[i] = table[i][c-1];
    }
    int f = nonFloaty2(lastColumn, r);
    soln[c-1] = f;
    for(int i=r-1; i>=0; i--){
        soln[i] = 0;
        for(int j=i+1; j<c; j++){
            soln[i] += -soln[j] * table[i][j];
        }
    }
    int g = soln[0];
    for(int i=1; i<c; i++){
        g = gcd(int(soln[i]), g);
    }
    for(int i=0; i<c;i++){
        soln[i] /= g;
    }
    // cout << "Solution: " << endl;
    // for(int i=0; i<c; i++){
    //     cout << soln[i] << endl;
    // }
}
