#ifndef WRITE_CODE_C
#define WRITE_CODE_C


#include "../include/write_code.h"
#include "../include/liste.h"
#include "../include/table_symb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

quad_op cst_vide = {QO_VIDE,-1};
quad_op cst_un = {QO_CST,1};
quad_op cst_zero = {QO_CST,0};



void gencode
(void** code_inter, int* next_quad, q_type operation, quad_op q1, quad_op q2, quad_op q3) {
    quad* code = *((quad**)code_inter);

    code[*next_quad].q_type = operation;
    code[*next_quad].q1 = q1;
    code[*next_quad].q2 = q2;
    code[*next_quad].q3 = q3;

    (*next_quad)++;

}

void complete_liste
(void** code_inter, int* l, int size, int q){

    quad* code = *((quad**)code_inter);

    for(int i = 0; i<size; i++){
        new_qo_cst(q,&(code[l[i]].q3));
    }
    if(size!=0){
        free(l);        
    }
}



void write_location_bool_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val* res){

    res->type = t1.type;
    new_qo_vide(&(res->dplc));

    quad_op qo_res;
    symbole* s_res = newname_temp(T_BOOL,current_ctx,num_temp);
    new_qo_name(s_res->name,&(qo_res));

    gencode(code_inter,next_quad,Q_COPY,t1.result.qo,t1.dplc,qo_res);

    res->result.liste_bool.liste_true = creer_liste((*next_quad),&(res->result.liste_bool.size_true));
    res->result.liste_bool.liste_false = creer_liste((*next_quad)+1,&(res->result.liste_bool.size_false));
    gencode(code_inter,next_quad,Q_IF,qo_res,cst_vide,cst_vide);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,cst_vide); 

}

void write_location_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val* res){

    res->type = t1.type;
    new_qo_vide(&(res->dplc));
    
    symbole* s_res = newname_temp(T_INT,current_ctx,num_temp);
    new_qo_name(s_res->name,&(res->result.qo));

    gencode(code_inter,next_quad,Q_COPY,t1.result.qo,t1.dplc,res->result.qo);

}

int write_bool_to_expr
(void** code_inter, int* next_quad, expr_val t1, expr_val* res){

    res->type = t1.type;
    new_qo_vide(&(res->dplc));

    if( t1.result.qo.qo_valeur.cst == 1 ){
        res->result.liste_bool.liste_true = creer_liste((*next_quad),&(res->result.liste_bool.size_true));
        res->result.liste_bool.liste_false = creer_liste_vide(&(res->result.liste_bool.size_false));
        gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,cst_vide);
    } else {
        res->result.liste_bool.liste_false = creer_liste((*next_quad),&(res->result.liste_bool.size_false));
        res->result.liste_bool.liste_true = creer_liste_vide(&(res->result.liste_bool.size_true));
        gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,cst_vide);                        
    }

    return 0;

}

int write_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val* res){

    res->type = t1.type;
    new_qo_vide(&(res->dplc));

    symbole* s_temp = newname_temp(T_INT, current_ctx, num_temp);
    new_qo_name(s_temp->name,&(res->result.qo));
    gencode(code_inter,next_quad,Q_COPY,t1.result.qo,cst_vide,(*res).result.qo);

    return 0;

}

int write_op_arith_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t3, expr_val* res, int op){
    
    new_qo_vide(&(res->dplc));
    res->type = T_INT;
    symbole* s_temp = newname_temp(T_INT,current_ctx,num_temp);
    new_qo_name(s_temp->name,&(res->result.qo));
    gencode(code_inter,next_quad,op,t1.result.qo,t3.result.qo,res->result.qo);        

    return 0;
}

int write_op_log_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t3, expr_val* res, int op){
    
    new_qo_vide(&(res->dplc));

    res->type = T_BOOL;
    res->result.liste_bool.liste_true = creer_liste((*next_quad),&(res->result.liste_bool.size_true));
    res->result.liste_bool.liste_false = creer_liste((*next_quad)+1,&(res->result.liste_bool.size_false));
    gencode(code_inter,next_quad,op,t1.result.qo,t3.result.qo,cst_vide);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,cst_vide);

    return 0;
}

