/*
 ============================================================================
 Name        : heated_plate_serial.c
 Author      :
 Version     :
 Copyright   :
 Description : Serial Version of Heated Plate
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef struct {
    int x;
    int y;
} point;

int main (int argc, char *argv[]) {

	int plate_x = 500;
	int plate_y = 500;
	int num_edge_searches = 100;

	//1. Get 4 temps from user
	int temp_top = atoi(argv[1]);
	int temp_left = atoi(argv[2]);
	int temp_right = atoi(argv[3]);
	int temp_bottom = atoi(argv[4]);

	printf("Temps are [T=%d,L=%d,R=%d,B=%d]",temp_top,temp_left,temp_right,temp_bottom);

	//2. Create and initialize the array
	double temps[plate_x][plate_y];

	//Initialize top

	//Initialize left

	//Initialize bottom

	//Initialize right

	//3. Iterate through the array in sequence starting from the bottom corner
	for (int x = 0; x < plate_x; x++) {
		for (int y = 0; y < plate_y; y++) {
			//Get info for point
			point p = {x,y};

			//Search for the edge many times
			double p_edge_temp_sum = 0d;
			int i = 0;
			for (i = 0; i < num_edge_searches; i++) {
				//Get the next point
				point pn = get_rndm_ngbr(p);
				while (!is_edge(pn)) {
					pn = get_rndm_ngbr(pn);
				}
				p_edge_temp_sum += temps[pn.x,pn.y]
			}

			temps[x][y] = p_edge_temp_sum / (i+1);
		}
	}
}

point get_rndm_ngbr(point p) {
	//randomly select a number 1 to 4
	//1=T,2=L,3=R,4=B

}

bool is_edge(point p) {
	return false;
}

