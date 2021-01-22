function result = testQ8()
    Xd = [-0.1,-0.7,0.3]';
    %q0 = [-pi/2,0,-pi/2,-pi/2,-pi/2,-pi/2];
    q0 = [-1.57,0,-1.47,-1.47,-1.47,-1.47];
    kmax = 100;
    E = 0.001;
    result = ComputeIGM(Xd,q0,kmax,E);
end