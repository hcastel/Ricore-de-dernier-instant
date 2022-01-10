#ifndef WRITE_SPIM_C
#define WRITE_SPIM_C


#include "../include/write_spim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




//Distance entre le sommet de la pile (au ctx1) et le symbole répondant au nom de str
int place_pile(char* str, ctx* ctx1){
    int sep = 0;
    int saut = 1;
    ctx* ctx_c = ctx1; 
    while(saut==1 && ctx_c!=NULL){
        int i = ctx_c->size_tab-1;
        int trouve = 0;
        while(i>=0 && trouve==0){
            if(0==strcmp(str,ctx_c->tab[i].name)){
                saut = 0;
                trouve = 1;
            } else {
                sep++;
            }
            i--;
            
        }
        ctx_c = ctx_c->prec;
    }
    return sep;
}


int write_data_spim(ctx* tab_symbole, FILE* f_ptr){
    
    fprintf(f_ptr,"\t.data\n");
    fprintf(f_ptr,"true:\t.asciiz \"true\"\n");
    fprintf(f_ptr,"false:\t.asciiz \"false\"\n");
    fprintf(f_ptr,"error_str_meth:\t.asciiz \"**** Erreur d'execution: Fin textuelle de méthode atteinte.\"\n");
    fprintf(f_ptr,"error_str_tab:\t.asciiz \"**** Erreur d'execution: Acces tableau hors des bornes.\"\n");
    
    for(int i = 0; i<tab_symbole->size_tab; i++){
        if(tab_symbole->tab[i].fonction==F_TAB){
            fprintf(f_ptr,"%s:\t.word ",tab_symbole->tab[i].name);
            for(int j = 0; j<tab_symbole->tab[i].type.tab.size-1; j++){
                fprintf(f_ptr,"0,");
            }
            fprintf(f_ptr,"0\n");
        } else if (tab_symbole->tab[i].fonction==F_VAR_GLB){
            fprintf(f_ptr,"%s:\t.word 0\n",tab_symbole->tab[i].name);
        } else if (tab_symbole->tab[i].fonction==F_STRING){
            fprintf(f_ptr,"%s:\t.asciiz %s\n",tab_symbole->tab[i].name,tab_symbole->tab[i].type.str.val);
        }
    }

    fprintf(f_ptr,"\t.text\n");
    fprintf(f_ptr,"WriteInt:\n\tli $v0, 1\n\tlw $a0, 0($sp)\n\tsyscall\n\tjr $ra\n");
    fprintf(f_ptr,"WriteBool:\n\tlw $t0, 0($sp)\n\tbeqz $t0, labelwbf\nlabelwbt:\n\tli $v0, 4\n\tla $a0, true\n\tsyscall\n\tb labelwbj\nlabelwbf:\n\tli $v0,4\n\tla $a0, false\n\tsyscall\nlabelwbj:\n\tjr $ra\n");
    fprintf(f_ptr,"ReadInt:\n\tli $v0, 5\n\tsyscall\n\tjr $ra\n");
    fprintf(f_ptr,"label_hors_tab:\n\tli $v0, 4\n\tla $a0, error_str_tab\n\tsyscall\n\tli $v0, 10\n\tsyscall\n");

    return 0;

}

int write_push_ctx_spim(quad q, ctx* tab_symbole, ctx** ite, FILE* f_ptr){

    if((*ite)==NULL){
        //ajout premier ctx à ite
        *ite = tab_symbole;
    } else {
        //on parcourt jusqu'à trouver une table fille pas encore visitée
        int i = 0;
        while((*ite)->next[i]->marqueur==1){
            i++;
        }
        *ite = (*ite)->next[i];
    }
    
    for(int j = 0; j<(*ite)->size_tab; j++){
        //F_ARG est informel, on le traite manuellement
        //les autres ne sont pas sur la pile
        if( (*ite)->tab[j].fonction == F_VAR
            || (*ite)->tab[j].fonction == F_TEMP){
            fprintf(f_ptr,"\taddiu $sp, $sp, -4 \t#pile <= %s\n",((*ite)->tab)[j].name);
            fprintf(f_ptr,"\tli $t0, 0\n");
            fprintf(f_ptr,"\tsw $t0, 0($sp)\n");
        }
    }      

    return 0;
}

