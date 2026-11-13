/*
Theremin5_modes : le poussoir change de forme d'onde (TP6, étape 5)
Montage : celui de l'étape 4, plus un poussoir entre D2 et GND.
*/

// inclure la bibliothèque, constantes (broches, fréquences)
#include <Volume2.h>
const byte pinBuzzer = 5;
const byte pinHauteur = A2;
const byte pinVolume = A3;
const byte pinBouton = 2;
const int FREQ_MIN = 20;
const int FREQ_MAX = 4000;

// type énuméré des modes (un par forme d'onde), variable du mode courant
enum Mode { CARRE, TRIANGLE, SINUS };
Mode modeCourant = CARRE;

// objet de la bibliothèque, mémoire de l'état précédent du poussoir
Volume vol;
int etatBoutonPrecedent = HIGH; 

// fonction qui détecte un appui (avec anti-rebond)
bool detecterAppui() {
  int etatBoutonActuel = digitalRead(pinBouton);
  bool appuiDetecte = false;
  
  // détection du front descendant (passage de relâché à appuyé)
  if (etatBoutonPrecedent == HIGH && etatBoutonActuel == LOW) {
    // filtrer les rebonds en attendant 15 ms avec delayMicroseconds()
    delayMicroseconds(15000); 
    etatBoutonActuel = digitalRead(pinBouton); // relire le poussoir après le rebond
    if (etatBoutonActuel == LOW) {
      appuiDetecte = true;
    }
  }
  etatBoutonPrecedent = etatBoutonActuel;
  return appuiDetecte;
}

// fonction qui passe au mode suivant
void changerMode() {
  switch (modeCourant) {
    case CARRE:
      modeCourant = TRIANGLE;
      break;
    case TRIANGLE:
      modeCourant = SINUS;
      break;
    case SINUS:
      modeCourant = CARRE;
      break;
  }
}

void setup() {
  // liaison série, poussoir en entrée avec résistance de rappel
  Serial.begin(115200);
  pinMode(pinBouton, INPUT_PULLUP); // relâché = HIGH, appuyé = LOW
  vol.begin();
}

void loop() {
  // si appui : mode suivant
  if (detecterAppui()) {
    changerMode();
  }
  
  // lire hauteur et volume, convertir
  int lectHauteur = analogRead(pinHauteur);
  int lectVolume = analogRead(pinVolume);
  int frequence = map(lectHauteur, 0, 1023, FREQ_MIN, FREQ_MAX);
  int volume = map(lectVolume, 0, 1023, 0, 255);
  
  // choisir la forme d'onde selon le mode
  int formeOnde;
  if (modeCourant == CARRE) {
    formeOnde = SQUARE;
  } else if (modeCourant == TRIANGLE) {
    formeOnde = TRIANGLE; 
  } else {
    formeOnde = SINE; 
  }

  // jouer : fréquence, forme d'onde, volume
  vol.tone(frequence, formeOnde, volume);
  
  // envoyer fréquence, volume et mode au traceur série
  Serial.print("Frequence:");
  Serial.print(frequence);
  Serial.print(", Volume:");
  Serial.print(volume);
  Serial.print(", Mode:");
  Serial.println(modeCourant);
  
  // pause courte
  delayMicroseconds(10000);
}