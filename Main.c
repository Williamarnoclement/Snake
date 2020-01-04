#include <stdio.h>
#include <stdlib.h>
#include <time.h>// Generation de pseudo-aléatoire
#include <graph.h>//Appel à la bibliothèque graphique
#include "snake.h"//Appel aux fonctions de snake.c
#include "tail.h"//Appel aux fonctions de tail.c
#include "pastille.h"//Appel aux fonctions de pastille.c
#include "timer.h"//Appel aux fonctions de timer.c


#define TAILLE_HORIZON_JEU 660//taille du Gameplay X
#define TAILLE_VERTICAL_JEU 540//taille du Gameplay Y


#define TAILLE_GRILLE_HORIZON 60
#define TAILLE_GRILLE_VERTICAL 40


#define TAILLE_CASE 10


#define DECALAGE 30

#define CYCLE 1000000L

#define TAILLE_MAX_SERPENT 100

struct componentPosition {

	int newX;
	int newY;
	int oldX;
	int oldY;

	int direction;

};

int convertToPix(int position_a_convertir){

	return (TAILLE_CASE * position_a_convertir) + DECALAGE;

}

void background(){

	couleur background;

	background = CouleurParNom("black");

	ChoisirCouleurDessin(background);


	RemplirRectangle(0, 0, TAILLE_HORIZON_JEU,TAILLE_VERTICAL_JEU);
}

void coloriage(){

	couleur environnement;

	environnement = CouleurParNom("green");

	ChoisirCouleurDessin(environnement);


	RemplirRectangle(DECALAGE, DECALAGE, TAILLE_CASE * TAILLE_GRILLE_HORIZON, TAILLE_CASE * TAILLE_GRILLE_VERTICAL);
}


void paused(){

	couleur affichage_pause;

	affichage_pause = CouleurParNom("white");
	ChoisirCouleurDessin(affichage_pause);

	EcrireTexte( TAILLE_CASE * TAILLE_GRILLE_HORIZON /2, TAILLE_CASE * TAILLE_GRILLE_VERTICAL/2, "PAUSE", 1);


}

void gameOver(){

	couleur environnement;

	environnement = CouleurParNom("black");

	ChoisirCouleurDessin(environnement);


	RemplirRectangle(0, 30, TAILLE_CASE * TAILLE_HORIZON_JEU, TAILLE_CASE * TAILLE_GRILLE_VERTICAL);
	couleur affichage_pause;

	affichage_pause = CouleurParNom("white");
	ChoisirCouleurDessin(affichage_pause);

	EcrireTexte( TAILLE_CASE * 27, TAILLE_CASE * TAILLE_GRILLE_VERTICAL/2, "GAME OVER", 1);


}


