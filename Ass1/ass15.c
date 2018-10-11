/* Sample Solution to COMP20005 Assignment 1, March 2015.
   Alistair Moffat, ammoffat@unimelb.edu.au
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAX_PTS 100		/* maximum number of points per polygon */
#define MAX_POLYS 100		/* maximum number of polygons */
#define END_INPUT 0		/* no more sections to input */

				/* formatting for Stage 2 table */
#define DIV "+-------+-------+-------+-------+-------+"
#define HDR "|    id |  nval | perim |  area | eccen |"

#define IMPOSSIBLE (-1)		/* error value from max function */

/* function prototypes */
int    read_poly(int *poly_id, double x_val[], double y_val[]);
double poly_peri(double x_val[], double y_val[], int npoints);
double poly_area(double x_val[], double y_val[], int npoints);
double poly_ecce(double peri, double area);
void   copy_array(double from[], double copy[], double nvals);
void   print_stage_heading(int stage);
void   print_stage_one(int poly_id[], int npoints[],
		double peri[], double area[], double ecce[], int fstpoly,
		double x_val[], double y_val[]);
void   print_stage_two(int poly_id[], int npoints[],
		double peri[], double area[], double ecce[], int npolys);
void   print_stage_three(int poly_id[], int npoints[],
		double peri[], double area[], double ecce[], int maxpoly,
		double x_val[], double y_val[]);
void   print_poly_points(double x_val[], double y_val[], int np);


/* main program binds it all together
*/
int
main(int argc, char *argv[]) {

	/* storage for all of the input data */
	double x_val[MAX_PTS+1], y_val[MAX_PTS+1];
	double x_val_s1[MAX_PTS+1], y_val_s1[MAX_PTS+1];
	double x_val_s3[MAX_PTS+1], y_val_s3[MAX_PTS+1];
	double maxarea=-1.0; /* no poly can have negative area */
	int npoints[MAX_POLYS], poly_id[MAX_POLYS], maxpoly;
	int npolys=0, np;
	double peri[MAX_POLYS], area[MAX_POLYS], ecce[MAX_POLYS];

	/* main loop -- read the data, one polygon at a time, keeping
	   record of the points associated with the first polygon,
	   and points associated with the largest area one too */
	while ((np = read_poly(poly_id+npolys, x_val, y_val)) > 0) {
		peri[npolys] = poly_peri(x_val, y_val, np);
		area[npolys] = poly_area(x_val, y_val, np);
		ecce[npolys] = poly_ecce(peri[npolys], area[npolys]);
		npoints[npolys] = np;
		/* make a record of the first polygon */
		if (npolys==0) {
			copy_array(x_val, x_val_s1, np+1);
			copy_array(y_val, y_val_s1, np+1);
		}
		if (area[npolys]>maxarea) {
			/* need to retain this polygon's data, so can be
			   used in stage 3 */
			copy_array(x_val, x_val_s3, np+1);
			copy_array(y_val, y_val_s3, np+1);
			maxarea = area[npolys];
			maxpoly = npolys;
		}
		npolys++;
	}

	/* ok, now for the first stage output */
	print_stage_heading(1);
	print_stage_one(poly_id, npoints, peri, area, ecce, 0,
			x_val_s1, y_val_s1);

	/* second stage output */
	print_stage_heading(2);
	print_stage_two(poly_id, npoints, peri, area, ecce, npolys);

	/* third stage output */
	print_stage_heading(3);
	print_stage_three(poly_id, npoints, peri, area, ecce, maxpoly,
			x_val_s3, y_val_s3);

	/* and done! */
	return 0;
}

/* read a single polygon from the input, storing the points in to the two
   parallel arrays */
