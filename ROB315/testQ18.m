%set parameter
qmin = [-pi -pi/2 -pi -pi -pi/2 -pi]';
qmax = [0 pi/2 0 pi/2 pi/2 pi/2]';
qdi = [-1 0 -1 -1 -1 -1]';
qdf = [0 1 0 0 0 0]';
Te = 0.001;
Rred = [100 100 100 70 70 70];
tau = 5;

%use the code of Q14
[number1,number2] = FindScalar(qmin,qmax);
%calculation of parameter
Distance = abs(qdf - qdi);
k = ((Rred * tau) / number1)';

%calculation of time
t = (sqrt((10/sqrt(3))*Distance./k))
t = max(t);