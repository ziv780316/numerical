#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "matrix_solver.h"

int main ( int argc, char **argv )
{
	g_matrix_print_format = MATRIX_PRINT_FORMAT_MATLAB;

	sparse_csc_t A;
	A.nz = 9;
	A.m = 4;
	A.n = 3;
	A.Ap = (sparse_int *) calloc ( A.n + 1, sizeof(sparse_int) );
	A.Ai = (sparse_int *) calloc ( A.nz, sizeof(sparse_int) );
	A.Ax = (sparse_float *) calloc ( A.nz, sizeof(sparse_float) );

	A.Ap[0] = 0;
	A.Ai[0] = 0;
	A.Ax[0] = 4.1;
	A.Ai[1] = 1;
	A.Ax[1] = 3.2;
	A.Ai[2] = 2;
	A.Ax[2] = 2.3;
	A.Ai[3] = 3;
	A.Ax[3] = 1.4;
	A.Ap[1] = 4;

	A.Ai[4] = 1;
	A.Ax[4] = 0.2;
	A.Ai[5] = 3;
	A.Ax[5] = 0.1;
	A.Ap[2] = 6;

	A.Ai[6] = 0;
	A.Ax[6] = -1;
	A.Ai[7] = 2;
	A.Ax[7] = -2;
	A.Ai[8] = 3;
	A.Ax[8] = -3;
	A.Ap[3] = 9;

	printf( "A = " );
	sparse_print_csc_full_matrix ( &A );

	sparse_float x[3] = { 1, 2, 3 };
	printf( "x = " );
	dense_print_vector ( 3, x, REAL_NUMBER );

	sparse_float b[4];
	sparse_matrix_multiply_vector ( &A, x, b );
	printf( "b = " );
	dense_print_vector ( 4, b, REAL_NUMBER );

	return EXIT_SUCCESS;
}

