#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_solver.h"

int main ( int argc, char **argv )
{
	double A[9] = {1, 2, 3, 4, 5, 6, 7, 8, 10}; 
	double x[3] = {2, 1, 3};
	int n = 3;

	printf( "A=\n" );
	dense_print_matrix( n, n, A );
	printf( "\nx=\n" );
	dense_print_vector( n, x );

	if ( !dense_factor_and_solve( n, A, x, false ) )
	{
		fprintf( stderr, "[Error] LU factorization fail\n" );
		abort();
	}

	printf( "\nLU=\n" );
	dense_print_matrix_LU( n, A );
	printf( "\nsolve result=\n" );
	dense_print_vector( n, x );

	return EXIT_SUCCESS;
}



