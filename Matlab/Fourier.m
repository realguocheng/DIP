function F = Fourier(f,M)
F=zeros(1,M);
for u = 0:M-1
    for xi = 0:M-1
        F(u+1) = F(u+1) + f(xi+1)*(cos(2*pi*u*xi/M)-1i*sin(2*pi*u*xi/M));
    end
    F(u+1) = F(u+1)/M;
end
end

