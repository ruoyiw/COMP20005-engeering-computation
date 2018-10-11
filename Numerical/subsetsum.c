/* Recursive exhaustive evaluation of subset sum problem
   using a generate and test approach.
*/
#include <stdio.h>
#include <stdlib.h>

int subsetsum(int A[], int n, int k);

int
main(int argc, char *argv[]) {
	/* simple data for testing */
	int A[] = {
	 34,  38,  39,  43,  55,  66,  67,  84,  85,  91,
	101, 117, 128, 138, 165, 168, 169, 182, 184, 186,
	234, 238, 241, 276, 279, 288, 386, 387, 388, 389,
	413, 444, 487, 513, 534, 535, 616, 722, 786, 787
	};
	int n=20, k=1000;
	if (argc==3) {
		n = atoi(argv[1]);
		k = atoi(argv[2]);
	}
	printf("n=%d, k=%d, subsetsum = %d\n",
			n, k, subsetsum(A, n, k));
	return 0;
}

int
subsetsum(int A[], int n, int k) {
	if (k==0) {
		return 1;
	} else if (n==0) {
		return 0;
	} else {
		return subsetsum(A, n-1, k-A[n-1]) ||
			subsetsum(A, n-1, k);
	}
}

/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */