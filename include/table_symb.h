#ifndef TAB_SYM_H
#define TAB_SYM_H

#include "../include/quad.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct symbole {

    enum fonction {
        F_VAR,
        F_TEMP,
        F_ARG,
        F_METH,    

        F_TAB,        
        F_VAR_GLB,
        F_STRING,
    } fonction;

    union type {
        type_simple simple;

        struct proc {
            int nb_arg;
            type_simple* arg;
            type_simple retour;
        } proc;

        struct tab {
            int size;
            type_simple simple; 
        } tab;

        struct str {
            int nb_char;
            char* val;
        } str;

    } type;

    char* name;
};
typedef struct symbole symbole;

typedef struct contexte ctx; 
struct contexte {
    enum ctx_type {
        CTX_SIMP,
        CTX_FOR,
        CTX_METH,
    } ctx_type;
    int size_tab;
    int size_next;
    symbole* tab;
    ctx* prec;
    ctx** next;
    int marqueur;
};


ctx* push_ctx(ctx* ctx_cour, enum ctx_type type);
symbole* look_up(char* name, ctx* ctx_cour);
int dans_ctx_for(ctx* ctx_cour);

symbole* newname_var(char* name, type_simple type, ctx* current_ctx);
symbole* newname_string(char* str, ctx* current_ctx, int* num_temp);
symbole* newname_var_glb(char* name, type_simple type, ctx* current_ctx);
symbole* newname_arg(char* name, type_simple type, ctx* current_ctx);
symbole* newname_proc(char* name, int* arg_type, int size_arg, type_simple return_type, ctx* current_ctx);
symbole* newname_proc_ext(char* name, int* arg_type, int size_arg, type_simple return_type, ctx* current_ctx);
symbole* newname_tab(char* name, type_simple type, int size, ctx* current_ctx);
symbole* newname_temp(type_simple type, ctx* current_ctx, int* num_temp);

void free_table_symb(ctx* ctx_first);

char* print_type_simple(int t);
void print_symb(symbole* s);
void print_tab_symb(ctx* ctx, int decal);


#endif