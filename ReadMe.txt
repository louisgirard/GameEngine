Utilisation :
Demo 1 et 2 du TP3 :
Il suffit de lancer l'application

Blob Game :
- Déplacement avec les touches directionnelles
- B : Séparer le blob
- F : Reconstituer le blob

Lancer du cube :
- Toucher Enter pour lancer le cube
- Clic droit pour accéder au menu à choisir l'axe du lancer

Général :
Requis :
- Avoir une configuration qui supporte OpenGL 3

Sous windows :
Requis :
- Visual Studio 2019 installé
Avant de lancer le projet, vous devez exécuter le fichier de commandes Windows setup.bat se
trouvant à la racine du dossier (./setupbat.) Puis vous pourrez ouvrir le projet sous Visual Studio en
exécutant le fichier ./GameEngine/Project/GameEngine.sln.


Sous Linux :
Requis :
- Le paquet freeglut3-dev installé
- Le paquet libglew-dev installé
- Le paquet assimp-utils installé
- Le paquet libassimp-dev installé
- Le paquet libsoil-dev installé
- Le logiciel make installé
- Le paquet gcc installé
Déplacez-vous dans le répertoire ./GameEngine puis exécuter la commande make clean suivie de la
commande make. Un fichier binaire Main est généré et exécutable (./Main.)

A savoir :
Il se peut que, par défaut, vous n'ailliez pas les droits d'éxécution sur le fichier binaire généré. Il
faudra donc utiliser la commande "chmod u+x Main".


Sous MacOS :
A titre indicatif : Nous n'avons pu tester notre projet sous cet OS. Il se peut donc qu'il ne
fonctionne pas de façon optimale sur celui ci.
Requis :
- Gestionnaire de paquet Homebrew installé (https://brew.sh/index_fr)
- freeglut installé
- glew installé
- assimp installé
- soil installé