#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_solver.h"

int main ( int argc, char **argv )
{
	number_type type = REAL_NUMBER;
	double A[9] = {1, 2, 3, 0, 4, 5, 0, 0, 6}; // column-major in Fortran, row based is [1; 2 4; 3 5 6]
	double b[3] = {3, 2, 1}; 
	double b_buf[3] = {3, 2, 1}; 
	int n = 3;

	printf( "A=\n" );
	dense_print_matrix( n, n, A, type );

	printf( "\nb=\n" );
	dense_print_vector( n, b, type );

	dense_triangular_solve( n, A, b, TRIG_LOWER, TRANS_NONE, type );
	printf( "\nx=\n" );
	dense_print_vector( n, b, type );

	memcpy( b, b_buf, sizeof(double) * n );
	dense_triangular_solve( n, A, b, TRIG_UPPER, TRANS_NONE, type );
	printf( "\nx=\n" );
	dense_print_vector( n, b, type );

	memcpy( b, b_buf, sizeof(double) * n );
	dense_triangular_solve( n, A, b, TRIG_LOWER_UNIT, TRANS_NONE, type );
	printf( "\nx=\n" );
	dense_print_vector( n, b, type );

	return EXIT_SUCCESS;
}


