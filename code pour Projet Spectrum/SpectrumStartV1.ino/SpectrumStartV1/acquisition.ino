// ===== Rôle Acquisition =====
const byte micPin = A1;
const int ECHELLE = 8; // échantillon centré multiplié par 8 (précision FHT)
int micMoy;

void initAcquisition() {
  analogReference(EXTERNAL);
  analogRead(micPin); // première conversion jetée pour valider AREF
}

void acquerir() {
  // À compléter à l'étape 2

// La sortie du micro oscille autour d'une tension continue (vers 1,25 V, soit environ 390 pas du
// CAN) ; la FHT demande un signal centré sur 0.
// 1. Lire FHT_SAMPLES_N (256) valeurs sur micPin avec analogRead(), les ranger dans fht_input[0]
// à fht_input[255], et en faire la somme (variable de type long : 256 * 1023 dépasse un int).
// 2. Calculer la moyenne, la ranger dans micMoy.
// 3. Remplacer chaque fht_input[i] par (fht_input[i] - micMoy) * ECHELLE.

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
