/*
Content: COMP20005 Assigment 2
Author: Ruoyi Wang
Student ID: 683436
Login Name: ruoyiw
Date: May 15 2016
*/

/* programming is fun! */
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100    /* maximum number of cells in row and column */
#define MAXCOST 10001  /* maximum cost that is larger than any possible cost */
#define MAXDIGIT 100   /* maximum number digits shown in cell is two */

/* type of the cell state */
#define WALL '#'
#define PASS '.'
#define REACHABLE '+'
#define NON_REACHABLE '-'

#define YES 1
#define NO 0

/* struct for representing each cell in the maze */
typedef struct {
	char type;
	int cost;
	int visited;
	int minpath;
} cell_t;

/* struct for recording a maze */
typedef struct {
	cell_t maze[MAXSIZE][MAXSIZE];
	int nrows;
	int ncolumns;
	int hassoln;
	int mincost;
	int mincol;
} maze_t;

/* function prototypes */
void print_stage_heading(int stage);
void read_maze(maze_t *M);
int min_cost(int cost1, int cost2);
void cal_min_cost(maze_t *M, int row, int col, int cost);
void fill_reachable(maze_t *M, int row, int col);
void assign_reachability(maze_t *M);
void check_min_path(maze_t *M,int row, int col);
void label_final_path(maze_t *M);
void print_stage_one(maze_t *M);
void print_stage_two(maze_t *M);
void print_stage_three(maze_t *M);
void print_stage_four(maze_t *M);

/* main program binds it all together */
int
main(int argc, char *argv[]) {
	        maze_t M;            /* the maze */

	        read_maze(&M);
	        print_stage_one(&M);
	        assign_reachability(&M);
	        print_stage_two(&M);
	        print_stage_three(&M);
	        if (M.hassoln) {
	                label_final_path(&M);
	                print_stage_four(&M);
	        } 
	        return 0;
}

/* print out a stage heading, with a prior blank line once the stage number
   goes plus one */
void 
print_stage_heading(int stage) {
	if (stage > 1) {
		/* separate the stages */
		printf("\n");
	}
	printf("Stage %d\n=======\n", stage);
	return;
}

/* read the input maze */
void
read_maze(maze_t *M) {
	int row = 0, col = 0;
	while ((M->maze[row][col].type = getchar()) != EOF) {
		if ((M->maze[row][col].type) == '\n') {	
			row += 1;
		    M->nrows = row;
		    col = 0;
		} else {
			M->maze[row][col].cost = MAXCOST;
			M->maze[row][col].visited = NO;
			col += 1;
			M->ncolumns = col;
		}
	}
}

/* generate the output format required for stage 1 */	
void
print_stage_one(maze_t *M) {
	int row, col;
	print_stage_heading(1);
	printf("maze has %d rows and %d columns\n", M->nrows, M->ncolumns);
	for (row = 0; row < M->nrows; row++) {
		for (col = 0; col < M->ncolumns; col++) {
			printf("%c%c", M->maze[row][col].type, M->maze[row][col].type);
		}
		printf("\n");
	}
}

/* compare two costs and return the minimum one */
int
min_cost(int cost1, int cost2) {
	if (cost1 > cost2) {
		return cost2;
	} else {
		return cost1;
	}
}

/* calculate the minimum cost from entry gap to the current cell */
void
cal_min_cost(maze_t *M, int row, int col, int cost) {
	if(row == 0) {
		M->maze[row][col].cost = 0;
	} else {
		cost = min_cost(cost, M->maze[row-1][col].cost + 1);
		if (row < M->nrows - 1) {
			cost = min_cost(cost, M->maze[row+1][col].cost + 1);
		}
		if (col > 0) {
			cost = min_cost(cost, M->maze[row][col-1].cost + 1);
		}
		if (col < M->ncolumns - 1) {
			cost = min_cost(cost, M->maze[row][col+1].cost + 1);
		}
        M->maze[row][col].cost = min_cost(cost, M->maze[row][col].cost);
    }
}

/* fill the reachable zones in maze */
void
fill_reachable(maze_t *M, int row, int col) {
	int cost = M->maze[row][col].cost;
	/* return if cell is outside maze */
    if (row < 0 || row >= M->nrows || col < 0 || col >= M->ncolumns) {
    	return;
    }
    /* return if cell is no-go */
    if (M->maze[row][col].type == WALL) {
    	return;
    }
    cal_min_cost(M, row, col, cost);  
    /* return if cost equals to the minimum value */
    if (cost == M->maze[row][col].cost) {
    	return;
    }
    M->maze[row][col].type = REACHABLE; /* mark the cell as reachable */
    fill_reachable(M, row + 1, col);    /* check down cell */
    fill_reachable(M, row - 1, col);    /* check up cell */
    fill_reachable(M, row, col - 1);    /* check left cell */
    fill_reachable(M, row, col + 1);    /* check right cell */
}

