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

% header
fprintf( '\nRunge-Kutta-Fehlberg_7(8) numerical integration. MEX verision\n\n' );

% Step-size of integration
h = 0.01; % [s]

% Initial values
step = 60;
span = 0:step:3600;

num = length(span);
y = zeros(num,length(y_0));
tic
% Integration from t=t_0 to t=t_end
y(1,:) = y_0;
for ii = 1:num-1
    [y_f, out, h_next] = func_mex('Runge_Kutta_Fehlberg_7_8',y(ii,:)',span(ii),h,span(ii+1),1.0e-13);
    h = h_next;
    y(ii+1,:) = y_f;
end
toc

y_ref = State(GM, Kep, span(end)); % Reference solution

fprintf(' Runge-Kutta-Fehlberg results\n');
fprintf(' Accuracy    Digits\n');
fprintf('%6.2e',norm(y(end,:)'-y_ref));
fprintf('%9.2f\n',-log10(norm(y(end,:)'-y_ref)));
fprintf('\n');

tic
% Integration from t=t_0 to t=t_end
options = odeset('RelTol',1e-13,'AbsTol',1e-13);
[t1,y1] = ode45(@func, span, y(1,:), options);
toc

fprintf(' ode45 MATLAB results\n');
fprintf(' Accuracy    Digits\n');
fprintf('%6.2e',norm(y1(end,:)'-y_ref));
fprintf('%9.2f\n',-log10(norm(y1(end,:)'-y_ref)));

