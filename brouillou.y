
%{
#include <stdio.h>
// #include <math.h>
#include <string.h>
#include <stdlib.h>
#include "quadtest.h"
#include "table_symb.c"

    extern int yylex();
    #define YYDEBUG 1
    #define SIZE_TABLE_SYMB 200
    void yyerror (const char* msg);

    quad code_inter[1000];
    char* tab_label[1000];
    int tab_label_check[1000] = {0};
    size_t next_quad = 0;
    quad_op qo_vide = {QO_VIDE,-1};


    ctx* first_ctx = NULL;

    // first_ctx->size_tab = 0;
    // first_ctx->size_next = 0;
    // first_ctx->tab = NULL;
    // first_ctx->prec = NULL;
    // first_ctx->next = NULL;

    ctx* current_ctx = NULL;
    
    void print_quad(quad q);
    void print_code_inter();

    // void new_temp();
    // symbole* new_const_branch(int cst);
    // symbole* new_const_int(int cst);
    // symbole* new_const_bool(int cst);
    // symbole* new_symb();

    symbole* newname_var(char* name, type_simple type);
    symbole* newname_arg(char* name, type_simple type);
    symbole* newname_proc(char* name, type_simple* arg_type, int size_arg, type_simple return_type);
    symbole* newname_tab(char* name, type_simple type, int size);
    symbole* newname_temp(type_simple type);

    quad_op new_qo_name(char* name){
        quad_op res;
        res.qo_type = QO_NAME;
        res.qo_valeur.name = name;
        return res;
    }

    quad_op new_qo_cst(int cst){
        quad_op res;
        res.qo_type = QO_CST;
        res.qo_valeur.cst = cst;
        return res;
    }


    // symbole* newname(char* name, int fonction);

    void gencode(int,quad_op,quad_op,quad_op);

    // symbole* find_in_tab_symb(char* name);
    void print_tab_symb(ctx* ctx, int decal);
    char* print_type_simple(int t);
    

    int* creer_liste(int nq);
    int* concat_liste(int* p1, int* p2, int size1, int size2);
    int* concat_liste_int(int* p1, int p2, int size1);
    void complete_liste(int* p, int size, int q);
    void print_liste(int* l, int s){
        printf("DEBUT PRINT\n");
        if(s==0){
            printf("s=0\n");
            return;
        } else {
            for(int i = 0; i<s; i++){
                printf("%i:%i,",i,l[i]);
            }            
        }
        printf("\n");

    }


    int nb_temp = 0;

    //pour print les types des quads
    char * nom_type[] = {"Q_ADD","Q_SUB","Q_MULT","Q_DIV","Q_RES","Q_EQ","Q_LESS","Q_GREAT","Q_LESS_EQ","Q_GREAT_EQ","Q_COPY","Q_GOTO","Q_IF","Q_PUSH_CTX","Q_POP_CTX","Q_FOR","Q_BREAK","Q_CONTINUE","Q_DEF_FUN","Q_INIT_FP_RA","Q_RETURN","Q_END_FUN","Q_CALL_FUN","Q_PARAM","Q_RES_FUN"};
    int numero_type[] = {Q_ADD,Q_SUB,Q_MULT,Q_DIV,Q_RES,Q_EQ,Q_LESS,Q_GREAT,Q_LESS_EQ,Q_GREAT_EQ,Q_COPY,Q_GOTO,Q_IF,Q_PUSH_CTX,Q_POP_CTX,Q_FOR,Q_BREAK,Q_CONTINUE,Q_DEF_FUN,Q_INIT_FP_RA,Q_RETURN,Q_END_FUN,Q_CALL_FUN,Q_PARAM,Q_RES_FUN};
    int nb_type = 23;

    extern char yytext[];
%}

%glr-parser
%code requires {
    #include "quadtest.h"
}

%union
{
    char *str_val;
    char char_val;
    int int_val;

    struct type_list {
        type_simple* list;
        int size;
    } type_list;
    
    
    struct result{

        type_simple type;
        
        union valeur{
            
            quad_op qo;

            struct liste{
                int size_true;
                int size_false;
                int size_next;
                int size_l_break;
                int size_l_continue;
                int size_l_return;

                int* true;
                int* false;
                int* next;
                int* l_break;
                int* l_continue;
                int* l_return;
            } liste;

        } valeur;  

    } result;
}



%token VIRG OP_PAR OP_CRO OP_BRA CL_BRA CL_CRO CL_PAR BEG SM TYPE_VOID STRING_LIT OP_NOT U_MOINS IF ELSE FOR BREAK CONTINUE WI RETURN
%type <result> location literal expr int_literal bool_literal block list_statement statement N method_call

%type <str_val> rtn_value
%type <int_val> arith_op bin_op assign_op rel_op eq_op cond_op type M Nq
%type <type_list> list_arg list_arg_decl list_method_call_arg method_call_arg
%token <str_val> ID
%token <int_val> HEX_LIT DEC_LIT BOOL_TRUE BOOL_FALSE CHAR_LIT OP_PLUS OP_SUB OP_MULT OP_DIV OP_RES OP_LESS OP_GREA OP_LESS_EQ OP_GREA_EQ AFF_EQ AFF_INC AFF_DEC OP_EQ OP_NOT_EQ OP_AND OP_OR TYPE_INT TYPE_BOOL


%left OP_PLUS
%left OP_MULT
%left U_MOINS


%start program


%%

program: BEG OP_BRA push_deb field_decls method_decls CL_BRA                { 
                                                                                gencode(Q_POP_CTX,qo_vide,qo_vide,qo_vide);
                                                                                
                                                                                print_code_inter();
                                                                                printf("avant OWF\n");
                                                                                open_write_file();


                                                                                printf("\n\n");
                                                                                printf("====TABLE_SYMBOLE====\n");
                                                                                print_tab_symb(first_ctx,0);
                                                                                
                                                                                printf("====FREE_TABLE_SYMBOLE====\n");
                                                                                free_table_symb(first_ctx);
                                                                            }
       ;

push_deb:   { 
                //printf("push_deb\n");
                first_ctx = pushctx(first_ctx);
                current_ctx = first_ctx;
                gencode(Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);

                type_simple* liste_type_write_int = malloc(1*sizeof(type_simple));
                liste_type_write_int[0] = T_INT;
                newname_proc("WriteInt",liste_type_write_int,1,T_VOID);
                newname_proc("ReadInt",NULL,0,T_INT);
                newname_proc("")
            }
        ;

field_decls: field_decls field_decl              
               | %empty
               ;

field_decl: type field_ids SM             //{ printf("AIEIAIEIE\n");}                   
          ;

//field_ids: error CL_BRA

// rec a gauche ou a droite, a voir

field_ids
    : field_id
    | field_ids VIRG field_id
    ;

field_id
    : ID                                            {   
                                                        printf("field_cde  : %s\n",$1); 
                                                        newname_var($1,$<int_val>0); 
                                                    }
    | ID OP_CRO int_literal CL_CRO                  {   newname_tab($1,$<int_val>0,$3.valeur.qo.qo_valeur.cst); }
    ;



method_decls: method_decls method_decl  //{ printf("ON ENTRE DANS METH_DECL"); }
                |
                ;

method_decl: 
//     type ID OP_PAR list_arg_decl CL_PAR block 
// |   TYPE_VOID ID OP_PAR list_arg_decl CL_PAR block
// ;
             type ID {
                newname_proc($2,NULL,0,$1);

            } push OP_PAR list_arg_decl {


                symbole* fun = lookup($2,first_ctx);
                
                quad_op qo_name_f;
                qo_name_f.qo_type = QO_NAME;
                qo_name_f.qo_valeur.name = fun->name;

                quad_op qo_nb_arg = {QO_CST,$6.size};

                fun->type.proc.nb_arg = $6.size;
                fun->type.proc.arg = $6.list;
                fun->type.proc.retour = $1;


//argument et registres à ctx_fun
                current_ctx->ctx_type = CTX_FUN;
                gencode(Q_DEF_FUN,qo_nb_arg,qo_name_f,qo_vide);


//si on ignore les arg, plus besoin de push pour separer les deux contextes,on melange initFPRA et DEF_FUN
                //on utilise jamais ces 2 symboles mais ils marquent la position de fp et ra
                
                
                symbole* fp = newname_temp(T_INT);
                fp->fonction = F_ARG_INV;
                symbole* ra = newname_temp(T_INT);
                ra->fonction = F_ARG_INV;

            } CL_PAR block {

                // print_tab_symb(first_ctx,0);
                quad_op nb_arg = {T_INT,$6.size};
                complete_liste($9.valeur.liste.l_return,$9.valeur.liste.size_l_return,next_quad);

                


//AJOUTER RETURN SI Y A PAS DE LISTE_RETURN
//Q_END_FUN termine ra et fp et repart par $ra
                symbole* fun = lookup($2,first_ctx);
                
                quad_op qo_name_f;
                qo_name_f.qo_type = QO_NAME;
                qo_name_f.qo_valeur.name = fun->name;

                gencode(Q_END_FUN,nb_arg,qo_name_f,qo_vide);
            } pop

           | TYPE_VOID ID{

                newname_proc($2,NULL,0,T_VOID);

           } push OP_PAR list_arg_decl {


                symbole* fun = lookup($2,first_ctx);
                
                quad_op qo_name_f;
                qo_name_f.qo_type = QO_NAME;
                qo_name_f.qo_valeur.name = fun->name;

                quad_op qo_nb_arg = {QO_CST,$6.size};

                fun->type.proc.nb_arg = $6.size;
                fun->type.proc.arg = $6.list;
                fun->type.proc.retour = T_VOID;

//argument et registres à ctx_fun
                current_ctx->ctx_type = CTX_FUN;
                gencode(Q_DEF_FUN,qo_nb_arg,qo_name_f,qo_vide);


//si on ignore les arg, plus besoin de push pour separer les deux contextes,on melange initFPRA et DEF_FUN
                //on utilise jamais ces 2 symboles mais ils marquent la position de fp et ra
                
                
                symbole* fp = newname_temp(T_INT);
                fp->fonction = F_ARG_INV;
                symbole* ra = newname_temp(T_INT);
                ra->fonction = F_ARG_INV;

            } CL_PAR block {

                // print_tab_symb(first_ctx,0);
                quad_op nb_arg = {T_INT,$6.size};
                complete_liste($9.valeur.liste.l_return,$9.valeur.liste.size_l_return,next_quad);

                


//AJOUTER RETURN SI Y A PAS DE LISTE_RETURN
//Q_END_FUN termine ra et fp et repart par $ra
                symbole* fun = lookup($2,first_ctx);
                
                quad_op qo_name_f;
                qo_name_f.qo_type = QO_NAME;
                qo_name_f.qo_valeur.name = fun->name;

                gencode(Q_END_FUN,nb_arg,qo_name_f,qo_vide);


//le pop permet de depop la derniere table arg et registre, on est a nouveau dans glob    
            } pop
           ;

