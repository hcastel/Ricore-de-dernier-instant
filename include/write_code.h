#ifndef WRITE_CODE_H
#define WRITE_CODE_H

#include "../include/quad.h"
#include "../include/table_symb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct types_liste {
    type_simple* list;
    quad_op* list_arg;
    int size;
};
typedef struct types_liste types_liste;


struct control_liste{
    int* l_return;
    int* l_break;
    int* l_continue;
    int* l_next;

    int size_return;
    int size_break;
    int size_continue;
    int size_next;

    type_simple type_return;
};
typedef struct control_liste control_liste;


struct expr_val{

    type_simple type;    
    
    union result{
        
        quad_op qo;
        struct liste_bool{
            int size_true;
            int size_false;

            int* liste_true;
            int* liste_false;
        } liste_bool;

    } result;
    
    quad_op dplc;

};
typedef struct expr_val expr_val;

void gencode
(void** code_inter, int* next_quad, q_type operation, quad_op q1, quad_op q2, quad_op q3);
void complete_liste
(void** code_inter, int* l, int size, int q);


void write_location_bool_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val* res);
void write_location_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val* res);
int write_bool_to_expr
(void** code_inter, int* next_quad, expr_val t1, expr_val* res);
int write_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val* res);
int write_op_arith_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t4, expr_val* res, int op);
int write_op_log_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t3, expr_val* res, int op);
int write_op_eq_bool_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, int m3 ,expr_val t4, expr_val* res, int op);
int write_op_eq_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t4, expr_val* res, int op);
int write_or_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, int m3, expr_val t4, expr_val* res);
int write_and_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, int m3, expr_val t4, expr_val* res);
int write_neg_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t2, expr_val* res);
int write_not_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t2, expr_val* res);


void write_inc_dec
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t3, int op);
void write_assign_bool
(void** code_inter, int* next_quad, ctx* current_ctx, expr_val t1, expr_val t3);


void write_empty_stat(control_liste* res);

void write_if_stat
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t3, int m5, control_liste t6, control_liste* res);
void write_if_else_stat
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t3, 
 int m5, control_liste t6, control_liste n8, int m9, control_liste t10, control_liste* res);

void write_end_loop_for_stat
(void** code_inter, int* next_quad, ctx** current_ctx, int* num_temp, char* id2, int m8, control_liste t10);

void write_return_stat
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t2, control_liste* res);



void write_method_call
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, symbole* s_meth ,types_liste t3, expr_val* res);



void write_method_void_decl_args
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, symbole* s_meth, types_liste t6);
#endif