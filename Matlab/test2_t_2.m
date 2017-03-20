clc,clear;
I = imread('2-1.tif');  
[height,width] = size(I);  
figure  
subplot(221)  
imshow(I)%��ʾԭʼͼ��  
subplot(222)  
imhist(I)%��ʾԭʼͼ��ֱ��ͼ  
  
%�������ػҶ�ͳ��;  
NumPixel = zeros(1,256);%ͳ�Ƹ��Ҷ���Ŀ����256���Ҷȼ�  
for i = 1:height  
    for j = 1: width  
        NumPixel(I(i,j) + 1) = NumPixel(I(i,j) + 1) + 1;%��Ӧ�Ҷ�ֵ���ص���������һ  
    end  
end  
%����Ҷȷֲ��ܶ�  
ProbPixel = zeros(1,256);  
for i = 1:256  
    ProbPixel(i) = NumPixel(i) / (height * width * 1.0);  
end  
%�����ۼ�ֱ��ͼ�ֲ�  
CumuPixel = zeros(1,256);  
for i = 1:256  
    if i == 1  
        CumuPixel(i) = ProbPixel(i);  
    else  
        CumuPixel(i) = CumuPixel(i - 1) + ProbPixel(i);  
    end  
end  
%�ۼƷֲ�ȡ��  
CumuPixel = uint8(255 .* CumuPixel + 0.5);  
%�ԻҶ�ֵ����ӳ�䣨���⻯��  
for i = 1:height  
    for j = 1: width  
        I(i,j) = CumuPixel(I(i,j)+1);  
    end  
end  
  
subplot(223)  
imshow(I)%��ʾԭʼͼ��  
subplot(224)  
imhist(I)%��ʾԭʼͼ��ֱ��ͼ 