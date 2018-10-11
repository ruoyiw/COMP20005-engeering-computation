#include <stdio.h>
#include <stdlib.h>

int print_prime_factors(int n);

int
main(int argc, char *argv[]) {
	int n, factor;
	printf("Enter a number n: ");
	if (scanf("%d", &n) != 1) {
		printf("Incorrect input\n");
		exit(EXIT_FAILURE);
	}
	
	printf("%d = ", n);
	
	while (n > 1) {
		factor = print_prime_factors(n);
		printf("%d x", factor);
	}
	return 0;
}

int 
print_prime_factors(int n) {
	int divisor = 2;
	for ( ; divisor*divisor<=n; divisor++) {
			if (n%divisor==0) {
				break;
			}
	}
    if (divisor*divisor>n) {
			/* no divisor was found, so n is now prime */
			return n;
    } else {
		 	/* in here because loop broke with a factor */
			return divisor;
			/* at least one more factor to come */
			n /= divisor;
	}
		
}