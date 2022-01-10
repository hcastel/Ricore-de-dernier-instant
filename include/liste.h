#ifndef LISTE_H
#define LISTE_H

#include "../include/quad.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//creer une liste vide et met size à 0
int* creer_liste_vide(int* size);
//creer une liste de taille 1 contenant first_elem, size est mis à 1
int* creer_liste(int first_elem, int* size);
//concatene 2 listes et les libere pour rendre une nouvelle de taille size_res
int* concat_listes(int* l1, int* l2, int size1, int size2, int* size_res);
//concatene une liste et un entier p2 pour rendre une nouvelle liste de taille size_res
int* concat_liste_int(int* p1, int p2, int size1, int* size_res);
//affiche la liste l
void print_liste(int* l, int s);

#endif