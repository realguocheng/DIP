for i = 1:dims(1)
    for j = 1:dims(2)
        for k = 1:dims(3)
            ie = edgeTable(cube_code(i,j,k)+1);
            temp0 = find(bitget(ie,1:12) == 1);
            if(~isempty(temp0))
                temp1 = [edgePort(temp0,:) temp0'];
                l1 = size(V,1);
                %--------get V-----------
                for ii = 1:size(temp1,1)
                    p1 = [i,j,k]+vectors(temp1(ii,1),:);                 
                    p2 = [i,j,k]+vectors(temp1(ii,2),:);
                    p1v = v(p1(1),p1(2),p1(3));
                    p2v = v(p2(1),p2(2),p2(3));
                    mu = (s - p1v)/(p2v - p1v);
                    p = p1 + mu*(p2-p1);
                    V = [V;p temp1(ii,3)];
                end
                pn = size(temp1,1);
                p1 = repmat([i,j,k],pn,1)+vectors(temp1(1:pn,1),:);
                p2 = repmat([i,j,k],pn,1)+vectors(temp1(1:pn,2),:);
                p1v = v(p1(1),p1(2),p1(3));
                p2v = v(p2(1),p2(2),p2(3));
                
                l2 = size(V,1);
                %--------get F----------
                tri = triTable(cube_code(i,j,k)+1,:);
                for ii = 1:3:15
                    if(tri(ii) > 0)
                        f1 = find(V(l1+1:l2,4) == tri(ii))+l1;
                        f2 = find(V(l1+1:l2,4) == tri(ii+1))+l1;
                        f3 = find(V(l1+1:l2,4) == tri(ii+2))+l1;
                        F=[F; f1,f2,f3];
                    end
                end
            end
        end
    end
end