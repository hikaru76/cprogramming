syms x;
left = cos(3*x);
right = 1/2*x;
fplot([left right])
xlim([-3 3])
ylim([-1 3])
title([texlabel(left) ' = ' texlabel(right)])
vpasolve(left == right, x)