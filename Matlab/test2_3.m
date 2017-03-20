clc,clear;
I = imread('2-2.tif');
figure(1)
subplot(121)
imshow(I);
I = im2double(I);
H=[-1,-1,-1;-1,8,-1;-1,-1,-1];
K=padarray(I,[1 1],'replicate');
[height,width] = size(K);
L=zeros(height,width);
for i = 2:(height-1)
    for j = 2:(width-1)
        PMat = K(i-1:i+1,j-1:j+1);
        L(i,j) = sum(sum(PMat.*H));
    end
end
FI = L(2:(height-1),2:(width-1));
figure(2)
subplot(121)
imshow(FI,[0 1]);
min0 = min(min(FI));
max0 = max(max(FI));
FI1 = (FI-min0)/(max0-min0);
figure(2)
subplot(122)
imshow(FI1,[0 1]);
figure(1)
subplot(122)
imshow(I+FI,[0 1]);


