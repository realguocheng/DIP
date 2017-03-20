clc,clear;
x = 0:0.01:1;
y = log(1+70*x)/log(71);
figure(1)
subplot(121);
plot(x,y);
axis square;
y = x.^0.4;
subplot(122);
plot(x,y);
axis square;