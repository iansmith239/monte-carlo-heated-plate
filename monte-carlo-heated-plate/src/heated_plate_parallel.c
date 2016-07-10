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
#include <stdlib.h>
#include <math.h>

typedef enum {
	false, true
} bool;

typedef struct {
	int x;
	int y;
} point;

int plate_x;
int plate_y;

point get_rndm_ngbr(point p, int r) {
	//randomly select a number 1 to 4
	//0=T,1=L,2=R,3=B

	int x_add = 0;
	int y_add = 0;

	point pn = { p.x, p.y };

	//return the randomly selected point
	if (r == 0) {
		y_add = 1;
	} else if (r == 1) {
		x_add = -1;
	} else if (r == 2) {
		x_add = 1;
	} else {
		y_add = -1;
	}

	pn.x = pn.x + x_add;
	pn.y = pn.y + y_add;

	return pn;
}

bool is_edge(point p) {
	if (p.x == 0 || p.y == 0 || p.x == plate_x - 1 || p.y == plate_y - 1) {
		//printf(">>>>>>>>>> Found edge point [%d,%d]\n", p.x, p.y);
		return true;
	}
	return false;
}

int main(int argc, char *argv[]) {

	plate_x = 10;
	plate_y = 10;
	int num_edge_searches = 10;

	//1. Get 4 temps from user
	int temp_top = atoi(argv[1]);
	int temp_left = atoi(argv[2]);
	int temp_right = atoi(argv[3]);
	int temp_bottom = atoi(argv[4]);

	printf("Temps are [T=%d,L=%d,R=%d,B=%d]\n", temp_top, temp_left, temp_right,
			temp_bottom);

	//2. Create and initialize the array
	double temps[plate_x][plate_y];

	int count;
#pragma omp parallel shared ( temps ) private ( count )
	{
#pragma omp for
		//Initialize top
		for (count = 0; count < plate_x; count++) {
			//t1 = (0 to 499,499)
			temps[count][plate_y - 1] = temp_top;
		}

#pragma omp for
		//Initialize left
		for (count = 0; count < plate_y; count++) {
			//t2 = (0,0 to 499)
			temps[0][count] = temp_left;
		}

#pragma omp for
		//Initialize bottom
		for (count = 0; count < plate_x; count++) {
			//t3 = (0 to 499,0)
			temps[count][0] = temp_bottom;
		}

#pragma omp for
		//Initialize right
		for (count = 0; count < plate_y; count++) {
			//t4 = (499, 0 to 499)
			temps[plate_x - 1][count] = temp_right;
		}
	}

	//3. Iterate through the array in sequence starting from the bottom corner
	int x;
	int y;

# pragma omp parallel shared ( temps ) private ( x, y )
	{
		unsigned int myseed = omp_get_thread_num();
# pragma omp for
		for (x = 1; x < plate_x - 1; x++) {
			printf("Started y values for x=%d\n",x);
			for (y = 1; y < plate_y - 1; y++) {
				//Get info for point
				point p = { x, y };

				//printf("Starting at point [%d,%d]\n", p.x, p.y);

				//Search for the edge many times
				double p_edge_temp_sum = 0.0;
				double pn_temp = 0.0;
				int i = 0;
				for (i = 0; i < num_edge_searches; i++) {
					//Get the next point
					int r1 = rand_r(&myseed) % 4;

					point pn = get_rndm_ngbr(p, r1);
					while (is_edge(pn) == false) {
						int r2 = rand_r(&myseed) % 4;

						pn = get_rndm_ngbr(pn, r2);
						//printf("Got next point [%d,%d]\n", pn.x,pn.y);
					}

					pn_temp = *(*(temps + pn.x) + pn.y);
					p_edge_temp_sum = p_edge_temp_sum + pn_temp;
				}
				temps[x][y] = p_edge_temp_sum / (i + 1);
			}

		}
	}

	//4.Output the temp at some random points
	int z;
	double rand_point_temp = 0.0;
	# pragma omp parallel shared ( rand_point_temp, temps ) private ( z )
		{
			unsigned int myseed = omp_get_thread_num();
			# pragma omp for
				for (z = 0; z < 10; z++) {

					int rand_x = rand_r(&myseed) % plate_x;
					int rand_y = rand_r(&myseed) % plate_y;

					rand_point_temp = *(*(temps + rand_x) + rand_y);

					printf("Temperature for point [%d,%d] is %f\n", rand_x, rand_y,
							rand_point_temp);
				}
		}

	return 0;
}

