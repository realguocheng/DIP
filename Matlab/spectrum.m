function spectrum(F,t)
B = abs(F);
B = B / max(max(B));
d = 3000;
B = log(1+d*B)/log(d+1);
figure(t)
imshow(B,[0,1]);
end