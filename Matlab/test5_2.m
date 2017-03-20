clc,clear;
image = imread('3-1.tif');
F = fftshift(fft2(image));
[M,N] = size(image);
u0 = M/2;
v0 = N/2;
[v,u] = meshgrid(0:M-1,0:N-1);
D = sqrt((u-u0).^2+(v-v0).^2);
D0 = [inf,10,30,60,160,460];
K = (-1).^(u+v);
%ILPF
% figure(1);
% for i = 4
%     id = D <= D0(i);
%     H = zeros(M,N);
%     H(id) = 1;
%     G = real(ifft2(H.*F)).*K;
%     G = (G - min(min(G)))/(max(max(G))-min(min(G)));
%     figure(i)
%     imshow(G,[0,1]);
% end
%BLPF
% figure(2);
% for i = 4
%     H = (1 + (D/D0(i)).^4).^(-1);
%     G = real(ifft2(H.*F)).*K;
%     G = (G - min(min(G)))/(max(max(G))-min(min(G)));
%     figure(i+6)
%     %imshow(G,[0,1]);
% end
% %GLPF
% figure(3);
for i = 4
    H = exp(-1*D.^2/(2*D0(i).^2));
    G = real(ifft2(H.*F)).*K;
    G = (G - min(min(G)))/(max(max(G))-min(min(G)));
    %figure(12+i)
    %imshow(G,[0,1]);
end