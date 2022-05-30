t=0;
dt=8e-9;
amp=10;
tau = 1e-7;
signal_time = 1e-6;
clear x
n=1;
for t=0:dt:signal_time
    ex = t / tau;
    ep(n) = t / tau;
    d = exp(-ep(n));
    x(n) = amp * d;
    n = n + 1;
end
