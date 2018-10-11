/*
Content: COMP20005 Assigment 1
Author: Ruoyi Wang
Student ID: 683436
Login Name: ruoyiw
Date: April 14 2016
*/

/* programming is fun! */
#include <stdio.h>
#include <stdlib.h>

/* the numbers represent the nine room types */
#define UNUSED    0
#define HALLWAY   1	
#define BEDROOM   2
#define LIVING    3
#define BATHROOM  4
#define KITCHEN   5
#define LAUNDRY   6
#define STORAGE   7
#define GARAGE    8
#define BALCONY   9

#define MAX_RMS 100		/* maximum number of rooms per apartment */
#define MAX_APRTS 100		/* maximum number of apartments */

				/* formatting for Stage 4 table */
#define DIV "+-------+----------------+----------------+----------------+"
#define HEADER "| Apart |    Dry areas   |    Wet areas   |  Utility areas |"

#define SENTINEL (-1) /* the sentinel to end the input stream */

/* function prototypes */
int read_apartment(int aprtment_number[], int n_aprt);
int read_room(int room_type[], int room_num[], double xsize[], double ysize[], 
	double room_area[], double total_area[], int n_aprt);
void print_apartment_heading(int apartment_number[], int n_aprt);
void print_room_type(int room_type_code);
void print_apartment_data(int room_type[], int room_num[], double xsize[], 
	double ysize[], double room_area[], double total_area[], int n_aprt, 
	int n_room);


/* main program binds it all together */
int
main(int argc, char *argv[]) {
	
    /* storage for all of the input data */
	int apartment_number[MAX_APRTS], room_type[MAX_RMS+1], room_num[MAX_RMS+1];
	double xsize[MAX_RMS], ysize[MAX_RMS];
	double room_area[MAX_RMS+1], total_area[MAX_APRTS];
	int n_aprt, n_room;
	
	
	/* main loop to read the data of one apartment at a time, calculating 
	different types of area and print out the data */
	for (n_aprt = 0; read_apartment(apartment_number, n_aprt); n_aprt++) {
		print_apartment_heading(apartment_number, n_aprt);
		n_room = read_room(room_type, room_num, xsize, ysize, room_area, 
			total_area, n_aprt);
        print_apartment_data(room_type, room_num, xsize, ysize, room_area, 
        	total_area, n_aprt, n_room);
	}
	
	
	return 0;
}

/* read the apartment number first */
int
read_apartment(int apartment_number[], int n_aprt) {
	if (scanf("%d", &apartment_number[n_aprt]) == 1 && 
		apartment_number[n_aprt] > 0) {
	    return 1;
	} else {
		return 0;
	}
}

/* print out a apartment heading, with a prior blank line to separate 
   apartments */
void 
print_apartment_heading(int apartment_number[], int n_aprt) {
	printf("Apartment %d\n-------------\n", apartment_number[n_aprt]);
}

/* read a single apartment from the input, storing and calculating room data 
   into arrays, return the number of rooms */
int 
read_room(int room_type[], int room_num[], double xsize[], double ysize[], 
	double room_area[], double total_area[], int n_aprt) {
	int next, i;
	total_area[n_aprt] = 0;
	if (scanf("%d", &next) == 0 || next == SENTINEL) {
		/* no more data available */
		return 0;
	} 
	for (i = 0; next > 0; i++) {
		room_type[i] = next;
		scanf("%d %lf %lf", &room_num[i], &xsize[i], &ysize[i]);
		
		/* calculate each room area */
		room_area[i] = xsize[i] * ysize[i];
		total_area[n_aprt] += room_area[i];
		scanf("%d", &next);
	}
	/* store an extra room for comparing later */
	room_type[i] = 0;
	room_num[i] = 0;
	return i;
}

/* get the indicator of the type of room, print out associated room type */
void 
print_room_type(int room_type_code) {
		if (room_type_code == UNUSED) {
			printf("    Unused  ");
		} else if (room_type_code == HALLWAY) {
			printf("    Hallway ");
		} else if (room_type_code == BEDROOM) {
			printf("    Bedroom ");
		} else if (room_type_code == LIVING) {
		    printf("    Living  ");
		} else if (room_type_code == BATHROOM) {
		    printf("    Bathroom");
		} else if (room_type_code == KITCHEN) {
		    printf("    Kitchen ");
	    } else if (room_type_code == LAUNDRY) {
		    printf("    Launtry ");
	    } else if (room_type_code == STORAGE) {
		    printf("    Storage ");
	    } else if (room_type_code == GARAGE) {
		    printf("    Garage  ");
	    } else if (room_type_code == BALCONY) {
		    printf("    Balcony ");
	    } else {
		    printf("Invalid input\n");
		    exit(EXIT_FAILURE);
	    }
}

/* print out all the room data in an apartment */
void 
print_apartment_data(int room_type[], int room_num[], double xsize[], 
	double ysize[], double room_area[], double total_area[], int n_aprt,
	int n_room) {
    int i;
    /* print out the types, numbers, sizes and areas of each room */
    for (i = 0; i < n_room; i++) {
    	print_room_type(room_type[i]);
    	printf("%2d %6.2f %6.2f", room_num[i], xsize[i], ysize[i]);
    	
    	/* check the same room and print out a single total area for each room
    	   as a whole */
		if(room_type[i] == room_type[i+1] && room_num[i] == room_num[i+1]) {
			room_area[i+1] += room_area[i];
			printf("   ---\n");
		} else {
			printf("%7.2f\n",room_area[i]);
		}			
	}
	/* print out the total area of apartment */
	printf("    Total area %20.2f metres^2\n", total_area[n_aprt]);
	printf("\n");
}
	
/* calculate the area in an apartment of the three categories */
void 
calculate_category_area(int room_type[], int double room_area[], 
	double dry_area[], double wet_area[], double utility_area[], int n_aprt, 
	int n_room) {
	int i;
	/* determine which category the room falls in */
	for(i = 0; i < n_room; i++) {
		if (room_type[i] == HALLWAY || room_type[i] == BEDROOM 
			|| room_type[i] == LIVING) {
		    dry_area[n_aprt] += room_area[i];
		} if (room_type[i] == BATHROOM ||room_type[i] == KITCHEN
			||room_type[i] == LAUNDRY) {
		    wet_area[n_aprt] += room_area[i];
		} if (room_type[i] == STORAGE ||room_type[i] == GARAGE
			||room_type[i] == BALCONY) {
			utility_area[n_aprt] += room_area[i];
		} else {
			
		}
	}
}		
	
	
