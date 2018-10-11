/* Starting point for Gaussian elimination on fixed matrix
 * Alistair Moffat, June 2013.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-6

#define EQUATIONS 10

void gaussian(double A[][EQUATIONS+1], int n);
void printeqs(double A[][EQUATIONS+1], int n, char *msg);
void swaprows(double A[][EQUATIONS+1], int n, int row, int maxrow);

int
main(int argc, char *argv[]) {

	
	double A[EQUATIONS][EQUATIONS+1] =
		{{0,2,3,1},
		 {3,5,6,2},
		 {9,2,3,3}};
	/* that is, 0x_0 + 2x_1 + 3x_2 = 1, etc */
	
	double B[EQUATIONS][EQUATIONS+1] =
		{{ 1, 1, 2, 3, 4},
		 {-1, 4,-2, 0, 5},
		 { 2, 0, 0, 1,-6},
		 { 4, 0, 0, 2,-12}};
		
	int nA=3, nB=4;

	printeqs(B, nB, "Starting");
	gaussian(B, nB);
	printeqs(B, nB, "Final");
	
	return 0;
	
	printeqs(A, nA, "Starting");
	gaussian(A, nA);
	printeqs(A, nA, "Final");
	
	return 0;

	
}

void
gaussian(double A[][EQUATIONS+1], int n) {
	int row, i, j, maxrow;
	double pivot;
	/* forwards stage, to build into upper triangular */
	for (row=0; row<n; row++) {
		/* look at A[row][row] and below for largest magnitude */
		maxrow = row;
		for (i=row+1; i<n; i++) {
			if (fabs(A[i][row]) > fabs(A[maxrow][row])) {
				maxrow = i;
			}
		}
		/* check for nonzero in maxrow */
		if (fabs(A[maxrow][row]) < EPS) {
			printf("System does not have simple solution\n\n");
			return;
		}
		/* swap the rows over */
		swaprows(A, n, row, maxrow);
		printeqs(A, n, "After row swap");

		/* optional -- scale row to get 1.0 in A[row][row] */
		for (j=n; j>=row; j--) {
			A[row][j] = A[row][j]/A[row][row];
		}
		printeqs(A, n, "After row normalization");

		/* eliminate below A[row][row] */
		for (i=row+1; i<n; i++) {
			pivot = -A[i][row]/A[row][row];
			for (j=row; j<=n; j++) {
				A[i][j] = A[i][j] + pivot*A[row][j];
			}
			printeqs(A, n, "After elimination");
		}
	}

	/* Now in upper triangular form, next step is the 
	   back substitution */


	return;
}

void
swaprows(double A[][EQUATIONS+1], int n, int row, int maxrow) {
	double tmp;
	int i;
	for (i=row; i<n+1; i++) {
		tmp = A[row][i];
		A[row][i] = A[maxrow][i];
		A[maxrow][i] = tmp;
	}
}

void
printeqs(double A[][EQUATIONS+1], int n, char *msg) {
	int i, j;
	printf("%s:\n", msg);
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			printf("%6.3fx_%d", A[i][j], j);
			if (j<n-1) {
				printf(" + ");
			} else {
				printf(" = ");
			}
		}
		printf("%6.3f\n", A[i][n]);
	}
	printf("\n");
	return;
}