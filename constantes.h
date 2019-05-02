/*

contantes.h

définir les constante pour le jeux

auteur patrik kenfack

derniere modification: 03/03/2015
*/
#ifndef Def_Constantes
#define Def_Constantes

    #define Taille_bloc         34//taille d'un bloc carré constante
    #define Nb_bloc_largeur     12
    #define Nb_bloc_hauteur     12
    #define Largeur_fenetre     Nb_bloc_largeur * Taille_bloc
    #define hauteur_fenetre     Nb_bloc_hauteur * Taille_bloc


    enum{Haut, Bas, Gauche, Droite};
    enum{Vide, Mur, Caisse, Objectif, Mario, Caisse_ok};

#endif

// structre de pile pour les retours dans le jeux
int chargerNivo(int carte[][Nb_bloc_hauteur],FILE* fichier,SDL_Rect* pos);

void deplaceJoueur(int carte[][Nb_bloc_hauteur], SDL_Rect* pos, int direction);

int SauverNiv1(int carte[][Nb_bloc_hauteur]);


typedef struct Pile{
        int carte[Nb_bloc_largeur][Nb_bloc_hauteur];
        struct Pile* svt;
}Pile;

void empiler(Pile* P1,int cart[][Nb_bloc_hauteur]){
    Pile* p; int i,j;
    p=(Pile*)malloc(sizeof(Pile));
    if(p==NULL) return;
    for(i=0;i<Nb_bloc_largeur;i++){
        for(j=0;j<Nb_bloc_hauteur;j++){
            P1->carte[i][j]=cart[i][j];
        }
    }
    p->svt=P1;
    P1=p;
    free(p);
}
int depiler(Pile *p1,int cart[][Nb_bloc_hauteur]){
    int i,j;
    Pile* p=p1;
if(p1==NULL) return 1;
for(i=0;i<Nb_bloc_largeur;i++){
        for(j=0;j<Nb_bloc_hauteur;j++){
            cart[i][j]=p->carte[i][j];
        }
    }
    p1=p1->svt;
    free(p);
    return 0;
}


void deplaceCaisse(int *PerCase,int *secCase);

void deplaceJoueur(int carte[][Nb_bloc_hauteur], SDL_Rect* pos, int direction){

/// ***********Gestion des collisions*************

switch(direction){

    case Haut:
    if(pos->y-1<0) break;
    if(carte[pos->x][pos->y-1]==Mur) break; // arret en cas de présence de Mur
    if((carte[pos->x][pos->y-1]==Caisse || carte[pos->x][pos->y-1]==Caisse_ok)&&(pos->y-2<0 || carte[pos->x][pos->y-2]==Mur || carte[pos->x][pos->y-2]==Caisse || carte[pos->x][pos->y-2]==Caisse_ok)) break;
   deplaceCaisse(&carte[pos->x][pos->y-1],&carte[pos->x][pos->y-2]);
     SDL_Delay(50);pos->y--; break;
    case Droite :
        if(pos->x+1 > Nb_bloc_largeur-1) break;
            if(carte[pos->x+1][pos->y]==Mur) break;
                if((carte[pos->x+1][pos->y]==Caisse || carte[pos->x+1][pos->y]==Caisse_ok) && (pos->x+1>Nb_bloc_largeur || carte[pos->x+2][pos->y]==Mur || carte[pos->x+2][pos->y]==Caisse || carte[pos->x+2][pos->y]==Caisse_ok)) break;
            deplaceCaisse(&carte[pos->x+1][pos->y],&carte[pos->x+2][pos->y]);
       SDL_Delay(50); pos->x++; break;
    case Gauche:
        if(pos->x-1<0) break;
            if(carte[pos->x-1][pos->y]==Mur) break;

                if((carte[pos->x-1][pos->y]==Caisse || carte[pos->x-1][pos->y]==Caisse_ok) && (pos->x-2<0 || carte[pos->x-2][pos->y]==Mur || carte[pos->x-2][pos->y]==Caisse || carte[pos->x-2][pos->y]==Caisse_ok)) break;

            deplaceCaisse(&carte[pos->x-1][pos->y],&carte[pos->x-2][pos->y]);
        SDL_Delay(50);pos->x--;break;
    case Bas:
        if(pos->y+1>Nb_bloc_hauteur-1) break;
            if(carte[pos->x][pos->y+1]==Mur) break;
                if((carte[pos->x][pos->y+1]==Caisse || carte[pos->x][pos->y+1]==Caisse_ok)&&(pos->y+2<0 || carte[pos->x][pos->y+2]==Mur || carte[pos->x][pos->y+2]==Caisse || carte[pos->x][pos->y+2]==Caisse_ok)) break;
            deplaceCaisse(&carte[pos->x][pos->y+1],&carte[pos->x][pos->y+2]);
        SDL_Delay(50);pos->y++;break;
        SDL_Delay(50);pos->y++;break;

}
}
void deplaceCaisse(int *PerCase,int *secCase){

    if(*PerCase==Caisse || *PerCase==Caisse_ok){

        if(*secCase==Objectif)
            *secCase=Caisse_ok;
        else   *secCase=Caisse;
        if(*PerCase==Caisse_ok)
                *PerCase=Objectif;
        else *PerCase=Vide;

    }

}




int chargerNivo(int carte[][Nb_bloc_hauteur],FILE* fichier,SDL_Rect* pos){


char LigneFichier[Nb_bloc_hauteur*Nb_bloc_largeur+1]={0};

int i=0, j=0;


if(fichier==NULL) return 0;

fgets(LigneFichier,Nb_bloc_hauteur*Nb_bloc_largeur+1,fichier);

for(i=0;i<Nb_bloc_largeur;i++){
    for(j=0;j<Nb_bloc_hauteur;j++){
        switch(LigneFichier[(i*Nb_bloc_largeur)+j]){

            case '0':
            carte[j][i]=0;break;
            case '1':
            carte[j][i]=1;break;
            case '2':
            carte[j][i]=2;break;
            case '3':
            carte[j][i]=3;break;
            case '4':
            carte[j][i]=4;break;
            case '5':
            carte[j][i]=5;break;

        }
    }

}
fclose(fichier);
for(i=0;i<Nb_bloc_largeur;i++){
    for(j=0;j<Nb_bloc_hauteur;j++){

    if(carte[i][j]== Mario){
    pos->x=i;
    pos->y=j;
    carte[i][j]=Vide;
    }
    }
}
return 1;
}

int SauverNiv(int carte[][Nb_bloc_hauteur]){
int i,j;
FILE* fichier;
fichier=fopen("niveau.lvl","w");
for(i=0;i<Nb_bloc_largeur;i++){
    for(j=0;j<Nb_bloc_hauteur;j++){
        fprintf(fichier,"%d",carte[j][i]);
    }
}
fclose(fichier);
return 1;
}

int SauverNiv1(int carte[][Nb_bloc_hauteur]){
int i,j;
FILE* fichier;
fichier=fopen("sauvInt.lvl","w");
for(i=0;i<Nb_bloc_largeur;i++){
    for(j=0;j<Nb_bloc_hauteur;j++){
        fprintf(fichier,"%d",carte[j][i]);
    }
}
fclose(fichier);
return 1;
}

