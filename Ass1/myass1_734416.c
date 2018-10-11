/* assignment1 of COMP20005 to show the data of the apartments.
   Author: qiulei zhang
   My user name: qiuleiz 
   My student number: 734416;
   Last time to modify:25/04/2016
   programming is fun! */

#include <stdio.h>
#include <stdlib.h>

/*define the maximum number of the room and apartment */
#define MAX_ROOM 100
#define MAX_APRT 100
#define MAX_X    99.99
#define MAX_Y    99.99

#define SUCCESS 1
#define FALSE 0

/* define the type of the room */
#define END_ROOM -1
#define HALLWAY 1
#define BEDROOM 2
#define LIVING 3
#define BATHROOM 4
#define KITCHEN 5
#define LAUNDRY 6
#define STORAGE 7
#define GARAGE 8
#define BALCONY 9

/* formatting for table */
#define SHORT_DIV "-------------"
#define SAME_ROOM "   ---"
#define DIV "+-------+---------------+---------------+-----------------+"
#define HDR "| Apart |    Dry areas  |   Wet areas   |   Utility areas |"
#define STA "    Total area               "

/* function prototypes */
int read_apartment(int apartment_number[],int num_aprt);
int read_rooms(int room_type[],int room_num[],
	double xsize[],double ysize[]);
void calculate_area(int length_room,double area[],double xsize[],
	double ysize[],double sum_area[],int num_aprt);
void calculate_area_type(int length_room,double area[],
	int room_type[],double dry_area[],double wet_area[],
	double utility_area[],int num_aprt);
void print_apartment(int num_aprt,int length_room,int apartment_number[],
	int room_type[],int room_num[],double xsize[],double ysize[],
	double area[],double sum_area[]);
void printf_room_type(int room_type);
void print_table(int length_apartment,int apartment_number[],double dry_area[],
	double wet_area[],double utility_area[], double sum_area[]);
void check_max(double num,double max);
void check_positive(int num);
void check_input(int i);
double cal_percent(double num,double deno);

int
main(int argc, char *argv[]) {
	/* storage for all of the data of all apartments */
	int apartment_number[MAX_APRT],
		 room_type[MAX_ROOM+1],  /*including one more number '0' for comparing*/
		 room_num[MAX_ROOM+1];
	double xsize[MAX_ROOM], ysize[MAX_ROOM];		
	double area[MAX_ROOM+1],
			sum_area[MAX_APRT], 
			dry_area[MAX_APRT],
			wet_area[MAX_APRT],
			utility_area[MAX_APRT];	
	int length_room=0,i;  
	
	/* the main loop--reading the data of all the rooms of each apartment,
	calculating the different types of area, print the data out*/
	for(i=0;read_apartment(apartment_number,i);i++){ 
		/* input and store all the data of rooms in an apartment*/			
		length_room = read_rooms(room_type,room_num,xsize,ysize);
		
		/*calculate the different types of area*/
		calculate_area(length_room,area,xsize,ysize,sum_area,i);
		calculate_area_type(length_room,area,room_type,dry_area,
			wet_area,utility_area,i);
		
		/* output the the data all of the rooms of an apartment*/
		print_apartment(i,length_room,apartment_number,room_type,
			room_num,xsize,ysize,area,sum_area);
	}
	/*judge whether there is no data*/
	check_input(i); 
	
	/*output the table about different types of area in different apartments*/
	print_table(i,apartment_number,dry_area,wet_area,utility_area,sum_area);
	return 0;
}
/* read the data about an apartment*/
int
read_apartment(int apartment_number[],int num_aprt){
	if(scanf("%d",&apartment_number[num_aprt])==1){
		/* input file will have fewer than 100 apartments described in it */
		check_max(num_aprt*1.0,MAX_APRT*1.0);		
		/* the value of apartment_number should be positive*/
		check_positive(apartment_number[num_aprt]);	
		return SUCCESS;
	}
	else{
		return FALSE;
	}
}

/* read all of the rooms'data,including type,number,xsize,ysize*/
int 
read_rooms(int room_type[],int room_num[],
	double xsize[],double ysize[]){
	int j;
	for(j=0;scanf("%d",&room_type[j])==1&&room_type[j]!=END_ROOM;j++){
			if(scanf("%d %lf %lf",&room_num[j],&xsize[j], &ysize[j])!=3){
				printf("incorrect number");
				exit(EXIT_FAILURE);
			}

			/* check the input number not exceed the maximum*/
			check_max(j*1.0,MAX_ROOM*1.0);
			check_max(xsize[j],MAX_X);
			check_max(ysize[j],MAX_Y);
			
			/* the value of room_type and room_num should be positive*/
			check_positive(room_type[j]);
			check_positive(room_num[j]);
	}
	/* ensure the last room(length+1) has variables for comparing*/
	room_type[j] = 0;
	room_num[j] = 0;
	/* judge whether there is datat*/
	check_input(j);
	return j;
}

