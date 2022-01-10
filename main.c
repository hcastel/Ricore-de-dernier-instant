#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/write_spim.h"
#include "include/table_symb.h"
#include "include/quad.h"    
#define SIZE_CODE_INTER 1000

extern int yyparse();
extern FILE* yyin;
// extern int numero_type[];


int place_pile(char* str, ctx* ctx1);
void open_write_file(char* file, ctx* tab_symbole, quad* code_inter, int next_quad);
void print_code_inter(quad* code_inter, int next_quad);

char NOM_GRP[] ="ESCUDIE Erwan, NICOLAZO David, ANDRIANANDRASANA-DINA Vagnona, BASTIEN Théo, CASTEL Hugo";

char* NOMS_TYPES[] = {"Q_ADD","Q_SUB","Q_MULT","Q_DIV","Q_RES","Q_EQ","Q_LESS","Q_GREAT","Q_LESS_EQ","Q_GREAT_EQ","Q_COPY","Q_GOTO","Q_IF","Q_PUSH_CTX","Q_POP_CTX","Q_NEG","Q_BREAK","Q_CONTINUE","Q_DEF_METH","Q_RETURN","Q_END_METH","Q_CALL_METH","Q_PARAM","Q_PRINT"};
int NUMEROS_TYPES[] = {Q_ADD,Q_SUB,Q_MULT,Q_DIV,Q_RES,Q_EQ,Q_LESS,Q_GREAT,Q_LESS_EQ,Q_GREAT_EQ,Q_COPY,Q_GOTO,Q_IF,Q_PUSH_CTX,Q_POP_CTX,Q_NEG,Q_BREAK,Q_CONTINUE,Q_DEF_METH,Q_RETURN,Q_END_METH,Q_CALL_METH,Q_PARAM,Q_PRINT};
int NB_Q_TYPES = 24;


int main(int argc, char* argv[]){
    char* file_dest = NULL;
    int tos = 0;

    for(int i = 1; i < argc; i++){
        if( strcmp(argv[i],"-version")==0 ){
            printf("%s\n",NOM_GRP);
            return 0;
        }
        if( strcmp(argv[i],"-o")==0 ){
            file_dest = argv[i+1];
        }
        if( strcmp(argv[i],"-tos")==0 ){
            tos = 1;
        }
    }
    
    yyin = fopen(argv[1],"r");
    if( yyin==NULL ){
        fprintf(stderr,"Le fichier decaf n'existe pas.\n");
        return 1;
    }


    quad* code_inter = malloc(SIZE_CODE_INTER*sizeof(quad));
    ctx* tab_symbole = NULL;
    int next_quad = 0;

    if( yyparse(&tab_symbole,&code_inter,&next_quad)!=0 ){
        printf("Programme non conforme.\n");
        fclose(yyin);
        return 1;
    }
    else {
        printf("Programme valide.\n");
        if( tos==0 ){
            printf("===TAB_SYMBOLE===\n");
            print_tab_symb(tab_symbole,0);
            print_code_inter(code_inter,next_quad);            
        }
        
        open_write_file(file_dest,tab_symbole,code_inter,next_quad);

        free_table_symb(tab_symbole);  
        free(code_inter);  
        fclose(yyin);
    }

    return 0;
}




//AFFICHAGE DU CODE
char* print_type_quad(quad q) {
    int op = q.q_type;
    for(int i = 0; i<NB_Q_TYPES; i++){
        if(NUMEROS_TYPES[i]==op){
            return NOMS_TYPES[i];
            break;
        }
    }
    return "RIEN";

}
void print_quad(quad q){

    printf("| %s |",print_type_quad(q));

    if( q.q1.qo_type!=QO_VIDE ) {
        if( q.q1.qo_type==QO_CST ) {
            printf("| 1:CST:%i\t|",q.q1.qo_valeur.cst);
        }
        if( q.q1.qo_type==QO_NAME ) {
            printf("| 1:VAR:%s\t|",q.q1.qo_valeur.name);
        }
    }

    if( q.q2.qo_type!=QO_VIDE ) {
        if( q.q2.qo_type==QO_CST ) {
            printf("| 2:CST:%i\t|",q.q2.qo_valeur.cst);
        }
        if( q.q2.qo_type==QO_NAME ) {
            printf("| 2:VAR:%s\t|",q.q2.qo_valeur.name);
        }
    }

    if( q.q3.qo_type!=QO_VIDE ) {
        if( q.q3.qo_type==QO_CST ) {
            printf("| 3:CST:%i\t|",q.q3.qo_valeur.cst);
        }
        if( q.q3.qo_type==QO_NAME ) {
            printf("| 3:VAR:%s\t|",q.q3.qo_valeur.name);
        }
    }
}
void print_code_inter(quad* code_inter, int next_quad){
    printf("====CODE INTER:====\n");
    for(size_t i = 0; i<next_quad; i++){
        printf("%lu\t",i);
        print_quad(code_inter[i]);
        printf("\n");
    }    
}




