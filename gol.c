//
// Created by sam on 09/02/2020.
//
#define  _GNU_SOURCE
#include<stdio.h>
#include"gol.h"
#include<stdlib.h>
#include <string.h>


void read_in_file (FILE *infile, struct universe *u) {
	if (infile==NULL){
		fprintf(stderr, "ERROR: Input file is Null\n");
		exit(1);
	}
	u->average_alive=0;
	u->generations=0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    u->rows = 0;
	int j;
	 u->arr = (char **)malloc(1 * sizeof(char *));
	while ((read = getline(&line, &len, infile)) != -1) {
		if (read!=u->columns && u->columns!=0){
			fprintf(stderr, "ERROR: Not all lines the same length\n");
			exit(1);
		}
		u->columns=(int) read;
		if (u->rows==0){
			u->arr[0] = (char *)malloc(u->columns * sizeof(char));
		}
		for (j = 0; j < ((int) read)-1; j++){
			if (!(line[j]=='.'|| line[j]=='*')){
				fprintf(stderr, "ERROR: Invalid character\n");
				exit(1);
			}

			u->arr[u->rows][j] = line[j];}
	u->rows++;
	char **tmp = (char **) realloc(u->arr, 2*sizeof(char *)*((int) u->rows));
	u->arr=tmp;
	u->arr[u->rows] = (char *)malloc(u->columns * sizeof(char));
	}
	fclose(infile);
	u->columns--;
}

void write_out_file(FILE *outfile, struct universe *u){
	if (u->rows==0 || u->columns==0){
		fprintf(stderr, "ERROR: The universe has not been defined\n");
		exit(1);
	}
	int i,j=0;
	for (i = 0; i <  u->rows; i++){
		for (j = 0; j < u->columns; j++){
			fprintf(outfile,"%c",u->arr[i][j]);}
		fprintf(outfile,"\n");
	}
}

int is_alive(struct universe *u, int column, int row){
	if(column>u->columns || row>u->rows){
		fprintf(stderr, "ERROR: Index out out range\n");
		exit(1);
	}
	char cell=u->arr[row][column];
	if (cell=='.'){
		return 0;
	}else{
		return 1;
	}
}


int will_be_alive(struct universe *u, int column, int row){
	if(column>u->columns || row>u->rows){
		fprintf(stderr, "ERROR: Index out out range\n");
		exit(1);
	}
	int alive=is_alive(u,column,row);
	int i,j;
	int total_alive=-alive;
	for (i = row-1; i <=  row+1; i++){
		for (j = column-1; j <= column+1; j++){
			if ((i>=u->rows || i<0) || (j>=u->columns || j<0)){
			} else{
			total_alive+=is_alive(u,j,i);}
		}
	}
	if (alive && ((total_alive==2) || (total_alive==3)) ){
		return 1;
	}
	if (!alive && (total_alive==3)){
		return 1;
	}
	return 0;
}


int will_be_alive_torus(struct universe *u, int column, int row){
	if(column>u->columns || row>u->rows){
		fprintf(stderr, "ERROR: Index out out range\n");
		exit(1);
	}
	int alive=is_alive(u,column,row);
	int i,j;
	int total_alive=-alive;
	for (i = row-1; i <= row+1; i++) {
		for (j = column - 1; j <= column + 1; j++) {
			total_alive += is_alive(u, j, ((i % u->rows) + u->rows) % u->rows);
		}
	}
	if (alive && ((total_alive==2) || (total_alive==3)) ){
		return 1;
	}
	if (!alive && (total_alive==3)){
		return 1;
	}
	return 0;
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){
	if (u->rows==0 || u->columns==0){
		fprintf(stderr, "ERROR: The universe has not been defined\n");
		exit(1);
	}
	float currently_alive=0;
	int i=0;
	char **newarr = (char **)malloc(u->rows * sizeof(char *));
	for (i=0; i<u->rows; i++)
		newarr[i] = (char *)malloc(u->columns * sizeof(char));
	int j=0;
	for (i = 0; i <  u->rows; i++){
		for (j = 0; j < u->columns; j++){
		int next_state=rule(u,j,i);
		if (next_state==1){
			newarr[i][j]= '*';
			currently_alive++;
		} else{
			newarr[i][j]='.';
		}
		}
	}
	u->currently_alive=currently_alive/( (float) u->rows* (float)u->columns);
	u->average_alive=((u->average_alive* (float) u->generations)+u->currently_alive)/((float) u->generations+1);
	u->generations++;
	memcpy(&u->arr,&newarr, sizeof newarr);
}


void print_statistics(struct universe *u){
	if (u->rows==0 || u->columns==0){
		fprintf(stderr, "ERROR: There has not been an input file\n");
		exit(1);
	}
	printf("%0.3f%% of cells currently alive\n",u->currently_alive);
	printf("%0.3f%% of cells alive on average\n",u->average_alive);
}




