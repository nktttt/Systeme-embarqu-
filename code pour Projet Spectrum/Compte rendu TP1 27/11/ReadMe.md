Rôles équipe : 
-  Acquisition, Affichage : Théo
-  Traitement : Rayan
-  Intégrateur : Nikita
  
Difficultés :
- Comprendre le cablage (entrée/sortie)
- Arriver a avancer à la même vitesse
- Manipulation git (televersement, importation)
  
Solutions apportées :
- Aide entre nous
- Investissement plus dans le montage
- Communication nette

* **SpectrumStart.ino (rôle d'intégrateur - fichier maître)**  
  Définit les paramètres globaux FHT (`FHT_SAMPLES_N = 256`, `OCT_NORM = 1`), connecte les bibliothèques (`AvrFHT`, `LiquidCrystal`) et annonce l'interface du module (`NB_OCTAVES`, `octaveForte`, `levelOctave`). Contrôle l'initialisation (`setup()`), la boucle principale (`loop()`) et le choix du mode de fonctionnement via la macro `TEST` (0 - mode normal, 1-4 - tests unitaires).

* **acquisition.ino (rôle de collecte de données)**  
  Contrôle la capture du signal audio du microphone MAX9814 sur la broche analogique `A1`. `initAcquisition()` définit la tension de référence externe `AREF` (3,3V), et `acquerir()` prend 256 échantillons, calcule la composante constante (`micMoy`) et centre le signal autour de zéro dans `fht_input[]`. Contient `testAcquisition()` (`TEST 1`) pour sortir la forme d'onde vers le traceur sur le port série.

* **treatment.ino (rôle de traitement)**  
  Effectue l'analyse de la fréquence du signal audio. La fonction `computeSpectrum()` lance la transformation rapide de Hartley (FHT) et distribue l'énergie audio à 7 octaves (`fht_oct_out[1..7]`). `analysis()` scanne les octaves, classe l'octave dominante (`octaveForte`, 1 à 7) et extrait son intensité (`levelOctave`, 0 à 255). Inclut `testProcess()` (`TEST 2`) et `testProcessTracer()` (`TEST 4`).

* **view.ino (Afficher le rôle)**  
  Contrôle l'affichage LCD1602 en mode 4 bits (broches `D2`-`D7`). `initDisplay()` initialise l'écran 16x2 et affiche l'en-tête du niveau d'octave sur la première ligne. `display()` efface les chiffres résiduels et met à jour le rang d'octave et le niveau de volume maximum sur la deuxième ligne. Contient `testDisplay()` (`TEST 3`) pour tester l'affichage sur des valeurs simulées.
<img width="2862" height="1598" alt="image" src="https://github.com/user-attachments/assets/2d88cf21-7699-4f72-b215-61307cbaf23d" />
<img width="2880" height="1676" alt="image" src="https://github.com/user-attachments/assets/fb9fbe0b-47f1-4b29-9ec6-7701d5a1685d" />
<img width="1570" height="984" alt="image" src="https://github.com/user-attachments/assets/4463c13b-fda1-4b08-b4ae-4b8b26545a79" />
