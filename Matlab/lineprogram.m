f = [-2; -3; 5];
A = [-2, 5, -1; 1, 3, 1];
b = [-10; 12];
Aeq = [1, 1, 1];
beq = 7;
lb = zeros(3,1);
[x,y] = linprog(f,A,b,Aeq,beq,zeros(3,1));
x;
y=-y;
