#include <stdio.h>

#define ROW 5
#define COUL 5
#define DIAGONAL 5

typedef enum state {
	start = 257,
	impossible = 258,
	success = 259,
	go_to_next_grid = 260,
	go_to_upper = 261,
	go_to_lower = 262
}State;


int row_full_check(int [ROW][COUL+1]);
int check_last_line_last_grid(int [ROW][COUL+1]);
int get_last_line(int [ROW][COUL+1]);
int get_last_grid(int [ROW][COUL+1], int);
int check_last_grid(int [ROW][COUL+1], int);
int check_diagonal_condition(int [ROW][COUL+1], int, int);
int check_coulum_condition(int [ROW][COUL+1], int, int);
int check_row_condition(int [ROW][COUL+1]);
int check_each_row_condition(int [ROW][COUL+1], int, int);
int call_check_each_row_condition(int a[ROW][COUL+1]);
void move_right(int [ROW][COUL+1]);
void move_upper(int [ROW][COUL+1]);
void move_lower(int [ROW][COUL+1]);
void show_grid(int [ROW][COUL+1]);
State test_grid(int [ROW][COUL+1], int);
void main_test(void);
void beta_test(void);

int main(void){
	//main_test();
	beta_test();
	return 0;
}

void beta_test(void){
	int i;
	int matter = -1;
	//int grid[ROW][COUL+1] = {{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	int grid[ROW][COUL+1] = 
		{{0,0,0,0,0}
		,{0,0,0,0,0}
		,{0,0,0,0,0}
		,{0,0,0,0,0}
		,{0,0,0,0,0}};
	show_grid(grid);
	State state; 
	
	for(; ;){
		i++;
		state = test_grid(grid, matter);
		printf(" %d , state : %d \n",i,(int)state);
		if(state == start){
			grid[0][0] = 1; 
			matter = 0; //start
		}else if(state == impossible){
			printf(" impossible \n");	//impossible
			break;
		}else if(state == success){
			printf(" success \n");		//success
			break;
		}
		switch(state){
			case go_to_next_grid :
				move_right(grid); 
				matter = 0;
				show_grid(grid);
				break;
			case go_to_upper :
				move_upper(grid); 
				matter = 1;
				show_grid(grid);
				break;
			case go_to_lower :
				move_lower(grid); 
				matter = 0;
				show_grid(grid);
				break;
			default:
				break;
		}
	}
}


State test_grid(int a[ROW][COUL+1], int matter){
	int row_full_check_result = row_full_check(a);
	int condition_check_result = call_check_each_row_condition(a);
	int last_line_last_grid_result = check_last_line_last_grid(a);
	switch(row_full_check_result){
		case 0 :
			if(matter != 1){
				return start;// Start
			}else{
				return impossible;// Impossible
			}
			break;
		case COUL : 
			if(condition_check_result == 1){
				return success;// Success
			}
			else{
				if(last_line_last_grid_result == 1){
					return go_to_upper;// matter exist. upper.
				}else{
					return go_to_next_grid; // next grid
				}
			}
			break;
		default : 
			switch(matter){
				case 1 :
					if(last_line_last_grid_result == 1){
						return go_to_upper; //matter exist. upper.
					}else{
						return go_to_next_grid; //next grid
					}
					break;
				default : 
					if(condition_check_result == 1){
						return go_to_lower; //lower line
					}else{
						if(last_line_last_grid_result == 1){
							return go_to_upper; //matter exist. upper
						}else{
							return go_to_next_grid; //next grid
						}
					}
					break;
			}
			break;
	}
}