void open_write_file(char* file, ctx* tab_symbole, quad* code_inter, int next_quad){

    // tab_label_check contient les lignes de debut de blocs de base (1 si debut, 0 sinon)
    int tab_label_check[SIZE_CODE_INTER] = {0};
    // ite sera le contexte courant lors de notre parcours du code intermediaire
    ctx* ite = NULL;
    
    if( file==NULL ){
        return;
    }

    FILE* f_ptr = fopen(file, "w+");
    if(f_ptr==NULL){
        fprintf(stderr,"Ouverture du fichier spim a échoué\n");
        return;
    }

    write_data_spim(tab_symbole,f_ptr);

    for(int i = 0; i<next_quad; i++){
        if(code_inter[i].q_type == Q_IF ||
           code_inter[i].q_type == Q_EQ ||
           code_inter[i].q_type == Q_NOT_EQ ||
           code_inter[i].q_type == Q_LESS ||
           code_inter[i].q_type == Q_LESS_EQ ||
           code_inter[i].q_type == Q_GREAT ||
           code_inter[i].q_type == Q_GREAT_EQ ||
           code_inter[i].q_type == Q_GOTO ||
           code_inter[i].q_type == Q_BREAK ||
           code_inter[i].q_type == Q_CONTINUE || 
           code_inter[i].q_type == Q_RETURN )
        {            
            tab_label_check[code_inter[i].q3.qo_valeur.cst]=1;
        }
    }


    for(int i = 0; i<next_quad; i++){    

        if(tab_label_check[i]==1){
            fprintf(f_ptr,"label%i:\n",i);
        }

        switch(code_inter[i].q_type) {
            case Q_PUSH_CTX:
                
                write_push_ctx_spim(code_inter[i], tab_symbole, &ite, f_ptr);                
                break;

            case Q_POP_CTX:

                write_pop_ctx_spim(code_inter[i], tab_symbole, &ite, f_ptr);
                break;

            case Q_COPY:

                //SOURCE
                if( code_inter[i].q1.qo_type==QO_CST ){
                //src:cst
                    fprintf(f_ptr,"\tli $t0, %i\n",code_inter[i].q1.qo_valeur.cst);
                } else {
                //src:non cst    
                    symbole* s1 = look_up(code_inter[i].q1.qo_valeur.name,ite);
                    // symbole* s2 = look_up(code_inter[i].q2.qo_valeur.name,ite);
                    
                    if( s1->fonction==F_TAB ){
                        

                        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(code_inter[i].q2.qo_valeur.name,ite));
                        fprintf(f_ptr,"\tbge $t0, %i, label_hors_tab\n",s1->type.tab.size);
                        fprintf(f_ptr,"\tblt $t0, 0, label_hors_tab\n");
                        //on charge le deplacement par rapport à addr tab
                        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(code_inter[i].q2.qo_valeur.name,ite));
                        //on charge addr tab et la ressource qu'elle contient dans $t0
                        fprintf(f_ptr,"\tla $t1, %s\n",code_inter[i].q1.qo_valeur.name);
                        fprintf(f_ptr,"\tmul $t0, $t0, 4\n");
                        fprintf(f_ptr,"\tadd $t1, $t1, $t0\n");
                        fprintf(f_ptr,"\tlw $t0, 0($t1)\n");

                    } else if( s1->fonction==F_ARG 
                            || s1->fonction==F_TEMP
                            || s1->fonction==F_VAR ){
                        fprintf(f_ptr,"\tlw $t0, %i($sp)\n",4*place_pile(code_inter[i].q1.qo_valeur.name,ite));
                    } else if( s1->fonction==F_VAR_GLB){
                        fprintf(f_ptr,"\tlw $t0, %s\n",code_inter[i].q1.qo_valeur.name);
                    } else {
                        fprintf(stderr,"-ERREUR:generationSpim-\tQ_COPY source.");
                        exit(1);
                    }
                }


                //DESTINATION
                symbole* s3 = look_up(code_inter[i].q3.qo_valeur.name,ite);
                if( s3->fonction==F_TAB ){
                    fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(code_inter[i].q2.qo_valeur.name,ite));
                    fprintf(f_ptr,"\tbge $t1, %i, label_hors_tab\n",s3->type.tab.size);
                    fprintf(f_ptr,"\tblt $t1, 0, label_hors_tab\n");
                    //on charge le deplacement par rapport à addr tab
                    fprintf(f_ptr,"\tlw $t1, %i($sp)\n",4*place_pile(code_inter[i].q2.qo_valeur.name,ite));
                    //on charge addr tab et la ressource qu'elle contient dans $t0
                    fprintf(f_ptr,"\tla $t2, %s\n",code_inter[i].q3.qo_valeur.name);
                    fprintf(f_ptr,"\tmul $t1, $t1, 4\n");
                    fprintf(f_ptr,"\tadd $t1, $t1, $t2\n");
                } else if( s3->fonction==F_ARG 
                        || s3->fonction==F_TEMP
                        || s3->fonction==F_VAR ){
                    fprintf(f_ptr,"\tla $t1, %i($sp)\n",4*place_pile(code_inter[i].q3.qo_valeur.name,ite));
                } else if( s3->fonction==F_VAR_GLB ){
                    fprintf(f_ptr,"\tla $t1, %s\n",code_inter[i].q3.qo_valeur.name);
                } else {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_COPY destination.");
                    exit(1);
                }

                fprintf(f_ptr,"\tsw $t0, 0($t1)\n");

                // printf("ALLO\n");
                // if( write_copy_spim(code_inter[i], ite, f_ptr) == 1 ) {
                // //     fprintf(stderr,"-ERREUR:generationSpim-\tQ_COPY");
                //     printf("dsdsdd\n");
                // //     exit(1);
                // }
                // write_copy_spim(code_inter[i],ite,f_ptr);
                break;

            case Q_ADD:
            case Q_SUB:
            case Q_MULT:
            case Q_DIV:
            case Q_RES:
                
                if( write_arith_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tOP_ARITH");
                    exit(1);   
                }
                break;

            case Q_NEG:

                if( write_neg_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tOP_NEG");
                    exit(1);   
                }
                break;

            case Q_GOTO:

                if( write_goto_spim(code_inter[i],f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_GOTO");
                    exit(1);   
                }
                break;

            case Q_IF:

                if( write_if_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tOP_IF");
                    exit(1);   
                }
                break;
            
            case Q_LESS:
            case Q_LESS_EQ:
            case Q_GREAT:
            case Q_GREAT_EQ:
            case Q_EQ:
            case Q_NOT_EQ:

                if( write_boolean_op_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tOP_BOOL");
                    exit(1);   
                }
                break;
            
            case Q_BREAK:
            case Q_CONTINUE:

                if( write_break_loop_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_BREAK\\Q_CONTINUE");
                    exit(1);   
                }
                break;
            
            case Q_DEF_METH:

                tab_label_check[i] = 1;
                if( write_def_meth_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_DEF_METH");
                    exit(1);   
                }
                break;

            case Q_RETURN:

                if( write_return_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_RETURN");
                    exit(1);   
                }
                break;
            
            case Q_END_METH:
                
                if( write_end_meth_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_END_METH");
                    exit(1);   
                }

                break;
            case Q_PARAM:
                
                if( write_param_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_PARAM");
                    exit(1);   
                }
                break;  
            
            case Q_CALL_METH:
                
                if( write_call_meth_spim(code_inter[i],ite,f_ptr)==1 ) {
                    fprintf(stderr,"-ERREUR:generationSpim-\tQ_CALL_METH");
                    exit(1);   
                }
                break;

            case Q_PRINT:
                
                fprintf(f_ptr,"\tli $v0, 4\n\tla $a0, %s\n\tsyscall\n",code_inter[i].q3.qo_valeur.name);
                break;

        }
    }
    
    fclose(f_ptr);
}
