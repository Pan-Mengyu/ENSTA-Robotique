function qStar = ComputeIGM(Xd,q,kmax,E)
    alpha = [0,pi/2,0,pi/2,-pi/2,pi/2];
    d = [0,0,0.7,0,0,0];
    r = [0.5,0,0,0.2,0,0.1];%r+rE
    theta = q + [0,0,pi/2,0,0,0];
    
    for k = 1:kmax
        theta = q + [0,0,pi/2,0,0,0];
        J = ComputeJac(alpha, d, theta, r);
        Ji = J(1:3,:);
        g = ComputeDGM(alpha, d, theta, r);
        %g = g*TransformMatElem(0,0,0,0.1);
        X = g(1:3, 4);
        dX = Xd - X;
        temp = q' + pinv(Ji) * dX;
        q = temp';
        error = norm(dX, 2);
        if error < E
            break;
        end
    end
    qStar = q;
end