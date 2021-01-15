%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           TP Filtre Particulaire
%           Nicolas Merlinge (ONERA, TP ENSTA ROB312)
%           Version 2.0
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear % effacer toutes les variables
close all % fermer toutes les fenêtres
clc % effacer la ligne de commande
rng(123457) % imposer la graine de génération de nombres pseudo-aléatoire pour la répétabilit?


% Paramètres initiaux et de simulation
erreurInitiale = sqrt(diag([5000, 5000, 100, 20*pi/180].^2))*randn(4,1);
X_reel = [230000, 90000, 1000, 150*pi/180]' + erreurInitiale; % état vrai initial (inconnu du filtre)    
d = size(X_reel,1); % dimension de l'état
dt = 1; % pas de temps
R = 20.^2; % matrice de covariance du bruit de mesure réelle (inconnu du filtre)
dm = size(R,1); % dimension du vecteur de mesures

% Chargement des données
load carte.mat
params.pasx_reel = pasx_reel;
params.pasy_reel = pasy_reel;
params.nrow_h = size(h_MNT,1);
params.dxh_MNT = diff(h_MNT,1,2)/pasx_reel;
params.dyh_MNT = diff(h_MNT)/pasy_reel;
params.h_MNT = h_MNT;
params.x_MNT = x_MNT;
params.y_MNT = y_MNT;

% Initialisation des variables de stockage des données
tk=1;
t_sim(tk) = 0;
Y_sim(:,tk) = 0;
X_reel_sim(:,tk) = X_reel;

%% Boucle de simulation physique de la trajectoire
T = 80; % durée (s)
for tk = 2:(T/dt)
    % commande (définit la trajectoire)
    V = 300; % Vitesse (connue)
    omega = -0.01; % vitesse angulaire (rad/s) (connue)
    
    % simulation de l'état vrai (attention, inconnu du filtre)
    t = dt*(tk-1); % temps courant
    X_reel = [X_reel(1) + V*dt*cos(X_reel(4)); X_reel(2) + V*dt*sin(X_reel(4)); X_reel(3); X_reel(4) + dt*omega]; % propagation de l'état réel (? compléter)
    X_reel(4) = mod(X_reel(4), 2*pi); % modulo 2pi sur le cap

    X_reel_sim(:,tk) = X_reel;
    t_sim(tk) = t;
end

%% Boucle de simulation physique des mesures
T = 80; % durée (s)
for tk = 2:(T/dt)
    % Récupération de l'état
    X_reel = X_reel_sim(:,tk);
    
    % génération de la mesure réelle    
    Y = X_reel(3,:) - lectureCarte(X_reel, params) + sqrt(R)*randn(dm,1);
    
    Y_sim(:,tk) = Y;
end

%% Boucle du filtre particulaire

% Paramètres du filtre
N = 3000; % nombre de particules
P_hat = diag([5000, 5000, 100, 20*pi/180].^2); % matrice de covariance initiale
X_hat = [230000, 90000, 1000, 150*pi/180]'; % estim? initial (x, y, z, theta)
Qf = diag([3, 3, 0.6, 0.001*180/pi].^2); % matrice de covariance de bruit de dynamique
Rf = 20.^2; % covariance du bruit de mesure du filtre
threshold_resampling = 0.5; % seuil de r?-échantillonnage (theta_eff)

% Initialisation des variables de stockage des données
tk=1;
P_sim(:,:,tk) = P_hat;
Pdiag_sim(:,tk) = diag(P_hat);
X_hat_sim(:,tk) = X_hat;

% Initialisation du filtre
Xp = zeros(4,N)+X_hat+sqrt(diag([5000, 5000, 100, 20*pi/180].^2))*randn(4,N); % Tirage des particules autours de X_hat initial (? compléter)
wp = 1/N*ones(1,N); % poids initiaux (? compléter)

T = 80; % durée (s)
for tk = 2:(T/dt)
    % commande (définit la trajectoire)
    V = 300; % Vitesse (connue)
    omega = -0.01; % vitesse angulaire (rad/s) (connue)
    
    % Récupération de la mesure réelle
    Y = Y_sim(:,tk);
    
    % prediction (? compléter: variables Xp, X_hat et P_hat)
    
    vk = normrnd(0,Rf);
    Xp = Xp+[V*dt*cos(Xp(4));
             V*dt*sin(Xp(4));
             0;
             dt*omega;]; % particules prédites
    X_hat = sum(wp.*Xp,2); % état estim? prédit

    X_hat(4,:) = mod(X_hat(4,:), 2*pi); % modulo 2pi sur le cap
    P_hat = (wp.*(Xp-X_hat))*(Xp-X_hat)';% matrice de covariance prédite
    
    
    % validit? de la mesure réelle (? compléter pour la gestion des fréquences et des trous de mesures)
    is_measurementValid = true;
    
