/*
  SpectrumStart : visualiseur de spectre, version de départ du TP7.1 (projet Spectrum), à compléter en équipe
  Licence CC BY-SA 4.0.
  But de cette première étape : afficher le niveau du son capté par le micro dans l'octave la plus
  forte (la bande de fréquences, de 1 à 7, où il est le plus fort), et le rang de cette octave.
  Un rôle par onglet (l'IDE assemble les onglets : celui-ci d'abord, puis les autres par ordre alphabétique) :
  - acquisition.ino : rôle Acquisition : micro, 256 conversions, centrage ;
*/

#define FHT_SAMPLES_N 256 // nombre d'échantillons, lu par AvrFHT (avant les #include)
#define OCT_NORM 1        // énergie de chaque octave divisée par son nombre de raies

#include <AvrFHT.h>
#include <fht_window.h>
#include <fht_reorder.h>
#include <fht_mag_octave.h>
#include <LiquidCrystal.h>

// 0 : normal | 1 : Acquisition | 2 : Traitement | 3 : Affichage | 4 : Traitement (traceur)
// Remettre TEST à 0 avant chaque commit.
#define TEST 0

// Contrat entre les rôles
const byte NB_OCTAVES = 7; // octaves 1 à 7 (l'octave 0, continue, est ignorée)
byte octaveForte;          // rang de l'octave de plus haut niveau (1 à 7)
byte niveauOctave;         // niveau de cette octave (0 à 255)

void setup() {
  Serial.begin(115200);
  initAcquisition();
  initAffichage();
}

void loop() {
#if TEST == 1
  acquerir();
  testerAcquisition();
#elif TEST == 2
  acquerir();
  analyser();
  testerTraitement();
#elif TEST == 4
  acquerir();
  analyser();
  testerTraitementTraceur();
#elif TEST == 3
  testerAffichage();
  afficher();
#else
  acquerir();
  analyser();
  afficher();
#endif
}