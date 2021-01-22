function g=TransformMatElem(alpha,d,theta,r)
    g = [cos(theta), -sin(theta), 0, d;
         cos(alpha)*sin(theta), cos(alpha)*cos(theta), -sin(alpha), -r*sin(alpha);
         sin(alpha)*sin(theta), sin(alpha)*cos(theta), cos(alpha), r*cos(alpha);
         0, 0, 0, 1;];
end