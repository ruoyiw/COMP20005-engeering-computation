#include <stdio.h>
#include <stdlib.h>

int amicable_pair(int n1, int n2);

int main(int argc, char *argv[]){
	int n1, n2;
	
	printf("Enter two numbers: ");
	if (scanf("%d%d", &n1, &n2) != 2) {
		printf("Invalid input\n");
		exit(EXIT_FAILURE);
	}
	
	if (amicable_pair(n1, n2)) {
		printf ("%d and %d are an amicable pair\n", n1, n2);
	} else {
		printf ("%d and %d are not an amicable pair\n", n1, n2);
	}
	return 0;
}

int amicable_pair(int n1, int n2) {
	int divisor, sum1 = 1, sum2 = 1;
	for (divisor = 2; divisor * divisor < n1; divisor++) {
		if (n1%divisor == 0) {
			sum1 += divisor;
			sum1 += (n1/divisor);
		}
		if (divisor * divisor == n1) {
			sum1 += divisor;
		}
	}
	
	for (divisor = 2; divisor * divisor < n2; divisor++) {
		if (n2%divisor == 0) {
			sum2 += divisor;
			sum2 += (n2/divisor);
		}
		if (divisor * divisor == n2) {
			sum2 += divisor;
		}
	}
	
	if (n1 == sum2 && n2 == sum1 && n1!=n2) {
		return 1;
	} else {
		return 0;
	}
}
	
	
	
	
	
	