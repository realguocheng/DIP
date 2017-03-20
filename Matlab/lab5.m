clc,clear;
image = imread('3-1.tif');
F = fft2(image);
[M,N] = size(image);
u0 = M/2;
v0 = N/2;
[v,u] = meshgrid(0:M-1,0:N-1);
D = sqrt(u.^2+v.^2);
D0 = [inf,10,30,60,160,460];
K = (-1).^(u+v);
%ILPF
figure(1);
for i = 1:6
    id = D <= D0(i);
    H = zeros(M,N);
    H(id) = 1;
    G = real(ifft2(H.*F));
    G = (G - min(min(G)))/(max(max(G))-min(min(G)));
    subplot(2,3,i)
    imshow(G,[0,1]);
end
