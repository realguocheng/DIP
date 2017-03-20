clc,clear;
data = [15.6, 5.6, 3.5, 25.5, 22.9
        27.8, 4.3, 1.0, 7.7, 23.4
        35.2, 3.0, 38.1, 3.7, 36.8
        10.2, 3.4, 3.5, 7.4, 22.0
        29.1, 33.2, 1.6, 24.0, 6.4
        10.2, 11.6, 2.2, 26.7,29.4
        35.4, 4.1, 1.3, 7.0, 26.2
        8.7, 3.5, 7.5, 5.0, 20.9
        25.4, 0.7, 22.2, 35.4, 26.5
        15.3, 6.0, 2.0, 17.5, 37.3];
data = data';
IN = data(1:4, 1:end-1);
[IN, PS1] = mapminmax(IN);
OUT = data(5, 1:end-1);
[OUT, PS2] = mapminmax(OUT);
rbf_net = newrb(IN, OUT);

x = mapminmax('apply', data(1:4, end), PS1);
y = sim(rbf_net, x);
y = mapminmax('reverse', y, PS2);

disp(y);