type: TYPE_INT                      {$$=T_INT;}
    | TYPE_BOOL                     {$$=T_BOOL;}
    ;

list_arg_decl: list_arg                                            {
                                                                            $$ = $1;
                                                                        }
             | 
             ;

//commence par le dernier donc bon pour la version MIPS
list_arg: list_arg VIRG type ID                                     {
                                                                        $$.list = concat_liste_int($1.list,$3,$1.size);
                                                                        $$.size = $1.size + 1 ;
                                                                        // char* name_arg = malloc(5*sizeof(char));
                                                                        // strcpy(name_arg,$4);
                                                                        symbole* arg = newname_arg($4,$3);
                                                                        printf("NEWNAMEARG: %s %i %i\n",arg->name,$3,T_INT);
                                                                        arg->fonction = F_ARG_INV;
                                                                    }
        | type ID                                                   {
                                                                        $$.list = malloc(1*sizeof(int));
                                                                        $$.list[0] = $1;
                                                                        $$.size = 1;
                                                                        
                                                                        // char* name_arg = malloc(5*sizeof(char));                                                                        char* name_arg = malloc(5*sizeof(char));
                                                                        // strcpy(name_arg,$2);
                                                                        symbole* arg = newname_arg($2,$1);
                                                                        
                                                                        printf("NEWNAMEARG: %s %i %i\n",arg->name,arg->type,T_INT);
                                                                        arg->fonction = F_ARG_INV;
                                                                    }
        ;

block: OP_BRA push list_var_decl list_statement M pop CL_BRA    {
                                                                        //LISTE STATEMENT NE CONTIENT JAMAIS DE GOTO EN DEHORS DU BLOCK, DONC ON LAISSE LA LIBERATION SE FAIRE

                                                                        //le bloc met fin à son contexte
                                                                        complete_liste($4.valeur.liste.next,$4.valeur.liste.size_next,$5);
                                                                        // current_ctx = current_ctx->prec; 
                                                                        // gencode(Q_POP_CTX,qo_vide,qo_vide,qo_vide);

                                                                        //goto vers la suite du bloc
                                                                        $$.valeur.liste.next = creer_liste(next_quad);
                                                                        $$.valeur.liste.size_next = 1;
                                                                        // printf("block: %i",next_quad);
                                                                        gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);

                                                                        // print_quad(code_inter[next_quad-1]);

                                                                        printf("LISTEEEEEEEEEEEEEEEEE\n");
                                                                        affiche_liste($4.valeur.liste.l_return,$4.valeur.liste.size_l_return);

                                                                        //goto en cas de l_break
                                                                        $$.valeur.liste.l_break = $4.valeur.liste.l_break;
                                                                        $$.valeur.liste.size_l_break = $4.valeur.liste.size_l_break;
                                                                        $$.valeur.liste.l_continue = $4.valeur.liste.l_continue;
                                                                        $$.valeur.liste.size_l_continue = $4.valeur.liste.size_l_continue;
                                                                        $$.valeur.liste.l_return = $4.valeur.liste.l_return;
                                                                        $$.valeur.liste.size_l_return = $4.valeur.liste.size_l_return;


                                                                        // if($4.valeur.liste.size_l_break != 0 ){
                                                                        //     printf("BREAK\n");
                                                                        //     complete_liste($4.valeur.liste.l_break,$4.valeur.liste.size_l_break,next_quad);
                                                                        //     $$.valeur.liste.l_break = creer_liste(next_quad);
                                                                        //     $$.valeur.liste.size_l_break = 1;
                                                                        //     //printf("block break: %i",next_quad);
                                                                        //     // current_ctx = current_ctx->prec; 
                                                                        //     // gencode(Q_POP_CTX,qo_vide,qo_vide,qo_vide);
                                                                        //     // gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);   
                                                                        //     gencode(Q_BREAK,qo_vide,qo_vide,qo_vide);   
                                                                        //     printf("FINBREAK\n")   ;                                                                  
                                                                        // }


                                                                        
                                                                        // $$.valeur.liste.next = $4.valeur.liste.next;
                                                                        // $$.valeur.liste.size_next = $4.valeur.liste.size_next;
                                                                }
     ;

push:   { printf("PUSH\n"); current_ctx = pushctx(current_ctx); print_tab_symb(current_ctx,0); gencode(Q_PUSH_CTX,qo_vide,qo_vide,qo_vide); }
    ;
pop:    { printf("POP\n"); current_ctx = current_ctx->prec; /*print_tab_symb(current_ctx,0);*/ gencode(Q_POP_CTX,qo_vide,qo_vide,qo_vide); }
    ;

list_var_decl: var_decl list_var_decl
             |
             ;

list_statement: list_statement M statement  {
                                                complete_liste($1.valeur.liste.next,$1.valeur.liste.size_next,$2);
                                                
                                                $$.valeur.liste.next = $3.valeur.liste.next;
                                                $$.valeur.liste.size_next = $3.valeur.liste.size_next;            
                                                
                                                // printf("LIST_STATEMENT\n");

                                                // print_liste($1.valeur.liste.l_break,$1.valeur.liste.size_l_break);
                                                // printf("\n");
                                                // print_liste($3.valeur.liste.l_break,$3.valeur.liste.size_l_break);
                                                // printf("\n");

                                                $$.valeur.liste.l_break = concat_liste($1.valeur.liste.l_break,$3.valeur.liste.l_break,$1.valeur.liste.size_l_break,$3.valeur.liste.size_l_break);
                                                $$.valeur.liste.size_l_break = $1.valeur.liste.size_l_break + $3.valeur.liste.size_l_break;
                                                $$.valeur.liste.l_return = concat_liste($1.valeur.liste.l_return,$3.valeur.liste.l_return,$1.valeur.liste.size_l_return,$3.valeur.liste.size_l_return);
                                                $$.valeur.liste.size_l_return = $1.valeur.liste.size_l_return + $3.valeur.liste.size_l_return;
                                                $$.valeur.liste.l_continue = concat_liste($1.valeur.liste.l_continue,$3.valeur.liste.l_continue,$1.valeur.liste.size_l_continue,$3.valeur.liste.size_l_continue);
                                                $$.valeur.liste.size_l_continue = $1.valeur.liste.size_l_continue + $3.valeur.liste.size_l_continue;
                                                // printf("FIN LIST_STATEMENT\n");
                                            }
              |                             {   
                                                $$.valeur.liste.l_break = NULL;
                                                $$.valeur.liste.size_l_break = 0;
                                                $$.valeur.liste.l_continue = NULL;
                                                $$.valeur.liste.size_l_continue = 0;
                                                $$.valeur.liste.next = NULL;
                                                $$.valeur.liste.size_next = 0;
                                                $$.valeur.liste.l_return = NULL;
                                                $$.valeur.liste.size_l_return = 0;
                                            }
              ;

var_decl: type list_var SM                
        ;

list_var: list_var VIRG ID              {   
                                            newname_var($3,$<int_val>0);
                                        }
        | ID                            {
                                            newname_var($1,$<int_val>0);
                                        }
        ;

//si assign_op = = alors copy sinon inc sinon ...

