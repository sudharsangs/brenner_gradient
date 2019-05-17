function [bren] = calcbren(handles)
poutImage = imread('pout.png');
[M, N] = size(double(poutImage));
        DH = zeros(M, N);
        DV = zeros(M, N);
        DV(1:M-2,:) = poutImage(3:end,:)-poutImage(1:end-2,:);
        DH(:,1:N-2) = poutImage(:,3:end)-poutImage(:,1:end-2);
        FM = max(DH, DV);        
        FM = FM.^2;
        bren = mean2(FM);
        
set(handles.brenDisp,'String',num2str(bren));

