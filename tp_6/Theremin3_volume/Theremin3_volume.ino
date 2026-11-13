/*
Theremin3_volume : sous un seuil de volume, le son est coupé (TP6, étape 3)
Montage : celui de l'étape 2, plus un potentiomètre de volume : curseur sur A3.
*/

// constantes: broches, fréquences, seuil de volume
const byte pinBuzzer = 5;
const byte pinHauteur = A2;
const byte pinVolume = A3;
const int FREQ_MIN = 20;
const int FREQ_MAX = 4000;
const int SEUIL = 50; // Seuil à ajuster selon la lecture minimale de votre potentiomètre

void setup() {
  // liaison série pour le traceur
  Serial.begin(115200);
}

void loop() {
  // lire la hauteur et le volume
  int lectHauteur = analogRead(pinHauteur);
  int lectVolume = analogRead(pinVolume);
  
  // convertir la hauteur en fréquence
  int frequence = map(lectHauteur, 0, 1023, FREQ_MIN, FREQ_MAX);
  
  // si le volume atteint le seuil : jouer ; sinon : couper le son
  if (lectVolume >= SEUIL) {
    tone(pinBuzzer, frequence);
  } else {
    noTone(pinBuzzer);
  }
  
  // envoyer la fréquence et le volume au traceur série
  Serial.print("Frequence:");
  Serial.print(frequence);
  Serial.print(", Volume:");
  Serial.println(lectVolume);
  
  // courte pause
  delay(10);
}