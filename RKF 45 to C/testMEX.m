%--------------------------------------------------------------------------
% 
%    Runge-Kutta-Fehlberg_7(8) Numerical Integration
%
% Last modified:   2019/07/13   M. Mahooti
%--------------------------------------------------------------------------
clc
clear
format long g

% constants
GM  = 1;                   % gravitational coefficient
e   = 0.1;                 % eccentricity
Kep = [1, e ,0 ,0 ,0 ,0]'; % (a,e,i,Omega,omega,M)

% Initial state of satellite (x,y,z,vx,vy,vz)
y_0 = State(GM, Kep, 0);

var.mu=GM;
var.Cd=2.2;
options = odeset('RelTol',1e-13,'AbsTol',1e-13);
options.MaxStep=0.01;
% fprintf('\nFixed step test\n\n');
% tspan=[0:60]';
fprintf('\nVariable step test\n\n');
tspan= [0 60]';

tic
[ts,yout,tf,yend] = RK45_mex('wrapRK45',tspan,y_0,options,var);
toc
y_ref = State(GM, Kep, ts(end)); % Reference solution

fprintf(' Runge-Kutta-45 .MEX64 version; results calculation step: %d\n', length(ts));
fprintf(' Accuracy    Digits\n');
fprintf('%6.2e',norm(yend-y_ref));
fprintf('%9.2f\n',-log10(norm(yend-y_ref)));
fprintf('\n');

tic
% Integration from t=t_0 to t=t_end
[t1,y1] = ode45(@yprime, tspan, y_0, options,var);
toc

fprintf(' ode45 MATLAB; results calculation step: %d\n', length(t1));
fprintf(' Accuracy    Digits\n');
fprintf('%6.2e',norm(y1(end,:)'-y_ref));
fprintf('%9.2f\n',-log10(norm(y1(end,:)'-y_ref)));



