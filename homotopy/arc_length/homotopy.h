#ifndef HOMOTOPY_H
#define HOMOTOPY_H

#include "newton.h"

typedef enum {
	HOMOTOPY_ARC_LENGTH_CONSTRAINT_NONE,
	HOMOTOPY_ARC_LENGTH_CONSTRAINT_TANGENT,
	HOMOTOPY_ARC_LENGTH_CONSTRAINT_CIRCLE,
} homotopy_arc_length_constrain_type;

typedef enum {
	HOMOTOPY_ARC_LENGTH_BACKTRACE_HANDLE_NONE,
	HOMOTOPY_ARC_LENGTH_BACKTRACE_HANDLE_DIFFERENCE,
	HOMOTOPY_ARC_LENGTH_BACKTRACE_HANDLE_CROSS_PRODUCT,
	HOMOTOPY_ARC_LENGTH_BACKTRACE_HANDLE_SUB_CROSS_PRODUCT,
	HOMOTOPY_ARC_LENGTH_BACKTRACE_HANDLE_DIAG_CROSS_PRODUCT,
} homotopy_arc_length_backtrace_handle_type;

typedef enum {
	HOMOTOPY_EXTRAPOLATE_NONE,
	HOMOTOPY_EXTRAPOLATE_DIFFERENCE,
	HOMOTOPY_EXTRAPOLATE_DIFFERENTIAL,
} homotopy_extrapolate_type;

typedef enum {
	HOMOTOPY_DF_DP_EXACT,
	HOMOTOPY_DF_DP_FORWARD,
	HOMOTOPY_DF_DP_CENTRAL
} homotopy_df_dp_type;

typedef struct 
{
	int n_step;
	int n_success;
	int n_fail;
	int n_limit_point;

	int n_iter;
	int n_mat_factor;
	int n_mat_solve;
	int n_mat_solve_sensitivity;
	int n_f_load;
	int n_f_load_sensitivity;
	int n_df_dp_load;
	int n_jac_load;
} homotopy_performance_stat_t;

typedef struct
{
	homotopy_arc_length_constrain_type arc_length_constrain_type;
	homotopy_arc_length_backtrace_handle_type arc_length_backtrace_type;;
	homotopy_extrapolate_type extrapolate_type;
	homotopy_df_dp_type df_dp_type;

	double lamda_start;
	double lamda_stop;
	double arc_length;

	int maxsteps;

	bool debug;

	homotopy_performance_stat_t hom_stat;

} homotopy_param_t;

// perform BBD Newton-Raphson iterations 
bool arc_length_bbd_newton_solve ( 
		homotopy_param_t *homotopy_param,
		newton_param_t *newton_param,
		int *perm, // permuation for matrix ordering
		double *J, // jacobian
		double *pp,
		double *x0, // initial x
	        double *x_ans, // user give solution x*
		double p0, // initial p
		double *dx_dt, // use in arc length constrain
		double dp_dt, //  use in arc length constrain
		double *x_result, // final x
		double *p_result, // final x
		double *f_result, // final f(x)
		double *g_result, // final g(x)
		double *xc, // hyper circle central (xc,pc)
		double pc, // hyper circle central (xc,pc)
		double dt, // arc length
		void (load_f) (double *x, double*f),
		void (load_df_dp) (double *x, double*f),
		void (load_jacobian) (double *x, double*J),
		char *debug_file );


#endif

