%局部直方图均衡化
clc,clear;
I = imread('2-3.tif');
figure(1)
%subplot(121);
%imshow(I);
K=padarray(I,[1 1],'replicate');
[height,width] = size(K);
L=zeros(height-2,width-2);
for i = 2:height-1
    for j = 2:width-1
        Pixels = zeros(1,256);
        SPixels = zeros(1,256);
        for m = 1:3
            for n = 1:3
                Pixels(K(i+m-2,j+n-2)+1) = Pixels(K(i+m-2,j+n-2)+1)+1;
            end
        end
        SPixels(1) = Pixels(1);
        for k = 2:256
            SPixels(k) = Pixels(k)+SPixels(k-1);
        end
        for l = 1:256
            SPixels(l) = SPixels(l)/9;
        end
        L(i-1,j-1) = SPixels(K(i,j)+1);
    end
end
%subplot(122);
imshow(L,[0 1]);

