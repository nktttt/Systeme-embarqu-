/*
Theremin1_tone : une note, puis une courte mélodie (TP6, étape 1
Montage: buzzer piézo entre D5 et GND.
*/

const byte pinBuzzer = 5; // Broche du buzzer

void setup() {
  // rien à initialiser : tone configure la broche
}

void loop() {
  // jouer la note la (440 Hz), pendant une demi-seconde
  tone(pinBuzzer, 440);
  delay(500);
  
  // couper le son, pause courte
  noTone(pinBuzzer);
  delay(100);
  
  // jouer deux autres notes, même structure
  tone(pinBuzzer, 523); // do
  delay(500);
  noTone(pinBuzzer);
  delay(100);

  tone(pinBuzzer, 659); // mi
  delay(500);
  noTone(pinBuzzer);
  delay(100);
  
  // pause plus longue avant de recommencer
  delay(2000); 
}