int write_op_eq_bool_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, int m3 ,expr_val t4, expr_val* res, int op){
    
    res->type = T_BOOL;
    new_qo_vide(&(res->dplc));

    symbole* s_1 = newname_temp(T_BOOL,current_ctx,num_temp);
    symbole* s_2 = newname_temp(T_BOOL,current_ctx,num_temp);
    quad_op b1, b2;
    new_qo_name(s_1->name,&(b1));
    new_qo_name(s_2->name,&(b2));

    quad_op qo_deb_b2 = {QO_CST,m3};
    quad_op qo_next_2 = {QO_CST,(*next_quad)+3};

    //réification de b1
    complete_liste(code_inter,t1.result.liste_bool.liste_true,t1.result.liste_bool.size_true,(*next_quad));
    complete_liste(code_inter,t1.result.liste_bool.liste_false,t1.result.liste_bool.size_false,(*next_quad)+2);
    gencode(code_inter,next_quad,Q_COPY,cst_un,cst_vide,b1);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,qo_next_2);
    gencode(code_inter,next_quad,Q_COPY,cst_zero,cst_vide,b1);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,qo_deb_b2);

    //réification de b2
    qo_next_2.qo_valeur.cst = (*next_quad) + 3;
    complete_liste(code_inter,t4.result.liste_bool.liste_true,t4.result.liste_bool.size_true,(*next_quad));
    complete_liste(code_inter,t4.result.liste_bool.liste_false,t4.result.liste_bool.size_false,(*next_quad)+2);
    gencode(code_inter,next_quad,Q_COPY,cst_un,cst_vide,b2);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,qo_next_2);
    gencode(code_inter,next_quad,Q_COPY,cst_zero,cst_vide,b2);

    //comparaison
    res->result.liste_bool.liste_true = creer_liste((*next_quad),&(res->result.liste_bool.size_true)); 
    res->result.liste_bool.liste_false = creer_liste((*next_quad)+1,&(res->result.liste_bool.size_false));
    gencode(code_inter,next_quad,op,b1,b2,cst_vide);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,cst_vide); 

    return 0;

}

int write_op_eq_int_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t4, expr_val* res, int op){
    
    res->type = T_BOOL;
    new_qo_vide(&(res->dplc));

    res->result.liste_bool.liste_true = creer_liste((*next_quad),&(res->result.liste_bool.size_true));
    res->result.liste_bool.liste_false = creer_liste((*next_quad)+1,&(res->result.liste_bool.size_false));
    gencode(code_inter,next_quad,op,t1.result.qo,t4.result.qo,cst_vide);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,cst_vide); 

    return 0;
}

int write_or_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, int m3, expr_val t4, expr_val* res){
    res->type = T_BOOL;
    new_qo_vide(&(res->dplc));

    complete_liste(code_inter,t1.result.liste_bool.liste_false,t1.result.liste_bool.size_false,m3);
    res->result.liste_bool.liste_true = concat_listes(t1.result.liste_bool.liste_true,t4.result.liste_bool.liste_true,t1.result.liste_bool.size_true,t4.result.liste_bool.size_true,&(res->result.liste_bool.size_true));
    res->result.liste_bool.liste_false = t4.result.liste_bool.liste_false;
    res->result.liste_bool.size_false = t4.result.liste_bool.size_false;

    return 0;
}

int write_and_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, int m3, expr_val t4, expr_val* res){
    res->type = T_BOOL;
    new_qo_vide(&(res->dplc));
    
    res->type = T_BOOL;
    complete_liste(code_inter,t1.result.liste_bool.liste_true,t1.result.liste_bool.size_true,m3);
    res->result.liste_bool.liste_false = concat_listes(t1.result.liste_bool.liste_false,t4.result.liste_bool.liste_false,t1.result.liste_bool.size_false,t4.result.liste_bool.size_false,&(res->result.liste_bool.size_false));
    res->result.liste_bool.liste_true = t4.result.liste_bool.liste_true;
    res->result.liste_bool.size_true = t4.result.liste_bool.size_true;  

    return 0;

}

int write_neg_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t2, expr_val* res){

    new_qo_vide(&(res->dplc));
    res->type = T_INT;

    symbole* s_temp = newname_temp(T_INT,current_ctx,num_temp);
    new_qo_name(s_temp->name,&(res->result.qo));
    gencode(code_inter,next_quad,Q_NEG,t2.result.qo,cst_vide,res->result.qo);

    return 0;

}

int write_not_to_expr
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t2, expr_val* res){

    new_qo_vide(&(res->dplc));
    res->type = T_BOOL;

    res->result.liste_bool.liste_true = t2.result.liste_bool.liste_false;
    res->result.liste_bool.size_true = t2.result.liste_bool.size_false;
    res->result.liste_bool.liste_false = t2.result.liste_bool.liste_true;
    res->result.liste_bool.size_false = t2.result.liste_bool.size_true;

    return 0;

}



