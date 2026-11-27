// ===== Rôle Affichage =====
// Entrées : octaveForte, de 1 à 7, et niveauOctave, 0 à 255. Sortie : texte sur l'afficheur.

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, DB4, DB5, DB6, DB7

// 1. Démarrer l'afficheur : 16 colonnes, 2 lignes (lcd.begin()).
// 2. Écrire sur la ligne 1, une seule fois, le titre "octave niveau" (lcd.print()).
void initAffichage() {
  lcd.begin(16, 2);
  lcd.print("octave   niveau"); // 3 espaces placent "octave" au-dessus de col. 3 et "niveau" vers col. 11
}

// Sur la ligne 2 (lcd.setCursor(colonne, ligne), numérotées à partir de 0) :
// 1. écrire octaveForte sous le mot "octave" (colonne 3) ;
// 2. écrire niveauOctave sous le mot "niveau" (colonne 11).
// L'afficheur garde ce qu'on n'écrase pas : si le niveau passe de 245 à 5, "545" s'affiche.
// Écrire des espaces après le niveau pour effacer les anciens chiffres.
void afficher() {
  lcd.setCursor(3, 1);
  lcd.print(octaveForte);

  lcd.setCursor(11, 1);
  lcd.print(niveauOctave);
  lcd.print("  "); // efface les caractères résiduels lors du passage de 3 à 1 ou 2 chiffres
}

// Fourni. TEST 3 : valeurs fictives, une par demi-seconde (sans micro ni spectre) : octaves 1 à 7,
// niveaux de 1, 2 et 3 chiffres (5, 20, 45, 80, 125, 180, 245)
void testerAffichage() {
  static byte k = 1;
  octaveForte = k;
  niveauOctave = 5 * k * k;
  k = k % NB_OCTAVES + 1;
  delay(500);
<<<<<<< HEAD:code pour Projet Spectrum/SpectrumStartV1.ino/SpectrumStartV1/affichage.ino
}
=======
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
>>>>>>> 3d5c19a09e6d1ca7dd37fe3bfa538e97c9a7a8ed:code pour Projet Spectrum/affichage.ino/affichage.ino.ino
