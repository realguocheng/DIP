function [fp, H] = motion( f, a, b, T )
% A degradation model based on uniform linear motion between the image and
% the sensor during image acquisition.
% (M,N) -- Size of the image
% a,b,T -- Parameters about the model
% H(u,v) = T/(pi*(u*a+v*b))*sin( pi*(u*a+v*b) )*exp( -j*(u*a+v*b) )

[M,N] = size( f );
[V,U] = meshgrid(1:N, 1:M);

%Following two steps are very critical, trans the (M/2, N/2) to the origin(0,0)
U = U - floor( M/2 );
V = V - floor( N/2 );

uavb = pi*( U*a + V*b + eps);
H = T./uavb .* sin( uavb ) .* exp( -1j*uavb );
H = ifftshift( H );

F = fft2( f );
Fp = H.*F;
fp = real( ifft2(Fp) );
fp = im2uint8( mat2gray(fp) );
end