%     if mod(tk,10) == 0
%         is_measurementValid = true;
%     else
%         is_measurementValid = false;
%     end
    
%     if tk > 75
%         is_measurementValid = false;
%     elseif tk < 50
%         is_measurementValid = false;
%     else
%         is_measurementValid = true;
%     end

    % correction (? compléter)
    if is_measurementValid
        % définition de la mesure prédite (? compléter)
        %Y_hat = Xp(3)-lectureCarte(Xp(1:2),params);
        
        % correction des poids des particules (? compléter)
        %inno = Y-Y_hat;
        %likelihood = exp(-0.5*inno'/R*inno);
        %wp = wp*likelihood; % correction des poids
        %wp = wp/sum(wp); % normalisation des poids (la somme doit être égale ? 1)
        for i=1:N
            Yp =  Xp(3,i) - lectureCarte(Xp(:,i),params);
            inno = Y - Yp;
            wp(i) = wp(i)*exp(-inno.^2/(2*Rf));
        end
        n_wp = sum(wp);
        wp = wp/n_wp;
%         figure(3)
%         clf
%         hold on
%         hist(wp)
    end
    
    % R?-échantillonnage (critère de seuil ? compléter, puis coder un
    % autre algorithme de r?-échantillonnage de votre choix pour la
    % dernière question, en substitution du fichier select.p)
    criterionResampling = 1/(wp*wp'); % ? compléter
    if criterionResampling < N*threshold_resampling
        MaxWeightIndex = find(wp== max(wp));
        MaxWeightIndex = max(MaxWeightIndex);
        for i = 1:0.1*N
            MinWeightIndex = find(wp== min(wp));
            MinWeightIndex = min(MinWeightIndex);
            wp(MinWeightIndex) = wp(MaxWeightIndex);
            Xp(:,MinWeightIndex) = Xp(:,MaxWeightIndex);
        end
        %Xp = Xp(:,select(wp)); % sélection des nouvelles particules selon l'algorithme de r?-échantillonnage multinomial
        wp = 1/N*ones(1,N); % r?-initialisation des poids (? compléter)
        %wp = wp/sum(wp);
    end
    
    % enregistrement des variables (pour plot)
    P_sim(:,:,tk) = P_hat;
    Pdiag_sim(:,tk) = diag(P_hat);
    X_hat_sim(:,tk) = X_hat;
    
    % plot instantan? (ne pas hésiter ? passer <is_temporalPlot> ? false pour gagner du temps d'éxécution)
    is_temporalPlot = true;
    if is_temporalPlot
        figure(2)
        clf
        hold on
        imagesc(params.x_MNT*params.pasx_reel/1000, params.y_MNT*params.pasx_reel/1000, h_MNT)
        xlabel('km'); ylabel('km'); 
        title(['Erreur position: ', num2str(norm(X_hat(1:3) - X_reel(1:3))), ' m'])
        grid
        colorbar
        hold on
        plot(X_reel_sim(1,1:tk)./1000, X_reel_sim(2,1:tk)./1000,'.k')
        plot(X_hat_sim(1,1:tk)./1000, X_hat_sim(2,1:tk)/1000,'.r')
        scatter(Xp(1,:)./1000, Xp(2,:)./1000, '.y')
        scatter(X_reel_sim(1,tk)./1000, X_reel_sim(2,tk)./1000, '.k')
        scatter(X_hat_sim(1,tk)./1000, X_hat_sim(2,tk)./1000, '.r')
        grid on
        ylim([50, 150])
        xlim([170, 250])
        legend('Position vraie', 'position estime','particules')
        drawnow

    end
end

% Plot des résultats
figure(1)
labels = {'x (m)','y (m)','z (m)','\theta (rad)'};
for i = 1:d
    subplot(4,1,i)
    hold on
    fill([t_sim flip(t_sim,2)],[X_hat_sim(i,:) - 3*sqrt(Pdiag_sim(i,:)), X_hat_sim(i,end:-1:1) + 3*sqrt(Pdiag_sim(i,end:-1:1))], [7 7 7]/8);
    plot(t_sim, X_reel_sim(i,:), 'b')
    plot(t_sim, X_hat_sim(i,:), 'r')
    grid on
    xlabel('time (s)')
    ylabel(labels(i))
end
legend('uncertainty (3\sigma)', 'actual state', 'estimated state')