int main(int argc, char const *argv[])
{

	InitialiserGraphique();
	CreerFenetre(10,10,TAILLE_HORIZON_JEU,TAILLE_VERTICAL_JEU);
	SourisPosition();

	///////////////////////////////////////////////////////////////
	/**                  INITIALISATION !                       **/
	///////////////////////////////////////////////////////////////

	//création d'une grille via un tableau multi-dimensionnel
	int Grille[TAILLE_GRILLE_HORIZON][TAILLE_GRILLE_VERTICAL];//grille qui stocke au format grille les position X et Y	

	//0 pour gauche 
	//1 pour droite 
	//2 pour haut
	//3 pour bas
	int direction_ancienne;//deprecated
	int direction_actuelle = 1;// deprecated

	//taille de la queue du serpent.
	int taille = 10;
	int changement = 0;

	//position actuelle des éléments composant la queue du serpent
	struct componentPosition headSnake  = {convertToPix(30), convertToPix(20), convertToPix(30), convertToPix(20) , 3};
	struct componentPosition tailSnake[TAILLE_MAX_SERPENT];

	srand(time(NULL));//mise en place du rand

	//tableau permettant de stocker la position de chaque pastille
	int pastille[5][2];


	//gestion du temps
	long long suivant = Microsecondes()+CYCLE;//gestion des secondes 
	int secondes = 0;
	int minutes = 0;

	//gestion de la vitesse du serpent
	long long rampe = 100000L;
	long long celerite = Microsecondes() + rampe;//gestion de la vitesse du serpent 
	

	//gestion de la pause 
	int pause = 0;

	//Le joueur est-il encore en train de jouer ou a t-il perdu ?
	int still_playing = 1;

	// gestion du scoring
	int scoring = 0;

	//mise en place du décor !
	background();
	coloriage();
	currentScore(scoring);
	currentTime(minutes, secondes);

	//generateur de pastille
	for (int i = 0; i < 5; ++i)
	{
		pastille[i][1] = (rand()%TAILLE_GRILLE_HORIZON) - 0;
		pastille[i][2] = (rand()%TAILLE_GRILLE_VERTICAL) - 0;
		afficherPastille(convertToPix(pastille[i][1]), convertToPix(pastille[i][2]));
	}

	
	///////////////////////////////////////////////////////////////
	/**                  PARTIE TEMPS REEL                      **/
	///////////////////////////////////////////////////////////////


	while(1){

		//gestion game over
		if (headSnake.newX < convertToPix(0) || headSnake.newX >= convertToPix(TAILLE_GRILLE_HORIZON) || headSnake.newY <= convertToPix(0) || headSnake.newY >= convertToPix(TAILLE_GRILLE_VERTICAL) )
		{
			still_playing = 0;
		}

		for (int i = 1; i <= taille; ++i)
		{
			if (headSnake.newX == tailSnake[i].newX && headSnake.newY == tailSnake[i].newY  )
			{
				still_playing = 0;
			}
		}

		if (still_playing == 1)
		{

		//gestion collision pastille
			for (int i = 0; i < 5; ++i)
			{

				if (headSnake.newX == convertToPix(pastille[i][1]) && headSnake.newY == convertToPix(pastille[i][2]))
				{	
					scoring += 5;


					currentScore_eraser();
					currentScore(scoring);

					taille = taille + 2;
					//snakeTail_eraser(pastille[i][1],pastille[i][2]);
					printf("score : %d\n", scoring);
					pastille[i][1] = (rand()%TAILLE_GRILLE_HORIZON) - 0;
					pastille[i][2] = (rand()%TAILLE_GRILLE_VERTICAL) - 0;
				}

			}

	///////////////////////////////////////////////////////////////
	/**                 GESTION DU TEMPS                        **/
	///////////////////////////////////////////////////////////////
			if(pause == 0){

				if (Microsecondes()>suivant)
				{

					suivant= Microsecondes()+CYCLE;
					secondes++;
					currentTime_eraser();
					currentTime(minutes, secondes);


					if(secondes > 60){
						secondes = 0;
						minutes++;
					}

				}


				if(Microsecondes() > celerite){


					if (direction_actuelle == 0)
					{

						headSnake.newX = headSnake.oldX - TAILLE_CASE;

					} else if(direction_actuelle == 1) {

						headSnake.newX = headSnake.oldX + TAILLE_CASE;

					} else if(direction_actuelle == 2) {

						headSnake.newY = headSnake.oldY - TAILLE_CASE;

					} else if(direction_actuelle == 3) {

						headSnake.newY = headSnake.oldY + TAILLE_CASE;

					}

					tailSnake[0].newX = headSnake.oldX;
					tailSnake[0].newY = headSnake.oldY;

					for (int i = 1; i <= taille; ++i)
					{
						tailSnake[i].newX = tailSnake[i-1].oldX;
						tailSnake[i].newY = tailSnake[i-1].oldY;

					}

					snakeTail(tailSnake[0].newX, tailSnake[0].newY);


					for (int i = 1; i <= taille; ++i)
					{
						snakeTail(tailSnake[i].newX, tailSnake[i].newY);
					}

					snakeTail_eraser(tailSnake[taille].newX, tailSnake[taille].newY);

					celerite = Microsecondes()+rampe;


				}
			}
		} else if (still_playing == 0)
		{

			gameOver();
			
		}


	///////////////////////////////////////////////////////////////
	/**                 GESTION DES TOUCHES                     **/
	///////////////////////////////////////////////////////////////


		if (ToucheEnAttente())
		{
			int touche = Touche();
			//background();
			//coloriage();

			//Quand le joueur veut quitter le jeu !
			if (touche == XK_Escape)
			{
				FermerGraphique();
				return 0;

			} 
			else if (touche == XK_Right && direction_actuelle != 0)
			{


				//snakeTail(Snake_X,Snake_Y);
				//snakeTail_eraser(Snake_X,Snake_Y, taille, direction_actuelle);
				printf("go right\n");
				//Snake_X = Snake_X + TAILLE_CASE;
				direction_actuelle=1;

			} 
			else if (touche == XK_Left && direction_actuelle != 1)
			{

				//snakeTail(Snake_X,Snake_Y);
				//snakeTail_eraser(Snake_X,Snake_Y, taille, direction_actuelle);
				printf("go left\n");
				//Snake_X = Snake_X - TAILLE_CASE;
				direction_actuelle = 0;
			} 
			else if (touche == XK_Up && direction_actuelle != 3)
			{

				//snakeTail(Snake_X,Snake_Y);
				//snakeTail_eraser(Snake_X,Snake_Y, taille, direction_actuelle);
				printf("go upside\n");
				//Snake_Y = Snake_Y - TAILLE_CASE;
				direction_actuelle = 2;

			} 
			else if (touche == XK_Down && direction_actuelle != 2)
			{

				//snakeTail(Snake_X,Snake_Y);
				//snakeTail_eraser(Snake_X,Snake_Y, taille, direction_actuelle);
				printf("go down\n");
				//Snake_Y = Snake_Y + TAILLE_CASE;
				direction_actuelle = 3;

			}

			if (touche == XK_space && still_playing == 1)
			{
				if (pause == 1)
				{
					pause = 0;
					coloriage();

				} else {

					pause = 1;
					paused();
				}
			}

			if (direction_actuelle != direction_ancienne)
			{
				//printf("virage !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				changement = 0;

				//virage(Snake_X,Snake_Y,taille,direction_ancienne);
			}

			direction_ancienne = direction_actuelle;

		}

		if (still_playing == 1)
		{
			
			//on affiche les pastilles
			for (int i = 0; i < 5; ++i)
			{
				afficherPastille(convertToPix(pastille[i][1]), convertToPix(pastille[i][2]));
			}

	///////////////////////////////////////////////////////////////
	/**               MISE A JOUR DES POSITIONS                 **/
	///////////////////////////////////////////////////////////////

			headSnake.oldX = headSnake.newX;
			headSnake.oldY = headSnake.newY;

			tailSnake[0].oldX = headSnake.oldX;
			tailSnake[0].oldY = headSnake.oldY;

			for (int i = 1; i <= taille; ++i)
			{
				tailSnake[i].oldX = tailSnake[i].newX;
				tailSnake[i].oldY = tailSnake[i].newY;
			}

			if (scoring >= 15)
			{
				rampe = 40000L;
			}

			snakeHead(headSnake.newX, headSnake.newY);


		}
	}




}