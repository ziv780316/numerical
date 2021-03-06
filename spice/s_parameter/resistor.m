% lossy network
clear;
format long e;
r = 1;
Y = [1/r -1/r;-1/r 1/r];
Z0 = 1;
Zo = Z0 * eye(2);
Zo(1,1)=2;
Zo(2,2)=3;
[S,v,i] = y2s(Y, Zo, true);
fprintf( 'S=\n' );
disp( S );
fprintf( 'v=\n' );
disp( v );
fprintf( 'i=\n' );
disp( i );

is = abs(i(1,1));
vr = is*r;
Pr = is*vr*0.5;
fprintf( 'Pr = %.10e\n', Pr );

