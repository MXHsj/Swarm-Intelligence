%% generate figures
clc; clear; close all;

tunnel_data = load('data.dat');
agent1 = tunnel_data(1:10:end-9,:);
agent2 = tunnel_data(2:10:end-8,:);
agent3 = tunnel_data(3:10:end-7,:);
agent4 = tunnel_data(4:10:end-6,:);
agent5 = tunnel_data(5:10:end-5,:);
agent6 = tunnel_data(6:10:end-4,:);
agent7 = tunnel_data(7:10:end-3,:);
agent8 = tunnel_data(8:10:end-2,:);
agent9 = tunnel_data(9:10:end-1,:);
agent10 = tunnel_data(10:10:end,:);

time = 1:1:tunnel_data(end,1);

% plot internal agent position
figure
plot(agent1(:,4),agent1(:,3),'LineWidth',1);
hold on
grid on
plot(agent2(:,4),agent2(:,3),'LineWidth',1);
plot(agent3(:,4),agent3(:,3),'LineWidth',1);
plot(agent4(:,4),agent4(:,3),'LineWidth',1);

line([-3 -3],[-2,-0.8],'color','black','LineWidth',2);
line([-3 -3],[0.8,2],'color','black','LineWidth',2);
line([3 3],[-2,-0.8],'color','black','LineWidth',2);
line([3 3],[0.8,2],'color','black','LineWidth',2);
line([-1 -1],[-1,-0.8],'color','black','LineWidth',2);
line([-1 -1],[0.8,1],'color','black','LineWidth',2);
line([1 1],[-1,-0.8],'color','black','LineWidth',2);
line([1 1],[0.8,1],'color','black','LineWidth',2);

line([-3 -1],[-0.8,-0.8],'color','black','LineWidth',2);
line([-3 -1],[0.8,0.8],'color','black','LineWidth',2);
line([1 3],[-0.8,-0.8],'color','black','LineWidth',2);
line([1 3],[0.8,0.8],'color','black','LineWidth',2);
line([-1 1],[-1,-1],'color','black','LineWidth',2);
line([-1 1],[1,1],'color','black','LineWidth',2);

xlabel('y [m]')
ylabel('x [m]')
xlim([-6 6])
ylim([-2 2])
title('internal agents position in X-Y plane')
legend('agent0','agent1','agent2','agent3');


figure
plot(agent5(:,4),agent5(:,3),'LineWidth',1);
hold on
grid on
plot(agent6(:,4),agent6(:,3),'LineWidth',1);
plot(agent7(:,4),agent7(:,3),'LineWidth',1);
plot(agent8(:,4),agent8(:,3),'LineWidth',1);
plot(agent9(:,4),agent9(:,3),'LineWidth',1);
plot(agent10(:,4),agent10(:,3),'LineWidth',1);   

line([-3 -3],[-2,-0.8],'color','black','LineWidth',2);
line([-3 -3],[0.8,2],'color','black','LineWidth',2);
line([3 3],[-2,-0.8],'color','black','LineWidth',2);
line([3 3],[0.8,2],'color','black','LineWidth',2);
line([-1 -1],[-1,-0.8],'color','black','LineWidth',2);
line([-1 -1],[0.8,1],'color','black','LineWidth',2);
line([1 1],[-1,-0.8],'color','black','LineWidth',2);
line([1 1],[0.8,1],'color','black','LineWidth',2);

line([-3 -1],[-0.8,-0.8],'color','black','LineWidth',2);
line([-3 -1],[0.8,0.8],'color','black','LineWidth',2);
line([1 3],[-0.8,-0.8],'color','black','LineWidth',2);
line([1 3],[0.8,0.8],'color','black','LineWidth',2);
line([-1 1],[-1,-1],'color','black','LineWidth',2);
line([-1 1],[1,1],'color','black','LineWidth',2);

xlabel('y [m]')
ylabel('x [m]')
xlim([-6 6])
ylim([-2 2])
title('external agents position in X-Y plane')
legend('agent4','agent5','agent6','agent7','agent8','agent9');
   

% % plot TARGET_KIN
% figure
% plot(time',agent1(:,5),'LineWidth',2);
% hold on
% grid on
% plot(time',agent2(:,5),'LineWidth',2);
% plot(time',agent3(:,5),'LineWidth',2);
% plot(time',agent4(:,5),'LineWidth',2);
% % plot(time',agent5(:,5),'LineWidth',2);
% % plot(time',agent6(:,5),'LineWidth',2);
% % plot(time',agent7(:,5),'LineWidth',2);
% % plot(time',agent8(:,5),'LineWidth',2);
% % plot(time',agent9(:,5),'LineWidth',2);
% % plot(time',agent10(:,5),'LineWidth',2);
% 
% xlabel('time step')
% xlim([0 2500])
% ylabel('TARGET_NONKIN')
% ylim([0 40])
% legend('agent0','agent1','agent2','agent3')
%    
%    
% % plot TARGET_NONKIN
% figure
% % plot(time',agent1(:,6),'LineWidth',1.5);
% % plot(time',agent2(:,6),'LineWidth',1.5);
% % plot(time',agent3(:,6),'LineWidth',1.5);
% % plot(time',agent4(:,6),'LineWidth',1.5);
% plot(time',agent5(:,6),'LineWidth',1.5);
% hold on
% grid on
% plot(time',agent6(:,6),'LineWidth',1.5);
% plot(time',agent7(:,6),'LineWidth',1.5);
% plot(time',agent8(:,6),'LineWidth',1.5);
% plot(time',agent9(:,6),'LineWidth',1.5);
% plot(time',agent10(:,6),'LineWidth',1.5);
% 
% xlabel('time step')
% xlim([0 2500])
% ylabel('TARGET_NONKIN')
% ylim([15 50])
% legend('agent4','agent5','agent6','agent7','agent8','agent9', ...
%        'Location','SouthEast');
