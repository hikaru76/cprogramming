syms x y(x) z(x);
z(x) = diff(y, x);
eqn = diff(z, x) == -z -5. * y;
S = dsolve(eqn);
cond = [y(0) == 2, z(0)==0];
S = dsolve(eqn, cond);
fplot(S, [0, 20])