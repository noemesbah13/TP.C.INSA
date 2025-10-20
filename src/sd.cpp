#include <stdio.h>
#include <stdlib.h>
#include "sd.h"
#include <Fat16.h>
#include <Fat16util.h>
#include "lcd.h"
#include "nfc.h"

struct element 
{
    Tag tag;
    struct element* suivant;
};

struct element* racine = nullptr;



void ajouter(Tag tag)
{
    if(contient(tag))
    {
        //la liste contient déjà la tag, il n'y a rien à faire.
        return;
    }

    struct element* nouveau = (struct element*) malloc(sizeof(struct element));
    //Ajouter dynamiquement en mémoire un nouvel élément, permet de s'assurer 
    //que cet élément existe toujours pendant l'éxecution du programme même après 
    //la fin de l'execution de la fonction ajouter.
    nouveau->tag= tag; //on stocke la tag dans notre nouvel élément.
    nouveau->suivant = nullptr;

    struct element** dernier = &racine; //Début de la liste
    while(*dernier != nullptr) //recherche du dernier élément, tant qu'il ne s'agit pas du dernier element, on passe l'élément suivant.
    {
        dernier = &((*dernier)->suivant);
    }
    *dernier = nouveau; //Ajout du nouvel élément à la fin de la liste.
}

//Parcourir la liste est verifie si il contient la tag donnée en paramètre.
int contient(Tag tag)
{
    struct element* courant = racine;
    //Parcourt de la liste
    while(courant != nullptr)
    {
        //Verification de la tag du noeud courant
        if(tag_are_equals(courant->tag,tag))
        {
            //La liste contient la tag recherchée
            return 1;
        }
        courant = courant->suivant;
    }
    //La liste ne contient pas la tag recherchée
    return 0;
}

void supprimer(Tag tag)
{
    if(!contient(tag))
    {
        //la liste ne contient pas la tag, il n'y a rien à faire.
        return;
    }

    struct element** precedent = &racine; //Début de la liste
    struct element* suivant= racine;

    while(*precedent != nullptr)
    {
        if(tag_are_equals((*precedent)->tag,tag))
        {
            //Il s'agit de l'element que l'on recherche
            struct element* elementASupprimer=*precedent;
            *precedent = (*precedent)->suivant;
            free(elementASupprimer);
            return;
        }
    precedent = &((*precedent)->suivant);
    }
}

int taille()
{
    int taille = 0;
    struct element* courant = racine;
    while(courant != nullptr)
    {
        taille++;
        courant = courant->suivant;
    }
    return taille;
}
