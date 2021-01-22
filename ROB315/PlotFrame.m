function PlotFrame(q)
    %% initialization
    alpha = [0,pi/2,0,pi/2,-pi/2,pi/2];
    d = [0,0,0.7,0,0,0];
    r = [0.5,0,0,0.2,0,0.1];
    theta = [q(1),q(2),pi/2+q(3),q(4),q(5),q(6)];
    direction =eye(3);
    StartPos = zeros(3);
    
    %%axe drawing for start position
    x = [1;0;0];
    y = [0;1;0];
    z = [0;0;1];
    ox = 0.15 * direction * x;
    oy = 0.15 * direction * y;
    oz = 0.15 * direction * z;
    id = 'o';
    c = 'red';
    plot3([StartPos(1),StartPos(1)+ ox(1)],[StartPos(2),StartPos(2)+ ox(2)] ...
        ,[StartPos(3),StartPos(3)+ ox(3)],c,'LineWidth',1);
    text(0.05 +StartPos(1)+ox(1),0.05 +StartPos(2)+ox(2),0.05 +StartPos(3)+ox(3), ...
        strcat('x',id),'Color', c);
    hold on
    plot3([StartPos(1),StartPos(1)+ oy(1)],[StartPos(2),StartPos(2)+ oy(2)] ...
        ,[StartPos(3),StartPos(3)+ oy(3)],c,'LineWidth',1);
    hold on
    text(0.05 +StartPos(1)+oy(1),0.05 +StartPos(2)+oy(2),0.05 +StartPos(3)+oy(3), ...
        strcat('y',id),'Color', c);
    plot3([StartPos(1),StartPos(1)+ oz(1)],[StartPos(2),StartPos(2)+ oz(2)] ...
        ,[StartPos(3),StartPos(3)+ oz(3)],c,'LineWidth',1);
    text(0.05 +StartPos(1)+oz(1),0.05 +StartPos(2)+oz(2),0.05 +StartPos(3)+oz(3), ...
        strcat('z',id),'Color', c);
    hold on
    
    %%graph drawing
    scatter3(StartPos(1),StartPos(2),StartPos(3),'black','filled');
    hold on
    for i = 1:length(q)
        g = TransformMatElem(alpha(i),d(i),theta(i),r(i));
        EndPos = StartPos + direction * g(1:3,4);
        direction = direction*g(1:3,1:3);
        plot3([StartPos(1),EndPos(1)],[StartPos(2),EndPos(2)],[StartPos(3),EndPos(3)],'black','LineWidth',2);
        hold on
        StartPos = EndPos;
        scatter3(StartPos(1),StartPos(2),StartPos(3),'black','filled');
        hold on
    end
    
    %%axe drawing for end position
    x = [1;0;0];
    y = [0;1;0];
    z = [0;0;1];
    ox = 0.15 * direction * x;
    oy = 0.15 * direction * y;
    oz = 0.15 * direction * z;
    id = 'e';
    c = 'blue';
    plot3([StartPos(1),StartPos(1)+ ox(1)],[StartPos(2),StartPos(2)+ ox(2)] ...
        ,[StartPos(3),StartPos(3)+ ox(3)],c,'LineWidth',1);
    text(0.05 +StartPos(1)+ox(1),0.05 +StartPos(2)+ox(2),0.05 +StartPos(3)+ox(3), ...
        strcat('x',id),'Color', c);
    hold on
    plot3([StartPos(1),StartPos(1)+ oy(1)],[StartPos(2),StartPos(2)+ oy(2)] ...
        ,[StartPos(3),StartPos(3)+ oy(3)],c,'LineWidth',1);
    hold on
    text(0.05 +StartPos(1)+oy(1),0.05 +StartPos(2)+oy(2),0.05 +StartPos(3)+oy(3), ...
        strcat('y',id),'Color', c);
    plot3([StartPos(1),StartPos(1)+ oz(1)],[StartPos(2),StartPos(2)+ oz(2)] ...
        ,[StartPos(3),StartPos(3)+ oz(3)],c,'LineWidth',1);
    text(0.05 +StartPos(1)+oz(1),0.05 +StartPos(2)+oz(2),0.05 +StartPos(3)+oz(3), ...
        strcat('z',id),'Color', c);
    hold on
    
    xlabel('x');
    ylabel('y');
    zlabel('z');
    grid on;
    axis equal;
    view(-135,45)

end