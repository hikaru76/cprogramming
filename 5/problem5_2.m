syms x(t) y(t);
dfun=@(t,X) [X(1) - 0.1*X(1)*X(2);0.1*X(1)*X(2) - X(2)];
tspan = [0 10];
x0 = 1;
y0 = 1;
[t,X]= ode45(dfun, tspan, [x0; y0]);
plot(t,X)