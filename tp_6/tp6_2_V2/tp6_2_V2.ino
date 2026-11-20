/*
 * Nom du fichier : Theremin5_modes.ino
 * Rôle           : Instrument Theremin-like complet avec contrôle sans contact
 *                  (photorésistance), réglage du volume, lissage et sélection
 *                  de la forme d'onde par bouton-poussoir.
 * Auteurs        : Rayan LEBLANC, <Prénom NOM> (B2 Human-IT, ENSEA)
 * Version        : 1.0 (Séance 5 - Final)
 * Date           : 20 novembre 2026
 * Licence        : GNU GPL v3 (compatible avec la bibliothèque Volume2)
 * Montage        : - Buzzer piézoélectrique entre D5 et GND
 *                  - Photorésistance (pont diviseur 10 kOhm) sur A2
 *                  - Potentiomètre de volume sur A3
 *                  - Bouton-poussoir entre D2 et GND
 */

#include <Volume2.h>

// Broches, plages de mesures et paramètres temporels

const byte PIN_BUZZER  = 5;   // Sortie PWM imposée pour buzzer
const byte PIN_HAUTEUR = A2;  // Entrée analogique de la photorésistance
const byte PIN_VOLUME  = A3;  // Entrée analogique du potentiomètre de volume
const byte PIN_BOUTON  = 2;   // Entrée numérique du poussoir (avec pull-up)

// Plages de fréquences audibles souhaitées (en Hz)
const int FREQ_MIN_HZ = 100;
const int FREQ_MAX_HZ = 2500;

// Étalonnage de la photorésistance (valeurs ADC entre 0 et 1023 à ajuster selon la salle)
const int LUMIERE_MIN_ADC = 150; // Main proche (ombre)
const int LUMIERE_MAX_ADC = 850; // Pleine lumière ambiante

// Plage de volume de la bibliothèque Volume2 (sans unité, 8 bits)
const int VOLUME_MIN    = 0;
const int VOLUME_MAX    = 255;
const int SEUIL_SILENCE = 10;  // Coupe le son en dessous de ce seuil

// Paramètres de filtrage et d'anti-rebond
const byte NB_ECHANTILLONS_LISSAGE     = 8;     // Taille de la moyenne glissante
const unsigned int DELAI_ANTIREBOND_US = 15000; // 15 ms en microsecondes
const unsigned int DELAI_BOUCLE_US     = 10000; // 10 ms (100 Hz d'échantillonnage)
const long VITESSE_SERIE_BAUDS         = 115200;


// TYPES ET VARIABLES GLOBALES

enum ModeOnde { CARRE = 0, TRIANGLE_ONDE = 1, SINUS = 2 };
ModeOnde modeCourant = CARRE;

Volume vol; // Objet de synthèse sonore Volume2

int etatBoutonPrecedent = HIGH; // HIGH = relâché grâce à INPUT_PULLUP
int historiqueHauteur[NB_ECHANTILLONS_LISSAGE];
byte indexLissage = 0;


// FONCTIONS Par TACHE


//Lit la photorésistance et applique une moyenne glissante pour stabiliser la note.
 //Retourne : valeur ADC lissée entre 0 et 1023.


int lireHauteurLissee() {
  historiqueHauteur[indexLissage] = analogRead(PIN_HAUTEUR);
  indexLissage = (indexLissage + 1) % NB_ECHANTILLONS_LISSAGE;

  long somme = 0;
  for (byte i = 0; i < NB_ECHANTILLONS_LISSAGE; i++) {
    somme += historiqueHauteur[i];
  }
  return somme / NB_ECHANTILLONS_LISSAGE;
}

// Détecte un front descendant sur le bouton-poussoir avec anti-rebond.
// Retourne : true lors d'un nouvel appui validé, false sinon.
 
bool detecterAppuiBouton() {
  int etatActuel = digitalRead(PIN_BOUTON);
  bool appuiValide = false;

  if (etatBoutonPrecedent == HIGH && etatActuel == LOW) {
    // Utilisation de delayMicroseconds() car Volume2 modifie le Timer0 (delay() inutilisable)
    delayMicroseconds(DELAI_ANTIREBOND_US);
    etatActuel = digitalRead(PIN_BOUTON);
    if (etatActuel == LOW) {
      appuiValide = true;
    }
  }
  etatBoutonPrecedent = etatActuel;
  return appuiValide;
}


//Passe cycliquement à la forme d'onde suivante.

void changerMode() {
  if (modeCourant == CARRE) {
    modeCourant = TRIANGLE_ONDE;
  } else if (modeCourant == TRIANGLE_ONDE) {
    modeCourant = SINUS;
  } else {
    modeCourant = CARRE;
  }
}

//Traduit le mode courant en constante reconnue par la bibliothèque Volume2.
 
byte obtenirFormeOndeVolume2() {
  switch (modeCourant) {
    case CARRE:         return SQUARE;
    case TRIANGLE_ONDE: return TRIANGLE;
    case SINUS:         return SINE;
    default:            return SQUARE;
  }
}


// INITIALISATION ET BOUCLE PRINCIPALE


void setup() {
  Serial.begin(VITESSE_SERIE_BAUDS);
  pinMode(PIN_BOUTON, INPUT_PULLUP);

  // Initialisation du tableau de lissage avec une première mesure réelle
  int mesureInitiale = analogRead(PIN_HAUTEUR);
  for (byte i = 0; i < NB_ECHANTILLONS_LISSAGE; i++) {
    historiqueHauteur[i] = mesureInitiale;
  }

  vol.begin(); // Démarre le générateur PWM haute fréquence sur D5
}

void loop() {
  // 1. Gestion de l'interface utilisateur (changement de timbre)
  if (detecterAppuiBouton()) {
    changerMode();
  }

  // 2. Acquisition des capteurs
  int hauteurBrute = lireHauteurLissee();
  int volumeBrut   = analogRead(PIN_VOLUME);

  // 3. Conversion et bornage des valeurs
  int hauteurBornee = constrain(hauteurBrute, LUMIERE_MIN_ADC, LUMIERE_MAX_ADC);
  int frequenceHz   = map(hauteurBornee, LUMIERE_MIN_ADC, LUMIERE_MAX_ADC, FREQ_MIN_HZ, FREQ_MAX_HZ);
  int volumeSortie  = map(volumeBrut, 0, 1023, VOLUME_MIN, VOLUME_MAX);

  if (volumeSortie < SEUIL_SILENCE) {
    volumeSortie = 0;
  }

  // 4. Génération sonore sur le buzzer piézoélectrique
  vol.tone(frequenceHz, obtenirFormeOndeVolume2(), volumeSortie);

  // 5. Envoi des données au traceur série Arduino
  Serial.print("Frequence:");
  Serial.print(frequenceHz);
  Serial.print(", Volume:");
  Serial.print(volumeSortie);
  Serial.print(", Mode:");
  Serial.println(modeCourant);

  // Cadencement de la boucle (sans utiliser delay() ni millis())
  delayMicroseconds(DELAI_BOUCLE_US);
}