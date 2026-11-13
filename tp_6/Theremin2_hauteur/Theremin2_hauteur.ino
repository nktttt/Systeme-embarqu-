/*
Theremin2_hauteur : la hauteur du son suit le potentiomètre (TP6, étape 2)
Montage: piézo entre D5 et GND potentiomètre de hauteur : curseur sur A2.
*/

// constantes: broches, fréquences minimale et maximale
const byte pinBuzzer = 5;
const byte pinPotHauteur = A2;
const int FREQ_MIN = 20;
const int FREQ_MAX = 4000;

void setup() {
  // liaison série pour le traceur (vitesse demandée : 115200)
  Serial.begin(115200);
}

void loop() {
  // lire le potentiomètre
  int lecture = analogRead(pinPotHauteur);
  
  // convertir la lecture en fréquence
  int frequence = map(lecture, 0, 1023, FREQ_MIN, FREQ_MAX);
  
  // jouer la fréquence
  tone(pinBuzzer, frequence);
  
  // envoyer la lecture et la fréquence au traceur série
  Serial.print("Lecture:");
  Serial.print(lecture);
  Serial.print(", Frequence:");
  Serial.println(frequence);
  
  // courte pause
  delay(10);
}