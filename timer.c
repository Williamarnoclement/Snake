#include <stdio.h>
#include <stdlib.h>
#include <graph.h>//L'appel à la bibliothèque graphique

#include "timer.h"

void currentTime(int minutes, int secondes){

	couleur affichage_timer;

	affichage_timer = CouleurParNom("white");
	ChoisirCouleurDessin(affichage_timer);

	char str[7];

	sprintf(str, "%0d : %0d", minutes, secondes);

	EcrireTexte(30,500, str, 1);


}


void currentTime_eraser(){

	couleur affichage_timer;

	affichage_timer = CouleurParNom("black");
	ChoisirCouleurDessin(affichage_timer);


	RemplirRectangle(30, 480, 100, 20);

}

void currentScore(int score){

	couleur affichage_score;

	affichage_score = CouleurParNom("white");
	ChoisirCouleurDessin(affichage_score);

	char str[6 + 7];

	sprintf(str, "score: %0d", score);

	EcrireTexte(540,500, str, 1);

}
void currentScore_eraser(){

	couleur affichage_timer;

	affichage_timer = CouleurParNom("black");
	ChoisirCouleurDessin(affichage_timer);


	RemplirRectangle(540,480, 100, 20);

}