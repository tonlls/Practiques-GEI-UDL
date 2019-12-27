#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR_STATE 0
#define GET_LABYRINTH_ERR "error getting labyrinth"
#define GET_START_POS_ERR "error getting start position"
#define GET_DIRECTIONS_ERR "error getting direcctions"
#define DRAW_PATH_ERR "error drawing the path"

#define FREE_PLACE 'O'
#define DISP_FREE_PLACE ' '

#define WALL 'X'
#define DISP_WALL 'X'

#define STEP 'i'
#define DISP_STEP 'i'

#define START_POS 'I'
#define DISP_START_POS 'I'

#define ROWS 10
#define COLUMNS 20

#define NORTH 'n'
#define SOUTH 's'
#define EAST 'e'
#define WEST 'o'

////////
void check_error(int,char[]);
int check_labyrinth_row(char[COLUMNS+1]);
void display_labyrinth(char[ROWS][COLUMNS+1]);
int draw_path(char[ROWS][COLUMNS+1],char[],int,int);
int get_directions(char[]);
char get_display_char(char);
int get_labyrinth(char[ROWS][COLUMNS+1]);
int get_start_pos(int*,int*);
int has_escaped(int,int);
int is_wall(char);
void walk(int*,int*,char);
////////

/*
gets the char to display on the display_labyrinth function
*/
char get_display_char(char c){
	switch(c){
		case FREE_PLACE:return DISP_FREE_PLACE;
		case WALL:return DISP_WALL;
		case STEP:return DISP_STEP;
		case START_POS:return DISP_START_POS;
	}
	return ' ';
}


/*
prints the labyrinth to stdout
*/
void display_labyrinth(char labyrinth[ROWS][COLUMNS+1]){
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLUMNS;j++){
			printf("%c",get_display_char(labyrinth[i][j]));
		}
		printf("\n");
	}
}


/*
modifies x and y depending on the direction you want to walk
*/
void walk(int *x,int *y,char c){
	switch(c){
		case NORTH:{
			(*y)--;
		}break;
		case SOUTH:{
			(*y)++;
		}break;
		case EAST:{
			(*x)++;
		}break;
		case WEST:{
			(*x)--;
		}break;
	}
}


/*
gets the directions from stdin and checks if they are correct
returns 1 if direcctions are correct and 0 if error
*/
int get_directions(char directions[]){
	printf("Input the directions you want to follow(%c North, %c South, %c East, %c West):\n",NORTH,SOUTH,EAST,WEST);
	scanf("%s",directions);
	for(int i=0;i<(int)strlen(directions);i++){
		if(directions[i]!=NORTH&&directions[i]!=SOUTH&&directions[i]!=EAST&&directions[i]!=WEST){
			return 0;
		}
	}
	return 1;
}


/*
checs the labyrinth row format
returns 1 if correct and 0 if incorrect
*/
int check_labyrinth_row(char row[COLUMNS+1]){
	if(strlen(row)!=COLUMNS){
		return 0;
	}
	for(int i=0;i<COLUMNS;i++){
		if(row[i]!=FREE_PLACE && row[i]!=WALL){
			return 0;
		}
	}
	return 1;
}


/*
gets the labyrinth from stdin
returns 0 if the format isn't correct and 1 if is correct
*/
int get_labyrinth(char labyrinth[ROWS][COLUMNS+1]){
	printf("Input the labyrinth form %i rows and %i columns(%c for a free space and %c for wall):\n",ROWS,COLUMNS,FREE_PLACE,WALL);
	for(int i=0;i<ROWS;i++){
		scanf("%s[^\n]",labyrinth[i]);
		if(!check_labyrinth_row(labyrinth[i])){
			return 0;
		}
	}
	return 1;
}


/*
gets x and y from stdin and checks if correct 
returns 1 if correct and 0 if incorrect
*/
int get_start_pos(int *x,int *y){
	printf("Input the position to start:\n");
	printf("Row: ");
	scanf("%i",y);
	printf("\nColumn: ");
	scanf("%i",x);
	if(*x>=COLUMNS || *x<0 || *y<0 || *y>=ROWS ){
		return 0;
	}
	return 1;
}


/*
checks if user have escaped from labyrinth 
returns 1 if true and 0 if false
*/
int has_escaped(int x,int y){
	if(x==0||y==0||x==COLUMNS-1||y==ROWS-1){
		return 1;
	}
	return 0;
}


/*
checks if the char is wall char
returns 1 if true and 0 if false
*/
int is_wall(char c){
	if(c==WALL){
		return 1;
	}
	return 0;
}


/*
follows the directions and sets a step on every step you do
returns 0 if error and 1 if everithing is correct
*/
int draw_path(char labyrinth[ROWS][COLUMNS+1],char directions[],int x,int y){
	char c,wall=0;
	if(!is_wall(labyrinth[y][x])){
		return 0;
	}
	labyrinth[y][x]=START_POS;
	for(int i=0;i<(int)strlen(directions)&&!has_escaped(x,y)&&!wall;i++){
		c=directions[i];
		walk(&x,&y,c);
		if(is_wall(labyrinth[y][x])){
			wall=1;
		}
		else{
			labyrinth[y][x]=STEP;
		}
	}
	return 1;
}


/*
checks if state is on ERROR_STATE and if it is prints the error message and ends the program
*/
void check_error(int state,char error_str[]){
	if(state==ERROR_STATE){
		printf("%s\n\n",error_str);
		exit(EXIT_FAILURE);
	}
}


int main () {
	char labyrinth[ROWS][COLUMNS+1];
	char directions[COLUMNS*ROWS+1]="";
	int x,y;

	check_error(get_labyrinth(labyrinth),(char*)GET_LABYRINTH_ERR);
	check_error(get_start_pos(&x,&y),(char*)GET_START_POS_ERR);
	check_error(get_directions(directions),(char*)GET_DIRECTIONS_ERR);

	check_error(draw_path(labyrinth,directions,x,y),(char*)DRAW_PATH_ERR);
	display_labyrinth(labyrinth);
	if(has_escaped(x,y)){
		printf("You have escaped the labyrinth!!!\n");
	}
	else{
		printf("You are lost in the labyrinth, you will die among terrible suffering!!!\n");
	}
}
