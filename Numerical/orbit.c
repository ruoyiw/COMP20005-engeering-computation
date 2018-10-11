/* Estimate, via an approximation, the orbital period of the earth.
 * Data from http://en.wikipedia.org/wiki/Earth, from
 *           http://en.wikipedia.org/wiki/Sun and from
 *           http://en.wikipedia.org/wiki/Gravity
 * 
 * Alistair Moffat, ammoffat@unimelb.edu.au
 * May 2011
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OUTSIZE 80		/* size of plot, characters per quadrant */

#define G	(6.67428e-11)	/* gravitational constant, N x (m/kg)^2  */
#define M_SUN	(1.9891e30)	/* mass of the sun, kg */
#define M_EARTH (5.9736e24)	/* mass of earth, kg */
#define V_EARTH	(29.78e3)	/* earth average orbital velocity, m/sec */
#define X_EARTH	((152.098e9+147.098e9)/2)
				/* max/min distance of earth from sun */

#define	SEC_PER_DAY (60*60*24)	/* length of day, seconds */

#define RATIO	0.45		/* ratio width/height of characters */
#define XSCALE	(OUTSIZE/(1.51*X_EARTH))
#define YSCALE	(XSCALE*RATIO)

#define ITERATIONS 1e7		/* maximum loop iterations */

typedef int pix_t[2*OUTSIZE+1][2*OUTSIZE+1];

int
myround(double x) {
	if (x>0) return (int)(x+0.5);
	if (x<0) return (int)(x-0.5);
	return x;
}

/* clear all the entries in the map */
void
clear_pix(pix_t pix) {
	int x, y;
	for (y=OUTSIZE; y>=-OUTSIZE; y--) {
		for (x=-OUTSIZE; x<=OUTSIZE; x++) {
			pix[y+OUTSIZE][x+OUTSIZE] = 0;
		}
	}
}

/* compute location within the map and record a day number */
void
set_pix(pix_t pix, double x, double y, double sec) {
	int sx, sy;
	sx = myround(x*XSCALE);
	sy = myround(y*YSCALE);
	if (-OUTSIZE<=sx && sx<=OUTSIZE && -OUTSIZE<=sy && sy<=OUTSIZE) {
		pix[sy+OUTSIZE][sx+OUTSIZE] = 0.5+sec/SEC_PER_DAY;
	}
}

/* print the map, in this version the day numbers are ignored */
void
print_pix(pix_t pix) {
	int x, y;
	for (y=OUTSIZE*RATIO; y>=-OUTSIZE*RATIO; y--) {
		for (x=-OUTSIZE; x<=OUTSIZE; x++) {
			if (y==0 && x==0) {
				printf("+") ;
			} else if (pix[y+OUTSIZE][x+OUTSIZE]!=0) {
				printf("*");
			} else if (x==0) {
				printf("|") ;
			} else if (y==0) {
				printf("-") ;
			} else {
				printf(" ") ;
			}
		}
		printf("\n");
	}
}

int
main(int argc, char **argv) {
	pix_t pix;
	double mass=M_EARTH, x=X_EARTH, y=0, vx=0, vy=V_EARTH, fx, fy;
	double d, f;
	double sec=0.0;
	double delta_t=0.0;
	int seennegx=0, seennegy=0;
	int iterations=0;

	if (argc<2) { 
		printf("Usage: %s delta_t\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	delta_t = atof(argv[1]);

	clear_pix(pix);
	/* try and step through one complete orbit */
	while ((!seennegx || !seennegy || y<0) && (iterations<ITERATIONS)) {
		/* compute magnitude of the force applying */
		d = sqrt(x*x + y*y);
		f = G*M_SUN*mass/(d*d);
		/* project the force vector, it opposes the displacement */
		fx = -f*x/d;
		fy = -f*y/d;
		/* now move the object by one timestep */
		x += vx*delta_t;
		y += vy*delta_t;
		/* and adjust velocity too, according to force projections */
		vx = vx + fx/mass*delta_t;
		vy = vy + fy/mass*delta_t;
		/* and record new location */
		set_pix(pix, x, y, sec);
		/* bookkeeping, to make sure we stop after one orbit,
		   or after a fixed amount of computation */
		if (y<0) seennegy = 1;
		if (x<0) seennegx = 1;
		sec += delta_t;
		iterations += 1;
	}
	print_pix(pix);
	if (iterations<ITERATIONS) {
		printf("Orbit = %.4f days\n", 1.0*sec/SEC_PER_DAY);
	} else {
		printf("Non-convergenge after %.4f days tracked\n",

			1.0*sec/SEC_PER_DAY);
	}
	return 0;
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