/* assign the reachability to all cells in maze */
void
assign_reachability(maze_t *M) {
	int row = 0, col;
	M->mincost = MAXCOST;
	for (col = 0; col < M->ncolumns; col++) {
		fill_reachable(M, row, col);
		/* determine the minimum cost and the leftmost column with minimum 
		   cost */
		if(M->mincost > M->maze[M->nrows-1][col].cost) {
			M->mincost = M->maze[M->nrows-1][col].cost;
			M->mincol = col;
		}
	}
	/* go over the matrix and mark the remaining passable cells as 
	   non-reachable */
	for (row = 0; row < M->nrows; row++) {
		for (col = 0; col < M->ncolumns; col++) {
			if (M->maze[row][col].type == PASS) {
				M->maze[row][col].type = NON_REACHABLE;
			}
		}
	}
}

/* generate the output format required for stage 2 */
void
print_stage_two(maze_t *M) {
	int row = M->nrows - 1, col;
	print_stage_heading(2);
	M->hassoln = NO;
	for (col = 0; col < M->ncolumns; col++) {
		if (M->maze[row][col].type == REACHABLE) {
			printf("maze has a solution\n");
			M->hassoln = YES;
			break;
		}	
	}	
	if (M->hassoln == NO) {
		printf("maze does not have a solution\n");
	}
	for (row = 0; row < M->nrows; row++) {
		for (col = 0; col < M->ncolumns; col++) {
			printf("%c%c", M->maze[row][col].type, M->maze[row][col].type);
		}
		printf("\n");
	}
}

/* generate the output format required for stage 3 */
void
print_stage_three(maze_t *M) {
	int row, col;
	print_stage_heading(3);
	if (M->hassoln) {
		printf("maze has a solution with cost %d\n", M->mincost);
	} else {
		printf("maze does not have a solution\n");
	}
	for (row = 0; row < M->nrows; row++) {
		for (col = 0; col < M->ncolumns; col++) {
			if (M->maze[row][col].type == REACHABLE &&
				M->maze[row][col].cost % 2 == 0) {
			    printf("%02d", M->maze[row][col].cost % MAXDIGIT);
			} else {
				printf("%c%c", M->maze[row][col].type, M->maze[row][col].type);
		    }
	    }
	    printf("\n");
	 }
}

/* check the path with minimum costs backwards */
void 
check_min_path(maze_t *M,int row, int col) {
	if (row < 0 || row >= M->nrows || col < 0 || col >= M->ncolumns) {
    	return;
    }
    if (M->maze[row][col].visited == YES) {
    	return;
    }
    
    M->maze[row][col].minpath = M->maze[row][col].cost;
    M->maze[row][col].visited = YES; /* mark the cell as visited status */
    if (M->maze[row][col].cost - M->maze[row-1][col].cost == 1) {
    	check_min_path(M, row - 1, col);
    } else if (M->maze[row][col].cost - M->maze[row+1][col].cost == 1) {
    	check_min_path(M, row + 1, col);
    } else if (M->maze[row][col].cost - M->maze[row][col-1].cost == 1) {
        check_min_path(M, row, col - 1);
    } else if (M->maze[row][col].cost - M->maze[row][col+1].cost == 1) {
    	check_min_path(M, row, col + 1);
    }
}
	 
/* label the final path from the exit gap with minimum cost  */
void
label_final_path(maze_t *M){
	int row = M->nrows - 1;
	int col = M->mincol;
	check_min_path(M, row, col);
}

/* generate the output format required for stage 4 */
void
print_stage_four(maze_t *M) {
	int row, col;
	print_stage_heading(4);
	printf("maze solution\n");
	
	for(row = 0; row < M->nrows; row++){
		for(col = 0; col < M->ncolumns; col++){
			if(M->maze[row][col].visited == YES && 
				M->maze[row][col].minpath % 2 == 0) {
			    printf("%02d", M->maze[row][col].minpath % MAXDIGIT);
			} else if (M->maze[row][col].visited == YES) {
				printf("%c%c", PASS, PASS);
			} else if (M->maze[row][col].type == REACHABLE) {
			    printf("  ");
			} else {
			    printf("%c%c", M->maze[row][col].type, M->maze[row][col].type);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}


	
	
	