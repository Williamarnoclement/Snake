#include <stdio.h>
#include <stdlib.h>

#include <graph.h>//L'appel à la bibliothèque graphique

#include "snake.h"

void snakeHead(int snake_Horizon, int snake_Vertical)
{

	couleur snake_color;

	snake_color = CouleurParNom("yellow");

	ChoisirCouleurDessin(snake_color);


	RemplirRectangle(snake_Horizon, snake_Vertical, 10, 10);

}

void snakeHead_eraser(int ancienne_position_X, int ancienne_position_Y)
{

	couleur snake_color;

	snake_color = CouleurParNom("purple");

	ChoisirCouleurDessin(snake_color);


	RemplirRectangle(ancienne_position_X, ancienne_position_Y, 10, 10);

}