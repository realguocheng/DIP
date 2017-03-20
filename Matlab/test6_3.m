clc,clear;
image = imread('4-1.tif');
F = fft2(image);
[M,N] = size(F);
[v,u] = meshgrid(1:N, 1:M);
a = 0.1;
b = 0.1;
T = 100;

u = u - floor( M/2 );
v = v - floor( N/2 );

uavb = pi*(u*a + v*b +eps);
H = T*sin(uavb)./uavb.*exp(-1i*uavb);%degradation funtion
H = ifftshift(H);

F = F.*H;
G = real(ifft2(F));
G = im2uint8(mat2gray(G));
figure(1);
imshow(G);%show degradation result
pause;
% PSF = fspecial('motion',70,135);
% gb = imfilter(image,PSF,'conv','circular');
% figure(2)
% imshow(gb,[]);

G = imnoise(G,'gaussian',0,0.003);
figure(2);
imshow(G);%show degradation & gaussian noise
pause;

L = fft2(G);
k = 0.001;
absh2 = abs(H).^2;
F = L./H.*absh2./(k + absh2);
G = real(ifft2(F));
G = uint8(mapminmax(G,0,255));
figure(3);
imshow(G);%show wiener filtering result
pause;
close all;

