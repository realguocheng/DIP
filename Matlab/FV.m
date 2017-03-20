clc,clear;
[x,y,z] = meshgrid(0:1,0:1,0:1);
v = ones(2,2,2);
v(:,:,1)=ones(2,2);
v(:,:,2)=2*ones(2,2);
[F,V] = isosurface(x,y,z,v,1.5);
patch('vertices',V,'faces',F,'edgecolor','none',...
        'facecolor','red','facelighting','phong');
light;

