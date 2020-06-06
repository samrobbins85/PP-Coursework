#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include"gol.h"

int main(int argc, char *argv[]){
	struct universe v;
	FILE *input;
	FILE *output;
	int num_generations;
	bool stats;
	bool torus;
	input=stdin;
	output=stdout;
	num_generations=5;
	stats=false;
	torus=false;
	bool i_set=false;
	bool o_set=false;
	bool g_set=false;
	int i;
	for (i=0;i<argc;i++){
		switch(argv[i][0]){
			case '-':
				if (strlen(argv[i])==2){
				switch (argv[i][1]){
					case 'i':
						if (i_set){
							fprintf(stderr, "ERROR: The input flag has been given multiple times\n");
							exit(1);
						}
						i_set=true;
						input = fopen(argv[i+1], "r");
						if(!input){
							fprintf(stderr, "ERROR: Can't open provided file name\n");
							exit(1);
						}
						break;
					case 'o':
						if (o_set){
							fprintf(stderr, "ERROR: The output flag has been given multiple times\n");
							exit(1);
						}
						o_set=true;
						output = fopen(argv[i+1],"w+");
						if(!output){
							fprintf(stderr, "ERROR: Invalid output file\n");
							exit(1);
						}
						break;
					case 'g':
						if ((int) strtod(argv[i+1],NULL)==num_generations){
							break;
						}
						if (g_set){
							fprintf(stderr, "ERROR: The generations flag has been given multiple times\n");
							exit(1);
						}
						g_set=true;
						num_generations=(int) strtod(argv[i+1],NULL);
						if (num_generations<=0){
							fprintf(stderr, "ERROR: Invalid or unprovided number of generations\n");
							exit(1);
						}
						break;
					case 's':
						stats=true;
						break;
					case 't':
						torus=true;
						break;
					default:
						fprintf(stderr, "ERROR: Invalid flag\n");
						exit(1);

				}}
			break;
		}
	}

	read_in_file(input,&v);
	for (i=0;i< num_generations;i++){
		if(torus){
			evolve(&v,will_be_alive_torus);
		}else{
			evolve(&v,will_be_alive);
		}
	}
	write_out_file(output,&v);
	if(stats){
		print_statistics(&v);
	}
	return 0;
}
