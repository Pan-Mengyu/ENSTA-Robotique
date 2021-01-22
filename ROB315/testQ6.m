function result = testQ6()
    alpha = [0,pi/2,0,pi/2,-pi/2,pi/2];
    d = [0,0,0.7,0,0,0];
    theta = [-pi/2, 0, 0, -pi/2, -pi/2, -pi/2];%%qi+bias
    %theta = [0, pi/4, pi/2, pi/2, pi/2, 0];%%qf+bias
    r = [0.5,0,0,0.2,0,0.1];%r+rE
    J = ComputeJac(alpha,d,theta,r);
    q_point = [0.5,1,-0.5,0.5,1,-0.5]';
    result = J * q_point;
end