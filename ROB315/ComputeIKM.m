function [X,q]=ComputeIKM(Xdi,Xdf,V,Te,qi)
    %%according to Q8
    kmax = 100;
    E = 0.001;
    
    distance = norm(Xdf - Xdi,2);
    step = (V*Te)*(Xdf - Xdi)/distance;
    
    Xd = Xdi;
    X = Xdi;
    qI = qi;
    q = qi';
    for i = [1:distance/V/Te]
        Xd = Xd + step;
        qI = ComputeIGM(Xd,qI,kmax,E);
        X = [X Xd];
        q = [q, qI'];
    end
    
end