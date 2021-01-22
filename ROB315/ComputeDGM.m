function g=ComputeDGM(alpha,d,theta,r)
    g = diag([1,1,1,1]);
    i = 0;
    while i < length(alpha)
        i = i + 1;
        g1 = TransformMatElem(alpha(i),d(i),theta(i),r(i));
        g = g * g1;
    end
end