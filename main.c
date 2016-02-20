#include "stdio.h"
#include "malloc.h"
//#include 

//using namespace std;

int main(){
int n, i, j, ff, fs, sf, ss;
scanf("%d", &n);
int **a = (int**)malloc(n * sizeof(int*));
for(i = 0; i < n; i++){
	a[i] = (int*)malloc(n * sizeof(int));
	for(int j = 0; j < n; j++){
		a[i][j] = (i + 1) * (j + 1);	
	}
}
while(1 != 0){
	scanf("%d", &ff);
	if(ff == 0){
		for(i = 0; i < n; i++){
			free(a[i]);
		}
		free(a);
	}
	else{
	scanf("%d %d %d", &fs, &sf, &ss);
	for(i = ff - 1; i < sf; i++){
		for(j = fs - 1; j < ss; j++){
		printf("%*d", 5, a[i][j]);
		}
		printf("\n");
	}
		
	}
}

}
