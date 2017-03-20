clc,clear;
data = xlsread('bac.xlsx','B2:D17');
[H,W] = size(data);
sot = zeros(H,W);
for i = 1:H
    for j = 1:W
        sot(i,j) = size(find(data > data(i,j)),1) + 1;
    end
end
sot = sot/sum(sum(sot));
sum(sum(sot))