# RKF87.MATLAB-to-C-MEX
Use MATLAB Coder to generate C code and MEX file for MATLAB, an example of RK45 and RKF87 for numerical integration。 

The purpose of numerical integration in this blog is to solve the initial value problem of ordinary differential equations, that is, to solve the following problems
$$
\dot{\boldsymbol{x}}=\boldsymbol{f}[\boldsymbol{x}(t), t,p]\\
t_0给定,已知\boldsymbol{x}(t_0),t\in[t_0,t_f]<Empty \space Math \space Block>
$$
Where $p$ on the right side of the equation represents one or more parameters. The purpose of this blog is to build C programs that quickly calculate ode results and call them in MATLAB.



RK-4的是使用最多的，其具体的单步迭代格式为：
$$
\begin{aligned}
x_{i+1} &=x_{i}+\frac{h}{6}\left(K_{1}+2 K_{2}+2 K_{3}+K_{4}\right) \\
K_{1} &=f\left(t_{i}, x_{i}\right) \\
K_{2} &=f\left(t_{i}+\frac{h}{2}, x_{i}+\frac{h}{2} K_{1}\right) \\
K_{3} &=f\left(t_{i}+\frac{h}{2}, x_{i}+\frac{h}{2} K_{2}\right) \\
K_{4} &=f\left(t_{i}+h, x_{i}+h K_{3}\right)
\end{aligned}
$$
多步计算法，一个时间区间内$[t_i,t_{i+1}]$内会进行多次RK4求解。RK45不同于RK4，还加了一个估计精度的步骤，以此确定下一步变步长的长度，然后进行多步求解。这个算法也叫Runge-Kutta-Fehlberg 4(5) ，也就是MATLAB自带函数``[T,Y,TE,YE,IE] = ode45(odefun,tspan,y0,options)``所采用的算法，它的核心部分是以下代码：

```matlab
function [x, errorEstimate] = RK45( x, t, dt ,var)
% REFERENCE1: https://github.com/recalon/rkf_calon/rkf_calon.cpp
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
```

对应C函数可以查看[GitHub: kf_calon/rkf_calon.cpp](https://github.com/recalon/rkf_calon/blob/master/rkf_calon.cpp) .

The ode equation used here is a two body gravitational field orbital dynamics problem:


$$
\left\{\begin{array}{l}
\dot{\boldsymbol{r}}=\boldsymbol{v} \\
\dot{\boldsymbol{v}}=-\frac{\mu}{r^{3}} \boldsymbol{r}
\end{array}\right.
$$
calls for the  MATLAB function``[ts,yout,tf,yend] = wrapRK45(tspan,y_0,options,var);``测试算法是否无误，以便后续转为C代码。

### 测试

要调用.mex64里的函数而不是原来的.m源文件，应该按照``mexFileName('functionName',allParametersInPut)``这样的调用格式，即``[ts,yout,tf,yend] = RK45_mex('wrapRK45',tspan,y_0,options,var);``。

建立testMEX.m脚本进行测试，固定步长计算结果如下：

```
Fixed step test

>>时间已过 0.039140 秒。
 Runge-Kutta-45 .MEX64 version; results calculation step: 61
 Accuracy    Digits
1.74e-12    11.76

>>时间已过 0.471013 秒。
 ode45 MATLAB; results calculation step: 61
 Accuracy    Digits
8.57e-11    10.07
```

可见运算速度相较其.m文件版本提高了$1.00/0.04=25$倍，精度也略高、

以下测试变步长.mex版本：

```
Variable step test

时间已过 0.152232 秒。
 Runge-Kutta-45 .MEX64 version; results calculation step: 7090
 Accuracy    Digits
2.13e-10     9.67

时间已过 0.618282 秒。
 ode45 MATLAB; results calculation step: 28025
 Accuracy    Digits
8.57e-11    10.07
```

可见由于我没有更改动态分配内存这一部分的源代码，其计算效率只和ode45大致一样。如果能优化好C语言代码，再重新用mex编译一个.mex64动态库，计算效率应该会好一点。当然，MATLAB Coder转C语言只能说是给C程序编写打下了一个基础，其中的关键代码是可能复用的。这只能在.m文件较为简单的情况下起效，否则其复杂的调用框架和数据结构并不会比.m文件快多少。