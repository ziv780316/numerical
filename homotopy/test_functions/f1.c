#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int nf = 3;

// homotopy variable
double lamda = 1;

double x0[] = {
	0,
	0,
	0,
};

static double r = 1;
static double v = 1;
static double is = 1e-12;
static double vt = 0.0254;
static double vth = 0.3;
static double gshunt = 1e-3;

void load_f ( double *x, double *f )
{
	double v1 = x[0];
	double v2 = x[1];
	double i  = x[2];
	f[0] = (v1 - v2) / r + i;
	if ( v2 < vth )
	{
		f[1] = (v2 - v1) / r;
	}
	else
	{
		f[1] = (v2 - v1) / r + is * (exp((v2 - vth) / vt) - 1);
	}
	f[2] = v1 - v;

	// homotopy variable
	f[0] += (1 - lamda) * gshunt * v1;
	f[1] += (1 - lamda) * gshunt * v2;
}


void load_jacobian ( double *x, double *J )
{
	double v1 = x[0];
	double v2 = x[1];
	double i  = x[2];
	*(J + nf*0 + 0) = 1.0 / r; // (1,1)
	*(J + nf*0 + 1) = -1.0 / r; // (2,1)
	*(J + nf*0 + 2) = 1.0; // (3,1)
	*(J + nf*1 + 0) = -1.0 / r; // (1,2)
	if ( v2 < vth )
	{
		*(J + nf*1 + 1) = (1.0 / r); // (2,2)
	}
	else
	{
		*(J + nf*1 + 1) = (1.0 / r) + (is / vt) * exp((v2 - vth) / vt); // (2,2)
	}
	*(J + nf*1 + 2) = 0.0; // (3,2)
	*(J + nf*2 + 0) = 1.0; // (1,3)
	*(J + nf*2 + 1) = 0.0; // (2,3)
	*(J + nf*2 + 2) = 0.0; // (3,3)

	// homotopy variable
	*(J + nf*0 + 0) += (1 - lamda) * gshunt; // (1,1)
	*(J + nf*1 + 1) += (1 - lamda) * gshunt; // (2,2)
}

void load_df_dp ( double *x, double *df_dp, double p )
{
	double v1 = x[0];
	double v2 = x[1];
	double i  = x[2];

	df_dp[0] = -gshunt * v1;
	df_dp[1] = -gshunt * v2;
}
