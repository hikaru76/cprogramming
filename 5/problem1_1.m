syms x;
left = x^5 - 7/6 * x^4 - x^3 + 4/3 * x^2 - 1/6;
right = 0;
fplot([left right])
xlim([-3 3])
ylim([-1 3])
title([texlabel(left) ' = ' texlabel(right)])
solve(left == right, x)