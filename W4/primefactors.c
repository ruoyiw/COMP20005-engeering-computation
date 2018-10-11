/* Determine the prime factorization of an input number.
*/
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
	int
		n, 		/* the number being checked out */
		divisor;	/* a potential factor */
		
	/* print a prompt, read a number */
	printf("Enter a number n: ");
	if (scanf("%d", &n) != 1) {
		printf("Incorrect input\n");
		exit(EXIT_FAILURE);
	}

	/* a value for n has been read */
	printf("%d = ", n);

	/* first possible factor is 2
	   note that n decreases each time a factor is found, and that the
	   next potential divisor is the last one that was found to be
	   a factor */
	divisor = 2;
	while (n>1) {
		/* check divors, and onward, looking for factor */
		for ( ; divisor*divisor<=n; divisor++) {
			if (n%divisor==0) {
				break;
			}
		}
		/* check for completion of the loop via guard */
		if (divisor*divisor>n) {
			/* no divisor was found, so n is now prime */
			printf("%d", n);
			break;
		 } else {
		 	/* in here because loop broke with a factor */
			printf("%d x ", divisor);
			/* at least one more factor to come */
			n /= divisor;
		}
	}
	/* finish the output line */
	printf("\n");
	
	/* all done, folks, nothing more to see here */
	return 0;
}