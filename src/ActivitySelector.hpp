#include <iostream>

using namespace std;

void recursiveActivitySelector(int* s,int* f, int k, int n,int *res,int iRes){
	int m;
	
	m = k + 1;
	
	while(m <= n && s[m] < f[k]){
		m++;
	}
	if(m <= n){
		iRes++;
		res[iRes] = m;
		recursiveActivitySelector(s,f,k,n,res,iRes);
	}else{
		return;
	}
}

int* greedyActivitySelector(int* s,int* f,int n,int *index){
	int *A,*aux,i = 1;
	
	A = createArray(n);
	
	A[i] = 1;
	int k = 1;
	for(int m = 2; m <= n; m++){
		if(s[m] >= f[k]){
			A[i] = m;
			++i;
			k = m;
		}
	}
	(*index) = i;
	return A;
}
