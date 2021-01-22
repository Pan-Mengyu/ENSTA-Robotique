function [Direction, manipulabilite] = testQ7()
    alpha = [0,pi/2,0,pi/2,-pi/2,pi/2];
    d = [0,0,0.7,0,0,0];
    theta = [-pi/2, 0, 0, -pi/2, -pi/2, -pi/2];%%qi+bias
    %theta = [0, pi/4, pi/2, pi/2, pi/2, 0];%%qf+bias
    r = [0.5,0,0,0.2,0,0.1];
    J = ComputeJac(alpha,d,theta,r);
    J7 = J(1:3,:);
    [U,S,V] = svd(J7*J7.');
    [m,idx] = max(diag(S));
    Direction = V(:,idx);
    eigenvalues = sqrt(diag(S));
    manipulabilite = prod(eigenvalues);
end