function testQ3
    alpha = [0,pi/2,0,pi/2,-pi/2,pi/2];
    d = [0,0,0.7,0,0,0];
    theta = [0,0,pi/2,0,0,0];
    r = [0.5,0,0,0.2,0,0];
    ComputeDGM(alpha,d,theta,r)*ComputeDGM(0,0,0,0.1)
end
