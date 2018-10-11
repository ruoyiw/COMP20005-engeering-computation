#include <stdio.h>
    #include <stdlib.h>

    int A[] = {1,2,3,4,6,7,8,9,10,11,12,13,22,33,44,55,66,77,99};

    void
    subsetsumrec(int A[], int n, int k, int B[], int nb) {
        int i;
        if (n==0) {
            /* there aren't any more numbers to consider, do we have
               a solution? */
            if (k==0) {
                /* yes, so print out the values that make it up, 
                   these are stored in B[0..nb-1] */
                for (i=0; i<nb; i++) {
                    printf("%3d ", B[i]);
                }
                printf("\n");
            }
        } else {
            /* still values to be either added in or not added in.
               if we do add another value in, it will be A[0] that gets
               included, so lets get it in to B now */
            B[nb] = A[0];
            /* first, try adding A[0] in to the solution, and recurse
               using the trailing n-1 items in A, and for B[0..nb-1] to
               be the value used so far, need to recurse with nb+1 */
            subsetsumrec(A+1, n-1, k-A[0], B, nb+1);
            /* and then try without that first item in A[0],
               try to make original total out of trailing items in A,
               with B[0..nb-1] again the ones used so far, recursing
               with the original nb value and ignoring B[nb] (which is
               still A[0]) */
            subsetsumrec(A+1, n-1, k,      B, nb  );
        }
        return;
    }

    /* starter function, needed in order to declare the array B */
    void
        print_subsetsum(int A[], int n, int k) {
        int B[100]; /* 100 is pretty safe, since running time is 2^n */
        /* now call the recursive helper, starting with empty array B */
        subsetsumrec(A, n, k, B, 0);
        return;
    }

    /* you don't have to write this as part of your answer, it is here just
       so that you can compile and play with the function */
    int
    main(int argc, char *argv[]) {
        int k;
        if (argc>1) {
            /* get target value form command line */
            k = atoi(argv[1]);
        } else {
            /* any old default value will do */
            k = 100;
        }
        printf("subsets summing to %d:\n", k);
        print_subsetsum(A, sizeof(A)/sizeof(*A), k);
        return 0;
    }
