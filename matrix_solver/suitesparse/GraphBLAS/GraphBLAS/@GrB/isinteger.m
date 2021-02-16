function s = isinteger (G)
%ISINTEGER true for integer matrices.
% isinteger (G) is true if the matrix G has an integer type
% (int8, int16, int32, int64, uint8, uint16, uint32, or uint64).
%
% See also GrB/isnumeric, GrB/isfloat, GrB/isreal, GrB/islogical,
% GrB.type, GrB/isa, GrB.

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights
% Reserved. http://suitesparse.com.  See GraphBLAS/Doc/License.txt.

G = G.opaque ;
s = contains (gbtype (G), 'int') ;

