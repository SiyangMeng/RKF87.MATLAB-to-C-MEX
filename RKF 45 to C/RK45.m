%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  RK4(yprime, y, x0, h)                                               
%                                                                            
%  Description:                                                              
%     This routine uses Fehlberg's embedded 7th and 8th order methods to     
%     approximate the solution of the differential equation y'=f(x,y) with   
%     the initial condition y = y0 at x = x0. The value at x + h is returned 
%     in y. The function returns err/h ( the absolute error per step size ). 
%                                                                            
%  Arguments:                                                                
%     yprime	function handle which returns the slope at (x,y) of integral 
%           curve of the differential equation y' = f(x,y) which passes    
%           through the point (x0,y0). 			                       
%     y     On input y is the initial value of y at x, on output y is     
%               the solution at x + h.                              	   
%     x     Initial value of x.                                       
%     h     Step size                                                 
%                                                                            
%  Return Values:                                                            
%     This routine returns the err/h.  The solution of y(x) at x + h is      
%     returned in y.                                                         
%                                                                            
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [x, errorEstimate] = RK45( x, t, dt ,var)
% REFERENCE1: https://github.com/recalon/rkf_calon/rkf_calon.cpp
% REFERENCE2: https://github.com/lcsamaro/rkf45/blob/master/main.cpp
% const Real tableau[8][7]{
%   {       0.0,           0.0,            0.0,            0.0,             0.0,        0.0,      0.0 },
%   {   1.0/4.0,       1.0/4.0,            0.0,            0.0,             0.0,        0.0,      0.0 },
%   {   3.0/8.0,      3.0/32.0,       9.0/32.0,            0.0,             0.0,        0.0,      0.0 },
%   { 12.0/13.0, 1932.0/2197.0, -7200.0/2197.0,  7296.0/2197.0,             0.0,        0.0,      0.0 },
%   {       1.0,   439.0/216.0,           -8.0,   3680.0/513.0,   -845.0/4104.0,        0.0,      0.0 },
%   {   1.0/2.0,     -8.0/27.0,            2.0, -3544.0/2565.0,   1859.0/4104.0, -11.0/40.0,      0.0 },
%   {       0.0,    16.0/135.0,            0.0, 6656.0/12825.0, 28561.0/56430.0,  -9.0/50.0, 2.0/55.0 },
%   {       0.0,    25.0/216.0,            0.0,  1408.0/2565.0,   2197.0/4104.0,   -1.0/5.0,      0.0 }
% };
k1 = yprime(t,x ,var);
k2 = yprime(t+dt/4, x+dt*k1/4 ,var);	
k3 = yprime(t+3*dt/8,  x+3*dt*k1/32+9*dt*k2/32 ,var);		
k4 = yprime(t+12*dt/13, x+1932*dt*k1/2197-7200*dt*k2/2197+7296*dt*k3/2197 ,var);
k5 = yprime(t+dt, x+439*dt*k1/216-8*dt*k2+3680*dt*k3/513-845*dt*k4/4104 ,var);
k6 = yprime(t+dt/2, x-8*dt*k1/27+2*dt*k2-3544*dt*k3/2565+1859*dt*k4/4104-11*dt*k5/40 ,var);

x = x+ dt*(k1*25/216 + k3*1408/2565 + k4*2197/4104 - k5/5);

by1 = 25*k1/216+1408*k3/2565+2197*k4/4104-k5/5;
by2 = 16*k1/135+6656*k3/12825+28561*k4/56430-9*k5/50+2*k6/55;
errorEstimate = by2-by1;
% errorEstimate = k1/360 - k3*128/4275 - k4*2197/75240 + k5/50 + k6*2/55;
end

