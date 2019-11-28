#include <stdio.h>
#include <string.h>

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
#define WEST 'w'

char get_display_char(char c){
	switch(c){
		case FREE_PLACE:return DISP_FREE_PLACE;
		case WALL:return DISP_WALL;
		case STEP:return DISP_STEP;
		case START_POS:return DISP_START_POS;
	}
}

void display_laberinth(char laberinth[ROWS][COLUMNS]){
	for(int i=ROWS-1;i<=0;i--){
		for(int j=COLUMNS-1;j<=0;j--){
			printf("")
		}
	}
}

void walk(int *x,int *y,char c){
	switch(c){
		case NORTH:{
			y++;
		}break;
		case SOUTH:{
			y--;
		}break;
		case EAST:{
			x++;
		}break;
		case WEST:{
			x--;
		}break;
	}
}

int get_directions(char directions[]){
	scanf("%s",directions);
	for(int i=0;i<strlen(directions);i++){
		if(directions[i]!=NORTH&&directions[i]!=SOUTH&&directions[i]!=EAST&&directions[i]!=WEST){
			return 0;
		}
	}
	return 1;
}
int check_laberinth_row(char row[COLUMNS]){
	if(strlen(row)!=COLUMNS ){
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
gets the laberinth from stdin and returns 0 if the format isn't correct and 1 if is correct
*/
int get_laberinth(char laberinth[ROWS][COLUMNS]){
	for(int i=0;i<ROWS;i++){
		scanf("%s",laberinth[i]);
		if(!check_laberinth_row(laberinth[i])){
			return 0;
		}
	}
	return 1;
}

int get_start_pos(int *x,int *y){
	scanf("%i",x);
}

void draw_path(char laberinth[ROWS][COLUMNS])
int main () {
	char laberinth[ROWS][COLUMNS+]={""};

}