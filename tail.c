#include <stdio.h>
#include <stdlib.h>

#include <graph.h>//L'appel à la bibliothèque graphique

#include "tail.h"

void snakeTail(int snake_Horizon, int snake_Vertical)
{

	couleur tail_color;

	tail_color = CouleurParNom("yellow");

	ChoisirCouleurDessin(tail_color);


	RemplirRectangle(snake_Horizon, snake_Vertical, 10, 10);

}


void snakeTail_eraser(int ancienne_position_X, int ancienne_position_Y)
{

	couleur snake_color;

	snake_color = CouleurParNom("green");

	ChoisirCouleurDessin(snake_color);


	RemplirRectangle(ancienne_position_X, ancienne_position_Y, 10, 10);

}


