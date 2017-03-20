clc,clear;
I = imread('4-1.tif');
figure(1)
imshow(I);
pause
I = double(I);
F1 = fftshift(fft2(I));
[M,N] = size(I);
u0 = M/2;
v0 = N/2;
[v,u] = meshgrid(0:N-1,0:M-1);
%show spectrum
spectrum(F1,10);
pause
%add sin noise
A = 50;
U = M / 2;
V = 0;
I = I + A * sin(U * u + V * v);
I = uint8(I);
figure(2)
imshow(I);
pause
%show spectrum again
F2 = fftshift(fft2(I));
spectrum(F2,11);
pause
%add notch filter (butterwoz)
d0 = 90;
n = 2;
x1 = 67; y1 = N / 2;
x2 = 381; y2 = N / 2;
D = sqrt((u - x1).^2 + (v - y1).^2).*sqrt((u - x2).^2 + (v - y2).^2);
val = (d0.^2 ./ D).^n;
H = 1 ./ (1 + val);
imshow(H);
pause
%show spectrum again
spectrum(F2.*H,12);
pause
%show reault
G = real(ifft2(ifftshift(F2.*H)));
figure(3)
imshow(uint8(G));
pause
%end
close all;

