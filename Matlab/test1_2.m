clc,clear;
ori=imread('1-1.tif');
a=[256 128 64 32 16 8 4 2];
for i=1:8
    b=255/(a(i)-1);
    orix=round(round(ori/b)*b);
    figure(1);
    subplot(2,4,i);
    imshow(orix);
    figure(2);
    subplot(2,4,i);
    imhist(orix);
    imwrite(orix,['p_' num2str(i) '.jpg']);
end