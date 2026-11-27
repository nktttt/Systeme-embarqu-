// ===== Rôle Acquisition =====
const byte micPin = A1; // broche analogique du micro MAX9814
const byte ECHELLE = 1; // facteur d'échelle pour le traceur série (TEST 1)
int micMoy;          // composante continue du signal

void initAcquisition() {
  analogReference(EXTERNAL); // référence 3,3 V sur AREF
  analogRead(micPin);        // première conversion jetée pour valider AREF
}

void acquerir() {
  long somme = 0;

  for (int i = 0; i < FHT_SAMPLES_N; i++) {
    fht_input[i] = analogRead(micPin);
    somme += fht_input[i];
  }

  micMoy = somme / FHT_SAMPLES_N;
  for (int i = 0; i < FHT_SAMPLES_N; i++) {
    fht_input[i] -= micMoy;
  }
}

void testerAcquisition() {
  for (int i = 0; i < FHT_SAMPLES_N; i++) {
    Serial.print("micro:");
    Serial.println(fht_input[i] / ECHELLE);
  }
}

// Pistes, étape par étape :
// - mesurer la durée des 256 conversions (micros()) et en déduire la fréquence d'échantillonnage ;
// - l'augmenter : diviseur d'horloge du CAN (registre ADCSRA, bits ADPS2 à ADPS0) ;
// - calculer l'amplitude crête à crête, puis la valeur efficace (somme des carrés) du signal.
