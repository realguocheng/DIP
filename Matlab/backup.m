clc,clear;
f = imread('dip.tif');
[fp, H] = motion(f, 0.1, 0.1, 1);
imshow(fp,[]);