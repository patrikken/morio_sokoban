#include "fichier.h"
#include "jeu.h"

void editeur(SDL_Surface *ecran){
SDL_Surface *mario=NULL, *mur=NULL, *caisse=NULL, *caisseok=NULL, *objectif=NULL;
SDL_Rect position, positionJoueur;
SDL_Event event;
int objetactuel,continuer=1 , ClicGauch=0,ClicDroi=0 , i=0, j=0;
int carte[Nb_bloc_largeur][Nb_bloc_hauteur]={0};
FILE* fichier=NULL;

fichier=fopen("niveau.lvl","w");
// initialisation des surfaces
mur=IMG_Load("sprites/mur.jpg");
mario=IMG_Load("sprites/mario_bas.gif");
caisse=IMG_Load("sprites/caisse.jpg");
caisseok=IMG_Load("sprites/caisse_ok.jpg");
objectif=IMG_Load("sprites/objectif.png");
objetactuel=Mur;
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 255,255,255));
//SDL_EnableKeyRepeat(3000,3000);
//if(!chargerNivo(carte)) return;
// construction
while(continuer){
SDL_PollEvent(&event);

switch(event.type){

case SDL_QUIT: continuer=0; break;
case SDL_MOUSEBUTTONDOWN:
    if(event.button.button==SDL_BUTTON_LEFT){

        carte[event.button.x/Taille_bloc][event.button.y/Taille_bloc]=objetactuel;
        ClicGauch=1;
    }else if(event.button.button==SDL_BUTTON_RIGHT){
        carte[event.button.x/Taille_bloc][event.button.y/Taille_bloc]=Vide;
        ClicDroi=1;
    } break;
case SDL_MOUSEBUTTONUP:
    if(event.button.button==SDL_BUTTON_LEFT)
    ClicGauch=0;
    else if(event.button.button==SDL_BUTTON_RIGHT)
        ClicDroi=0;
    break;
case SDL_MOUSEMOTION :

if(ClicGauch)
{
carte[event.motion.x/Taille_bloc][event.motion.y/Taille_bloc]=objetactuel;
}else if(ClicDroi)
{
carte[event.motion.x/Taille_bloc][event.motion.y/Taille_bloc]=Vide;
}

case SDL_KEYDOWN:
switch(event.key.keysym.sym){
case SDLK_ESCAPE: continuer=0; break;
case SDLK_s:  SauverNiv(carte);break;
case SDLK_c:  chargerNivo(carte,fichier,&positionJoueur);break;
case SDLK_1:  objetactuel=Mur;break;
case SDLK_2:  objetactuel=Caisse;break;
case SDLK_3:  objetactuel=Objectif;break;
case SDLK_4:  objetactuel=Mario; break;
case SDLK_5:  objetactuel=Caisse_ok; break;
};break;
}
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 0,0,0));
for(i=0;i<Nb_bloc_largeur;i++){
    for(j=0;j<Nb_bloc_hauteur;j++){
        position.x=i*Taille_bloc;
        position.y=j*Taille_bloc;
        switch(carte[i][j]){
            case Mur: SDL_BlitSurface(mur,NULL,ecran,&position); break;
            case Objectif: SDL_BlitSurface(objectif,NULL,ecran,&position); break;
            case Caisse: SDL_BlitSurface(caisse,NULL,ecran,&position); break;
            case Mario:SDL_BlitSurface(mario,NULL,ecran,&position); break;
            case Caisse_ok:SDL_BlitSurface(caisseok,NULL,ecran,&position); break;
        }

    }
}
SDL_Flip(ecran);
}


SDL_FreeSurface(caisse);
SDL_FreeSurface(caisseok);
SDL_FreeSurface(objectif);
SDL_FreeSurface(mario);
fclose(fichier);
return;
}

/*  Mario sodoban

Par Patrik Kenfack

Main du jeux

*/


