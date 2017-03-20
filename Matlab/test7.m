clc,clear;
I = imread('10-1.tif');
G = edge(I,'canny');
imshow(G);