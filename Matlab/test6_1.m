clc,clear;
I = imread('4-1.tif');
[M,N] = size(I);
%original image
figure(1)
imshow(I)
figure(6)
imhist(I)
pause
%polluted by gaussian noise
G1 = imnoise(I,'gaussian',0,0.01);
figure(2)
imshow(G1)
figure(7)
imhist(G1)
pause
%polluted by salt & pepper noise
G2 = imnoise(I,'salt & pepper',0.1);
figure(3)
imshow(G2)
figure(8)
imhist(G2)
pause
%polluted by uniform noise
a = -50;
b = 50;
r = rand(M,N) * (b - a) + a;
G3 = uint8(double(I) + r);
figure(4)
imshow(G3)
figure(9)
imhist(G3)
pause
%polluted by sinusoidal noise
A = 70;
u = 0;
v = 40;
[y, x] = meshgrid(1:N, 1:M);
sn = A * sin(u * x + v * y);
G4 = uint8(double(I) + sn);
figure(5)
imshow(G4)
figure(10)
imhist(G4)
pause
%end
close all;

% a = 0.1;
% b = 0.1;
% r = rand(M,N);
% G3 = I;
% G3(r < a) = 0;
% G3(r > a & r < a+b) = 255;
% figure(4)
% imshow(G3)
% pause