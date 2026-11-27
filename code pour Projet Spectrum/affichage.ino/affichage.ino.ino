// ===== Rôle Affichage =====
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, DB4, DB5, DB6, DB7

void initAffichage() {
// À compléter.
// 1. Démarrer l'afficheur : 16 colonnes, 2 lignes (lcd.begin()).
// 2. Écrire sur la ligne 1, une seule fois, le titre "octave niveau" (lcd.print()).

}

void afficher() {
// Sur la ligne 2 (lcd.setCursor(colonne, ligne), numérotées à partir de 0) :
// 1. écrire octaveForte sous le mot "octave" (colonne 3) ;
// 2. écrire niveauOctave sous le mot "niveau" (colonne 11).
// L'afficheur garde ce qu'on n'écrase pas : si le niveau passe de 245 à 5, "545" s'affiche.
// Écrire des espaces après le niveau pour effacer les anciens chiffres.

}
// Fourni. TEST 3 : valeurs fictives, une par demi-seconde (sans micro ni spectre) : octaves 1 à 7,
// niveaux de 1, 2 et 3 chiffres (5, 20, 45, 80, 125, 180, 245)

void testerAffichage() {
  static byte k = 1;
  octaveForte = k;
  niveauOctave = 5 * k * k;
  k = k % NB_OCTAVES + 1;
  delay(500);
}
// Pistes, étape par étape :
// - afficher la bande de fréquences de l'octave au lieu de son rang ;
// - écrire "silence" sous un seuil de niveau ;
// - dessiner une barre par octave : caractères personnalisés (lcd.createChar(), puis lcd.clear()
// obligatoire, sinon le texte suivant abîme les caractères) ;
// - allumer une DEL de son trop fort, en tout ou rien (la MLI d'analogWrite() parasite le micro) ;
// - changer le contenu de la ligne 2 par un bouton-poussoir (machine à états).
git add .
git commit -m "Integration de l'affichage"
git push
