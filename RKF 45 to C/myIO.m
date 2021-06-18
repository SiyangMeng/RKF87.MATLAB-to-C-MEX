% time span series or t0 tf
tspan=[0:60]';
tspan =[0, 60]';
assert(all(size(tspan)<=[1e6 1]));
% initial state
y_0=[0.900000000000000;0;0;0;1.10554159678513;0];
% options for RKF45, also could use 'odeset' in matlab code, but not in C
options = odeset('RelTol',1e-8,'AbsTol',1e-13);
options.MaxStep=0.01;
% auxilary variables in ode system
var.mu=1.0;
var.Cd=2.2;

[ts,yout,tf,yend] = wrapRK45(tspan,y_0,options,var);