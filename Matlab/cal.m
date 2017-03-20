clc,clear;
a=textread('path.txt');
N=a(end,1);
a1=a(:,1);
resultA=[];
resultb=[];
for i=1:N
    temp=find(a1==i);
    down=min(temp);
    up=max(temp);
    span=up-down+1;
    a2=a(down:up,2:end-1);
    a3=a(down:up,end);
    for j=1:span
        for k=j+1:span
            a4=a2(j,:)-a2(k,:);
            a5=a3(k)-a3(j);
            resultA=[resultA;a4];
            resultb=[resultb;a5];
        end
    end
end
A=-resultA;
b=resultb;
f=pinv(A)*b;
fh=1./f.*3.6
