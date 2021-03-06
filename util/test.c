#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "numerical_util.h"

double f1 ( double x ) 
{
	return x;
}

double f2 ( double x ) 
{
	return x * x;
}

double f3 ( double x ) 
{
	return x * x * x; 
}

int main ( int argc, char **argv )
{
	// test interpolation_lagrange
	{
		printf( "test interpolation_lagrange\n" );
		long n = 2;
		long ldy = 3;
		double x[3] = {3, 1, 0};
		double **y;
		double xp = 2;
		double yp[3];
		y = (double **) malloc ( ldy * sizeof(double *) );
		for ( int i = 0; i < ldy; ++i )
		{
			y[i] = (double *) malloc ( (n + 1) * sizeof(double) );
		}
		y[0][0] = f1(x[0]);
		y[0][1] = f1(x[1]);
		y[0][2] = f1(x[2]);
		y[1][0] = f2(x[0]);
		y[1][1] = f2(x[1]);
		y[1][2] = f2(x[2]);
		y[2][0] = f3(x[0]);
		y[2][1] = f3(x[1]);
		y[2][2] = f3(x[2]);

		FUNC_WITH_POSTFIX( interpolation_lagrange, POSTFIX ) ( 1, ldy, x, y, xp, yp );
		for ( long i = 0; i < ldy; ++i )
		{
			for ( long k = 0; k <= n; ++k )
			{
				printf( "y%ld[%ld] = %.15le\n", i, k, y[i][k] );
			}
			printf( "yp[%ld] = %.15le\n\n", i, yp[i] );
		}
	}

	// test divide_difference
	{
		printf( "\ntest divide_difference\n" );

		long n = 3;
		double x[4] = {0.4, 0.3, 0.2, 0.1};
		double y[4];
		double dd[4];
		for ( int i = 0; i <= n; ++i )
		{
			y[i] = cos( x[i] );
		}

		FUNC_WITH_POSTFIX( divide_difference, POSTFIX ) ( n, x, y, dd );

		for ( int i = 0; i <= n; ++i )
		{
			printf( "y%d = %.16le\n", i, y[i] );
		}
		for ( int i = 0; i <= n; ++i )
		{
			printf( "dd%d = %.16le\n", i, dd[i] );
		}
	}

	// test interpolation_newton
	{
		printf( "\ntest interpolation_newton\n" );

		long n = 3;
		int ldx = 2;
		double x[4] = {-0.04121, -0.00684, 0.02697, 0.05992};
		double y[4] = {5.4, 5.5, 5.6, 5.7};
		double xp[2] = {0, 0.02};
		double yp[2];
		double dd[4];

		FUNC_WITH_POSTFIX( divide_difference, POSTFIX ) ( n, x, y, dd );
		for ( int i = 0; i <= n; ++i )
		{
			printf( "dd%d = %.16le\n", i, dd[i] );
		}

		FUNC_WITH_POSTFIX( interpolation_newton, POSTFIX ) ( n, ldx, x, xp, yp, dd );
		for ( int i = 0; i < ldx; ++i )
		{
			printf( "yp%d = P%ld(%.16le) = %.16le\n", i, n, xp[i], yp[i] );
		}
	}

	return EXIT_SUCCESS;
}

