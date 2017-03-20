clc,clear;
image = imread('3-1.tif');
F = fftshift(fft2(image));
[M,N] = size(image);
u0 = M/2;
v0 = N/2;
[v,u] = meshgrid(0:M-1,0:N-1);
D = sqrt((u-u0).^2+(v-v0).^2);
D0 = [30,60,160];
K = (-1).^(u+v);
%IHPF
% for i = 2
%     id = D <= D0(i);
%     H = zeros(M,N);
%     H(~id) = 1;
%     G = real(ifft2(H.*F)).*K;
%     G = (G - min(min(G)))/(max(max(G))-min(min(G)));
%     %set(gca, 'Units', 'normalized', 'Position', [0 0.1 0.2 0.7]);
%     %figure(i)
%     %imshow(G,[0,1]);
% end
%BHPF
% figure(2);
% for i = 2
%     H = (1 + (D0(i)./D).^4).^(-1);
%     G = real(ifft2(H.*F)).*K;
%     G = (G - min(min(G)))/(max(max(G))-min(min(G)));
% %     figure(3+i)
% %     imshow(G,[0,1]);
% end
% %GHPF
% figure(3);
for i = 2
    H = 1 - exp(-1*D.^2/(2*D0(i).^2));
    G = real(ifft2(H.*F)).*K;
    G = (G - min(min(G)))/(max(max(G))-min(min(G)));
%     figure(6+i)
%     imshow(G,[0,1]);
end