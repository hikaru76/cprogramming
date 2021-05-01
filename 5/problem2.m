A = [2 -1 0 -1;-1 2 -1 0; 0 -1 2 -1; -1 0 -1 2];
syms x;
B=A-eye(4).*x;
solve(det(B)==0, x)
eig(A)