int write_pop_ctx_spim(quad q, ctx* tab_symbole, ctx** ite, FILE* f_ptr){
    // if((*ite)!=tab_symbole){
        for(int j = 0; j<(*ite)->size_tab; j++){
            //F_ARG est informel, on le traite manuellement
            //les autres ne sont pas sur la pile
            if( (*ite)->tab[j].fonction == F_VAR
             || (*ite)->tab[j].fonction == F_TEMP ){
                fprintf(f_ptr,"\taddiu $sp, $sp, 4 \t#pile => %s\n",(*ite)->tab[j].name);
            }
        }
    // }

    (*ite)->marqueur = 1;
    *ite = (*ite)->prec;  
}

int write_copy_spim(quad q, ctx* ite, FILE* f_ptr){
    //SOURCE
    if( q.q1.qo_type==QO_CST ){
    //src:cst
        fprintf(f_ptr,"\tli $t0, %i\n",q.q1.qo_valeur.cst);
    } else {
    //src:non cst    
        symbole* s1 = look_up(q.q1.qo_valeur.name,ite);
        // symbole* s2 = look_up(q.q2.qo_valeur.name,ite);
        
        if( s1->fonction==F_TAB ){
            

            fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
            fprintf(f_ptr,"\tbge $t0, %i, label_hors_tab\n",s1->type.tab.size);
            fprintf(f_ptr,"\tblt $t0, 0, label_hors_tab\n");
            //on charge le deplacement par rapport à addr tab
            fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
            //on charge addr tab et la ressource qu'elle contient dans $t0
            fprintf(f_ptr,"\tla $t1, %s\n",q.q1.qo_valeur.name);
            fprintf(f_ptr,"\tmul $t0, $t0, 4\n");
            fprintf(f_ptr,"\tadd $t1, $t1, $t0\n");
            fprintf(f_ptr,"\tlw $t0, 0($t1)\n");

        } else if( s1->fonction==F_ARG 
                || s1->fonction==F_TEMP
                || s1->fonction==F_VAR ){
            fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q1.qo_valeur.name,ite));
        } else if( s1->fonction==F_VAR_GLB){
            fprintf(f_ptr,"\tlw $t0, %s\n",q.q1.qo_valeur.name);
        } else {
            fprintf(stderr,"-ERREUR:generationSpim-\tQ_COPY source.");
            exit(1);
        }
    }

    //DESTINATION
    symbole* s3 = look_up(q.q3.qo_valeur.name,ite);
    if( s3->fonction==F_TAB ){
        fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
        fprintf(f_ptr,"\tbge $t1, %i, label_hors_tab\n",s3->type.tab.size);
        fprintf(f_ptr,"\tblt $t1, 0, label_hors_tab\n");
        //on charge le deplacement par rapport à addr tab
        fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
        //on charge addr tab et la ressource qu'elle contient dans $t0
        fprintf(f_ptr,"\tla $t2, %s\n",q.q3.qo_valeur.name);
        fprintf(f_ptr,"\tmul $t1, $t1, 4\n");
        fprintf(f_ptr,"\tadd $t1, $t1, $t2\n");
    } else if( s3->fonction==F_ARG 
            || s3->fonction==F_TEMP
            || s3->fonction==F_VAR ){
        fprintf(f_ptr,"\tla $t1, %i($sp)\n",4*place_pile(q.q3.qo_valeur.name,ite));
    } else if( s3->fonction==F_VAR_GLB ){
        fprintf(f_ptr,"\tla $t1, %s\n",q.q3.qo_valeur.name);
    } else {
        fprintf(stderr,"-ERREUR:generationSpim-\tQ_COPY destination.");
        exit(1);
    }

    fprintf(f_ptr,"\tsw $t0, 0($t1)\n");
    return 0;
}

// int write_copy_spim(quad q, ctx* ite, FILE* f_ptr){
// ///SOURCE
//     if( q.q1.qo_type==QO_CST ){
//     //src:cst
    
//         fprintf(f_ptr,"\tli $t0, %i\n",q.q1.qo_valeur.cst);
    
//     } else {
//     //src:name    
    
//         symbole* s1 = look_up(q.q1.qo_valeur.name,ite);
        
//         if( s1->fonction==F_TAB ){
            
