#include <iostream>

int max(int num1,int num2){
	int max;
	
	max = (num1 > num2) ? num1 : num2;
	
	return max;
}

int computeOpt(int j,int v[],int p[]){
	int num1,num2;
	if(j == 0){
		return 0;
	}else{
		return max(v[j] + computeOpt(p[j],v,p),computeOpt(j-1,v,p));
	}
}

int MComputeOpt(int j,int v[],int p[],int m[]){
	if(j == 0){
		return 0;
	}else if(m[j] != -1){
		return m[j];
	}else{
		m[j] = max(v[j] + MComputeOpt(p[j],v,p,m),MComputeOpt(j-1,v,p,m));
		return m[j];
	}
}

void findSolution(int j,int v[],int p[],int m[]){
	if(j == 0){
		return;
	}else{
		if(v[j] + m[p[j]] >= m[j-1]){
			std::cout << "[" << j << "]  ";
			findSolution(p[j],v,p,m);
		}else{
			findSolution(j-1,v,p,m);
		}	
	}
}