statement: location assign_op expr SM               {   
                                                        if($2==AFF_INC){
                                                            
                                                            if($1.type!=$3.type || $1.type!=T_INT){
                                                                fprintf(stderr,"\t-ERREUR- : Incrementation pas possible là, regarde le man.\n");
                                                            } else {

                                                                symbole* s_temp = newname_temp(T_INT);
                                                                quad_op qo_res;
                                                                qo_res.qo_type = QO_NAME;
                                                                qo_res.qo_valeur.name = s_temp->name;
                                                                

                                                                gencode(Q_ADD,$1.valeur.qo,$3.valeur.qo,qo_res);   
                                                                gencode(Q_COPY,qo_res,qo_vide,$1.valeur.qo);
                                                            }                                                
                                                        }

                                                        if($2==AFF_DEC){
                                                            if($1.type!=$3.type || $1.type!=T_INT){
                                                                fprintf(stderr,"\t-ERREUR- : Décrementation pas possible là, regarde le man.\n");
                                                            } else {
                                                                symbole* s_temp = newname_temp(T_INT);
                                                                quad_op qo_res;
                                                                qo_res.qo_type = QO_NAME;
                                                                qo_res.qo_valeur.name = s_temp->name;

                                                                gencode(Q_SUB,$1.valeur.qo,$3.valeur.qo,qo_res);   
                                                                gencode(Q_COPY,qo_res,qo_vide,$1.valeur.qo);
                                                            }                                                
                                                        }

                                                        if($2==Q_COPY){
                                                            if($1.type==T_INT && $3.type==T_INT){
                                                                gencode($2,$3.valeur.qo,qo_vide,$1.valeur.qo);
                                                            } else if ($1.type==T_BOOL && $3.type==T_BOOL) {
                                                                quad_op qo_true = {QO_CST,1};
                                                                quad_op qo_false = {QO_CST,0};
                                                                quad_op qo_jumb_false = {QO_CST,next_quad+3};

                                                                complete_liste($3.valeur.liste.true,$3.valeur.liste.size_true,next_quad); 
                                                                complete_liste($3.valeur.liste.false,$3.valeur.liste.size_false,next_quad+2); 
                                                                gencode(Q_COPY,qo_true,qo_vide,$1.valeur.qo);
                                                                gencode(Q_GOTO,qo_vide,qo_vide,qo_jumb_false);
                                                                gencode(Q_COPY,qo_false,qo_vide,$1.valeur.qo); 
                                                                                        
                                                            } else {                                            
                                                                fprintf(stderr,"\t-ERREUR- : Pourquoi t'assignes des types différents? Ca compilera pas.\n");
                                                            }
                                                        }

                                                        $$.valeur.liste.next = NULL;
                                                        $$.valeur.liste.size_next = 0;
                                                        $$.valeur.liste.l_break = NULL;
                                                        $$.valeur.liste.size_l_break = 0;
                                                        $$.valeur.liste.l_continue = NULL;
                                                        $$.valeur.liste.size_l_continue = 0;
                                                        $$.valeur.liste.l_return = NULL;
                                                        $$.valeur.liste.size_l_return = 0;

                                                    }
         | IF OP_PAR expr CL_PAR M block                        {
                                                                    //si vrai on va dans block
                                                                    complete_liste($3.valeur.liste.true,$3.valeur.liste.size_true,$5);
                                                                    //si faux ou si fin du block, on sort du statement
                                                                    $$.valeur.liste.next = concat_liste($3.valeur.liste.false,$6.valeur.liste.next,$3.valeur.liste.size_false,$6.valeur.liste.size_next);
                                                                    $$.valeur.liste.size_next = $3.valeur.liste.size_false + $6.valeur.liste.size_next;
                                                                    //si un l_break est reperé dans le block
                                                                    $$.valeur.liste.l_break = $6.valeur.liste.l_break;
                                                                    $$.valeur.liste.size_l_break = $6.valeur.liste.size_l_break;
                                                                    $$.valeur.liste.l_continue = $6.valeur.liste.l_continue;
                                                                    $$.valeur.liste.size_l_continue = $6.valeur.liste.size_l_continue;
                                                                    $$.valeur.liste.l_return = $6.valeur.liste.l_return;
                                                                    $$.valeur.liste.size_l_return = $6.valeur.liste.size_l_return;

                                                                    // int* list_temp = creer_liste(next_quad);
                                                                    // $$.valeur.liste.next = concat_liste($$.valeur.liste.next,list_temp,$$.valeur.liste.size_next,1);
                                                                    // $$.valeur.liste.size_next = $$.valeur.liste.size_next + 1;
                                                                    // gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);
                                                                }
         | IF OP_PAR expr CL_PAR M block ELSE N Nq block        {
                                                                    //on pourrait se passer de N car on a deja un GOTO dans le premier block
                                                                    complete_liste($3.valeur.liste.true,$3.valeur.liste.size_true,$5);
                                                                    complete_liste($3.valeur.liste.false,$3.valeur.liste.size_false,$9);
                                                                    int* temp_l = concat_liste($6.valeur.liste.next,$10.valeur.liste.next,$6.valeur.liste.size_next,$10.valeur.liste.size_next);
                                                                    int temp_s = $6.valeur.liste.size_next + $10.valeur.liste.size_next;
                                                                    $$.valeur.liste.next = concat_liste(temp_l,$8.valeur.liste.next,temp_s,$8.valeur.liste.size_next);
                                                                    $$.valeur.liste.size_next = temp_s + $8.valeur.liste.size_next;

                                                                    $$.valeur.liste.l_break = concat_liste($6.valeur.liste.l_break,$10.valeur.liste.l_break,$6.valeur.liste.size_l_break,$10.valeur.liste.size_l_break);
                                                                    $$.valeur.liste.size_l_break = $6.valeur.liste.size_l_break + $10.valeur.liste.size_l_break;
                                                                    $$.valeur.liste.l_continue = concat_liste($6.valeur.liste.l_continue,$10.valeur.liste.l_continue,$6.valeur.liste.size_l_continue,$10.valeur.liste.size_l_continue);
                                                                    $$.valeur.liste.size_l_continue = $6.valeur.liste.size_l_continue + $10.valeur.liste.size_l_continue;
                                                                    $$.valeur.liste.l_return = concat_liste($6.valeur.liste.l_return,$10.valeur.liste.l_return,$6.valeur.liste.size_l_return,$10.valeur.liste.size_l_return);
                                                                    $$.valeur.liste.size_l_return = $6.valeur.liste.size_l_return + $10.valeur.liste.size_l_return;
                                                                }
         | FOR ID AFF_EQ expr VIRG expr {
             printf("DEB FOR");
            // current_ctx = pushctx(current_ctx);
            current_ctx = pushctx_for(current_ctx);
            gencode(Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);
            symbole* temp = newname_var($2,T_INT);
            temp->protected = 1;
            quad_op qo_ite;
            qo_ite.qo_type = QO_NAME;
            qo_ite.qo_valeur.name = temp->name;

            //protected pour borne inf et borne sup de for
            symbole* bi = lookup($4.valeur.qo.qo_valeur.name,current_ctx);
            symbole* bs = lookup($4.valeur.qo.qo_valeur.name,current_ctx);
            bi->protected = 1;
            bs->protected = 1;

            
            gencode(Q_COPY,$4.valeur.qo,qo_vide,qo_ite);
            
         } M {

            symbole* temp = lookup($2,current_ctx);
            
            quad_op qo_ite;
            qo_ite.qo_type = QO_NAME;
            qo_ite.qo_valeur.name = temp->name;
            // gencode(Q_GREAT,qo_ite,$6.valeur.qo,qo_vide);
            gencode(Q_GREAT,qo_ite,$6.valeur.qo,qo_vide);

            
         } block {
            // printf("PROBLEME NEXT BLOCK: %i",$10.valeur.liste.size_next);
            //on complete le block.next avec l'operation i = i+1
            // printf("BLOCKKK FOR\n");
            complete_liste($10.valeur.liste.next,$10.valeur.liste.size_next,next_quad);
            // printf("FIN BLOCKKK FOR\n");
            symbole* temp = lookup($2,current_ctx);
            // printf("AIE?\n");
            symbole* temp_inc = newname_temp(T_INT);
            // printf("AIE?\n");
            
            
            quad_op qo_ite;
            qo_ite.qo_type = QO_NAME;
            qo_ite.qo_valeur.name = temp->name;
            quad_op qo_un;
            qo_un.qo_type = QO_CST;
            qo_un.qo_valeur.cst = 1;
            quad_op qo_inc;
            qo_inc.qo_type = QO_NAME;
            qo_inc.qo_valeur.name = temp_inc->name;
            
            symbole* new_temp = newname_temp(T_INT);
            
            quad_op qo_temp;
            qo_temp.qo_type = QO_NAME;
            qo_temp.qo_valeur.name = new_temp->name;
            quad_op qo_next;
            qo_next.qo_type = QO_CST;
            qo_next.qo_valeur.cst = $8;

            complete_liste($10.valeur.liste.l_continue,$10.valeur.liste.size_l_continue,next_quad);

            gencode(Q_COPY,qo_un,qo_vide,qo_inc);
            gencode(Q_ADD,qo_ite,qo_inc,qo_temp);
            gencode(Q_COPY,qo_temp,qo_vide,qo_ite);
            // printf("goto for: %i",next_quad);
            gencode(Q_GOTO,qo_vide,qo_vide,qo_next);

            

            //puisque le next du for et l'adresse de sorti du l_break sont les memes
            //elles poitent vers le pop du ctx_for et sa suite avec le goto
            int* temp_list = creer_liste($8);
            int* temp_list_2 = NULL;
            temp_list_2 = concat_liste(temp_list,$10.valeur.liste.l_break,1,$10.valeur.liste.size_l_break);
            complete_liste(temp_list_2,$10.valeur.liste.size_l_break+1,next_quad);
            current_ctx = current_ctx->prec;
            gencode(Q_POP_CTX,qo_vide,qo_vide,qo_vide);

            $$.valeur.liste.next = creer_liste(next_quad);
            $$.valeur.liste.size_next = 1;
            gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);


            $$.valeur.liste.l_break = NULL;
            $$.valeur.liste.size_l_break = 0;
            $$.valeur.liste.l_return = $10.valeur.liste.l_return;
            $$.valeur.liste.size_l_return = $10.valeur.liste.size_l_return;

            // $$.valeur.liste.next = creer_liste($8);
            // $$.valeur.liste.size_next = 1;
         }
         | method_call SM
         | BREAK SM                                             
                                                                {
                                                                    $$.valeur.liste.l_break = creer_liste(next_quad);
                                                                    $$.valeur.liste.size_l_break = 1;

                                                                    // printf("break: %i\n",next_quad);
                                                                    // affiche_liste($$.valeur.liste.l_break,$$.valeur.liste.size_l_break);
                                                                    gencode(Q_BREAK,qo_vide,qo_vide,qo_vide);
                                                                    $$.valeur.liste.next = NULL;
                                                                    $$.valeur.liste.size_next = 0;
                                                                    $$.valeur.liste.l_continue = NULL;
                                                                    $$.valeur.liste.size_l_continue = 0;
                                                                }
         | CONTINUE SM                                          
                                                                {
                                                                    $$.valeur.liste.l_continue = creer_liste(next_quad);
                                                                    $$.valeur.liste.size_l_continue = 1;

                                                                    // printf("break: %i\n",next_quad);
                                                                    // affiche_liste($$.valeur.liste.l_break,$$.valeur.liste.size_l_break);
                                                                    gencode(Q_CONTINUE,qo_vide,qo_vide,qo_vide);
                                                                    $$.valeur.liste.next = NULL;
                                                                    $$.valeur.liste.size_next = 0;
                                                                    $$.valeur.liste.l_continue = NULL;
                                                                    $$.valeur.liste.size_l_continue = 0;
                                                                }
         | block                                                
                                                                {
                                                                    $$.valeur.liste.l_return = $1.valeur.liste.l_return;
                                                                    $$.valeur.liste.size_l_return = $1.valeur.liste.size_l_return;
                                                                    $$.valeur.liste.next = $1.valeur.liste.next;
                                                                    $$.valeur.liste.size_next = $1.valeur.liste.size_next;
                                                                    $$.valeur.liste.l_break = $1.valeur.liste.l_break;
                                                                    $$.valeur.liste.size_l_break = $1.valeur.liste.size_l_break;
                                                                }
         | RETURN rtn_value SM                                            
                                                                {
                                                                    quad_op rtn;
                                                                    rtn.qo_type = QO_NAME;
                                                                    rtn.qo_valeur.name = $2;

                                                                    $$.valeur.liste.l_return = creer_liste(next_quad);
                                                                    $$.valeur.liste.size_l_return = 1;

                                                                    // printf("LISTEEEEEEEEEEEEEEEEE\n");
                                                                    // affiche_liste($$.valeur.liste.l_return,$$.valeur.liste.size_l_return);
                                                                    // printf("break: %i\n",next_quad);
                                                                    // affiche_liste($$.valeur.liste.l_break,$$.valeur.liste.size_l_break);
                                                                    gencode(Q_RETURN,rtn,qo_vide,qo_vide);
                                                                    $$.valeur.liste.next = NULL;
                                                                    $$.valeur.liste.size_next = 0;
                                                                    $$.valeur.liste.l_continue = NULL;
                                                                    $$.valeur.liste.size_l_continue = 0;
                                                                }
         | WI OP_PAR ID CL_PAR SM                               
                                                                {
                                                                    quad_op qo_int;
                                                                    qo_int.qo_type = QO_NAME;
                                                                    qo_int.qo_valeur.name = $3;
                                                                    gencode(Q_AFF_INT,qo_vide,qo_vide,qo_int);
                                                                }
         ;


