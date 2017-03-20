clc,clear;
M = 300;
r = [1,2,0.5,1.5,2/3];
for i= 1:5
    figure(i);
    d = 1/r(i);
    l = 0:d:M-d;
    f = sin(l)./l;
    f(1) = 1;
    subplot(121)
    plot(l,f);
    F = afourier(f,M,d);
    subplot(122)
    plot(l,abs(F));
end