void write_inc_dec
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t1, expr_val t3, int op){
    
    symbole* s_temp = newname_temp(T_INT,current_ctx,num_temp);
    quad_op qo_temp;
    new_qo_name(s_temp->name,&(qo_temp));

    if( t1.dplc.qo_type==QO_VIDE ){
        gencode(code_inter,next_quad,op,t1.result.qo,t3.result.qo,qo_temp);   
        gencode(code_inter,next_quad,Q_COPY,qo_temp,cst_vide,t1.result.qo);
    } else {
        //qo_tab_val = la valeur de tab[index]
        quad_op qo_tab_val;
        symbole* s_tab_val = newname_temp(T_INT,current_ctx,num_temp);
        new_qo_name(s_tab_val->name,&(qo_tab_val));

        //on retient la valeur de tab[index] dans qo_tab_val
        gencode(code_inter,next_quad,Q_COPY,t1.result.qo,t1.dplc,qo_tab_val);
        //on soustrait $3 à cette valeur
        gencode(code_inter,next_quad,op,qo_tab_val,t3.result.qo,qo_temp); 
        //on la replace dans le tableau
        gencode(code_inter,next_quad,Q_COPY,qo_temp,t1.dplc,t1.result.qo);
    }
}

void write_assign_bool
(void** code_inter, int* next_quad, ctx* current_ctx, expr_val t1, expr_val t3){

    //reification
    quad_op qo_jumb_false = {QO_CST,(*next_quad)+3};
    complete_liste(code_inter,t3.result.liste_bool.liste_true,t3.result.liste_bool.size_true,(*next_quad));
    complete_liste(code_inter,t3.result.liste_bool.liste_false,t3.result.liste_bool.size_false,(*next_quad)+2);
    gencode(code_inter,next_quad,Q_COPY,cst_un,t1.dplc,t1.result.qo);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,qo_jumb_false);
    gencode(code_inter,next_quad,Q_COPY,cst_zero,t1.dplc,t1.result.qo); 

}



void write_empty_stat(control_liste* res){
    res->l_break = creer_liste_vide(&(res->size_break));
    res->l_continue = creer_liste_vide(&(res->size_continue));
    res->l_return = creer_liste_vide(&(res->size_return));
    res->l_next = creer_liste_vide(&(res->size_next));
    res->type_return = T_VOID;
}



void write_if_stat
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t3, int m5, control_liste t6, control_liste* res){
    complete_liste(code_inter,t3.result.liste_bool.liste_true,t3.result.liste_bool.size_true,m5);
    *res = t6;
    res->l_next = concat_listes(t3.result.liste_bool.liste_false,t6.l_next,t3.result.liste_bool.size_false,t6.size_next,&(res->size_next));
}

void write_if_else_stat
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t3, 
 int m5, control_liste t6, control_liste n8, int m9, control_liste t10, control_liste* res){   
    complete_liste(code_inter,t3.result.liste_bool.liste_true,t3.result.liste_bool.size_true,m5);
    complete_liste(code_inter,t3.result.liste_bool.liste_false,t3.result.liste_bool.size_false,m9);
    int temp_s = 0;
    int* temp_l = concat_listes(t6.l_next,t10.l_next,t6.size_next,t10.size_next,&(temp_s));
    res->l_next = concat_listes(temp_l,n8.l_next,temp_s,n8.size_next,&(res->size_next));
    res->l_break = concat_listes(t6.l_break,t10.l_break,t6.size_break,t10.size_break,&(res->size_break));
    res->l_continue = concat_listes(t6.l_continue,t10.l_continue,t6.size_continue,t10.size_continue,&(res->size_continue));
    res->l_return = concat_listes(t6.l_return,t10.l_return,t6.size_return,t10.size_return,&(res->size_return));
}

