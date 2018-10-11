
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
	int num;  // the amount in cents
	
	printf("Enter amount in cents:  ");
	
	if((scanf("%d",&num)!=1) || num < 0 || num > 99){
		printf("incorrect amounts");
		return(EXIT_FAILURE);
	}
	
	printf("The coins required to make %d cents are:  \n", num);
	
	while(num != 0){
		if(num >= 50){
			num -= 50;
			printf("50");
		}
		else if(num >= 20){
			num -= 20;
			printf("20");
		}
		else if(num >= 10){
			num -= 10;
			printf("10");
		}
		else if(num >= 5){
			num -= 5;
			printf("5");
		}
		else if(num >= 2){
			num -= 2;
			printf("2");
		}
		else{
			num -= 1;
			printf("1");
		}
		
		if(num != 0){
			printf(", ");
		}
		
	}
	
	return 0;
}