//             fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
//             fprintf(f_ptr,"\tbge $t0, %i, label_hors_tab\n",s1->type.tab.size);
//             fprintf(f_ptr,"\tblt $t0, 0, label_hors_tab\n");
//             //on charge le deplacement par rapport à addr tab
//             fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
//             //on charge addr tab et la ressource qu'elle contient dans $t0
//             fprintf(f_ptr,"\tla $t1, %s\n",q.q1.qo_valeur.name);
//             fprintf(f_ptr,"\tmul $t0, $t0, 4\n");
//             fprintf(f_ptr,"\tadd $t1, $t1, $t0\n");
//             fprintf(f_ptr,"\tlw $t0, 0($t1)\n");

//         } else if( s1->fonction==F_ARG 
//                 || s1->fonction==F_TEMP
//                 || s1->fonction==F_VAR ){
    
//             fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q1.qo_valeur.name,ite));
    
//         } else if( s1->fonction==F_VAR_GLB){
    
//             fprintf(f_ptr,"\tlw $t0, %s\n",q.q1.qo_valeur.name);
    
//         } else {
//             return 1;
//         }
//     }


// ///DESTINATION
//     symbole* s3 = look_up(q.q3.qo_valeur.name,ite);
//     if( s3->fonction==F_TAB ){
        
//         fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
//         fprintf(f_ptr,"\tbge $t1, %i, label_hors_tab\n",s3->type.tab.size);
//         fprintf(f_ptr,"\tblt $t1, 0, label_hors_tab\n");
//         //on charge le deplacement par rapport à addr tab
//         fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
//         //on charge addr tab et la ressource qu'elle contient dans $t0
//         fprintf(f_ptr,"\tla $t2, %s\n",q.q3.qo_valeur.name);
//         fprintf(f_ptr,"\tmul $t1, $t1, 4\n");
//         fprintf(f_ptr,"\tadd $t1, $t1, $t2\n");
    
//     } else if( s3->fonction==F_ARG 
//             || s3->fonction==F_TEMP
//             || s3->fonction==F_VAR ){
    
//         fprintf(f_ptr,"\tla $t1, %i($sp)\n",4*place_pile(q.q3.qo_valeur.name,ite));
    
//     } else if( s3->fonction==F_VAR_GLB ){
    
//         fprintf(f_ptr,"\tla $t1, %s\n",q.q3.qo_valeur.name);
    
//     } else {
//         return 1;
//     }

//     fprintf(f_ptr,"\tsw $t0, 0($t1)\n");
//     return 0;
// }

int write_arith_spim(quad q, ctx* ite, FILE* f_ptr){
    
    if ( q.q3.qo_type!=QO_NAME ){
        return 1;
    }       

    if( q.q1.qo_type==QO_CST ){
        fprintf(f_ptr,"\tli $t0, %i\n",q.q1.qo_valeur.cst);
    } else if ( q.q1.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q1.qo_valeur.name,ite));
    } else {
        return 1;
    }

    if( q.q2.qo_type==QO_CST ){
        fprintf(f_ptr,"\tli $t1, %i\n",q.q2.qo_valeur.cst);
    } else if ( q.q2.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
    } else {
        return 1;
    }

    switch(q.q_type){
        case Q_ADD:
            fprintf(f_ptr,"\tadd $t0, $t0, $t1\n");
            break;
        case Q_SUB:
            fprintf(f_ptr,"\tsub $t0, $t0, $t1\n");
            break;
        case Q_MULT:
            fprintf(f_ptr,"\tmul $t0, $t0, $t1\n");
            break;
        case Q_DIV:
            fprintf(f_ptr,"\tdiv $t0, $t0, $t1\n");
            break;
        case Q_RES:
            fprintf(f_ptr,"\trem $t0, $t0, $t1\n");
            break;
    }
    fprintf(f_ptr,"\tsw $t0, %i($sp)\n",4*place_pile(q.q3.qo_valeur.name,ite));
    return 0;
}

int write_neg_spim(quad q, ctx* ite, FILE* f_ptr){
    //Q_NEG: nb_dep : _ : nb_dest
    if ( q.q3.qo_type!=QO_NAME ){
        return 1;
    }       

    if( q.q1.qo_type==QO_CST ){
        fprintf(f_ptr,"\tli $t0, %i\n",q.q1.qo_valeur.cst);
    } else if ( q.q1.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q1.qo_valeur.name,ite));
    } else {
        return 1;
    }

    fprintf(f_ptr,"\tneg $t0, $t0\n");
    fprintf(f_ptr,"\tsw $t0, %i($sp)\n",4*place_pile(q.q3.qo_valeur.name,ite));

    return 0;
}

