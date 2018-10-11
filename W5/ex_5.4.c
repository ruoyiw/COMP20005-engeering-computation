/* Exercise 5.4: Combinations
   Alistair Moffat, March 2013.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* function prototypes */
int n_choose_k(int n, int k);
int factorial(int n);

int
main(int argc, char *argv[]) {
	int n, k;

	/* simple scaffolding */
	printf("Enter n and k: ");
	if (scanf("%d%d", &n, &k) != 2) {
		printf("Invalid input\n");
		exit(EXIT_FAILURE);
	}

	/* now call the function */
	printf("%d choose %d = %d\n", n, k, n_choose_k(n,k));

	/* that's it folks */
	return 0;
}

int factorial(int n) {
	int i, factors =1;
	for (i = 2; i <= n; i++) {
		if (i * facotrs >= INT_MAX) {
			/* equivalent to fact*i>=INT_MAX */
			printf("Integer overflow problem\n");
			exit(EXIT_FAILURE);
		}
		/* ok, now know it is safe */
		factors *= i;
	}
	return factors;
}

int
n_choose_k(int n, int k) {
	/* too easy! */
	return (factorial(n)/(factorial(k)*(factorial(n-k))));
}