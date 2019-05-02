/*  Mario sodoban

Par Patrik Kenfack

Main du jeux

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>


#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "editeur.c"
#include "fichier.h"

void play(SDL_Surface *ecran);

int main(int argc, char *argv[]){

SDL_Surface *ecran=NULL , *menu=NULL, *im=NULL;
SDL_Rect positionMenu,pos;
SDL_Event event;

int continuer=1;

SDL_Init(SDL_INIT_VIDEO);

positionMenu.x=0;
positionMenu.y=0;
SDL_WM_SetIcon(IMG_Load("sprites/ma.ico"),NULL);

ecran=SDL_SetVideoMode(hauteur_fenetre,Largeur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

SDL_WM_SetCaption("Mario sokoban | by patrik kenfack",NULL);

menu=IMG_Load("sprites/man.png");

SDL_BlitSurface(menu,NULL,ecran,&positionMenu);
SDL_Flip(ecran);

while(continuer){

SDL_WaitEvent(&event);

switch(event.type){

case SDL_QUIT :  continuer=0; break; // arret du jeu

case SDL_KEYDOWN :

switch(event.key.keysym.sym){

    case SDLK_ESCAPE: continuer=0; break; // arret du jeu
    case SDLK_1:  play(ecran); break;   // acces au jeu
    case SDLK_2: editeur(ecran); break;   // acces à l'éditeur de niveau

}


}
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 15,67,255));
SDL_BlitSurface(menu,NULL,ecran,&positionMenu);

SDL_Flip(ecran);

}


SDL_FreeSurface(menu);
SDL_Quit();
return 0;

}

void play(SDL_Surface *ecran){

SDL_Surface *mario[4];
SDL_Surface *mur=NULL, *caisse=NULL, *caisseok=NULL, *marioactuel=NULL, *objectif=NULL;
SDL_Rect position, positionJoueur;
SDL_Event event;
int continuer=1 , Ojectifrestant=0 , i=0, j=0, k=0,back=0;;
Pile* p=NULL;
p=(Pile *)malloc(sizeof(Pile));
FILE* tab[16];
tab[0]=fopen("niveau.lvl","r");
tab[1]=fopen("soko lvl/niveaux1.lvl","r");
tab[2]=fopen("soko lvl/niveaux2.lvl","r");
tab[3]=fopen("soko lvl/niveaux3.lvl","r");
tab[4]=fopen("soko lvl/niveaux4.lvl","r");
tab[5]=fopen("soko lvl/niveaux5.lvl","r");
tab[6]=fopen("soko lvl/niveaux6.lvl","r");
tab[7]=fopen("soko lvl/niveaux7.lvl","r");
tab[8]=fopen("soko lvl/niveaux8.lvl","r");
tab[9]=fopen("soko lvl/niveaux9.lvl","r");
tab[10]=fopen("soko lvl/niveaux10.lvl","r");
tab[11]=fopen("soko lvl/niveaux11.lvl","r");
tab[13]=fopen("soko lvl/niveaux13.lvl","r");
tab[12]=fopen("soko lvl/niveaux12.lvl","r");
tab[14]=fopen("soko lvl/niveaux14.lvl","r");
tab[15]=fopen("soko lvl/niveaux15.lvl","r");
tab[16]=fopen("sauvInt.lvl","r");

int carte[Nb_bloc_largeur][Nb_bloc_hauteur]={0};

// initialisation des surfaces
mur=IMG_Load("sprites/mur.jpg");
caisse=IMG_Load("sprites/caisse.jpg");
caisseok=IMG_Load("sprites/caisse_ok.jpg");
objectif=IMG_Load("sprites/objectif.png");
mario[Bas]=IMG_Load("sprites/mario_bas.gif");
mario[Haut]=IMG_Load("sprites/mario_haut.gif");
mario[Droite]=IMG_Load("sprites/mario_droite.gif");
mario[Gauche]=IMG_Load("sprites/mario_gauche.gif");
marioactuel=mario[Bas];

SDL_EnableKeyRepeat(100,100);
chargerNivo(carte,tab[k],&positionJoueur);

// construction

while(continuer){

if(!Ojectifrestant)
{
     k++;
          back=0;
                  chargerNivo(carte,tab[k],&positionJoueur);

                                    SDL_WM_SetCaption("Mario sokoban by Patrik kenfack lvl",NULL);
}
if(back==1){chargerNivo(carte,tab[k],&positionJoueur);}
SDL_WaitEvent(&event);
Ojectifrestant=0;

SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 0,0,0));
for(i=0;i<=Nb_bloc_largeur;i++){

    for(j=0;j<=Nb_bloc_hauteur;j++){

            position.x=i*Taille_bloc;
            position.y=j*Taille_bloc;
        switch(carte[i][j]){

            case Mur:
             SDL_BlitSurface(mur,NULL,ecran,&position); break;
             case Caisse:
             SDL_BlitSurface(caisse,NULL,ecran,&position);
             break;
             case Caisse_ok:
             SDL_BlitSurface(caisseok,NULL,ecran,&position);
             break;
             case Objectif:
             SDL_BlitSurface(objectif,NULL,ecran,&position);
             Ojectifrestant=1; break;

        }
    }
}
switch(event.type){
case SDL_QUIT: continuer=0; break;
case SDL_KEYDOWN:
back=0;
switch(event.key.keysym.sym){
SauverNiv1(carte);
case SDLK_ESCAPE: continuer=0; break;
case SDLK_DOWN: marioactuel=mario[Bas];deplaceJoueur(carte,&positionJoueur,Bas); break;
case SDLK_UP:marioactuel=mario[Haut];  deplaceJoueur(carte,&positionJoueur,Haut);break;
case SDLK_LEFT: marioactuel=mario[Gauche]; deplaceJoueur(carte,&positionJoueur,Gauche);break;
case SDLK_RIGHT: marioactuel=mario[Droite];  deplaceJoueur(carte,&positionJoueur,Droite);break;
case SDLK_b: back=1;break;
}
}
// blittage du joueur

position.x=positionJoueur.x*Taille_bloc;
position.y=positionJoueur.y*Taille_bloc;
SDL_BlitSurface(marioactuel,NULL,ecran,&position);
SDL_Flip(ecran);
}
for(i=0;i<=16;i++)
fclose(tab[i]);
SDL_FreeSurface(caisse);
SDL_FreeSurface(caisseok);
SDL_FreeSurface(objectif);
for(i=0;i<=3;i++)
SDL_FreeSurface(mario[i]);

return;
}
