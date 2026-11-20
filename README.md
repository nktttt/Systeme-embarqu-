# Theremin-like : PhotoTheremin

Auteurs : Nikita MARALIUC, Theo KLING, Rayan LEBLANC  (B2 Human-IT, ENSEA)

## Description
Cet instrument est un synthétiseur monodique inspiré du thérémine[cite: 6]. Il permet de jouer de la musique sans contact : la hauteur de la note (fréquence) varie en approchant ou en éloignant la main d'une photorésistance (variation de luminosité)[cite: 6]. Un potentiomètre permet de régler le volume sonore, et un bouton-poussoir permet de changer le timbre de l'instrument en alternant entre trois formes d'onde (carrée, triangulaire et sinusoïdale)[cite: 5, 6].

## Matériel
- 1 carte Arduino UNO R3
- 1 plaque d'essai (breadboard) et des fils de connexion
- 1 buzzer piézoélectrique[cite: 1]
- 1 photorésistance (LDR) + 1 résistance de $10\text{ k}\Omega$ (montage en pont diviseur de tension)[cite: 6]
- 1 potentiomètre linéaire de $10\text{ k}\Omega$ (réglage du volume)[cite: 6]
- 1 bouton-poussoir (sélection du mode / forme d'onde)[cite: 5, 6]

## Câblage

| Broche Arduino | Relié à |
| :--- | :--- |
| **D2** | Bouton-poussoir (l'autre patte reliée à **GND**, résistance de rappel interne `INPUT_PULLUP` activée)[cite: 5] |
| **D5** | Borne positive (`+`) du buzzer piézoélectrique (borne négative reliée à **GND**)[cite: 1] |
| **A2** | Point milieu du pont diviseur formé par la photorésistance et la résistance de $10\text{ k}\Omega$[cite: 2, 6] |
| **A3** | Curseur (broche centrale) du potentiomètre de volume (broches extérieures sur **5V** et **GND**)[cite: 3, 6] |
| **5V / GND** | Alimentation générale sur les rails de la plaque d'essai |

*(https://github.com/nktttt/Systeme-embarqu-/blob/main/tp_6/TP%206.1%20volume.svg)*[cite: 7]

## Installation
- **IDE Arduino** : version `<ex: 2.3.4>`[cite: 7]
- **Bibliothèque requise** : `Volume2` version `<ex: 1.0.2>` (installée via le gestionnaire de bibliothèques de l'IDE Arduino)[cite: 7].

## Utilisation
1. Ouvrir le fichier `Theremin5_modes/Theremin5_modes.ino` dans l'IDE Arduino[cite: 5, 6].
2. Sélectionner la carte *Arduino Uno* et le port USB correspondant, puis cliquer sur **Téléverser**[cite: 7].
3. **Étalonnage** : Si besoin, ajuster les constantes `LUMIERE_MIN_ADC` et `LUMIERE_MAX_ADC` dans le code en fonction de l'éclairage ambiant de la salle[cite: 6].
4. **Jouer** : Passer la main au-dessus de la photorésistance pour faire varier la hauteur du son (de 100 Hz à 2500 Hz)[cite: 6]. Tourner le potentiomètre pour ajuster le volume (de 0 à 255)[cite: 4, 6]. Appuyer sur le bouton-poussoir pour basculer entre les formes d'onde Carrée (`0`), Triangle (`1`) et Sinus (`2`)[cite: 5].
5. **Traceur série** : Ouvrir *Outils > Traceur série* réglé sur **115200 bauds** pour visualiser en direct l'évolution des courbes `Frequence`, `Volume` et `Mode`[cite: 2, 5, 7].

## Objet et société
Un instrument de musique sans contact présente un fort intérêt en matière d'accessibilité, notamment pour les personnes en situation de handicap moteur ou ayant des difficultés de préhension, car il permet une expression musicale par de simples gestes dans l'espace[cite: 7]. Sur le plan matériel, ce prototype est constitué de composants électroniques standards : une carte à microcontrôleur (silicium, cuivre, résine époxy FR4), du plastique ABS pour la plaque d'essai et des alliages métalliques pour les connecteurs[cite: 7]. Sa consommation énergétique est très faible (quelques dizaines de milliampères sous 5 V, soit moins de 0,25 W), alimentée directement par le port USB d'un ordinateur[cite: 7]. En fin de vie, ces éléments relèvent de la filière de recyclage des Déchets d'Équipements Électriques et Électroniques (DEEE)[cite: 7]. Toutefois, l'assemblage sans soudure sur breadboard permet de démonter et réutiliser intégralement chaque composant pour de futurs projets, limitant ainsi le gaspillage électronique[cite: 7].

## Journal
- **Prise en main du dépôt (`FadeSerial`)** : Premiers tests de commande PWM (`analogWrite`), de temporisation (`delay`) et de communication série (`Serial.begin(9600)`) sur deux LED (broches D9 et D10) pour initialiser l'environnement de travail et Git.
- **Étape 1 (`Theremin1_tone`)** : Découverte de la génération sonore sur la broche D5 avec la fonction `tone()` en jouant une courte mélodie (La, Do, Mi)[cite: 1, 6].
- **Étape 2 (`Theremin2_hauteur`)** : Contrôle de la fréquence en temps réel via une entrée analogique (A2) et observation des valeurs sur le traceur série à 115200 bauds[cite: 2, 6].
- **Étape 3 (`Theremin3_volume`)** : Constat de la limitation de `tone()` qui ne permet pas de moduler l'amplitude du signal ; mise en place d'un seuil de coupure avec `noTone()`[cite: 3, 6].
- **Étape 4 (`Theremin4_volume2`)** : Intégration de la bibliothèque `Volume2` pour gérer le volume (0-255) et le timbre[cite: 4, 6]. Remplacement de `delay()` par `delayMicroseconds()` car `Volume2` modifie le Timer0[cite: 4, 7].
- **Étape 5 (`Theremin5_modes`)** : Remplacement du potentiomètre de hauteur par une photorésistance avec lissage par moyenne glissante, ajout du bouton-poussoir sur D2 (avec anti-rebond logiciel) pour changer de forme d'onde, et choix du buzzer piézoélectrique sur D5 en l'absence de casque audio[cite: 1, 5, 6].

## Licence
Ce projet est distribué sous licence **GNU GPL v3**, afin d'être compatible avec la bibliothèque `Volume2` également publiée sous licence GPL v3[cite: 7, 8].
