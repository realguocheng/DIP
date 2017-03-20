clc,clear;
I=imread('4-1.tif'); 

S=fft2(I);
[M,N]=size(S);     
H=zeros(M,N);
for i=1:M 
    for j=1:N 
        ii=i+1-floor(M/2);
        jj=j+1-floor(N/2);
        l=(0.1*ii+0.1*jj + eps)*pi;
        H(i,j)=sin(l)/l*cos(l)-sin(l)/l*sin(l)*1i;                     
    end
end
H = fftshift(H);
S=H.*S;       
S=real(ifft2(S));   
S= (S-min(min(S)))*255/(max(max(S))-min(min(S)));
S=uint8 (S);  



u=input('¾ùÖµ=');
z=input('·½²î=');
A=double(S);
T=A;
Y= randn(M, N)*sqrt(z)+u;
T=T+Y;
T= (T-min(min(T)))*255/(max(max(T))-min(min(T)));
T=uint8 (T);

TT=fftshift(fft2(T));
K=input('K=');
HH=zeros(M,N);
for i=1:M 
    for j=1:N 
        HH(i,j)=(abs(H(i,j))*abs(H(i,j)))/(abs(H(i,j))*abs(H(i,j))*H(i,j)+K*H(i,j));                     
    end
end
K=HH.*TT;
K=ifftshift(K);           
K=ifft2(K);   
K= (K-min(min(K)))*255/(max(max(K))-min(min(K)));
K=uint8 (K); 
subplot(2,2,1);
imshow(I);
subplot(2,2,2);
imshow(S);   
subplot(2,2,3);
imshow(T);
subplot(2,2,4);
imshow(K);
