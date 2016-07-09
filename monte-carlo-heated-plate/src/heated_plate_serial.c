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

int main (int argc, char *argv[]) {

	//1. Get 4 temps from user
	int temp_top = atoi(argv[1]);
	int temp_left = atoi(argv[2]);
	int temp_right = atoi(argv[3]);
	int temp_bottom = atoi(argv[4]);

	printf("Temps are [T=%d,L=%d,R=%d,B=%d]",temp_top,temp_left,temp_right,temp_bottom);

	//2. Create and initialize the array
	double temps[500][500];

	//Initialize top
	for ( int count = 0; count < 500; count++ )
	{
		//t1 = (0 to 499,499)
		temps[count][499]=0.0;
	}

	//Initialize left
	for ( int count = 0; count < 500; count++ )
	{
		//t2 = (0,0 to 499)
		temps[0][count]=100.0;
	}

	//Initialize bottom
	for ( int count = 0; count < 500; count++ )
	{
		//t3 = (0 to 499,0)
		temps[count][0]=100.0;
	}

	//Initialize right
	for ( int count = 0; count < 500; count++ )
	{
		//t4 = (499, 0 to 499)
		temps[499][count]=100.0;
	}

	//3. Iterate through the array in sequence starting from the bottom corner
	//4. Move in random direction
}

bool is_edge(int x, int y) {
	return false;
}

