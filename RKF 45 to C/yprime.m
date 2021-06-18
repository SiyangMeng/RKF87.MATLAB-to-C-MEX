%------------------------------------------------------------------------------
%
% deriv.m :Computes the derivative of the state vector for the normalized
%          (GM=var.mu) Kepler's problem in three dimensions
%
% Inputs:
%   t : time(s)
%   y : state vector(x,y,z,vx,vy,vz)
%
% Outputs:
%   yp : derivative of the state vector(vx,vy,vz,ax,ay,az)
%
% Last modified:   2018/01/27   M. Mahooti
%------------------------------------------------------------------------------
function yp = yprime(t, y,var)

% State vector derivative
r = y(1:3);
v = y(4:6);
mu=var.mu;
yp = [v;
    -mu*r/((norm(r))^3)];
end

