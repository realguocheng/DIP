clc,clear;
I = imread('2-5.tif');
figure(1)
%subplot(121);
%imshow(I);
I = im2double(I);
K=padarray(I,[1 1],'replicate');
[height,width] = size(K);
L=zeros(height-2,width-2);
for i = 2:height-1
    for j = 2:width-1
        L(i-1,j-1) = mean(mean(K(i-1:i+1,j-1:j+1)));
    end
end
k = 9;
L = I + k*(I-L);
%subplot(122);
imshow(L,[0 1]);