//------------------------------------------------------------------------------
// gb_round_binop: get a rounding operator
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

#include "gb_matlab.h"

GrB_BinaryOp gb_round_binop (GrB_Type type)
{ 
    if (type == GrB_FP32) return (GxB_ROUND_FP32) ;
    if (type == GrB_FP64) return (GxB_ROUND_FP64) ;
    if (type == GxB_FC32) return (GxB_ROUND_FC32) ;
    if (type == GxB_FC64) return (GxB_ROUND_FC64) ;
    return (NULL) ;
}