method_call
    : ID OP_PAR list_method_call_arg CL_PAR 
    {
        //verifier type existence etc etc
        symbole* symb_f = lookup($1,current_ctx);
        quad_op name_f;
        name_f.qo_type = QO_NAME;
        name_f.qo_valeur.name = symb_f->name;
        quad_op nb_arg = { T_INT, $3.size };

        gencode(Q_CALL_FUN,name_f,nb_arg,qo_vide);

        //$$ = $3.size;
    }
    ;

list_method_call_arg
    : method_call_arg
    {
        $$ = $1;
    }
    |
    {
        $$.list = NULL;
        $$.size = 0;
    }
    ;

method_call_arg
    : method_call_arg VIRG expr
    {
        //faire une liste des types et la comparer à la liste des types de la fonction dans method_call
        //si boolean, on doit le reifier
        $$.list = concat_liste_int($1.list,$3.type,$1.size);
        $$.size = $1.size + 1 ;
        quad_op qo_arg;
        qo_arg.qo_type = QO_NAME;
        qo_arg.qo_valeur.name = $3.valeur.qo.qo_valeur.name;
        gencode(Q_PARAM,qo_vide,qo_vide,qo_arg);
    }
    | expr
    {
        $$.list = malloc(1*sizeof(int));
        $$.list[0] = $1.type;
        $$.size = 1;
        quad_op qo_arg;
        qo_arg.qo_type = QO_NAME;
        qo_arg.qo_valeur.name = $1.valeur.qo.qo_valeur.name;
        gencode(Q_PARAM,qo_vide,qo_vide,qo_arg);
    }
    ;

rtn_value
    : ID        
    {
        $$ = $1;
    }
    |           
    {   
        $$ = NULL;
    }
    ;

N:      {
            $$.type = T_BOOL;
            $$.valeur.liste.next = creer_liste(next_quad); 
            $$.valeur.liste.false = NULL;
            $$.valeur.liste.true = NULL;
            $$.valeur.liste.size_next = 1;
            $$.valeur.liste.size_true = 0;
            $$.valeur.liste.size_false = 0;
            gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);
        } 
   ;

Nq:     {
            $$ = next_quad;
        }
    ;



location: ID                            {   

                                            symbole* s_temp = lookup($1,current_ctx);
                                            if(s_temp==NULL) {
                                                fprintf(stderr,"\t-ERREUR- : Faut définir avant.\n");
                                            } else if (s_temp->fonction==F_VAR || s_temp->fonction==F_TEMP || s_temp->fonction==F_ARG || s_temp->fonction==F_ARG_INV) {
                                                $$.type = s_temp->type.simple;
                                                $$.valeur.qo.qo_type = QO_NAME;
                                                $$.valeur.qo.qo_valeur.name = s_temp->name;
                                            }

                                
                                        }
        | ID OP_CRO expr CL_CRO         
        ;

assign_op: AFF_EQ                       {   $$ = Q_COPY;    }
         | AFF_INC                      {   $$ = AFF_INC;   }
         | AFF_DEC                      {   $$ = AFF_DEC;   }
         ;



