function J=ComputeJac(alpha,d,theta,r)
    J = zeros(6, length(theta));
    i = 0;
    gF = ComputeDGM(alpha,d,theta,r);
    Z = [0,0,1];
    while i < length(theta)
        i = i +1;
        j = 0;
        g = diag([1,1,1,1]);
        while j < i
           j = j +1; 
           g1 = TransformMatElem(alpha(j),d(j),theta(j),r(j));
           g = g * g1;
        end
        giN = (gF - g);
        piN = giN(1:3,4);
        J(1:6,i) = [cross(g(1:3,1:3) * Z',piN); g(1:3,1:3) * Z'];
    end
end