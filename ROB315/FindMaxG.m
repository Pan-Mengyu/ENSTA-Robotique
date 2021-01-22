function Gmax = FindMaxG(qmin,qmax)
    Gmax = 0;
    q = qmin;
    dq = (qmax-qmin)/1000;
    
    for i = 1:1000
       G = ComputeGravTorque(q);
       G = norm(G,1);
       if G > Gmax
           Gmax = G;
       end
       q = q + dq;
    end

end