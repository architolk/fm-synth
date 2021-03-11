Fs = 22050;            % Sampling frequency
T = 1/Fs;             % Sampling period
L = 1500;             % Length of signal
t = (0:L-1)*T;        % Time vector
Fc = 440;             % Carrier frequency
R = 3;                % Ratio
Fm = Fc*R;             % Modulation frequency
I = 1.0;              % Modulation index
X = sin(2*pi*Fc*t + I.*sin(2*pi*Fm*t));

figure (1)
plot(t(1:100),X(1:100))
title('Original signal')
xlabel('t (milliseconds)')
ylabel('X(t)')

Y = fft(X);

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;

figure (2)
plot(f,P1)
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')