expr: 
    method_call                         {

//METTRE POUR RES BOOL AUSSI
                                            //recuperer le v0 retourner par le v0
                                            symbole* s_temp = newname_temp(T_INT);

                                            // quad_op vide = {QO_VIDE,-1};
                                            $$.type = T_INT;
                                            $$.valeur.qo.qo_type = QO_NAME;
                                            $$.valeur.qo.qo_valeur.name = s_temp->name;
                                            gencode(Q_RES_FUN,qo_vide,qo_vide,$$.valeur.qo);

                                        }

    | location                          {   

                                            if($1.type==T_BOOL){
                                                $$.type = T_BOOL;
                                                $$.valeur.liste.true = creer_liste(next_quad);
                                                $$.valeur.liste.false = creer_liste(next_quad+1);
                                                $$.valeur.liste.size_true = 1;
                                                $$.valeur.liste.size_false = 1;
                                                gencode(Q_IF,$1.valeur.qo,qo_vide,qo_vide);
                                                gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);                                                
                                            } else if ($1.type==T_INT){
                                                $$ = $1;
                                            } else {
                                                fprintf(stderr,"Je sais pas trop quoi dire là, truc inconnu\n");
                                            }
                                            // $$ = $1; 

                                        }
    | literal                           {   
                                            if($1.type==T_BOOL){
                                                $$.type = T_BOOL;

                                                if($1.valeur.qo.qo_valeur.cst==1){
                                                    $$.valeur.liste.true = creer_liste(next_quad);
                                                    $$.valeur.liste.false = NULL;
                                                    $$.valeur.liste.size_true = 1;
                                                    $$.valeur.liste.size_false = 0;
                                                    gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);
                                                } else {
                                                    $$.valeur.liste.false = creer_liste(next_quad);
                                                    $$.valeur.liste.true = NULL;
                                                    $$.valeur.liste.size_false = 1;
                                                    $$.valeur.liste.size_true = 0;
                                                    gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);
                                                }

                                                // $$.valeur.liste.true = creer_liste(next_quad);
                                                // $$.valeur.liste.false = creer_liste(next_quad+1);
                                                // $$.valeur.liste.size_true = 1;
                                                // $$.valeur.liste.size_false = 1;

                                                // gencode(Q_IF,$1.valeur.symb,NULL,NULL);
                                                // gencode(Q_GOTO,NULL,NULL,NULL);
                                                
                                            }  else if ($1.type==T_INT) {
                                                $$.type = T_INT;
                                                symbole* s_temp = newname_temp(T_INT);
                                                quad_op vide = {QO_VIDE,-1};
                                                $$.valeur.qo.qo_type = QO_NAME;
                                                $$.valeur.qo.qo_valeur.name = s_temp->name;

                                                gencode(Q_COPY,$1.valeur.qo,vide,$$.valeur.qo);
                                            }
                                        }   
    | expr bin_op M expr                {
                                            
                                            if( $2 == Q_ADD ||
                                                $2 == Q_SUB ||
                                                $2 == Q_MULT ||
                                                $2 == Q_DIV ||
                                                $2 == Q_RES)
                                            {
                                                if($1.type!=T_INT || $4.type!=T_INT){
                                                    fprintf(stderr, "\t-ERREUR- : Operations arithmetiques et de comparaison entre entiers seulement. %s,%s\n",$1.valeur.qo.qo_valeur.name,$4.valeur.qo.qo_valeur.name);
                                                } else {
                                                    symbole* s_temp = newname_temp(T_INT);

                                                    $$.type = T_INT;
                                                    $$.valeur.qo.qo_type = QO_NAME;
                                                    $$.valeur.qo.qo_valeur.name = s_temp->name;

                                                    gencode($2,$1.valeur.qo,$4.valeur.qo,$$.valeur.qo);                                                    
                                                }
                                            }


                                            if( $2 == Q_GREAT ||
                                                $2 == Q_GREAT_EQ ||
                                                $2 == Q_LESS ||
                                                $2 == Q_LESS_EQ)
                                            {
                                                if($1.type!=T_INT || $4.type!=T_INT){
                                                    fprintf(stderr, "\t-ERREUR- : Operations arithmetiques et de comparaison entre entiers seulement.\n");
                                                    // return;
                                                } else {
                                                    $$.type = T_BOOL;
                                                    $$.valeur.liste.true = creer_liste(next_quad);
                                                    $$.valeur.liste.false = creer_liste(next_quad+1);
                                                    $$.valeur.liste.size_true = 1;
                                                    $$.valeur.liste.size_false = 1;

                                                    gencode($2,$1.valeur.qo,$4.valeur.qo,qo_vide);
                                                    gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);                                                  
                                                }
                                            }

                                            //type quelconque -> boolean
                                            if( $2 == Q_EQ )
                                            {

                                                if($1.type!=$4.type){
                                                    fprintf(stderr, "\t-ERREUR- : Operations arithmetiques et de comparaison entre entiers seulement.\n");
                                                } else {
                                                    $$.type = T_BOOL;
                                                    if($1.type==T_INT){
                                                        printf("Allo\n");
                                                        $$.valeur.liste.true = creer_liste(next_quad);
                                                        $$.valeur.liste.size_true = 1;
                                                        $$.valeur.liste.false = creer_liste(next_quad+1);
                                                        $$.valeur.liste.size_false = 1;
                                                        gencode(Q_EQ,$1.valeur.qo,$4.valeur.qo,qo_vide);
                                                        gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);

                                                    }

                                                    if($1.type==T_BOOL){
                                                        symbole* s_1 = newname_temp(T_BOOL);
                                                        symbole* s_2 = newname_temp(T_BOOL);
                                                        quad_op b1;
                                                        b1.qo_type = QO_NAME;
                                                        b1.qo_valeur.name = s_1->name;
                                                        quad_op b2;
                                                        b2.qo_type = QO_NAME;
                                                        b2.qo_valeur.name = s_2->name;


                                                        quad_op un;
                                                        un.qo_type = QO_CST;
                                                        un.qo_valeur.cst = 1;
                                                        quad_op zero;
                                                        zero.qo_type = QO_CST;
                                                        zero.qo_valeur.cst = 0;

                                                        quad_op nq;
                                                        nq.qo_type = QO_CST;
                                                        nq.qo_valeur.cst = $3;
                                                        quad_op nq2;
                                                        nq2.qo_type = QO_CST;

                                                        complete_liste($1.valeur.liste.true,$1.valeur.liste.size_true,next_quad);
                                                        complete_liste($1.valeur.liste.false,$1.valeur.liste.size_false,next_quad+2);

                                                        gencode(Q_COPY,un,qo_vide,b1);
                                                        nq2.qo_valeur.cst = next_quad + 2;
                                                        gencode(Q_GOTO,qo_vide,qo_vide,nq2);
                                                        gencode(Q_COPY,zero,qo_vide,b1);
                                                        gencode(Q_GOTO,qo_vide,qo_vide,nq);

                                                        complete_liste($4.valeur.liste.true,$4.valeur.liste.size_true,next_quad);
                                                        complete_liste($4.valeur.liste.false,$4.valeur.liste.size_false,next_quad+2);

                                                        gencode(Q_COPY,un,qo_vide,b2);
                                                        nq2.qo_valeur.cst = next_quad + 2;
                                                        gencode(Q_GOTO,qo_vide,qo_vide,nq2);
                                                        gencode(Q_COPY,zero,qo_vide,b2);

                                                        $$.valeur.liste.true = creer_liste(next_quad);
                                                        $$.valeur.liste.false = creer_liste(next_quad+1);
                                                        $$.valeur.liste.size_true = 1;
                                                        $$.valeur.liste.size_false = 1;
                                                        gencode(Q_EQ,b1,b2,qo_vide);
                                                        gencode(Q_GOTO,qo_vide,qo_vide,qo_vide); 

                                                    }           
                                                }
                                            }

                                            if( $2 == Q_NOT_EQ )
                                            {

                                                if($1.type!=$4.type){
                                                    fprintf(stderr, "\t-ERREUR- : Operations arithmetiques et de comparaison entre entiers seulement.\n");
                                                } else {
                                                    $$.type = T_BOOL;
                                                    if($1.type==T_INT){
                                                        printf("Allo");
                                                        $$.valeur.liste.true = creer_liste(next_quad);
                                                        $$.valeur.liste.size_true = 1;
                                                        $$.valeur.liste.false = creer_liste(next_quad+1);
                                                        $$.valeur.liste.size_false = 1;
                                                        gencode(Q_NOT_EQ,$1.valeur.qo,$4.valeur.qo,qo_vide);
                                                        gencode(Q_GOTO,qo_vide,qo_vide,qo_vide);

                                                    }

                                                    if($1.type==T_BOOL){
                                                        symbole* s_1 = newname_temp(T_BOOL);
                                                        symbole* s_2 = newname_temp(T_BOOL);
                                                        quad_op b1;
                                                        b1.qo_type = QO_NAME;
                                                        b1.qo_valeur.name = s_1->name;
                                                        quad_op b2;
                                                        b2.qo_type = QO_NAME;
                                                        b2.qo_valeur.name = s_2->name;


                                                        quad_op un;
                                                        un.qo_type = QO_CST;
                                                        un.qo_valeur.cst = 1;
                                                        quad_op zero;
                                                        zero.qo_type = QO_CST;
                                                        zero.qo_valeur.cst = 0;

                                                        quad_op nq;
                                                        nq.qo_type = QO_CST;
                                                        nq.qo_valeur.cst = $3;
                                                        quad_op nq2;
                                                        nq2.qo_type = QO_CST;

                                                        complete_liste($1.valeur.liste.true,$1.valeur.liste.size_true,next_quad);
                                                        complete_liste($1.valeur.liste.false,$1.valeur.liste.size_false,next_quad+2);

                                                        gencode(Q_COPY,un,qo_vide,b1);
                                                        nq2.qo_valeur.cst = next_quad + 2;
                                                        gencode(Q_GOTO,qo_vide,qo_vide,nq2);
                                                        gencode(Q_COPY,zero,qo_vide,b1);
                                                        gencode(Q_GOTO,qo_vide,qo_vide,nq);

                                                        complete_liste($4.valeur.liste.true,$4.valeur.liste.size_true,next_quad);
                                                        complete_liste($4.valeur.liste.false,$4.valeur.liste.size_false,next_quad+2);

                                                        gencode(Q_COPY,un,qo_vide,b2);
                                                        nq2.qo_valeur.cst = next_quad + 2;
                                                        gencode(Q_GOTO,qo_vide,qo_vide,nq2);
                                                        gencode(Q_COPY,zero,qo_vide,b2);

                                                        $$.valeur.liste.true = creer_liste(next_quad);
                                                        $$.valeur.liste.false = creer_liste(next_quad+1);
                                                        $$.valeur.liste.size_true = 1;
                                                        $$.valeur.liste.size_false = 1;
                                                        gencode(Q_NOT_EQ,b1,b2,qo_vide);
                                                        gencode(Q_GOTO,qo_vide,qo_vide,qo_vide); 

                                                    }           
                                                }
                                            }

                                            if( $2 == OP_AND )
                                            {
                                                if($1.type!=T_BOOL || $4.type!=T_BOOL){
                                                    fprintf(stderr, "\t-ERREUR- : Operations arithmetiques et de comparaison entre entiers seulement.\n");
                                                } else {
                                                    $$.type = T_BOOL;
                                                    
                                                    complete_liste($1.valeur.liste.true,$1.valeur.liste.size_true,$3);
                                                    
                                                    $$.valeur.liste.false = concat_liste($1.valeur.liste.false,$4.valeur.liste.false,$1.valeur.liste.size_false,$4.valeur.liste.size_false);
                                                    $$.valeur.liste.true = $4.valeur.liste.true;
                                                    $$.valeur.liste.size_false = $1.valeur.liste.size_false + $4.valeur.liste.size_false;
                                                    $$.valeur.liste.size_true = $4.valeur.liste.size_true;  
          
                                                }
                                            }


                                            if( $2 == OP_OR )
                                            {
                                                if($1.type!=T_BOOL || $4.type!=T_BOOL){
                                                    fprintf(stderr, "\t-ERREUR- : Operations arithmetiques et de comparaison entre entiers seulement.\n");
                                                } else {
                                                    $$.type = T_BOOL;
                                                    complete_liste($1.valeur.liste.false,$1.valeur.liste.size_false,$3);
                                                    $$.valeur.liste.true = concat_liste($1.valeur.liste.true,$4.valeur.liste.true,$1.valeur.liste.size_true,$4.valeur.liste.size_true);
                                                    $$.valeur.liste.false = $4.valeur.liste.false;
                                                    $$.valeur.liste.size_true = $1.valeur.liste.size_true + $4.valeur.liste.size_true;
                                                    $$.valeur.liste.size_false = $4.valeur.liste.size_false;               
                                                }
                                            }

                                            //AJOUTER OP_EQ
                                            //AJOUTER OP_NOT_EQ


                                        }
    | OP_SUB expr %prec U_MOINS         {
                                            if($2.type!=T_INT){
                                                fprintf(stderr, "\t-ERREUR- : Depuis quand on soustrait autre chose d'un entier? Réponse? Allo?\n");
                                                // return;
                                            } else {
                                                //CHANGER POUR UTILISER AUTRE TRUC

                                                $$.type = T_INT;
                                                symbole* s_temp = newname_temp(T_INT);
                                                //quad_op q_zero = {QO_CST,0};
                                                // $$.valeur.qo =  {QO_NAME,s_temp->name};
                                                $$.valeur.qo.qo_type = QO_NAME;
                                                $$.valeur.qo.qo_valeur.name = s_temp->name;
                                                //gencode($1,q_zero,$2.valeur.qo,$$.valeur.qo);  
                                                gencode(Q_NEG,$2.valeur.qo,qo_vide,$$.valeur.qo);                                                  
                                            }     
                                        }
    //corriger le OP_NOT expr en ajoutant une condition sur le type de $2
    | OP_NOT expr                       {
                                            if($2.type!=T_BOOL){
                                                fprintf(stderr, "\t-ERREUR- : Ca va pas compiler ça non? Tu sais pourquoi? Ben faut lire le man, je vais pas tout faire\n");
                                            } else {
                                                $$.type = T_BOOL;
                                                $$.valeur.liste.true = $2.valeur.liste.false;
                                                $$.valeur.liste.false = $2.valeur.liste.true;
                                                $$.valeur.liste.size_true = $2.valeur.liste.size_false;
                                                $$.valeur.liste.size_false = $2.valeur.liste.size_true;

                                            }
                                        }
    | OP_PAR expr CL_PAR                { 
                                            $$ = $2;
                                        }
    ;

