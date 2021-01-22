function testQ4
    alpha = [0,pi/2,0,pi/2,-pi/2,pi/2];
    d = [0,0,0.7,0,0,0];
    theta = [0,0,pi/2,0,0,0];
    r = [0.5,0,0,0.2,0,0];
    qi = [-pi/2,0,-pi/2,-pi/2,-pi/2,-pi/2];
    qf = [0,pi/4,0,pi/2,pi/2,0];
    %% initial state
    gi = ComputeDGM(alpha,d,theta+qi,r)*ComputeDGM(0,0,0,0.1)
    theta_i = atan2(0.5*sqrt(pow2(gi(3,2)-gi(2,3))+pow2(gi(1,3)-gi(3,1))+pow2(gi(2,1)-gi(1,2))),0.5*(gi(1,1)+gi(2,2)+gi(3,3)-1))
    Axe_i = [(gi(3,2) - gi(2,3))/(2*sin(theta_i)), ...
            (gi(1,3) - gi(3,1))/(2*sin(theta_i)), ...
            (gi(2,1) - gi(1,2))/(2*sin(theta_i))]
    %% final state 
    gf = ComputeDGM(alpha,d,theta+qf,r)*ComputeDGM(0,0,0,0.1)
    theta_f = atan2(0.5*sqrt(pow2(gf(3,2)-gf(2,3))+pow2(gf(1,3)-gf(3,1))+pow2(gf(2,1)-gf(1,2))),0.5*(gf(1,1)+gf(2,2)+gf(3,3)-1))
    Axe_f = [(gf(3,2) - gf(2,3))/(2*sin(theta_f)), ...
            (gf(1,3) - gf(3,1))/(2*sin(theta_f)), ...
            (gf(2,1) - gf(1,2))/(2*sin(theta_f))]
end