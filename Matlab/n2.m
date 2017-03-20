clc,clear;
data1 = xlsread('DATA.xlsx',4,'A2:B609');
data2 = xlsread('DATA.xlsx',5,'A2:E31741');
res=-1*ones(608,1);
for i = 1:608
    index = find(data2(:,1) == data1(i,1));
    if(size(index,1)~=0)
    res(i) = min(abs(data2(index,2) - data1(i,2)));
    %xlswrite('DATA.xlsx',dis,4,['C',num2str(i)])
    end
end