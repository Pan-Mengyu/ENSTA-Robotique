function [OJv_Gi, OJ_wi] = CalculMatriceJacobienneGi(alpha, d, theta, r, x_G, y_G, z_G)
 
    %Initialisation
    rE = [0,0,0,0,0,0.1];
    J = ComputeJac(alpha, d, theta, r+rE); %Matrice jacobienne du robot
    
    OJ_Oi = zeros(size(J,1), size(J,2), size(J,2));
    OJ_Gi = zeros(size(J,1), size(J,2), size(J,2));
    OJv_Gi = zeros(3, size(J,2), size(J,2));  
    OJ_wi = zeros(3, size(J,2), size(J,2));
    ROi = zeros(3,3,size(J,2));
    g_0i = eye(4);
    
    % Vecteur de position de l'organe effecteur dans R0:  
    
    g_06 = ComputeDGM(alpha, d, theta, r);
    rE = 0.1;
    g_6E = TransformMatElem(0,0,0,rE);
    g_0E = g_06 *g_6E;
    O0OE = g_0E(1:3, 4);
    OEO0 = -O0OE;
    
    O0Oi = zeros(3,1,6);
    
    %Boucle sur les corps
    for i = 1:size(J,2)
        %Construction de toutes les matrices jacobiennes des corps Ci
        %exprimee au centre Oi du repere Ri attache a Ci
        OJ_Oi(:,1:i,i) = J(:,1:i);
        %Vecteur OiGi exprim¨¦ dans Ri
        iOiGi = [x_G(i) y_G(i) z_G(i)]';
        %Matrice de rotation ROi du rep¨¨re R0 ¨¤ Ri
        g_elem = TransformMatElem(alpha(i), d(i), theta(i), r(i));
        %Matrice de transformation ¨¦l¨¦mentaire de passage de C(i-1)
        g_0i = g_0i*g_elem;
        ROi(:,:,i) = g_0i(1:3,1:3);
        %Vecteur OEGi dans RO ¨¤  calculer: OEGi = OEOi + OiGi
        %Vecteur OiGi exprim¨¦ dans R0
        OOiGi = ROi(:,:,i)*iOiGi;
        %Vecteur OEOi exprim¨¦ dans R0: OEOi = OEO0 + O0Oi
        O0Oi(:,:,i) = g_0i(1:3,4);
        OEOi = OEO0 + O0Oi(:,:,i);
        OOEGi = OEOi + OOiGi;
        OPreproduitVect_OEGi = [0 -OOEGi(3) OOEGi(2);...
                                OOEGi(3) 0 -OOEGi(1);...
                                -OOEGi(2) OOEGi(1) 0];
        %Formule de Varignon
        OJ_Gi(:,:,i) =  [eye(3) -OPreproduitVect_OEGi;...
                        zeros(3,3) eye(3)]*OJ_Oi(:,:,i);
        
        %Resultats
        OJv_Gi(:,:,i) = OJ_Gi(1:3,:,i);
        OJ_wi(:,:,i) = OJ_Gi(4:6,:,i);
    end
end