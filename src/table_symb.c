#ifndef TAB_SYM_C
#define TAB_SYM_C

#include "../include/table_symb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ctx* push_ctx(ctx* ctx_cour, enum ctx_type type) {
    ctx* new_ctx = malloc(sizeof(ctx));

    new_ctx->ctx_type = type;
    new_ctx->prec = ctx_cour;
    new_ctx->next = NULL;
    new_ctx->tab = NULL;
    new_ctx->size_tab = 0;
    new_ctx->size_next = 0;
    new_ctx->marqueur = 0;

    if(ctx_cour!=NULL){
        ctx_cour->size_next++;
        ctx_cour->next = realloc(ctx_cour->next,ctx_cour->size_next*sizeof(ctx*));
        ctx_cour->next[ctx_cour->size_next-1] = new_ctx;        
    }

    return new_ctx;
}

symbole* look_up(char* name, ctx* ctx_cour) {

    ctx* it_ctx = ctx_cour;
    symbole* res = NULL;

    while( it_ctx!=NULL ) {
        //printf("RECH\n");
        for(int i = 0; i<it_ctx->size_tab; i++) {
            if( strcmp(it_ctx->tab[i].name,name)==0 ) {
                res = &(it_ctx->tab[i]);
                return res;
            }
        }
        it_ctx = it_ctx->prec;

    }

    return res;
}

int dans_ctx_for(ctx* ctx_cour) {
    ctx* it_ctx = ctx_cour;

    while( it_ctx!=NULL ) {
        if( it_ctx->ctx_type==CTX_FOR ){
            return 1;
        }
        it_ctx = it_ctx->prec;
    }

    return 0;    
}

// Regroupe var, var_glb et arg
symbole* newname_simpvar(int fct, char* name, type_simple type, ctx* current_ctx) {
    if(!check_unicity(name, current_ctx)) return NULL;

    int ind_symb = current_ctx->size_tab++;

    current_ctx->tab = realloc(current_ctx->tab,(ind_symb+1)*sizeof(symbole));
    current_ctx->tab[ind_symb].name = name;
    current_ctx->tab[ind_symb].fonction = (enum fonction) fct;
    current_ctx->tab[ind_symb].type.simple = type;

    return &(current_ctx->tab[ind_symb]);
}

symbole* newname_var(char* name, type_simple type, ctx* current_ctx) {
    return newname_simpvar(F_VAR, name, type, current_ctx);
}

symbole* newname_var_glb(char* name, type_simple type, ctx* current_ctx) {
    return newname_simpvar(F_VAR_GLB, name, type, current_ctx);
}

symbole* newname_arg(char* name, type_simple type, ctx* current_ctx) {
    return newname_simpvar(F_ARG, name, type, current_ctx);
}

symbole* newname_proc(char* name, int* arg_type, int size_arg, type_simple return_type, ctx* current_ctx) {
    if(!check_unicity(name, current_ctx)) return NULL;

    int ind_symb = current_ctx->size_tab++;

    current_ctx->tab = realloc(current_ctx->tab,(ind_symb+1)*sizeof(symbole));
    current_ctx->tab[ind_symb].name = name;
    current_ctx->tab[ind_symb].fonction = F_METH;
    current_ctx->tab[ind_symb].type.proc.nb_arg = size_arg;
    current_ctx->tab[ind_symb].type.proc.arg = arg_type;
    current_ctx->tab[ind_symb].type.proc.retour = return_type;

    return &(current_ctx->tab[ind_symb-1]);
}

symbole* newname_proc_ext(char* name, int* arg_type, int size_arg, type_simple return_type, ctx* current_ctx) {
    char* name_meth_ext = malloc(strlen(name)*sizeof(char));
    strcpy(name_meth_ext,name);

    return newname_proc(name_meth_ext,arg_type,size_arg,return_type,current_ctx);
}


symbole* newname_tab(char* name, type_simple type, int size, ctx* current_ctx) {
    if(!check_unicity(name, current_ctx)) return NULL;
    
    int ind_symb = ++current_ctx->size_tab;

    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    current_ctx->tab[ind_symb-1].name = name;
    current_ctx->tab[ind_symb-1].fonction = F_TAB;
    current_ctx->tab[ind_symb-1].type.tab.size = size; 
    current_ctx->tab[ind_symb-1].type.tab.simple = type; 

    return &(current_ctx->tab[ind_symb-1]);
}

