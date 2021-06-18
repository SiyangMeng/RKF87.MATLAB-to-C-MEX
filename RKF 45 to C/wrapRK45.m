%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
%     k1 = f( x[i],y[i],var ),
%     k2 = f( x[i]+h/2, y[i] + k1*dt/2,var),
%     k3 = f( x[i]+h/2, y[i]+k2*dt/2 ,var),
%     k4 = f( x[i]+h, y[i]+k3*dt/2 ,var),
%     x[i+1] = x[i] + h.
%
%     The error is estimated to be
%        err = -41/840 * h * ( k1 + k11 - k12 - k13)
%     The step size h is then scaled by the scale factor
%         scale = 0.8 * | epsilon * y[i] / [err * (xmax - x[0])] | ^ 1/7
%     The scale factor is further constrained 0.125 < scale < 4.0.
%     The new step size is h := scale * h.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [tspan,yout,tf,yend] = wrapRK45(t0tf,yinit,options,var)
% this function is slightly Differentfrom the format of MATLAB
% [T,Y,TE,YE,IE] = solver(odefun,tspan,y0,options)
% options = odeset('RelTol',1e-13,'AbsTol',1e-13,...);
t0=t0tf(1);
tf=t0tf(end);
MaxStep=options.MaxStep;
% as the length of tspan is not known, it is allocated by the biggest
% stepsize, and the more lengths will be deleted
if(isempty(MaxStep))
    MaxStep=0.1*(tf-t0);
end
tolerance=options.RelTol;
if(length(t0tf)==2)
    tspan=[t0:MaxStep:tf]';
    if(tspan(end)<tf)
        tspan=[tspan;tf];
    end
    variableStepOutPut=true;
else
    tspan=t0tf;
    variableStepOutPut=false;
end

% Integration from t=t0 to t=tf
num = length(tspan);
yout = zeros(num,length(yinit));
yout(1,:) = yinit;
yend=reshape(yinit,length(yinit),1);% to column vector
ytemp=reshape(yend,1,length(yend));% to row vector
if(variableStepOutPut)
    % variable stepsize and multiple step in a horizon
    dt=MaxStep;
    tnext=t0+dt;
    ii=1;
    while tspan(ii)<tf
        [yend, out, dtAttemptVar] = multiStepRK45( yend, tspan(ii), dt, tnext, tolerance,var);
        dt=dtAttemptVar;
        ii=ii+1;
        if (ii>num)
            tspan=[tspan;tnext]; 
            yout =[yout;yend'];
            num=num+1;
        else
            tspan(ii)=tnext;
            yout(ii,:) = yend';
        end
        tnext=tnext+dt;
        if tnext>tf
            tnext=tf;
            dt=tf-tspan(ii);
        end
    end
    if ii<num
        tspan(ii+1:num)=[];
        yout(ii+1:num,:)=[];
    end
else
% variable stepsize and multiple step in a horizon
    dtAttemptVar=MaxStep;
    for ii = 1:num-1
        [yend, out, dtAttemptVar] = multiStepRK45( yend, tspan(ii), dtAttemptVar, tspan(ii+1), tolerance,var);
        yout(ii+1,:) = yend';
    end
end
yend=reshape(yend,size(yinit));% to the same size as yinit
end



function [x, out, h_next] = multiStepRK45( x0, t0, dt, tf, RelTol,var)

ATTEMPTS_FROM_T0_2_TF = 12;
MIN_SCALE_FACTOR = 0.125;
MAX_SCALE_FACTOR = 4.0;

err_exponent = 1.0/4.0;
last_interval = 0;

% Verify that the step size is positive and that the upper endpoint %
% of integration is greater than the initial enpoint.               %

if (tf < t0 || dt <= 0.0)
    x = x0;
    out = -2;
    h_next = dt;
    return
end

% If the upper endpoint of the independent variable agrees with the %
% initial value of the independent variable.  Set the value of the  %
% dependent variable and return success.                            %
h_next = dt;
x = x0;
if (tf == t0)
    x = x0;
    out = 0;
    h_next = dt;
    return
end

% Insure that the step size h is not larger than the length of the %
% integration interval.                                            %
if (dt > (tf - t0))
    dt = tf - t0;
    last_interval = 1;
end

% Redefine the error tolerance to an error tolerance per unit    %
% length of the integration interval.                            %
RelTol = RelTol/(tf - t0);

% Integrate the diff eq x'=f(t,x) from t=t0 to t=tf trying to  %
% maintain an error less than tolerance * (tf-t0) using an     %
% initial step size of h and initial value: x = x[0]            %
temp_x0 = x0;
while (t0 < tf)
    scale = 1.0;
    for i = 1:ATTEMPTS_FROM_T0_2_TF
        [temp_x, err] = RK45( temp_x0, t0, dt,var);
        err = norm(err);
        if (err == 0.0)
            scale = MAX_SCALE_FACTOR;
            break
        end
        if (norm(temp_x0) == 0.0)
            yy = RelTol;
        else
            yy = norm(temp_x0);
        end
        scale = 0.84*power(RelTol*yy/err,err_exponent);
        scale = min( max(scale,MIN_SCALE_FACTOR), MAX_SCALE_FACTOR);
        if (err < (RelTol*yy))
            break
        end
        dt = dt * scale;
        if ( t0 + dt > tf )
            dt = tf - t0;
        elseif ( t0 + dt + 0.5 * dt > tf )
            dt = 0.5 * dt;
        end
    end
    if (i >= ATTEMPTS_FROM_T0_2_TF)
        h_next = dt * scale;
        out = -1;
        return
    end
    temp_x0 = temp_x;
    t0 = t0 + dt;
    dt = dt * scale;
    h_next = dt;
    if (last_interval)
        break
    end
    if (t0+dt > tf)
        last_interval = 1;
        dt = tf - t0;
    elseif (t0+dt+0.5*dt > tf)
        dt = 0.5 * dt;
    end
end
x = temp_x0;
out = 0;

end




