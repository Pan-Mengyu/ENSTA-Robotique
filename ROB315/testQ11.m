function testQ11
    qmin = [-pi,-pi/2,-pi,-pi,-pi/2,-pi];
    qmax = [0,pi/2,0,pi/2,pi/2,pi/2];
    Xdi = [-0.1,-0.7,0.3]';
    Xdf = [0.64,-0.1,1.14]';
    V = 1;
    Te = 0.001;
    qi = [-pi/2,0,-pi/2,-pi/2,-pi/2,-pi/2];
    [X,q] = ComputeIKMlimits(Xdi,Xdf,V,Te,qi,qmin,qmax)
end