void main_test(void){	
	int grid[ROW][COUL+1] = {{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	
	int queen_row_number = row_full_check(grid);
	if (queen_row_number == ROW){
		printf(" full row \n");
	} else if(queen_row_number == 0){
		printf(" empty row \n");
	} else {
		printf(" exist and not exist \n");
	}
	
	int last_row = get_last_line(grid);
	int last_grid = check_last_grid(grid, last_row);
	if (last_grid == 1){
		printf(" last grid \n");
	} else {
		printf(" not last grid \n");
	};
	
	int grid_check_result = call_check_each_row_condition(grid);
	if(grid_check_result == 1){
		printf(" grid check result : OK \n");
	} else {
		printf(" grid check result : Not Satisfied \n");
	}
	
	show_grid(grid);
	
	move_right(grid);
	show_grid(grid);
	printf("\n");
	move_upper(grid);
	show_grid(grid);
	printf("\n");
	move_lower(grid);
	show_grid(grid);
}

int check_diagonal_condition(int a[ROW][COUL+1], int row, int coulum){
	int i, counter = 0;
	int s = row - coulum;
	if(s == 0){
		for(i = 0; i < DIAGONAL; i++){
			if(a[i][i] == 1){
				counter++;
			}
		}
	} else if(s > 0){
		for(i = s; i < DIAGONAL; i++){
			if(a[i][i-s] == 1){
				counter++;
			}
		}
	} else if(s < 0){
		for(i = s*(-1); i < DIAGONAL; i++){
			if(a[i+s][i] == 1){
				counter++;
			}
		}
	}
	if(counter > 1){
		return 0;
	} else {
		return 1;
	}
}

int check_coulum_condition(int a[ROW][COUL+1], int row, int coulum){
	int i, counter = 0;
	for(i = 0; i < ROW; i++){
		if(a[i][coulum] == 1){
			counter++;
		}
	}
	if(counter > 1){
		return 0;
	} else {
		return 1;
	}
}

int check_each_row_condition(int a[ROW][COUL+1], int row, int coulum){
	int coulum_check_result = check_coulum_condition(a, row, coulum);
	int diagonal_check_result = check_diagonal_condition(a, row, coulum);
	if(coulum_check_result == 1 && diagonal_check_result == 1){
		return 1;
	} else {
		return 0;
	}
}


int call_check_each_row_condition(int a[ROW][COUL+1]){
	int i, j, check_result = 0;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COUL; j++){
			if(a[i][j] == 1){
				if(check_each_row_condition(a,i,j) != 1){
					check_result++;
				}
			}
		}
	}
	if(check_result == 0){
		return 1;
	} else {
		return 0;
	}
}

int check_last_grid(int a[ROW][COUL+1], int n){
	if (1 == a[n][COUL-1]){
		return 1;
	} else {
		return 0;
	}
}

int get_last_grid(int a[ROW][COUL+1], int n){
	int i;
	for(i=0; i < ROW; i++){
		if(1 == a[n][i]){
			return i;
		}
	}
	return -1;
}

int get_last_line(int a[ROW][COUL+1]){
	int i, j, num = -1;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COUL; j++){
			if(a[i][j] == 1){
				num++;
			}
		}
	}
	return num;
}

int check_last_line_last_grid(int a[ROW][COUL+1]){
	int line_number = get_last_line(a);
	if(line_number == -1){
		return 0;
	}
	int last_grid_number = get_last_grid(a, line_number);
	if(last_grid_number != COUL-1){
		return 0;
	}
	return 1;
}

int row_full_check(int a[ROW][COUL+1]){
	int i, j, sum = 0;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COUL; j++){
			if (a[i][j] == 1){
				sum += 1;
			}
		}
	}
	return sum;
}


void move_right(int a[ROW][COUL+1]){
	int line_number = get_last_line(a);	
	int grid_number = get_last_grid(a, line_number);
	a[line_number][grid_number] = 0;
	a[line_number][grid_number+1] = 1;
}

void move_upper(int a[ROW][COUL+1]){
	int i;
	int line_number = get_last_line(a);
	for(i = 0; i < COUL; i++){
		a[line_number][i] = 0;
	}
}

void move_lower(int a[ROW][COUL+1]){
	int line_number = get_last_line(a);
	a[line_number+1][0] = 1;
}

void show_grid(int a[ROW][COUL+1]){
	int i, j;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COUL; j++){
			printf(" %d ",a[i][j]);
		}
		printf("\n");
	}
}