M:              {   $$ = next_quad; }
    ;

bin_op: arith_op                        { $$ = $1; }      
      | rel_op                          { $$ = $1; }
      | eq_op                           { $$ = $1; }
      | cond_op                         { $$ = $1; }
      ;

arith_op: OP_PLUS                       { $$ = Q_ADD; }
        | OP_SUB                        { $$ = Q_SUB; }
        | OP_MULT                       { $$ = Q_MULT; }
        | OP_DIV                        { $$ = Q_DIV; }
        | OP_RES                        { $$ = Q_RES; }
        ;

rel_op: OP_GREA                         { $$ = Q_GREAT; }
      | OP_GREA_EQ                      { $$ = Q_GREAT_EQ; }
      | OP_LESS                         { $$ = Q_LESS; }
      | OP_LESS_EQ                      { $$ = Q_LESS_EQ; }
      ;

eq_op: OP_EQ                            { $$ = Q_EQ; }
     | OP_NOT_EQ                        { $$ = Q_NOT_EQ; }
     ;

cond_op: OP_AND                         { $$ = OP_AND; }
       | OP_OR                          { $$ = OP_OR; }
       ;

literal: int_literal        {   $$ = $1;    }
       | bool_literal       {   $$ = $1;    }
       | CHAR_LIT
       ;

int_literal: DEC_LIT            {   
                                    $$.type = T_INT;
                                    // $$.valeur.qo = {QO_CST,$1};

                                    $$.valeur.qo.qo_type = QO_CST;
                                    $$.valeur.qo.qo_valeur.cst = $1;
                                }
           | HEX_LIT            {
                                    $$.type = T_INT;
                                    // $$.valeur.qo = {QO_CST,$1};
                                    $$.valeur.qo.qo_type = QO_CST;
                                    $$.valeur.qo.qo_valeur.cst = $1;
                                }
           ;

bool_literal: BOOL_FALSE        {
                                    $$.type = T_BOOL;
                                    // $$.valeur.qo = {QO_CST,0};
                                    $$.valeur.qo.qo_type = QO_CST;
                                    $$.valeur.qo.qo_valeur.cst = 0;
                                }
            | BOOL_TRUE         {
                                    $$.type = T_BOOL;
                                    // $$.valeur.qo = {QO_CST,1};
                                    $$.valeur.qo.qo_type = QO_CST;
                                    $$.valeur.qo.qo_valeur.cst = 1;
                                }
            ;



%%

void yyerror (const char* msg){
    fprintf(stderr,"%s\n",msg);
}



symbole* newname_var(char* name, type_simple type) {

    int ind_symb = ++current_ctx->size_tab;

    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    current_ctx->tab[ind_symb-1].protected = 0;
    current_ctx->tab[ind_symb-1].name = name;
    current_ctx->tab[ind_symb-1].fonction = F_VAR;
    current_ctx->tab[ind_symb-1].type.simple = type;

    return &(current_ctx->tab[ind_symb-1]);

}

symbole* newname_arg(char* name, type_simple type) {

    int ind_symb = ++current_ctx->size_tab;

    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    current_ctx->tab[ind_symb-1].protected = 0;
    current_ctx->tab[ind_symb-1].name = name;
    current_ctx->tab[ind_symb-1].fonction = F_ARG;
    current_ctx->tab[ind_symb-1].type.simple = type;

    return &(current_ctx->tab[ind_symb-1]);

}

symbole* newname_proc(char* name, type_simple* arg_type, int size_arg, type_simple return_type) {

    int ind_symb = ++current_ctx->size_tab;

    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    current_ctx->tab[ind_symb-1].protected = 1;
    current_ctx->tab[ind_symb-1].name = name;
    current_ctx->tab[ind_symb-1].fonction = F_PROC;
    current_ctx->tab[ind_symb-1].type.proc.nb_arg = size_arg;
    current_ctx->tab[ind_symb-1].type.proc.arg = arg_type;
    current_ctx->tab[ind_symb-1].type.proc.retour = return_type;

    return &(current_ctx->tab[ind_symb-1]);

}

symbole* newname_tab(char* name, type_simple type, int size) {

    int ind_symb = ++current_ctx->size_tab;

    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    current_ctx->tab[ind_symb-1].protected = 1;
    current_ctx->tab[ind_symb-1].name = name;
    current_ctx->tab[ind_symb-1].fonction = F_TAB;
    current_ctx->tab[ind_symb-1].type.tab.size = size; 
    current_ctx->tab[ind_symb-1].type.tab.simple = type; 

    return &(current_ctx->tab[ind_symb-1]);

}

//attention taille de name
symbole* newname_temp(type_simple type) {
    // printf("NEWNAME BUG\n");
// printf("NEWNAME BUG %i\n",current_ctx);
    int ind_symb = ++current_ctx->size_tab;
    // printf("NEWNAME BUG\n");
    current_ctx->tab = realloc(current_ctx->tab,ind_symb*sizeof(symbole));
    // printf("NEWNAME BUG\n");
    current_ctx->tab[ind_symb-1].name = malloc(5*sizeof(char));
    // printf("NEWNAME BUG\n");
    snprintf(current_ctx->tab[ind_symb-1].name,5,"$%i",nb_temp);
    current_ctx->tab[ind_symb-1].protected = 0;
    // printf("NEWNAME BUG\n");
    // snprintf(current_ctx->tab)
    current_ctx->tab[ind_symb-1].fonction = F_TEMP;
    current_ctx->tab[ind_symb-1].type.simple = type; 

    nb_temp++;

    // printf("FIN NEWNAME BUG\n");

    return &(current_ctx->tab[ind_symb-1]);

}



void gencode(int operation, quad_op q1, quad_op q2, quad_op q3) {

    code_inter[next_quad].q_type = operation;
    code_inter[next_quad].q1 = q1;
    code_inter[next_quad].q2 = q2;
    code_inter[next_quad].q3 = q3;

    next_quad++;

}

// void print_type_symb(symbole* s){

//     first_ctx
//     int t = s->type;
//     if(t==T_INT){
//         printf("%s\t","INT");
//     } else if (t==T_BOOL){
//         printf("%s\t","BOOL");
//     }
// }





char* print_type_quad(quad q) {
    
    int op = q.q_type;
    for(int i = 0; i<nb_type; i++){
        if(numero_type[i]==op){
            return nom_type[i];
            break;
        }
    }
    return "RIEN";

}

// char[] print_type_quad_op(quad_op qo) {
    
//     if( qo.type==QO_CST ) {
//         return "CST";
//     } else if ( qo.type==QO_NAME ) {
//         return "VAR";
//     }
//     return "RIEN";

// }


