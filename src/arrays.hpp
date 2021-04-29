#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

using namespace std;

void setArrayTo(int* a,int n, int num){
	for(int i = 1; i < n; i++){
		a[i] = num;
	}
}

void intercambia(int *A, int *B){
    int Aux;

    Aux = *A;
    *A = *B;
    *B = Aux;
}

void printArray(int* a,int n){
	
	for(int i = 1; i < n; i++){
		cout << "[";
		std::cout.width(2);
		cout << a[i] << "] ";
	}
	cout << "\n\n";
}

int* createArray(int n){
	int* a = new int[n];
	
	return a;
}

void randomizeArray(int* a,int n,double SEED){
	srand(SEED);
	for(int i = 1; i < n; i++){
		a[i] = rand() % 20 + 1;
	}
}

void Merge(int A[],int p,int q, int r){
    int i,j,k;
    int n1=q-p+1;
    int n2=r-q;
    int L[n1],R[n2];
    for(i=0;i<n1;i++){
    	L[i]=A[p+i];
    }
    for(j=0;j<n2;j++){
    	R[j]=A[q+j+1];
    }
    L[n1]=INT_MAX;
    R[n2]=INT_MAX;

    i=0;
    j=0;
    for(k=p;k<=r;k++){
        if(L[i]<=R[j]){
            A[k]=L[i];
            i++;
        }else{
            A[k]=R[j];
            j++;
        }
    }  
}

void MergeSort(int A[],int p,int r){
    int q;
    if(p<r){
        q=floor((p+r)/2);
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