/*count the area of each room and 
    then calculate the total area in an apartment*/
void 
calculate_area(int length_room,double area[],double xsize[],
	double ysize[],double sum_area[],int num_aprt){
	int j;
	sum_area[num_aprt] = 0;
	for(j=0;j<length_room;j++){			
		/*calculate the area of the room*/
		area[j] = xsize[j] *ysize[j];
		sum_area[num_aprt] += area[j];
	}
}

/*according to all types of room, count the different types of area*/
void 
calculate_area_type(int length_room,double area[],
	int room_type[],double dry_area[],double wet_area[],
	double utility_area[],int num_aprt){
	int j;
	for(j=0;j<length_room;j++){
		/*judge the room belong to which area*/
		if(room_type[j]==HALLWAY || room_type[j]== BEDROOM 
			|| room_type[j]== LIVING){
				dry_area[num_aprt] += area[j];
		}
		else if(room_type[j]==BATHROOM ||room_type[j]==KITCHEN
			||room_type[j]==LAUNDRY){
				wet_area[num_aprt] += area[j];
		}
		else{
			utility_area[num_aprt] += area[j];
		}
	}
}

/*generate the output format of all the data of rooms in an apartment*/
void 
print_apartment(int num_aprt,int length_room,int apartment_number[],
	int room_type[],int room_num[],double xsize[],double ysize[],
	double area[],double sum_area[]){
	int j;
	/*output the value of the apartment number*/
	printf("Apartment %d\n",apartment_number[num_aprt]);
	printf("%s\n",SHORT_DIV);
		
	/*output the data about the room*/
	for(j=0; j<length_room; j++){
		/* output the type of the room*/
		printf_room_type(room_type[j]);
			
		/*show the room_num, xsize,ysize*/
		printf("%2d  ",room_num[j]);
		printf("%5.2f  ",xsize[j]);
		printf("%5.2f",ysize[j]);
			
		/* judge the room whether is the same room*/
		if(room_type[j]==room_type[j+1]&&room_num[j]==room_num[j+1]){
			area[j+1] += area[j];
			printf("%s\n",SAME_ROOM);
		}else{
			printf("%7.2f\n",area[j]);
		}			
	}		
	/*output the total area of the apartment*/
	printf("%s%7.2f metres^2\n\n",STA,sum_area[num_aprt]);					
}

/*generate the output table to show different areas and their percent*/
void 
print_table(int length_apartment,int apartment_number[],double dry_area[],
	double wet_area[],double utility_area[], double sum_area[]){
	int i;
	printf("%s\n",DIV);
	printf("%s\n",HDR);
	printf("%s\n",DIV);
	for(i=0;i<length_apartment; i++){
		printf("|  %3d  |",apartment_number[i]);
		printf(" %6.2f  %4.1f%% |",dry_area[i],
			cal_percent(dry_area[i],sum_area[i]));
		printf(" %6.2f  %4.1f%% |",wet_area[i],
			cal_percent(wet_area[i],sum_area[i]));
		printf(" %6.2f   %4.1f%%  |\n",utility_area[i],
			cal_percent(utility_area[i],sum_area[i]));
	}
	printf("%s\n",DIV);
}

/*according to different type of room, output its type*/
void
printf_room_type(int room_type){
		printf("    ");
		if(room_type==HALLWAY){
			printf("Hallway  ");
		}else if(room_type==BEDROOM){
			printf("Bedroom  ");
		}else if(room_type==LIVING){
			printf("Living   ");
		}else if(room_type==BATHROOM){
			printf("Bathroom ");
		}else if(room_type==KITCHEN){
			printf("Kitchen  ");
		}else if(room_type==LAUNDRY){
			printf("Laundry  ");
		}else if(room_type==STORAGE){
			printf("Storage  ");
		}else if(room_type==GARAGE){
			printf("Garage   ");
		}else if(room_type==BALCONY){
			printf("Balcony  ");
		}else{
			printf("incorrect value of room type!");
			exit(EXIT_FAILURE);
		}
}

/*check the number whether it exceeds the maximum number*/
void 
check_max(double num,double max){
	if( num >= max){
		printf("exceed the maximun number");
		exit(EXIT_FAILURE);
	}	
	
}

/*check whether the number is positive*/
void 
check_positive(int num){
	if( num <= 0){
		printf("incorrct number");
		exit(EXIT_FAILURE);
	}		
}

/*check whether there is no data input*/
void
check_input(int i){
	if(i==0){
		printf("there is no data input");
		exit(EXIT_FAILURE);
	}
}


/*calculate the percent*/
double
cal_percent(double num,double deno){
	return num/deno*100.0;
}

