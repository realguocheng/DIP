function F = afourier(f,M,d)
n = M/d;
F=zeros(1,n);
for u = 0:d:M-d
    for xi = 0:d:M-d
        F(round(u/d+1)) = F(round(u/d+1)) + f(round(xi/d+1))*(cos(2*pi*u*xi/n)-1i*sin(2*pi*u*xi/n));
    end
    F(round(u/d+1)) = F(round(u/d+1))/n;
end
end

