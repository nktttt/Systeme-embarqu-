// ===== Rôle Affichage =====
// Entrées : octaveForte, de 1 à 7, et niveauOctave, 0 à 255. Sortie : texte sur l'afficheur.

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, DB4, DB5, DB6, DB7

void initAffichage() {
  lcd.begin(16, 2);
  lcd.print("octave   niveau");
}

void afficher() {
  lcd.setCursor(3, 1);
  lcd.print(octaveForte);

  lcd.setCursor(11, 1);
  lcd.print(niveauOctave);
  lcd.print("  ");
}

// Fourni. TEST 3 : valeurs fictives, une par demi-seconde
void testerAffichage() {
  static byte k = 1;
  octaveForte = k;
  niveauOctave = 5 * k * k;
  k = k % NB_OCTAVES + 1;
  delay(500);
}