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
fprintf( '\nRunge-Kutta-Fehlberg_7(8) numerical integration\n\n' );

% Step-size of integration
h = 0.01; % [s]

% Initial values
step = 60;
span = 0:step:60;

num = length(span);
y = zeros(num,length(y_0));
tol = 1.0e-13;
ii =1;
[y_f, out, h_next] = Runge_Kutta_Fehlberg_7_8(y(ii,:)',span(ii),h,span(ii+1),tol);
% tic
% Integration from t=t_0 to t=t_end
% y(1,:) = y_0;
% for ii = 1:num-1
%     [y_f, out, h_next] = Runge_Kutta_Fehlberg_7_8(@Deriv,y(ii,:)',span(ii),h,span(ii+1),tol);
%     h = h_next;
%     y(ii+1,:) = y_f;
% end
% toc


