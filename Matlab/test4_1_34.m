clc,clear;
M=512;
x=0:M-1;
%------------- 1 --------------
f0=cos(2*pi/16*x);%62.5 kHz 
F = Fourier(f0,M);
figure(1)
subplot(222)    %Fourier
plot(x,abs(F));title('2');
subplot(221)    %original func
plot(x,f0);axis([0 600 -1.5 1.5]);title('1');
subplot(223)    %inverse Fourier
f1 = iFourier(F,M);title('3');
plot(x,real(f1));axis([0 600 -1.5 1.5])
subplot(224)    %difference
plot(x,real(f1)-f0);title('4');
%------------- 2 --------------
f2=cos(2*pi*0.065*x);%65 kHz 
F1 = Fourier(f2,M);
figure(2)
subplot(222)    %Fourier
plot(x,abs(F1));title('2');
subplot(221)    %original func
plot(x,f2);axis([0 600 -1.5 1.5]);title('1');
subplot(223)    %inverse Fourier
f3 = iFourier(F1,M);
plot(x,real(f3));axis([0 600 -1.5 1.5]);title('3');
subplot(224)    %difference
plot(x,real(f3)-f2);title('4');
%------------compare 1&2------------
figure(3)
subplot(231); plot(x,f0);title('1');
subplot(232); plot(x,f2);title('2');
subplot(233); plot(x,f2-f0);title('3');
subplot(234); plot(x,abs(F));title('4');
subplot(235); plot(x,abs(F1));title('5');
subplot(236); plot(x,abs(F1)-abs(F));title('6');

