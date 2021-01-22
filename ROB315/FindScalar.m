function [number1,number2] = FindScalar(qmin,qmax)
    number1 = 0;
    number2 = inf;
    q = qmin;
    dq = (qmax-qmin)/1000;
    
    for i = 1: 1000
        A = ComputeMatInert(q);
        q = q + dq;
        Big = max(eig(A));
        Small = min(eig(A));
        if Big > number1
            number1 = Big;
        end
        if Small < number2
            number2 = Small;
        end        
    end