#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int num, n;
	
	printf ("Enter numbers: ");
	scanf("%d", &num);
	if (num < 1 || num > 70) {
		printf("Invalid input\n");
		exit(EXIT_FAILURE);
	}
	
	while (scanf("%d", &num) == 1) {
	printf ("%d |", num);
	
	for (n = 0; n < num; n++) {
		printf("*");
	}		
	printf("\n");
	}
	
	return 0;
}