int write_goto_spim(quad q, FILE* f_ptr){
    if ( q.q3.qo_type==QO_NAME ){
        return 1;
    }                  

    if( q.q3.qo_type==QO_CST ){
        fprintf(f_ptr,"\tb label%i\n",q.q3.qo_valeur.cst);
    }

    return 0;
}

int write_if_spim(quad q, ctx* ite, FILE* f_ptr){

    if ( q.q3.qo_type!=QO_CST ){
        return 1;
    }    

    if( q.q1.qo_type==QO_CST ){
        fprintf(f_ptr,"\tli $t0, %i\n",q.q1.qo_valeur.cst);
    } else if ( q.q1.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q1.qo_valeur.name,ite));
    } else {

    }
    fprintf(f_ptr,"\tli $t1, 1\n");
    fprintf(f_ptr,"\tbeq $t0, $t1, label%i\n",q.q3.qo_valeur.cst);

    return 0;
}

int write_boolean_op_spim(quad q, ctx* ite, FILE* f_ptr){

    if ( q.q3.qo_type!=QO_CST ){
        return 1;
    }    

    if( q.q1.qo_type==QO_CST ){
        fprintf(f_ptr,"\tli $t0, %i\n",q.q1.qo_valeur.cst);
    } else if ( q.q1.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(q.q1.qo_valeur.name,ite));
    }

    if( q.q2.qo_type==QO_CST ){
        fprintf(f_ptr,"\tli $t1, %i\n",q.q2.qo_valeur.cst);
    } else if ( q.q2.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(q.q2.qo_valeur.name,ite));
    }

    switch(q.q_type){
        case Q_LESS:
            fprintf(f_ptr,"\tblt $t0, $t1, label%i\n",q.q3.qo_valeur.cst);
            break;
        case Q_LESS_EQ:
            fprintf(f_ptr,"\tble $t0, $t1, label%i\n",q.q3.qo_valeur.cst);
            break;
        case Q_GREAT:
            fprintf(f_ptr,"\tbgt $t0, $t1, label%i\n",q.q3.qo_valeur.cst);
            break;
        case Q_GREAT_EQ:
            fprintf(f_ptr,"\tbge $t0, $t1, label%i\n",q.q3.qo_valeur.cst);
            break;
        case Q_EQ:
            fprintf(f_ptr,"\tbeq $t0, $t1, label%i\n",q.q3.qo_valeur.cst);
            break;
        case Q_NOT_EQ:
            fprintf(f_ptr,"\tbne $t0, $t1, label%i\n",q.q3.qo_valeur.cst);
            break;
    }
    
    return 0;

}

int write_break_loop_spim(quad q, ctx* ite, FILE* f_ptr){
    if ( q.q3.qo_type!=QO_CST ){
        return 1;
    }
    
    //On retire de la pile les blocs contenant break dans le ctx_for
    //Mais on laisse l'iterateur inchangé, Q_POP s'en occupera en quittant les blocs
    ctx* ite_for = ite;
    while(ite_for->ctx_type!=CTX_FOR){
        for(int j = 0; j<ite_for->size_tab; j++){
            fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
        }
        ite_for = ite_for->prec;
    }
    
    fprintf(f_ptr,"\tb label%i\n",q.q3.qo_valeur.cst);

    return 0;

}

int write_def_meth_spim(quad q, ctx* ite, FILE* f_ptr){
    //Q_DEF_METH : name_meth : nb_arg : _
            
    if ( q.q1.qo_type!=QO_NAME ){
        return 1;
    }       
    if ( q.q2.qo_type!=QO_CST ){
        return 1;
    }     
    int nb_arg = q.q2.qo_valeur.cst;  
    
    
    fprintf(f_ptr,"%s:\n",q.q1.qo_valeur.name);
    
    
    //Allocation et sauvegarde $ra et $fp
    fprintf(f_ptr,"\taddiu $sp, $sp, -4\n");
    fprintf(f_ptr,"\tli $t0, 0\n");
    fprintf(f_ptr,"\tsw $t0, 0($sp)\n");
    fprintf(f_ptr,"\taddiu $sp, $sp, -4\n");
    fprintf(f_ptr,"\tli $t0, 0\n");
    fprintf(f_ptr,"\tsw $t0, 0($sp)\n");

    fprintf(f_ptr,"\tsw $fp, 4($sp)\n");
    fprintf(f_ptr,"\tsw $ra, 0($sp)\n");
    //$fp = nb_arg + 2 (ra et fp)
    fprintf(f_ptr,"\taddiu $fp, $sp, %i\n",4*(nb_arg+2));

    return 0;
}