//attention taille de name
symbole* newname_temp(type_simple type, ctx* current_ctx, int* num_temp) {
    int ind_symb = ++current_ctx->size_tab;
    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    current_ctx->tab[ind_symb-1].name = malloc(10*sizeof(char));
    snprintf(current_ctx->tab[ind_symb-1].name,10,"%iTEMP",*num_temp);
    current_ctx->tab[ind_symb-1].fonction = F_TEMP;
    current_ctx->tab[ind_symb-1].type.simple = type; 

    (*num_temp)++;

    return &(current_ctx->tab[ind_symb-1]);
}

symbole* newname_string(char* str, ctx* current_ctx, int* num_temp) {
    int ind_symb = ++current_ctx->size_tab;
    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    current_ctx->tab[ind_symb-1].name = malloc(10*sizeof(char));
    snprintf(current_ctx->tab[ind_symb-1].name,10,"STR%i",*num_temp);
    current_ctx->tab[ind_symb-1].fonction = F_STRING;
    current_ctx->tab[ind_symb-1].type.str.nb_char = strlen(str);
    current_ctx->tab[ind_symb-1].type.str.val = str;

    (*num_temp)++;

    return &(current_ctx->tab[ind_symb-1]);
}

void free_table_symb(ctx* ctx_first) {
    if(ctx_first==NULL)
        return;
    
    for(int k=0; k<ctx_first->size_next; k++){
        free_table_symb(ctx_first->next[k]);    
    }
    for(int i=0; i<ctx_first->size_tab; i++) {
        if(ctx_first->tab[i].fonction==F_METH){
//AJOUTER FREE DE LA TABLE DES ARGUMENTS

            free(ctx_first->tab[i].type.proc.arg);
        }
        free(ctx_first->tab[i].name);
    }
}

char* print_type_simple(int t) {
    if( t==T_INT )          { return "INT"; }
    else if ( t==T_BOOL )   { return "BOOL"; }
    else if ( t== T_VOID )  { return "VOID"; }
    else if ( t==T_STRING ) { return "STRING"; }
    return "RIEN";
}

void print_symb(symbole* s){
    int f = s->fonction;
    
    if ( f==F_METH ) {
        printf("%s(",print_type_simple(s->type.proc.retour));
        for(int i=0; i<s->type.proc.nb_arg; i++) {
            printf(" %s ",print_type_simple(s->type.proc.arg[i]));
        }
        printf("):\t%s",s->name);

    } else if ( f==F_TAB ) {
        printf("%s[%i]:\t%s",print_type_simple(s->type.tab.simple),s->type.tab.size,s->name);

    } else if ( f==F_STRING) {
        printf("%s:\t%s",s->name,s->type.str.val);

    } else {
        printf("%s:\t%s",print_type_simple(s->type.simple),s->name);
    } 
}

//print_tab_symb en recurrence
void print_tab_symb(ctx* ctx, int decal){
    if(ctx==NULL){
        printf("Table symbole vide\n");
        return;
    }

    if(ctx->prec==NULL){
        //table globale
        int compt_meth = 0;
        for(int i=0; i<ctx->size_tab; i++){
            printf("-");
            print_symb(&(ctx->tab[i]));

            if(ctx->tab[i].fonction==F_METH
            && strcmp(ctx->tab[i].name,"WriteInt")!=0
            && strcmp(ctx->tab[i].name,"ReadInt")!=0
            && strcmp(ctx->tab[i].name,"WriteBool")!=0){
                printf("\n");
                print_tab_symb(ctx->next[compt_meth],decal+1);   
                compt_meth++;
            }         

            printf("\n");
        }
    } else {
        for(int i=0; i<ctx->size_tab; i++) {
            for(int j=0; j<decal; j++){
                printf("\t");
            }
            printf("-");
            print_symb(&(ctx->tab[i]));
            printf("\n");
        }

        for(int k=0; k<ctx->size_next; k++){
            print_tab_symb(ctx->next[k],decal+1);        
        }        
    }
}

int check_unicity(char* name, ctx* current_ctx){
    for(int i = 0; i<current_ctx->size_tab; i++) {
        if( strcmp(current_ctx->tab[i].name,name)==0 ) {
            return 0;
        }
    }
    return 1;
}

#endif