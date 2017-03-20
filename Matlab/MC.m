clc,clear;
f = fopen('mouse0.raw');
A = fread(f,'ushort','b');
n = [150,150,276];
[x,y,z] = meshgrid(0:n(1)-1,0:n(2)-1,0:n(3)-1);
v = zeros(n(1),n(2),n(3));
for i = 1:n(1)
    for j = 1:n(2)
        for k = 1:n(3)
            v(i,j,k) = A(x(i,j,k)+y(i,j,k)*n(1)+z(i,j,k)*n(1)*n(2)+1);
        end
    end
end
 [F,V] = MarchingCubes(x,y,z,v,40000);
patch('vertices',V,'faces',F,'edgecolor','none',...
        'facecolor','red','facelighting','phong')
view(0,0);
light
axis equal off