int write_return_spim(quad q, ctx* ite, FILE* f_ptr){

    //Q_RETURN : valeur_de_retour : _ : branchement

    if( q.q1.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tlw $v0, %i($sp)\n",4*place_pile(q.q1.qo_valeur.name,ite));
    }

    ctx* ite_meth = ite;
    //On retire de la pile les blocs contenant return dans le ctx_meth
    //Mais on laisse l'iterateur inchangé, Q_POP s'en occupera en quittant les blocs                
    while(ite_meth->ctx_type!=CTX_METH){
        for(int j = 0; j<ite_meth->size_tab; j++){
            fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
        }
        ite_meth = ite_meth->prec;
    }

    if( q.q3.qo_type == QO_CST ) {
        fprintf(f_ptr,"\tb label%i\n",q.q3.qo_valeur.cst);
    } else {
        fprintf(f_ptr,"\tli $v0, 10\n\tsyscall\n");
    }

    return 0;

}

int write_end_meth_spim(quad q, ctx* ite, FILE* f_ptr){

    //Q_END_METH : name_meth : nb_arg : _

    if ( q.q1.qo_type!=QO_NAME && q.q1.qo_type!=QO_VIDE){
        return 1;
    }     
    
    //On restaure et libère ra et fp
    fprintf(f_ptr,"\tlw $ra, 0($sp)\n");  
    fprintf(f_ptr,"\tlw $fp, 4($sp)\n");
    fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
    fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");            

    if( q.q1.qo_type==QO_VIDE ){
        fprintf(f_ptr,"\tli $v0, 4\n\tla $a0, error_str_meth\n\tsyscall\n");
        fprintf(f_ptr,"\tli $v0, 10\n\tsyscall\n");
    } else if( strcmp(q.q1.qo_valeur.name,"main") == 0 ) {
        fprintf(f_ptr,"\tli $v0, 10\n\tsyscall\n");
    } else {
        fprintf(f_ptr,"\tjr $ra\n");
    }

    return 0;

}

int write_param_spim(quad q, ctx* ite, FILE* f_ptr){

    //Q_PARAM : depl sur la pile : _ : arg

    if ( q.q1.qo_type!=QO_CST ){
        return 1;
    }
    
    //stockage au sommet de la pile
    fprintf(f_ptr,"\taddiu $sp, $sp, -4\n");
    fprintf(f_ptr,"\tli $t0, 0\n");
    fprintf(f_ptr,"\tsw $t0, 0($sp)\n");

    

    if( q.q3.qo_type==QO_NAME ) {
        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*(place_pile(q.q3.qo_valeur.name,ite)+q.q1.qo_valeur.cst));   
    } else if ( q.q3.qo_type==QO_CST ) {
        fprintf(f_ptr,"\tli $t0, %i\n",q.q3.qo_valeur.cst);   
    }
    fprintf(f_ptr,"\tsw $t0, 0($sp)\n");   

    return 0;  

}

int write_call_meth_spim(quad q, ctx* ite, FILE* f_ptr) {

    //Q_CALL_METH : name_meth : nb_arg : temp contenant le resultat
    
    if ( q.q1.qo_type!=QO_NAME ){
        return 1;
    }
    if ( q.q2.qo_type!=QO_CST ){
        return 1;
    }  
    if ( q.q3.qo_type==QO_CST ){
        return 1;
    }

    fprintf(f_ptr,"\tjal %s\n",q.q1.qo_valeur.name);
    
    for(int k = 0; k<q.q2.qo_valeur.cst; k++){
        fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
    }   

    if( q.q3.qo_type==QO_NAME ){
        fprintf(f_ptr,"\tsw $v0, %i($sp)\n",4*place_pile(q.q3.qo_valeur.name,ite));                        
    }

    return 0;

}

#endif