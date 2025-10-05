af32_potValInX = [0, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4096];
af32_PwmOutY = [0, 50, 100, 200, 300, 400, 500, 750, 1023];

plot(af32_potValInX, af32_PwmOutY);
grid on;
xlabel('Potmeter');
ylabel('PWM value');