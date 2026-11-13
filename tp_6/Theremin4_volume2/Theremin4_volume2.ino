/*
Theremin4_volume2: volume réglable et forme d'onde, bibliothèque Volume2 (TP6, étape 4)
Montage : celui de l'étape 3.
*/

// inclure la bibliothèque
#include <Volume2.h>

// constantes: broches, fréquences
const byte pinBuzzer = 5;
const byte pinHauteur = A2;
const byte pinVolume = A3;
const int FREQ_MIN = 20;
const int FREQ_MAX = 4000;

// déclarer l'objet de la bibliothèque
Volume vol;

void setup() {
  // liaison série pour le traceur
  Serial.begin(115200);
  vol.begin(); // Initialisation de la bibliothèque Volume2
}

void loop() {
  // lire la hauteur et le volume
  int lectHauteur = analogRead(pinHauteur);
  int lectVolume = analogRead(pinVolume);
  
  // convertir la hauteur en fréquence, le volume de 0 à 255
  int frequence = map(lectHauteur, 0, 1023, FREQ_MIN, FREQ_MAX);
  int volume = map(lectVolume, 0, 1023, 0, 255);
  
  // jouer : fréquence, forme d'onde, volume
  // SQUARE (carré) est l'une des formes possibles. Vous pouvez essayer SINE ou TRIANGLE
  vol.tone(frequence, SQUARE, volume); 
  
  // envoyer la fréquence et le volume au traceur série
  Serial.print("Frequence:");
  Serial.print(frequence);
  Serial.print(", Volume:");
  Serial.println(volume);
  
  // pause courte (attention : ni delay() ni millis() avec cette bibliothèque)
  // On utilise au plus 16000 microsecondes
  delayMicroseconds(10000); 
}