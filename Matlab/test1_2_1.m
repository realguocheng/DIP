clc,clear;
H=imread('1-1.tif');
[M,N]=size(H);
[counts,x]=imhist(H);%H是读取的图像，imhist是对图像直方图进行统计，其中count，是每个灰度值得个数，x代表灰度值。一般的，x=1:256
location=find(counts~=0);%找到所有像素个数不为0的灰度级
MinCDF=min(counts(location));%找到包含个数最少的灰度级
for  j=1:length(location)
      CDF=sum(counts(location(1:j)));%计算各个灰度级像素个数累计分布
      P=find(H==x(location(j)));%找到图像中等于某个灰度级所有像素点所在位置
      H(P)=(CDF-MinCDF)/(M*N-MinCDF);%%利用灰度换算公式，修改所有位置上的像素值
end
imshow(H);