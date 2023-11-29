close all;
clear all; 

s = serial('COM4','Baudrate',115200);
fopen(s);
j = 1;

plotting data Flex sensor
while (j<=200)  
    data = fscanf(s);
    L = length(data);
    for i=1:L
        if (data(i) == 'a')
           flex1(j) = str2double(data(i+1:i+3));
        elseif (data(i) == 'b')
           flex2(j) = str2double(data(i+1:i+3));
        elseif (data(i) == 'c')
           flex3(j) = str2double(data(i+1:i+3));
        elseif (data(i) == 'd')
           flex4(j) = str2double(data(i+1:i+3));
        elseif (data(i) == 'e')
           flex5(j) = str2double(data(i+1:i+3));
        elseif (data(i) == 'f')
            break;
        end
    end
    figure(1)
    plot(flex1,'r');
    ylim([450 600]);
    
    
%     figure(2)
%     plot(flex2,'r');
%     ylim([500 650]);
%     
%     figure(3)
%     plot(flex3,'r');
%     ylim([500 650]);
%     
%     figure(4)
%     plot(flex4,'r');
%     ylim([500 650]);
%     
%     figure(5)
%     plot(flex5,'r');
%     ylim([300 400]); 
    
    pause(0.01);
    j=j+1;
end

fclose(s);
delete (s);
clear s;

filter_flex1 = mean(flex1);
figure(1)
line([0,1000],[filter_flex1,filter_flex1]);

filter_flex2 = mean(flex2);
figure(2)
line([0,1000],[filter_flex2,filter_flex2]);

filter_flex3 = mean(flex3);
figure(3)
line([0,1000],[filter_flex3,filter_flex3]);

filter_flex4 = mean(flex4);
figure(4)
line([0,1000],[filter_flex4,filter_flex4]);

filter_flex5 = mean(flex5);
figure(5)
line([0,1000],[filter_flex5,filter_flex5]);

%---------Calib ACC MPU6050--------
% while (j<=400)
%     data = fscanf(s);
%     L = length(data);
%     for i=1:L
%         if (data(i) == 'a')
%            for x=i+1:i+7
%                if (data(x) == 'b')
%                     accX(j) = str2double(data(i+1:x-1));
%                     break;
%                end
%            end
%         elseif (data(i) == 'b')
%            for y=i+1:i+7
%                if (data(y) == 'c')
%                     accY(j) = str2double(data(i+1:y-1));
%                     break;
%                end
%            end
%         elseif (data(i) == 'c')
%            for z=i+1:i+7
%                if (data(z) == 'd')
%                     accZ(j) = str2double(data(i+1:z-1));
%                     break;
%                end
%            end
%         elseif (data(i) == 'd')
%             break;
%         end
%     end
%     figure(1)
%     plot(accX,'r');
%     hold on;
%     plot(accY,'b');
%     hold on;
%     plot(accZ,'g');
%     ylim([-2.2 2.2]);
%     
%     pause(0.1);
%     j=j+1;
% end
% 
% legend('accX','accY','accZ');
% fclose(s);
% delete (s);
% clear s;

%---------Angle MPU 6050-----------%
% while (j<=200)
%     data = fscanf(s);
%     L = length(data);
%     for i=1:L
%         if (data(i) == 'a')
%            for x=i+1:i+7
%                if (data(x) == 'b')
%                     angleX(j) = str2double(data(i+1:x-1));
%                     break;
%                end
%            end
%         elseif (data(i) == 'b')
%            for y=i+1:i+7
%                if (data(y) == 'c')
%                     angleY(j) = str2double(data(i+1:y-1));
%                     break;
%                end
%            end
%         elseif (data(i) == 'c')
%             break;
%         end
%     end
%     figure(1)
%     plot(angleX,'r');
%     hold on;
%     plot(angleY,'b');
%     ylim([-200 200]);
%     
%     pause(0.01);
%     j=j+1;
% end
% 
% legend('angleX','angleY');
% fclose(s);
% delete (s);
% clear s;