int
read_poly(int *poly_id, double x_val[], double y_val[]) {
	int npoints, i;
	if (scanf("%d", &npoints) == 0) {
		/* no more data available at all */
		return END_INPUT;
	} 
	if (npoints==0) {
		/* no more polygons available */
		return END_INPUT;
	}
	/* now assume that all other required components are available */
	scanf("%d", poly_id);
	for (i=0; i<npoints; i++) {
		scanf("%lf %lf", x_val+i, y_val+i);
	}
	/* close off, and store teh extra point */
	x_val[npoints] = x_val[0];
	y_val[npoints] = y_val[0];
	return npoints;
}

/* copy all elements of the first array to the second one
*/
void
copy_array(double from[], double copy[], double nvals) {
	int i;
	for (i=0; i<nvals; i++) {
		copy[i] = from[i];
	}
	return;
}


/* compute the perimeter of a polygon.
   first points is assumed to have been duplicated into last array
   position as well
*/
double
poly_peri(double x_val[], double y_val[], int npoints) {
	double sum=0, x_diff, y_diff;
	int i;
	for (i=0; i<npoints; i++) {
		/* assumes that an extra "closing" point is in the array */
		x_diff = x_val[i+1] - x_val[i];
		y_diff = y_val[i+1] - y_val[i];
		sum += sqrt(x_diff*x_diff + y_diff*y_diff);
	}
	return sum;
}

/* compute the area of a polygon.
   first points is assumed to have been duplicated into last array
   poistion as well
*/
double
poly_area(double x_val[], double y_val[], int npoints) {
	double sum=0, x_diff, y_avrg;
	int i;
	for (i=0; i<npoints; i++) {
		/* assumes that an extra "closing" point is in the array */
		x_diff = x_val[i+1] - x_val[i];
		y_avrg = (y_val[i+1] + y_val[i]) / 2;
		sum += y_avrg * x_diff;
	}
	return sum;
}

/* compute the eccentricity of a polygon, given its area and perimeter
*/
double
poly_ecce(double peri, double area) {
	return peri*peri/area/4/M_PI;
}

/* print out a stage heading, with a prior blank line once the stage number
   goes plus one */
void 
print_stage_heading(int stage) {
	/* main job is to print the stage number passed as an argument */
	if (stage>0) {
		/* separate the stages */
		printf("\n");
	}
	printf("Stage %d\n=======\n", stage);
	return;
}

/* generate the output format required for stage 1
*/
void
print_stage_one(int poly_id[], int npoints[],
		double peri[], double area[], double ecce[], int fstpoly,
		double x_val[], double y_val[]) {
	printf("First polygon is %d\n", poly_id[fstpoly]);
	print_poly_points(x_val, y_val, npoints[fstpoly]);
	printf("perimeter    = %5.2f m\n", peri[0]);
	printf("area         = %5.2f m^2\n", area[0]);
	printf("eccentricity = %5.2f\n", ecce[0]);
	return;
}

/* generate the output format required for stage 2
*/
void
print_stage_two(int poly_id[], int npoints[],
		double peri[], double area[], double ecce[],
		int npolys) {
	int i;
	printf("%s\n", DIV);
	printf("%s\n", HDR);
	printf("%s\n", DIV);
	for (i=0; i<npolys; i++) {
		printf("|");
		printf(" %5d | ", poly_id[i]);
		printf("%5d | ", npoints[i]);
		printf("%5.2f | ", peri[i]);
		printf("%5.2f | ", area[i]);
		printf("%5.2f ", ecce[i]);
		printf("|\n");
	}
	printf("%s\n", DIV);
	return;
}

/* generate the output format for required for stage 3
*/
void
print_stage_three(int poly_id[], int npoints[],
		double peri[], double area[], double ecce[], int maxpoly,
		double x_val[], double y_val[]) {
	printf("Largest polygon is %d\n", poly_id[maxpoly]);
	print_poly_points(x_val, y_val, npoints[maxpoly]);
	return;
}

/* print a set of points, used for stage 1 and stage 3
*/
void
print_poly_points(double x_val[], double y_val[], int np) {
	int i;
	printf("   x_val   y_val\n");
	for (i=0; i<np; i++) {
		printf("%7.1f %7.1f\n", x_val[i], y_val[i]);
	}
	return;
}