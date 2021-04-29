/** Se supone que toda la enumeracion de arreglos empieza en 1
	No hay una razon mas que no tengo ni idea de como programar las funciones 
	sin hacerlo de esa manera
*/

#include <iostream>
#include <iomanip>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sys/time.h>
#include "ComputeOpt.hpp"
#include "arrays.hpp"
#include "ActivitySelector.hpp"

#define T 10

using namespace std;

int readSize();
void showArrays(int* s,int* f,int* v,int* p,int n);
double* calculateTimes(int n);
double getAverage(double* array);
void showAverages(double* tOpt, double* tMOpt,double *tFS,double *tRAS,double *tGAS);
void showDuration(double duration);

int main() {
		
	int n = readSize();
	double tOpt[T],tMOpt[T],tFS[T],tRAS[T],tGAS[T],*temp;
	
	system("cls");
	
	cout << "n = " << n-1 << "\n\n";
	
	for(int i = 0; i < T; i++){
		temp = calculateTimes(n);
		tOpt[i] = temp[0];
		tMOpt[i] = temp[1];
		tFS[i] = temp[2];
		tRAS[i] = temp[3];
		tGAS[i] = temp[4];
	}
	
	cout << "\n   ComputeOpt   MComputeOpt    FindSolution    GActivitySelector\n\n";
	
	for(int i = 0; i < T; i++){				
		std::cout << std::setfill(' ') << std::setw(2) << i+1 << " |";
		std::cout << std::setfill(' ') << std::setw(6) << tOpt[i];
		cout << "      ";
		std::cout << std::setfill(' ') << std::setw(7) << tMOpt[i];
		cout << "      ";
		std::cout << std::setfill(' ') << std::setw(7) << tFS[i];
		cout << "      ";
		std::cout << std::setfill(' ') << std::setw(7) << tRAS[i];
		cout << "      ";
		std::cout << std::setfill(' ') << std::setw(7) << tGAS[i];
		cout<< "\n";
	}
	
	showAverages(tOpt,tMOpt,tFS,tRAS,tGAS);

	
	return 0;
}

double* calculateTimes(int n){
	int *v,*p,*s,*m,*f;
	double t1,t2,tGen;
	int res,index;
	double *times = new double[5];
	timeval tim;
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	v = createArray(n);
	p = createArray(n);
	s = createArray(n);
	m = createArray(n);
	f = createArray(n);
	
	randomizeArray(f,n,tim.tv_usec);
	setArrayTo(p,n,0);
	setArrayTo(m,n,-1);
	setArrayTo(v,n,1);
	
	p[0] = s[0] = f[0] = 0;
	v[0] = 1;
	m[0] = -1;
	
	MergeSort(f,0,n-1);
	
	for(int i = 1; i < n; i++){
		s[i] = f[i] - (rand() % 10 + 1);
		if(s[i] < 0 ){
			s[i] = 0;
		}
	}
	
	for(int i = 1; i < n; i++){
		for(int j = 1; j < n; j++){
			if(s[i] > f[j]){
				p[i]++;
			}
		}
	}

	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	tGen = (t2-t1);		
	
	//showArrays(s,f,v,p,n);
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec; 	
	res = computeOpt(n-1,v,p);	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[0] = (t2-t1) + tGen;	
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec; 
	res = MComputeOpt(n-1,v,p,m);
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[1] = (t2-t1) + tGen;
	
	cout <<"Tiempo maximo = " << res << "\n";
	cout <<"Intervalos a tomar:\n";
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	findSolution(n-1,v,p,m);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[2] = (t2-t1) + tGen;
	cout << "\n\n";
	
	int *b = createArray(n);
	index = 0;
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	recursiveActivitySelector(s,f,0,n-1,b,index);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[3] = (t2-t1) + tGen;
	
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	int *a = greedyActivitySelector(s,f,n,&index);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[4] = (t2-t1) + tGen;
	
	return times;	
}

void showDuration(double duration){
	int seconds,ms,usec;
	int temp = (int) duration;
	
	seconds = temp/1000000;
	temp %= 1000000;
	
	ms = temp/1000;
	temp %= 1000;
	
	usec = temp % 1000;
	
	cout << seconds << " seconds  " << ms << "  miliseconds  " << usec << "  usec";
}

double getAverage(double* array){
	double average=0;
	for(int i = 0; i < T; i++){
		average += array[i];
	}
	return(average/T);
}

void showAverages(double* tOpt, double* tMOpt,double *tFS,double *tRAS,double *tGAS){
	double promOtp,promMOpt,promTFS,promRAS,promGAS;
	
	promOtp = getAverage(tOpt);
	promMOpt = getAverage(tMOpt);
	promTFS = getAverage(tFS);
	promRAS = getAverage(tRAS);
	promGAS = getAverage(tGAS);
	
	cout<< "\n\nPromedios:\n\n" << "ComputeOpt: ";
	showDuration(promOtp);
	cout<< "\nMComputeOpt: ";
	showDuration(promMOpt);
	cout<< "\nFindSolution: ";
	showDuration(promTFS);
	cout<< "\nRActivitySelector: ";
	showDuration(promRAS);
	cout<< "\nGActivitySelector: ";
	showDuration(promGAS);
}


void showArrays(int* s,int* f,int* v,int* p,int n){
	cout << "start\n";
	printArray(s,n);
	cout << "finish\n";
	printArray(f,n);
	cout << "v\n";
	printArray(v,n);
	cout << "p\n";
	printArray(p,n);
} 

int readSize(){
	int num;
	
	cout << "Ingresa n:\n";
	cin >> num;
	
	return ++num;
}

