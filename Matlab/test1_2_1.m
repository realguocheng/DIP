clc,clear;
H=imread('1-1.tif');
[M,N]=size(H);
[counts,x]=imhist(H);%H�Ƕ�ȡ��ͼ��imhist�Ƕ�ͼ��ֱ��ͼ����ͳ�ƣ�����count����ÿ���Ҷ�ֵ�ø�����x����Ҷ�ֵ��һ��ģ�x=1:256
location=find(counts~=0);%�ҵ��������ظ�����Ϊ0�ĻҶȼ�
MinCDF=min(counts(location));%�ҵ������������ٵĻҶȼ�
for  j=1:length(location)
      CDF=sum(counts(location(1:j)));%��������Ҷȼ����ظ����ۼƷֲ�
      P=find(H==x(location(j)));%�ҵ�ͼ���е���ĳ���Ҷȼ��������ص�����λ��
      H(P)=(CDF-MinCDF)/(M*N-MinCDF);%%���ûҶȻ��㹫ʽ���޸�����λ���ϵ�����ֵ
end
imshow(H);