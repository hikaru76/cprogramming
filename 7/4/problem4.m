M = readmatrix('2.csv');
x = M(:,1); 
y = M(:,2);

plot(x,y)
xlabel('t(s)')
ylabel('y(m)')
title('Original signal')

w = fft(y); 
n = length(x);          
w0 = fftshift(w);         
f0 = (-n/2:n/2-1)*(2/n); 
power0 = abs(w0);    

plot(f0,power0)
grid on
xlim([0 1.0])
xlabel('Frequency')
ylabel('Power')
title('Power spectrum')
