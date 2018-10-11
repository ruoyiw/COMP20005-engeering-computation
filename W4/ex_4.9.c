/* Exercise 4.9: Compute the next prime number
   Alistair Moffat, March 2013
*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
	int n, isprime, d, prime_found = 0;
	
	printf("Enter an integer value: ");
	if (scanf("%d", &n) != 1) {
		printf("Invalid input\n");
		exit(EXIT_FAILURE);
	}
	
	while (prime_found == 0) {
		n += 1;
	    isprime = 1;
	    for (d = 2; d*d <= n; d++) {
		    if (n%d == 0) {
			    isprime = 0;
			    break;
		    }
	    }
	    if (isprime == 0) {
	    	prime_found = 0;
	    } else {
	    	prime_found = 1;
	    }
	}
	
	printf("The next prime is     : %d\n", n);
	
	return 0;
}