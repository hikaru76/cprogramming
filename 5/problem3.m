range = [-pi pi];
x = range(1):0.1:range(2);
y1 = sin(x) + cos(2. * x);
y2 = exp(-x.^2 / 4);
w = conv(y1, y2, 'same');
plot(x, w)

hold on;
i = 1:1:1024;
f1 = fft(y1);
f2 = fft(y2);
f = f1.*f2;
w1 = ifft(f);
w2 = ifftshift(w1);
plot(x, w2)