void write_end_loop_for_stat
(void** code_inter, int* next_quad, ctx** current_ctx, int* num_temp, char* id2, int m8, control_liste t10){
    
    //On incremente l'itérateur de un et on part sur ite>borne_sup
    complete_liste(code_inter,t10.l_next,t10.size_next,(*next_quad));
    complete_liste(code_inter,t10.l_continue,t10.size_continue,(*next_quad));
    symbole* temp_sum = newname_temp(T_INT,*current_ctx,num_temp);
    quad_op qo_ite, qo_sum, qo_next;
    new_qo_name(look_up(id2,*current_ctx)->name,&(qo_ite));
    new_qo_name(temp_sum->name,&(qo_sum));
    new_qo_cst(m8,&(qo_next));

    gencode(code_inter,next_quad,Q_ADD,cst_un,qo_ite,qo_sum);
    gencode(code_inter,next_quad,Q_COPY,qo_sum,cst_vide,qo_ite);
    gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,qo_next);
    
    //SUITE DU FOR
    //break et la suite du for pointent sur la même instruction
    int size_temp = 0;
    int* temp_list_2 = concat_liste_int(t10.l_break,m8,t10.size_break,&(size_temp));
    complete_liste(code_inter,temp_list_2,size_temp,(*next_quad));
    *current_ctx = (*current_ctx)->prec;
    gencode(code_inter,next_quad,Q_POP_CTX,cst_vide,cst_vide,cst_vide);

}

void write_return_stat
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, expr_val t2, control_liste* res){
    
    quad_op qo_rtn;
    
    if( t2.type==T_INT ){

        res->l_return = creer_liste((*next_quad),&(res->size_return));
        gencode(code_inter,next_quad,Q_RETURN,t2.result.qo,cst_vide,cst_vide);
        res->type_return = T_INT;

    } else if( t2.type==T_VOID ){

        res->l_return = creer_liste((*next_quad),&(res->size_return));
        gencode(code_inter,next_quad,Q_RETURN,cst_vide,cst_vide,cst_vide);  
        res->type_return = T_VOID;

    } else if( t2.type==T_BOOL ){

        //réification
        complete_liste(code_inter,t2.result.liste_bool.liste_true,t2.result.liste_bool.size_true,(*next_quad));
        complete_liste(code_inter,t2.result.liste_bool.liste_false,t2.result.liste_bool.size_false,(*next_quad)+2);
        
        symbole* s_temp = newname_temp(T_BOOL,current_ctx,num_temp);
        quad_op qo_next;
        new_qo_name(s_temp->name,&(qo_rtn));
        new_qo_cst((*next_quad)+3,&qo_next);

        gencode(code_inter,next_quad,Q_COPY,cst_un,cst_vide,qo_rtn);
        gencode(code_inter,next_quad,Q_GOTO,cst_vide,cst_vide,qo_next);
        gencode(code_inter,next_quad,Q_COPY,cst_zero,cst_vide,qo_rtn);

        res->l_return = creer_liste((*next_quad),&(res->size_return));    
        gencode(code_inter,next_quad,Q_RETURN,qo_rtn,cst_vide,cst_vide);  
        res->type_return = T_BOOL;     
    } else {
        res->type_return = T_VOID;
        gencode(code_inter,next_quad,Q_RETURN,cst_vide,cst_vide,cst_vide);
    }

}



void write_method_call
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, symbole* s_meth ,type_liste t3, expr_val* res){

    //renvoi un type
    res->type = s_meth->type.proc.retour;   
    new_qo_vide(&res->dplc);   

    quad_op qo_name_meth, qo_nb_arg;
    new_qo_name(s_meth->name,&(qo_name_meth));
    new_qo_cst(t3.size,&(qo_nb_arg));

    if(s_meth->type.proc.retour==T_VOID){
        new_qo_vide(&(res->result.qo));
    } else {
        new_qo_name(newname_temp(s_meth->type.proc.retour,current_ctx,num_temp)->name,&(res->result.qo));                  
    }

    //appel et mise de la valeur de retour dans la variable
    gencode(code_inter,next_quad,Q_CALL_METH,qo_name_meth,qo_nb_arg,res->result.qo);

    free(t3.list);
    free(t3.list_arg);    

}



void write_method_void_decl_args
(void** code_inter, int* next_quad, ctx* current_ctx, int* num_temp, symbole* s_meth, type_liste t6){

    // symbole* s_meth = look_up($2,(*((ctx**)tab_symbole)));

    quad_op qo_name_meth, qo_nb_arg;
    new_qo_name(s_meth->name,&(qo_name_meth));
    new_qo_cst(t6.size,&(qo_nb_arg));

    current_ctx->ctx_type = CTX_METH;
    gencode(code_inter,next_quad,Q_DEF_METH,qo_name_meth,qo_nb_arg,cst_vide);      
    //on alloue 2 places dans la table des symboles pour symboliser fp et ra
    newname_temp(T_INT,current_ctx,num_temp)->fonction = F_ARG;
    newname_temp(T_INT,current_ctx,num_temp)->fonction = F_ARG;

}




#endif