#include <stdio.h>
#include <stdlib.h>
int fadd( int x , int y ){
	return x+y;
}

int fsub( int x, int y){
	return x-y;
	
}

typedef int algebra(int x, int y);
int main (void){
	algebra*  tbl[]={[1]=fadd, [0]=fsub};

	printf("%d\n", abs(tbl[0](5,10)));
}