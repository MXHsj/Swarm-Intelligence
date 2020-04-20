%% fig 17
clc;
clear;
close all;

data = load('data.dat');
agent1 = data(1:5:end-4,:);
agent2 = data(2:5:end-3,:);
agent3 = data(3:5:end-2,:);
agent4 = data(4:5:end-1,:);
agent5 = data(5:5:end,:);

time = 1:1:data(end,1);
figure
plot(time',agent1(:,4),'LineWidth',2);
hold on
grid on
plot(time',agent1(:,4),'LineWidth',2);
plot(time',agent1(:,5),'LineWidth',2);
plot(time',agent2(:,4),'LineWidth',2);
plot(time',agent2(:,5),'LineWidth',2);
plot(time',agent3(:,4),'LineWidth',2);
plot(time',agent3(:,5),'LineWidth',2);
plot(time',agent4(:,4),'LineWidth',2);
plot(time',agent4(:,5),'LineWidth',2);
plot(time',agent5(:,4),'LineWidth',2);
plot(time',agent5(:,5),'LineWidth',2);

xlabel('timestep')
xlim([0 3000])
ylabel('theta')
title('reproduce figure on slide 17')
legend('theta10','theta11','theta20','theta21','theta30', ...
    'theta31','theta40','theta41','theta50','theta51');

%% fig 18
x10 = zeros(length(time),1);
x11 = zeros(length(time),1);
x20 = zeros(length(time),1);
x21 = zeros(length(time),1);
x30 = zeros(length(time),1);
x31 = zeros(length(time),1);
x40 = zeros(length(time),1);
x41 = zeros(length(time),1);
x50 = zeros(length(time),1);
x51 = zeros(length(time),1);

for i = 1:length(time)
    x10(i) = sum(agent1(1:i,3)==0)/i;
end

for i = 1:length(time)
    x11(i) = sum(agent1(1:i,3)==1)/i;
end

for i = 1:length(time)
    x20(i) = sum(agent2(1:i,3)==0)/i;
end

for i = 1:length(time)
    x21(i) = sum(agent2(1:i,3)==1)/i;
end

for i = 1:length(time)
    x30(i) = sum(agent3(1:i,3)==0)/i;
end

for i = 1:length(time)
    x31(i) = sum(agent3(1:i,3)==1)/i;
end

for i = 1:length(time)
    x40(i) = sum(agent4(1:i,3)==0)/i;
end

for i = 1:length(time)
    x41(i) = sum(agent4(1:i,3)==1)/i;
end

for i = 1:length(time)
    x40(i) = sum(agent5(1:i,3)==0)/i;
end

for i = 1:length(time)
    x41(i) = sum(agent5(1:i,3)==1)/i;
end

figure
plot(time',x10,'LineWidth',2);
hold on
grid on
plot(time',x11,'LineWidth',2);
plot(time',x20,'LineWidth',2);
plot(time',x21,'LineWidth',2);
plot(time',x30,'LineWidth',2);
plot(time',x31,'LineWidth',2);
plot(time',x40,'LineWidth',2);
plot(time',x41,'LineWidth',2);
plot(time',x50,'LineWidth',2);
plot(time',x51,'LineWidth',2);

xlabel('timestep')
xlim([0 3000])
ylabel('Xij')
title('reproduce figure on slide 18')
legend('X10','X11','X20','X21','X30','X31','X40','X41','X50','X51');