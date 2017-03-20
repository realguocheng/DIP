function f = iFourier(F,M)
f=zeros(1,M);
for u = 0:M-1
    for xi = 0:M-1
        f(u+1) = f(u+1) + F(xi+1)*(cos(2*pi*u*xi/M)+1i*sin(2*pi*u*xi/M));
    end
end
end

