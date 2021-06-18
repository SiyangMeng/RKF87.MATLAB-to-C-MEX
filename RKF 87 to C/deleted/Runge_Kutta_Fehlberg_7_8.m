%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% embedded_fehlberg_7_8                                                      
%                                                                            
%  Description:                                                              
%     The Runge-Kutta-Fehlberg method is an adaptive procedure for approxi-  
%     mating the solution of the differential equation y'(x) = f(x,y) with   
%     initial condition y(x0) = c.  This implementation evaluates f(x,y)     
%     thirteen times per step using embedded seventh order and eight order   
%     Runge-Kutta estimates to estimate the not only the solution but also   
%     the error.                                                             
%     The next step size is then calculated using the preassigned tolerance  
%     and error estimate.                                                    
%     For step i+1,                                                          
%        y[i+1] = y[i] +  h * (41/840 * k1 + 34/105 * k6 + 9/35 * k7         
%                        + 9/35 * k8 + 9/280 * k9 + 9/280 k10 + 41/840 k11 ) 
%     where                                                                  
%     k1 = f( x[i],y[i] ),                                                   
%     k2 = f( x[i]+2h/27, y[i] + 2h*k1/27),                                  
%     k3 = f( x[i]+h/9, y[i]+h/36*( k1 + 3 k2) ),                            
%     k4 = f( x[i]+h/6, y[i]+h/24*( k1 + 3 k3) ),                            
%     k5 = f( x[i]+5h/12, y[i]+h/48*(20 k1 - 75 k3 + 75 k4)),                
%     k6 = f( x[i]+h/2, y[i]+h/20*( k1 + 5 k4 + 4 k5 ) ),                    
%     k7 = f( x[i]+5h/6, y[i]+h/108*( -25 k1 + 125 k4 - 260 k5 + 250 k6 ) ), 
%     k8 = f( x[i]+h/6, y[i]+h*( 31/300 k1 + 61/225 k5 - 2/9 k6              
%                                                            + 13/900 K7) )  
%     k9 = f( x[i]+2h/3, y[i]+h*( 2 k1 - 53/6 k4 + 704/45 k5 - 107/9 k6      
%                                                      + 67/90 k7 + 3 k8) ), 
%     k10 = f( x[i]+h/3, y[i]+h*( -91/108 k1 + 23/108 k4 - 976/135 k5        
%                             + 311/54 k6 - 19/60 k7 + 17/6 K8 - 1/12 k9) ), 
%     k11 = f( x[i]+h, y[i]+h*( 2383/4100 k1 - 341/164 k4 + 4496/1025 k5     
%          - 301/82 k6 + 2133/4100 k7 + 45/82 K8 + 45/164 k9 + 18/41 k10) )  
%     k12 = f( x[i], y[i]+h*( 3/205 k1 - 6/41 k6 - 3/205 k7 - 3/41 K8        
%                                                   + 3/41 k9 + 6/41 k10) )  
%     k13 = f( x[i]+h, y[i]+h*( -1777/4100 k1 - 341/164 k4 + 4496/1025 k5    
%                      - 289/82 k6 + 2193/4100 k7 + 51/82 K8 + 33/164 k9 +   
%                                                        12/41 k10 + k12) )  
%     x[i+1] = x[i] + h.                                                     
%                                                                            
%     The error is estimated to be                                           
%        err = -41/840 * h * ( k1 + k11 - k12 - k13)                         
%     The step size h is then scaled by the scale factor                     
%         scale = 0.8 * | epsilon * y[i] / [err * (xmax - x[0])] | ^ 1/7     
%     The scale factor is further constrained 0.125 < scale < 4.0.           
%     The new step size is h := scale * h.                                   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [y, out, h_next] = Runge_Kutta_Fehlberg_7_8( y0, x, h, xmax, tolerance)

ATTEMPTS = 12;
MIN_SCALE_FACTOR = 0.125;
MAX_SCALE_FACTOR = 4.0;

err_exponent = 1.0/7.0;
last_interval = 0;

% Verify that the step size is positive and that the upper endpoint %
% of integration is greater than the initial enpoint.               %

if (xmax < x || h <= 0.0)
    y = y0;
    out = -2;
    h_next = h;
    return
end
   
% If the upper endpoint of the independent variable agrees with the %
% initial value of the independent variable.  Set the value of the  %
% dependent variable and return success.                            %
h_next = h;
y = y0;
if (xmax == x)
    y = y0;
    out = 0;
    h_next = h;
    return
end

% Insure that the step size h is not larger than the length of the %
% integration interval.                                            %
if (h > (xmax - x)) 
    h = xmax - x;
    last_interval = 1;
end

% Redefine the error tolerance to an error tolerance per unit    %
% length of the integration interval.                            %
tolerance = tolerance/(xmax - x);

% Integrate the diff eq y'=f(x,y) from x=x to x=xmax trying to  %
% maintain an error less than tolerance * (xmax-x) using an     %
% initial step size of h and initial value: y = y[0]            %
temp_y0 = y0;
while (x < xmax)
      scale = 1.0;
      for i = 1:ATTEMPTS
         [temp_y, err] = RKF87( temp_y0, x, h);
         err = norm(err);
         if (err == 0.0)
             scale = MAX_SCALE_FACTOR;
             break
         end
         if (norm(temp_y0) == 0.0)
             yy = tolerance;
         else
             yy = norm(temp_y0);
         end
         scale = 0.8*(tolerance*yy/err)^err_exponent;
         scale = min( max(scale,MIN_SCALE_FACTOR), MAX_SCALE_FACTOR);
         if (err < (tolerance*yy))
             break
         end
         h = h * scale;
         if ( x + h > xmax )
             h = xmax - x;
         elseif ( x + h + 0.5 * h > xmax )
             h = 0.5 * h;
         end
      end
      if (i >= ATTEMPTS)
          h_next = h * scale;
          out = -1;
          return
      end
      temp_y0 = temp_y;         
      x = x + h;
      h = h * scale;
      h_next = h;
      if (last_interval)
          break
      end
      if (x+h > xmax)
          last_interval = 1;
          h = xmax - x;
      elseif (x+h+0.5*h > xmax)
          h = 0.5 * h;
      end
end
y = temp_y0;
out = 0;

end


