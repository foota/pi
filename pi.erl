-module(pi).
-export([pi/0]).

pi()->N=e(10,10000),(a(5,N)*4-a(239,N))*4.
e(B,N)->e(B,N,1).
e(_,0,R)->R;
e(B,N,R)->e(B,N-1,R*B).

a(X,N)->a(X,N div X,N div X,N,1,1).
a(_,A,_,0,_,_)->A;
a(M,A,B,C,S,K)->B_=B div(M*M),C_=B_ div(K+2),S_=-S,A_=A+C_*S_,a(M,A_,B_,C_,S_,K+2).
