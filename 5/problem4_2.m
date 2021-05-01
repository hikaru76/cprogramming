syms y(t);
[V] = odeToVectorField(diff(y, 2) == -1. * diff(y) - 5.*y);
M = matlabFunction(V, 'vars', {'x', 'Y'});
sol = ode45(M, [0 20], [2 0]);
fplot(@(x)deval(sol, x, 1), [0, 20])