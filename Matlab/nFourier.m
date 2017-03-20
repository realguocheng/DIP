function F = nFourier(f,M,d)
F=zeros(1,M/d);
for u = 0:M/d-1
    for xi = 0:M/d-1
        F(u+1) = F(u+1) + f(xi*d)*(cos(2*pi*u*xi/M*d)-1i*sin(2*pi*u*xi/M*d));
    end
    F(u+1) = F(u+1)/M*d;
end
end