void print_quad(quad q){

    
    int op = q.q_type;
    for(int i = 0; i<nb_type; i++){
        if(numero_type[i]==op){
            printf("| %s |",nom_type[i]);
        }
    }

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


// void print_tab_symb(){
//     printf("TAB_SYMBOLE:\n");
//     for(size_t i = 0; i<next_symb; i++){
//         if(tab_symbole[i].format==F_CST){
//             print_type_symb(&tab_symbole[i]);
//             printf("%li CST : %i\n",i,tab_symbole[i].valeur.const_int);
//         }
//         if(tab_symbole[i].format==F_NAME){
//             print_type_symb(&tab_symbole[i]);
//             printf("%li VAR : %s\n",i,tab_symbole[i].valeur.name);
//         }
//     }
// }


char* print_type_simple(int t) {
    if( t==T_INT ) {
        return "INT";
    } else if ( t==T_BOOL) {
        return "BOOL";
    } else if ( t== T_VOID) {
        return "VOID";
    }
    return "RIEN";
}

void print_symb(symbole* s){

    int f = s->fonction;
    if( f==F_VAR ) {

        printf("%s:\t%s",print_type_simple(s->type.simple),s->name);

    } else if ( f==F_PROC ) {

        printf("%s(",print_type_simple(s->type.proc.retour));
        for(int i=0; i<s->type.proc.nb_arg; i++) {
            printf(" %s ",print_type_simple(s->type.proc.arg[i]));
        }
        printf("):\t%s",s->name);

    } else if ( f==F_TAB ) {

        printf("%s[%i]:\t%s",print_type_simple(s->type.tab.simple),s->type.tab.size,s->name);

    } else if ( f==F_TEMP ) {

        printf("%s:\t%s",print_type_simple(s->type.simple),s->name);

    } else if ( f==F_ARG ) {

        printf("%s:\t%s",print_type_simple(s->type.simple),s->name);

    } else if ( f==F_ARG_INV ) {

        printf("%s:\t%s",print_type_simple(s->type.simple),s->name);

    }

}

// void print_tab_symb(){
//     printf("TAB_SYMBOLE:\n");
//     int decal = 0;

//     for(size_t i = 0; i<next_symb; i++){
//         if(tab_symbole[i].format==F_CST){
//             print_type_symb(&tab_symbole[i]);
//             printf("%li CST : %i\n",i,tab_symbole[i].valeur.const_int);
//         }
//         if(tab_symbole[i].format==F_NAME){
//             print_type_symb(&tab_symbole[i]);
//             printf("%li VAR : %s\n",i,tab_symbole[i].valeur.name);
//         }
//     }
// }

//print_tab_symb en recurrence
void print_tab_symb(ctx* ctx, int decal){
    if(ctx==NULL){
        printf("Table symbole vide\n");
        return;
    }
    
    // printf("SIZE_TAB_SYMB: %i\n",ctx->size_tab);
    for(int i=0; i<ctx->size_tab; i++) {
        
        for(int j=0; j<decal; j++){
            printf("\t");
        }
        printf("-");
        // printf("numero_symbole_ctx=%i",i);
        print_symb(&(ctx->tab[i]));
        printf("\n");
    }

    for(int k=0; k<ctx->size_next; k++){
        // printf("numero_ctx_enfant=%i",k);
        print_tab_symb(ctx->next[k],decal+1);        
    }


}


void print_code_inter(){
    printf("====CODE INTER:====\n");
    for(size_t i = 0; i<next_quad; i++){
        printf("%lu\t",i);
        print_quad(code_inter[i]);
        printf("\n");
    }    
}

// symbole* find_in_tab_symb(char* name){
//     for(size_t i = 0; i<next_symb; i++){
//         if(tab_symbole[i].format==F_NAME){
//             if(strcmp(name,tab_symbole[i].valeur.name)==0){
//                 return &tab_symbole[i];
//             }
//         }
//     }
//     return NULL;
// }

int* creer_liste(int nq){
    // printf("Debut: CL\t");
    int* list = malloc(sizeof(int));
    list[0] = nq;
    // printf("Fin: CL\n");

    return list;
}


int* concat_liste(int* p1, int* p2, int size1, int size2){
    // printf("Debut: ConL\t");

    // printf("%i,%i\n=============\n",size1,size2);

    if(size1+size2 == 0){
        return NULL;
    }

    int* p_res = realloc(p1,(size1+size2)*sizeof(int));
    for(int i = 0; i<size2; i++){

        p_res[i+size1] = p2[i];
    }

    free(p2);
    // printf("Fin: ConL\n");

    return p_res;
}

int* concat_liste_int(int* p1, int p2, int size1){
    // printf("Debut: ConL\t");

    int* p_res = realloc(p1,(size1+1)*sizeof(int));
    p_res[size1] = p2;

    // printf("Fin: ConL\n");

    return p_res;
}

// void complete_liste(int* p, int size, int q){
//     // printf("Debut: ComL\t");

//     symbole* s = new_const_branch(q);
//     for(int i = 0; i<size; i++){
//         code_inter[p[i]].s3 = s;
//     }
//     // printf("Fin: ComL\n");
//     free(p);

// }

//complete la liste p des quad incomplet de taille size avec le quad_op numero q
void complete_liste(int* p, int size, int q){
    // printf("Debut: ComL\t");

    // symbole* s = new_const_branch(q);
    quad_op res = {QO_CST,q};
    for(int i = 0; i<size; i++){
        code_inter[p[i]].q3 = res;
    }
    // printf("Fin: ComL\n");
    free(p);

}


void affiche_liste(int* p, int size){
    // printf("LISTE \n");
    for(int i = 0; i<size; i++){
        printf(" %i",p[i]);
    }
    // printf("\n");

}




int dist_pile(char* str, ctx* ctx1){
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



void open_write_file(){
    FILE* f_ptr = fopen("test_ar.s", "w+");
    if(f_ptr==NULL){
        fprintf(stderr,"Terriblement embarrassant\n");
        return;
    }
    fprintf(f_ptr,"\t.text\n");
    
    ctx* ite = NULL;

    // fprintf(f_ptr,"main:\n");

    for(int i = 0; i<next_quad; i++){
        if(code_inter[i].q_type == Q_IF ||
           code_inter[i].q_type == Q_EQ ||
           code_inter[i].q_type == Q_NOT_EQ ||
           code_inter[i].q_type == Q_LESS ||
           code_inter[i].q_type == Q_LESS_EQ ||
           code_inter[i].q_type == Q_GREAT ||
           code_inter[i].q_type == Q_GREAT_EQ ||
           code_inter[i].q_type == Q_GOTO )
        {
            
            tab_label_check[code_inter[i].q3.qo_valeur.cst]=1;
        }
    }


    for(int i = 0; i<next_quad; i++){
        
        
        printf("%i:\n",i);


        if(tab_label_check[i]==1){
            fprintf(f_ptr,"label%i:\n",i);
        }
        
        
        if(code_inter[i].q_type == Q_PUSH_CTX){
            // printf("Q_PUSH\n");
            
            //ajout du contexte à la pile de mips
            if(ite==NULL){
                // printf("NULL\n");
                ite = first_ctx;
                ite->marqueur = 0;
            } else {

                printf("NEXT\n");
                print_tab_symb(ite,0);
                
                int i = 0;
                while(ite->next[i]->marqueur==1){
                    printf("%i\n",i);
                    i++;
                }
                ite = ite->next[i];

            }            

            // print_tab_symb(ite,0);

            for(int j = 0; j<ite->size_tab; j++){
                if(ite->tab[j].fonction != F_ARG_INV 
                && ite->tab[j].fonction != F_PROC ){
                    fprintf(f_ptr,"\t#pile <= %s\n",ite->tab[j].name);
                    fprintf(f_ptr,"\taddiu $sp, $sp, -4\n");
                }
            }

            
        } else if (code_inter[i].q_type == Q_POP_CTX) {
            printf("Q_POP\n");
            //retrait du contexte à la pile de mips
            // printf("ite : %i\n",ite);
            print_tab_symb(ite,0);
            for(int j = 0; j<ite->size_tab; j++){
                if(ite->tab[j].fonction != F_ARG_INV 
                && ite->tab[j].fonction != F_PROC ){
                    fprintf(f_ptr,"\t#pile => %s\n",ite->tab[j].name);
                    fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
                }
            }
            
            ite->marqueur = 1;
            ite = ite->prec;
        } else if (code_inter[i].q_type == Q_COPY) {
            //q3 est forcement une variable sur la pile
            if(code_inter[i].q1.qo_type==QO_NAME) {
                //ld adresse q1 dans registre $t0 (dist au sommet du ctx)
                //ld adresse q3 dans registre $t1 (dist au sommet du ctx)
                int place_pile_arg = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_dest = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_arg = 4*place_pile_arg;
                place_pile_dest = 4*place_pile_dest;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg);
                fprintf(f_ptr,"\tsw $t0, %i($sp)\n",place_pile_dest);
            } else if (code_inter[i].q1.qo_type==QO_CST) {
                // printf("=CST\n");
                //li Rdest,imm
                int place_pile_dest = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_dest = 4*place_pile_dest;
                fprintf(f_ptr,"\tli $t0, %i\n",code_inter[i].q1.qo_valeur.cst);
                fprintf(f_ptr,"\tsw $t0, %i($sp)\n",place_pile_dest);
            }
        } else if (code_inter[i].q_type == Q_ADD) {
            //q3 est forcement une variable sur la pile
            if(code_inter[i].q1.qo_type==QO_NAME) {
                //ld adresse q1 dans registre $t0 (dist au sommet du ctx)
                //ld adresse q3 dans registre $t1 (dist au sommet du ctx)
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                int place_pile_dest = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                place_pile_dest = 4*place_pile_dest;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);
                fprintf(f_ptr,"\tadd $t0, $t0, $t1\n");
                fprintf(f_ptr,"\tsw $t0, %i($sp)\n",place_pile_dest);
            }
        } else if (code_inter[i].q_type == Q_SUB) {
            //q3 est forcement une variable sur la pile
            if(code_inter[i].q1.qo_type==QO_NAME) {
                //ld adresse q1 dans registre $t0 (dist au sommet du ctx)
                //ld adresse q3 dans registre $t1 (dist au sommet du ctx)
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                int place_pile_dest = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                place_pile_dest = 4*place_pile_dest;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);
                fprintf(f_ptr,"\tsub $t0, $t0, $t1\n");
                fprintf(f_ptr,"\tsw $t0, %i($sp)\n",place_pile_dest);
            }
        } else if (code_inter[i].q_type == Q_MULT) {
            //q3 est forcement une variable sur la pile
            if(code_inter[i].q1.qo_type==QO_NAME) {
                //ld adresse q1 dans registre $t0 (dist au sommet du ctx)
                //ld adresse q3 dans registre $t1 (dist au sommet du ctx)
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                int place_pile_dest = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                place_pile_dest = 4*place_pile_dest;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);
                fprintf(f_ptr,"\tmul $t0, $t0, $t1\n");
                fprintf(f_ptr,"\tsw $t0, %i($sp)\n",place_pile_dest);
            }
        } else if (code_inter[i].q_type == Q_DIV) {
            //q3 est forcement une variable sur la pile
            if(code_inter[i].q1.qo_type==QO_NAME) {
                //ld adresse q1 dans registre $t0 (dist au sommet du ctx)
                //ld adresse q3 dans registre $t1 (dist au sommet du ctx)
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                int place_pile_dest = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                place_pile_dest = 4*place_pile_dest;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);
                fprintf(f_ptr,"\tdiv $t0, $t0, $t1\n");
                fprintf(f_ptr,"\tsw $t0, %i($sp)\n",place_pile_dest);
            }
        } else if (code_inter[i].q_type == Q_NEG) {
            //q3 est forcement une variable sur la pile
            if(code_inter[i].q1.qo_type==QO_NAME) {
                //ld adresse q1 dans registre $t0 (dist au sommet du ctx)
                //ld adresse q3 dans registre $t1 (dist au sommet du ctx)
                int place_pile_arg = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_dest = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_arg = 4*place_pile_arg;
                place_pile_dest = 4*place_pile_dest;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg);
                fprintf(f_ptr,"\tneg $t0, $t0\n");
                fprintf(f_ptr,"\tsw $t0, %i($sp)\n",place_pile_dest);
            }
        } else if (code_inter[i].q_type == Q_AFF_INT) {
            //q3 est forcement une variable sur la pile
            if(code_inter[i].q3.qo_type==QO_NAME) {
                //ld adresse q1 dans registre $t0 (dist au sommet du ctx)
                //ld adresse q3 dans registre $t1 (dist au sommet du ctx)
                int place_pile_arg = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_arg = 4*place_pile_arg;
                fprintf(f_ptr,"\tli $v0, 1\n");
                fprintf(f_ptr,"\tlw $a0, %i($sp)\n",place_pile_arg);
                fprintf(f_ptr,"\tsyscall\n");
            }
        } else if (code_inter[i].q_type == Q_GOTO) {
            printf("TEST\n");
            if( code_inter[i].q3.qo_valeur.cst == -1 ){
                printf("ALLO\n");
                continue;
            }
            
            if(code_inter[i].q3.qo_type==QO_CST) {
                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tb label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_IF) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                place_pile_arg = 4*place_pile_arg;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg);
                fprintf(f_ptr,"\tli $t1, 1\n");

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tbeq $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_LESS) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tblt $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_GREAT) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tbgt $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_FOR) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tbgt $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_LESS_EQ) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tble $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_GREAT_EQ) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tbge $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_EQ) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tbeq $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_NOT_EQ) {
            if(code_inter[i].q1.qo_type==QO_NAME) {
                int place_pile_arg_1 = dist_pile(code_inter[i].q1.qo_valeur.name,ite);
                int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
                place_pile_arg_1 = 4*place_pile_arg_1;
                place_pile_arg_2 = 4*place_pile_arg_2;
                fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg_1);
                fprintf(f_ptr,"\tlw $t1, %i($sp)\n",place_pile_arg_2);

                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tbne $t0, $t1, label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_BREAK) {
            //compte le nombre de var avant le dernier CTX_FOR
            // printf("ON EST DANS Q BREAK:\n");
            // print_tab_symb(ite->prec,0);
            // printf("%i %i\n",ite->prec->ctx_type,CTX_FOR);
            ctx* ite_for = ite;
            int itera = 0;
            while(ite_for->ctx_type!=CTX_FOR){
                // printf("ctx %i: \t",0);
                for(int j = 0; j<ite_for->size_tab; j++){
                    // printf("%i\n",j);
                    fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
                }
           
                ite_for->marqueur = 1;
                ite_for = ite_for->prec;
                itera++;
            }

            if(code_inter[i].q3.qo_type==QO_CST) {
                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tb label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_CONTINUE) {
            //compte le nombre de var avant le dernier CTX_FOR
            // printf("ON EST DANS Q CONTINUE:\n");
            // print_tab_symb(ite->prec,0);
            // printf("%i %i\n",ite->prec->ctx_type,CTX_FOR);
            ctx* ite_for = ite;
            int itera = 0;
            while(ite_for->ctx_type!=CTX_FOR){
                // printf("ctx %i: \t",0);
                for(int j = 0; j<ite_for->size_tab; j++){
                    // printf("%i\n",j);
                    fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
                }
           
                ite_for->marqueur = 1;
                ite_for = ite_for->prec;
                itera++;
            }

            if(code_inter[i].q3.qo_type==QO_CST) {
                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tb label%i\n",code_inter[i].q3.qo_valeur.cst);
            }
        } else if (code_inter[i].q_type == Q_DEF_FUN) {
            //A ce point, on a deja toute la tab des symbole et la pile qui va avec
            //fun                   
            //      arg1            <= point ou on est quand on fait Q_DEF_FUN
            //      arg2
            //      fp
            //      ra
            //              deb block


            if(code_inter[i].q2.qo_type==QO_NAME) {
                tab_label_check[i] = 1;
                fprintf(f_ptr,"%s:\n",code_inter[i].q2.qo_valeur.name);
            }

            int nb_arg = 0;
            if(code_inter[i].q1.qo_type==QO_CST) {
                nb_arg = code_inter[i].q1.qo_valeur.cst;
            }
            fprintf(f_ptr,"\taddiu $sp, $sp, -4\n");
            fprintf(f_ptr,"\taddiu $sp, $sp, -4\n");

            //sauvegarde fp et ra
            fprintf(f_ptr,"\tsw $fp, 4($sp)\n");
            fprintf(f_ptr,"\tsw $ra, 0($sp)\n");

            //calcul de fp
            // fprintf(f_ptr,"\tla $t0, $sp\n");
            // fprintf(f_ptr,"\tlw $t1, %i\n",);
            fprintf(f_ptr,"\taddiu $fp, $sp, %i\n",4*(nb_arg+2));

        } else if (code_inter[i].q_type == Q_RETURN) {
            
//Q_RETURN doit annuler les blocs (les piles d'arguments crées dans les blocs ) DANSSSS LE MIPS PAS DANS ite
            //var de retour
            char* rtn = code_inter[i].q1.qo_valeur.name;
            
            // fprintf(f_ptr,"AIEdsdsfds\n");
            // int place_pile_arg_2 = dist_pile(code_inter[i].q2.qo_valeur.name,ite);
            
            // place_pile_arg_1 = 4*place_pile_arg_1;
            // place_pile_arg_2 = 4*place_pile_arg_2;
            if(rtn!=NULL){
                int place_pile_rtn = dist_pile(rtn,ite);
                place_pile_rtn = 4*place_pile_rtn;
                fprintf(f_ptr,"\tlw $v0, %i($sp)\n",place_pile_rtn);
                // fprintf(f_ptr,"\tsw $t0, $v0\n");
            }
            ctx* ite_for = ite;
            //tant que j'ai pas trouvé fp ra et arg, je remonte en annulant les ctx
            while(ite_for->ctx_type!=CTX_FUN){
                // printf("ctx %i: \t",0);
                // printf("%s\n");
                for(int j = 0; j<ite_for->size_tab; j++){
                    // printf("%i\n",j);
                    fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
                }
           
                ite_for->marqueur = 0;
                ite_for = ite_for->prec;
            }
        
            // fprintf(f_ptr,"AIE\n");
            // if(rtn!=NULL){
            //     if( strcmp(rtn,"main") == 0 )
            //     {
            //         printf("%s\n",rtn);
            //         fprintf(f_ptr,"\tli $v0, 10\n\tsyscall\n");
            //     }
            // }

            if( code_inter[i].q3.qo_type == QO_CST ) 
            {
                tab_label_check[code_inter[i].q3.qo_valeur.cst] = 1;
                fprintf(f_ptr,"\tb label%i\n",code_inter[i].q3.qo_valeur.cst);
            } else {
                fprintf(f_ptr,"\tli $v0, 10\n\tsyscall\n");
            }
            

        } else if (code_inter[i].q_type == Q_END_FUN) {
            //s'occupe de ranger la pile et les registres
            //restauration de ra et fp
            // fprintf(f_ptr,"\tlw $t0, 0($sp)\n");
            fprintf(f_ptr,"\tlw $ra, 0($sp)\n");  
            // fprintf(f_ptr,"\tlw $t0, 4($sp)\n");
            fprintf(f_ptr,"\tlw $fp, 4($sp)\n");
            
            int nb_arg = code_inter[i].q1.qo_valeur.cst;
            for(int i = 0; i<2; i++){
                fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
            }



            // for(int j = 0; j<2; j++){
            //     ite->marqueur = 1;
            //     ite = ite->prec;
            // }
            

            if( strcmp(code_inter[i].q2.qo_valeur.name,"main") == 0 ) 
            {
                fprintf(f_ptr,"\tli $v0, 10\n\tsyscall\n");
            } else {
                fprintf(f_ptr,"\tjr $ra\n");
            }

                  

        } else if ( code_inter[i].q_type == Q_PARAM ) {
            //gencode(Q_PARAM,qo_vide,qo_vide,qo_arg);
            int place_pile_arg = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
            //on va aggrandir la pile d'un en mettant l'argument donc place_pile_arg+1
            place_pile_arg = 4*(place_pile_arg+1);
            fprintf(f_ptr,"\taddiu $sp, $sp, -4\n");
            fprintf(f_ptr,"\tlw $t0, %i($sp)\n",place_pile_arg);
            fprintf(f_ptr,"\tsw $t0, 0($sp)\n");
            
        } else if ( code_inter[i].q_type == Q_CALL_FUN ) {
            //gencode(Q_CALL_FUN,name_f,nb_arg,qo_vide);
            int nb_arg = code_inter[i].q2.qo_valeur.cst;

            fprintf(f_ptr,"\tjal %s\n",code_inter[i].q1.qo_valeur.name);
            // fprintf(f_ptr,"#arg=%i\n",nb_arg);
            for(int k = 0; k<nb_arg; k++){
                fprintf(f_ptr,"\taddiu $sp, $sp, 4\n");
            }
            
        } else if ( code_inter[i].q_type == Q_RES_FUN ) {
            if(code_inter[i].q3.qo_type==QO_NAME){
                int place_pile_res = dist_pile(code_inter[i].q3.qo_valeur.name,ite);
                place_pile_res = 4*place_pile_res;
                fprintf(f_ptr,"\tsw $v0, %i($sp)\n",place_pile_res);
            }
        }




        
    }
    
    fprintf(f_ptr,"\tli $v0, 10\n\tsyscall\n");






    fclose(f_ptr);
}
