#include <stdio.h>
#include <stdlib.h>

#include <graph.h>//L'appel à la bibliothèque graphique

#include "pastille.h"

#define TAILLE_CASE 10

void afficherPastille(int x, int y){

	couleur pastille;

	pastille = CouleurParNom("red");

	ChoisirCouleurDessin(pastille);


	RemplirRectangle(x, y, TAILLE_CASE , TAILLE_CASE);


}