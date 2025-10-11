close('all','force');
bdclose all;
clear all;

NofElements = 8;
HallSaxLow = 1000;
HallSaxHigh = 3050;


HallSax = HallSaxLow:(HallSaxHigh-HallSaxLow)/(NofElements-1):HallSaxHigh; 
fprintf('float af32_HallSensorSax[] = {');
fprintf('%.0f, ', HallSax); 
fprintf('};\n');

PwmOutCrvPower = 0:1023/(NofElements-1):1023; 

PwmOutCrv = sort(PwmOutCrvPower,'descend'); 
fprintf('float af32_PwmOutCrv[] = {');
fprintf('%.0f, ', PwmOutCrv); 
fprintf('};\n');

plot(HallSax, PwmOutCrv);
hold;
plot(HallSax, PwmOutCrvPower, 'r');
grid on;
xlabel('Hall Sensor');
ylabel('PWM value');

legend('ESP PWM','Real power');

% float af32_HallSensorSax[] = {1000, 1293, 1586, 1879, 2171, 2464, 2757, 3050 };
% float af32_PwmOutCrv[] = {1023, 877, 731, 585, 438, 292, 146, 0 };