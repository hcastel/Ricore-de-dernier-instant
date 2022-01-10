#ifndef LISTE_C
#define LISTE_C


#include "../include/liste.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>








int* creer_liste_vide(int* size){

    *size = 0;
    return NULL;

}
int* creer_liste(int first_elem, int* size){

    *size = 1;
    int* list = malloc(sizeof(int));
    if(list!=NULL){
        list[0] = first_elem;
    }
    
    return list;

}

int* concat_listes(int* l1, int* l2, int size1, int size2, int* size_res){
    
    *size_res = size1 + size2;

    if( size1+size2 == 0 ){
        return NULL;
    }
    if( size1 == 0 ){
        return l2;
    }
    if( size2 == 0 ){
        return l1;
    }

    int* l_res = realloc(l1,(size1+size2)*sizeof(int));
    for(int i = 0; i<size2; i++){
        l_res[i+size1] = l2[i];
    }
    free(l2);

    return l_res;

}
int* concat_liste_int(int* l1, int i2, int size1, int* size_res){
    
    *size_res = size1 + 1;

    int* l_res = realloc(l1,(size1+1)*sizeof(int));
    l_res[size1] = i2;

    return l_res;

}
// void complete_liste(int* l, int size, int q, quad code_inter[]){
//     quad_op res = {QO_CST,q};
//     for(int i = 0; i<size; i++){
//         code_inter[l[i]].q3 = res;
//     }
//     // printf("Fin: ComL\n");
//     free(p);
// }
void print_liste(int* l, int s){
    printf("==Liste==\n");
    if(s==0){
        printf("liste vide");
    } else {
        for(int i = 0; i<s; i++){
            printf("%i:%i, ",i,l[i]);
        }            
    }
    printf("\n");

}


#endif