#ifndef WRITE_SPIM_H
#define WRITE_SPIM_H

#include "../include/quad.h"
#include "../include/table_symb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// int write_quad_spim(quad q){

//     switch(q.q_type){
//         case Q_PUSH_CTX:
//             break;
//         default:
//             break;
//     }

//     return 0;
// }

//Distance entre le sommet de la pile (au ctx1) et le symbole répondant au nom de str
int place_pile(char* str, ctx* ctx1);


int write_data_spim                 (ctx* tab_symbole, FILE* f_ptr);
int write_push_ctx_spim             (quad q, ctx* tab_symbole, ctx** ite, FILE* f_ptr);
int write_pop_ctx_spim              (quad q, ctx* tab_symbole, ctx** ite, FILE* f_ptr);
int write_copy_spim                 (quad q, ctx* ite, FILE* f_ptr);
int write_arith_spim                (quad q, ctx* ite, FILE* f_ptr);
int write_neg_spim                  (quad q, ctx* ite, FILE* f_ptr);
int write_goto_spim                 (quad q, FILE* f_ptr);
int write_if_spim                   (quad q, ctx* ite, FILE* f_ptr);
int write_boolean_op_spim           (quad q, ctx* ite, FILE* f_ptr);
int write_break_loop_spim           (quad q, ctx* ite, FILE* f_ptr);
int write_def_meth_spim             (quad q, ctx* ite, FILE* f_ptr);
int write_return_spim               (quad q, ctx* ite, FILE* f_ptr);
int write_end_meth_spim             (quad q, ctx* ite, FILE* f_ptr);
int write_param_spim                (quad q, ctx* ite, FILE* f_ptr);
int write_call_meth_spim            (quad q, ctx* ite, FILE* f_ptr);

#endif