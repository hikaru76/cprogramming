% できていないかもしれない

syms t x(t) y(t)
eqn1 = diff(x, t) == 6.*x - 1.*x*y;
eqn2 = diff(y, t) == 1.*x*y - 4.*y;
eqns = [eqn1; eqn2];
S = dsolve(eqns);
xSol(t) = S.x;
ySol(t) = S.y;
[xSol(t), ySol(t)] = dsolve(eqns);
cond1 = x(0) == 0;
cond2 = y(0) == 1;
conds = [cond1; cond2];
[xSol(t), ySol(t)] = dsolve(eqns, conds);
fplot(xSol)
hold on
fplot(ySol)
grid on
legend('xSol', 'ySol', 'Location', 'best')