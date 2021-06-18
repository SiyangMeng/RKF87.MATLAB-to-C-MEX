%--------------------------------------------------------------------------
%
% State: Computes the satellite state vector from osculating Keplerian
%        elements for elliptic orbits
%
% Inputs:
%   gm        Gravitational coefficient
%   Kep       Keplerian elements (a,e,i,Omega,omega,M) with
%               a      Semimajor axis 
%               e      Eccentricity 
%               i      Inclination [rad]
%               Omega  Longitude of the ascending node [rad]
%               omega  Argument of pericenter  [rad]
%               M      Mean anomaly at epoch [rad]
%   dt        Time since epoch
% 
% Output:
%   Y         State vector (x,y,z,vx,vy,vz)
%
% Notes:
%   The semimajor axis a=Kep(0), dt and gm must be given in consistent
%   units, e.g. [m], [s] and [m^3/s^2]. The resulting units of length and
%   velocity are implied by the units of gm, e.g. [m] and [m/s].
% 
% Last modified:   2018/01/27   M. Mahooti
%--------------------------------------------------------------------------
function Y = State(gm, Kep, dt)

% Keplerian elements at epoch
a = Kep(1);  Omega = Kep(4);
e = Kep(2);  omega = Kep(5);
i = Kep(3);  M0    = Kep(6);

% Mean anomaly
if (dt==0)
    M = M0;
else
    n = sqrt (gm/(a*a*a));
    M = M0 +n*dt;
end

% Eccentric anomaly
E = EccAnom(M,e);

cosE = cos(E);
sinE = sin(E);

% Perifocal coordinates
fac = sqrt((1-e)*(1+e));

R = a*(1-e*cosE);  % Distance
V = sqrt(gm*a)/R;    % Velocity

r = [a*(cosE-e), a*fac*sinE , 0]';
v = [-V*sinE   , +V*fac*cosE, 0]';

% Transformation to reference system (Gaussian vectors)
PQW = R_z(-Omega) * R_x(-i) * R_z(-omega);

r = PQW*r;
v = PQW*v;

Y = [r;v];
end
%--------------------------------------------------------------------------
%  Input:
%    angle       angle of rotation [rad]
%
%  Output:
%    rotmat      rotation matrix
%
% Last modified:   2018/01/27   M. Mahooti
%--------------------------------------------------------------------------
function rotmat = R_x(angle)

C = cos(angle);
S = sin(angle);
rotmat = zeros(3,3);

rotmat(1,1) = 1.0;  rotmat(1,2) =    0.0;  rotmat(1,3) = 0.0;
rotmat(2,1) = 0.0;  rotmat(2,2) =      C;  rotmat(2,3) =   S;
rotmat(3,1) = 0.0;  rotmat(3,2) = -1.0*S;  rotmat(3,3) =   C;
end
%--------------------------------------------------------------------------
%  Input:
%    angle       angle of rotation [rad]
%
%  Output:
%    rotmat      rotation matrix
%
% Last modified:   2018/01/27   M. Mahooti
%--------------------------------------------------------------------------
function rotmat = R_y(angle)

C = cos(angle);
S = sin(angle);
rotmat = zeros(3,3);

rotmat(1,1) =   C;  rotmat(1,2) = 0.0;  rotmat(1,3) = -1.0*S;
rotmat(2,1) = 0.0;  rotmat(2,2) = 1.0;  rotmat(2,3) =    0.0;
rotmat(3,1) =   S;  rotmat(3,2) = 0.0;  rotmat(3,3) =      C;

end
%--------------------------------------------------------------------------
%  Input:
%    angle       angle of rotation [rad]
%
%  Output:
%    rotmat      rotation matrix
%
% Last modified:   2018/01/27   M. Mahooti
%--------------------------------------------------------------------------
function rotmat = R_z(angle)

C = cos(angle);
S = sin(angle);
rotmat = zeros(3,3);

rotmat(1,1) =      C;  rotmat(1,2) =   S;  rotmat(1,3) = 0.0;
rotmat(2,1) = -1.0*S;  rotmat(2,2) =   C;  rotmat(2,3) = 0.0;
rotmat(3,1) =    0.0;  rotmat(3,2) = 0.0;  rotmat(3,3) = 1.0;

end