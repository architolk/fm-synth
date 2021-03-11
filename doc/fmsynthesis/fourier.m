Fs = 44100;            % Sampling frequency
T = 1/Fs;             % Sampling period
L = 400;             % Length of signal
t = (0:L-1)*T;        % Time vector
Fc = 440;             % Carrier frequency
R = 5;                % Ratio
Fm = Fc*R;             % Modulation frequency
I = 1;              % Modulation index
X = sin(2*pi*Fc*t + I.*sin(2*pi*Fm*t));

figure (1)
plot(t(1:102),X(1:102))
title('Original signal')
xlabel('t (milliseconds)')
ylabel('X(t)')

Y = fft(X);

f = Fs*(0:(L/2))/L;

Z = 2*abs(Y)/L;

n = 4;
sidamp = besselj(0:n,I);
sidamp = [fliplr(sidamp(2:end)), sidamp];
sidf = (Fc-n*Fm):Fm:(Fc+n*Fm);
sidf(1:4)=-sidf(1:4);
sidamp(1:4) = -sidamp(1:4);

sidamp = abs(sidamp);

figure (3)
plot(f(1:L/2),Z(1:L/2),sidf(1:4),sidamp(1:4),"o",sidf(5:9),sidamp(5:9),"x")
