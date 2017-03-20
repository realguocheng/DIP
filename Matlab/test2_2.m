clc,clear;
image = imread('2-3.tif');
figure(1);
%subplot(2,2,1);
imshow(image);%��ʾԭͼ��
%subplot(2,2,2);
%imhist(image);%��ʾԭͼ���Ӧ��ֱ��ͼ
NPixel = zeros(1,256);%ͳ�ƶ�Ӧ�����������ظ���
[height,width] = size(image);
for i = 1:height
    for j = 1:width
        NPixel(image(i,j)+1) = NPixel(image(i,j)+1) + 1;
    end
end
SPixel = zeros(1,256);%ͳ���ۼ����طֲ�
SPixel(1) = NPixel(1);
for i = 2:256
    SPixel(i) = NPixel(i) + SPixel(i-1);
end
SPixel = SPixel/(height*width);
image1 = ones(height,width);
for i = 1:height
    for j = 1:width
        image1(i,j) = SPixel(image(i,j)+1);
    end
end
image1 = im2uint8(image1);
%subplot(2,2,3);
%imshow(image1);
%subplot(2,2,4);
%imhist(image1);


    