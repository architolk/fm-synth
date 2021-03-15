Fs = 44100;            % Sampling frequency
T = 1/Fs;             % Sampling period
L = 1000;             % Length of signal
t = (0:L-1)*T;        % Time vector
Fc = 440;             % Carrier frequency
R = 5;                % Ratio
Fm = Fc*R;             % Modulation frequency
I = 1.4;              % Modulation index
% Regular sine
X = sin(2*pi*Fc*t);
% Feedback loop: from i = 2, using previous value
X(1) = 0;
X(2) = sin(2*pi*Fc*2*T);
for i = 3:L-1
  X(i) = sin(2*pi*Fc*i*T + I*(X((i-2))+ X((i-1)))/2);
end

figure (1)
plot(t(1:102),X(1:102))
title('Original signal')
xlabel('t (milliseconds)')
ylabel('X(t)')

Y = fft(X);

f = Fs*(0:(L/2))/L;

Z = 2*abs(Y)/L;

# Sideband analysis for feedback
n = 1:9
sidamp = 2*besselj(n,I*n)./(I*n);
sidf = n*Fc;

# Plot fourier transformation result and predicted sidebands in the same figure
figure (2)
plot(f(1:L/2),Z(1:L/2),sidf(1:9),sidamp(1:9),"o")
