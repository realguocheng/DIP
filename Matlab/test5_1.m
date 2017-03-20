clc,clear;
image = imread('3-1.tif');
A = fft2(image);
F = fftshift(A);%move to the center
B = abs(F);
B = B / max(max(B));
v = 3000;
B = log(1+v*B)/log(v+1);
figure(1)
imshow(B,[0,1]);
iimage = real(ifft2(A));
low = min(min(iimage));
high = max(max(iimage));
iimage = (iimage - low) / (high - low);
figure(2)
subplot(121)
imshow(image);
figure(3)
imshow(iimage,[0,1]);