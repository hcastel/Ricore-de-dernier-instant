%code requires{
    #include "include/quad.h"   
    #include "include/write_code.h" 
}

%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "include/quad.h"
    #include "include/liste.h"
    #include "include/table_symb.h"

    #define TAB_SYMBOLES (*((ctx**)tab_symbole))
    #define ERROR(msg) yyerror(tab_symbole,code_inter,next_quad,"-ERREUR-\t"msg".")
    #define CHECK_NOT_REDEF(new_symb)   if((new_symb)==NULL){ \
                                        ERROR("Redéfinition d'un identifiant de la même portée"); \
                                        YYABORT; \
                                    }

    extern int yylex();
    /* extern int numero_type[]; */
    #define YYDEBUG 1

    void yyerror (void**,void**,int*,const char* msg);

    //LONGUEUR MAXIMALE D'UN NOM DE TEMPORAIRE
    #define SIZE_MAX_NAME_TEMP 10

    //ITERATEUR DU NOMBRE DE TEMPORAIRES
    int num_temp = 0;

    //QUAD_OP SOUVENT UTILISES
    quad_op qo_vide = {QO_VIDE,-1};
    quad_op qo_un = {QO_CST,1};
    quad_op qo_zero = {QO_CST,0};

    //AJOUTE LE CODE A code_inter
    void gencode(void**,int*,q_type,quad_op,quad_op,quad_op);

    //COMPLETE LES QUADS DONT LE NUMERO EST DANS l PAR q
    void complete_liste(void** code_inter, int* l, int size, int q);

    //ITERATEUR DE CTX DE LA TABLE
    ctx* current_ctx = NULL;    

    extern char yytext[];
%}


%token VIRG
%token OP_PAR
%token OP_CRO
%token OP_BRA
%token CL_BRA
%token CL_CRO
%token CL_PAR
%token BEG SM
%token TYPE_VOID
%token U_MOINS
%token IF
%token ELSE
%token FOR
%token BREAK
%token CONTINUE
%token RETURN

%union{
    char *str_val;
    long int int_val;

    // liste de types (typiquement utilisée pour les arguments de fonction)
    types_liste types_liste;
    // liste contenant l'état d'un bloc (break, return, etc...)
    control_liste control_liste;
    // expr (listes booléennes, entier, etc...)
    expr_val expr_val;
}

%token <str_val> ID
%token <str_val> STRING_LIT

%token <int_val> HEX_LIT
%token <int_val> DEC_LIT
%token <int_val> CHAR_LIT
%token WS
%token BOOL_TRUE
%token BOOL_FALSE
%token OP_PLUS
%token OP_SUB
%token OP_MULT
%token OP_DIV
%token OP_RES
%token OP_LESS
%token OP_GREAT
%token OP_LESS_EQ
%token OP_GREAT_EQ
%token OP_EQ
%token OP_NOT_EQ
%token OP_AND
%token OP_OR
%token OP_NOT
%token AFF_EQ
%token AFF_INC
%token AFF_DEC
%token TYPE_INT
%token TYPE_BOOL


%type <expr_val> location
%type <expr_val> literal
%type <expr_val> expr
%type <expr_val> int_literal
%type <expr_val> bool_literal
%type <expr_val> method_call
%type <expr_val> return_res

%type <control_liste> block
%type <control_liste> statements
%type <control_liste> statement
%type <control_liste> N

%type <types_liste> method_decl_args
%type <types_liste> method_decl_arg
%type <types_liste> method_call_args
%type <types_liste> method_call_arg

%type <int_val> assign_op
%type <int_val> M
%type <int_val> type


%left OP_OR
%left OP_AND
%left OP_EQ OP_NOT_EQ
%left OP_LESS OP_LESS_EQ OP_GREAT OP_GREAT_EQ
%left OP_PLUS OP_SUB
%left OP_MULT OP_DIV OP_RES
%left OP_NOT
%left U_MOINS


%parse-param { void** tab_symbole } { void* code_inter[] } { int* next_quad }
%start program


%%

program: 
    BEG ID OP_BRA push_deb field_decls method_decls pop CL_BRA
            {
                int trouve = 0;

                for(int i = 0; i<TAB_SYMBOLES->size_tab; i++){
                    if(strcmp(TAB_SYMBOLES->tab[i].name,"main")==0
                    && TAB_SYMBOLES->tab[i].type.proc.nb_arg==0
                    && TAB_SYMBOLES->tab[i].type.proc.retour==T_VOID){
                        trouve=1;
                    }
                }
                
                if(trouve==0){
                    ERROR("Main non défini");
                    YYABORT;
                }
            }
    ;

push_deb:
    %empty
            {
                TAB_SYMBOLES = push_ctx(TAB_SYMBOLES, CTX_SIMP);
                current_ctx = TAB_SYMBOLES;

                int* list_i = malloc(1*sizeof(int));
                list_i[0] = T_INT;
                newname_proc_ext("WriteInt",list_i,1,T_VOID,current_ctx);

                int* list_b = malloc(1*sizeof(int));
                list_b[0] = T_BOOL;
                newname_proc_ext("WriteBool",list_b,1,T_VOID,current_ctx);

                newname_proc_ext("ReadInt",NULL,0,T_INT,current_ctx);

                gencode(code_inter,next_quad,Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);
            }
    ;


field_decls:
    field_decls field_decl
    | %empty
    ;

field_decl:
    type field_ids SM
    ;

field_ids:
    field_ids VIRG field_id
    | field_id
    ;

field_id:
    ID
            {
                CHECK_NOT_REDEF(newname_var_glb($1,$<int_val>0,current_ctx))
            }
    | ID OP_CRO int_literal CL_CRO
            {
                CHECK_NOT_REDEF(newname_tab($1,$<int_val>0,$3.result.qo.qo_valeur.cst,current_ctx))
            }
    ;

method_decls:
    method_decls method_decl
    | method_decl
    ;

method_decl:
    type ID 
            {
                if( strncmp("label",$2,5)==0 ){
                    ERROR("Méthode commencant par label interdite");
                    YYABORT;
                }
                CHECK_NOT_REDEF(newname_proc($2,NULL,0,$1,current_ctx))
            }
    push OP_PAR method_decl_args
            {
                symbole* s_meth = look_up($2,TAB_SYMBOLES);
                s_meth->type.proc.nb_arg = $6.size;
                s_meth->type.proc.arg = $6.list;
                s_meth->type.proc.retour = $1;

                write_method_void_decl_args(code_inter, next_quad, current_ctx, &num_temp, s_meth, $6);
            }
    CL_PAR block
            {
                if($9.size_return!=0 && $9.type_return!=$1){
                    ERROR("Types de retour incohérents");
                    YYABORT;
                }

                quad_op qo_name_meth, qo_nb_arg;
                new_qo_name(look_up($2,TAB_SYMBOLES)->name,&(qo_name_meth));
                new_qo_cst($6.size,&(qo_nb_arg));
                
                gencode(code_inter,next_quad,Q_END_METH,qo_vide,qo_vide,qo_vide);
                complete_liste(code_inter,$9.l_return,$9.size_return,(*next_quad));
                gencode(code_inter,next_quad,Q_END_METH,qo_name_meth,qo_nb_arg,qo_vide);  
            }
    pop
    | TYPE_VOID ID
            {
                if( strncmp("label",$2,5)==0 ){
                    ERROR("Mot commencant par label interdit");
                    YYABORT;
                }
                CHECK_NOT_REDEF(newname_proc($2,NULL,0,T_VOID,current_ctx))
            }
    push OP_PAR method_decl_args
            {
                symbole* s_meth = look_up($2,TAB_SYMBOLES);
                s_meth->type.proc.nb_arg = $6.size;
                s_meth->type.proc.arg = $6.list;
                s_meth->type.proc.retour = T_VOID;

                write_method_void_decl_args(code_inter, next_quad, current_ctx, &num_temp, s_meth, $6);
            }
    CL_PAR block
            {
                if($9.size_return!=0 && $9.type_return!=T_VOID){
                    ERROR("Types de retour incohérents");
                    YYABORT;
                }
                
                quad_op qo_name_meth, qo_nb_arg;
                new_qo_name(look_up($2,TAB_SYMBOLES)->name,&(qo_name_meth));
                new_qo_cst($6.size,&(qo_nb_arg));

                complete_liste(code_inter,$9.l_return,$9.size_return,(*next_quad));
                gencode(code_inter,next_quad,Q_END_METH,qo_name_meth,qo_nb_arg,qo_vide);
            }
    pop
    ;

method_decl_args:
    method_decl_arg
            {
                $$ = $1;
            }
    | %empty
            {
                $$.list = NULL;
                $$.size = 0;
            }
    ;

method_decl_arg:
    method_decl_arg VIRG type ID
            {
                CHECK_NOT_REDEF(newname_arg($4,$3,current_ctx))
                $$.list = concat_liste_int((int*)$1.list,$3,$1.size,&($$.size));
            }
    | type ID
            {
                CHECK_NOT_REDEF(newname_arg($2,$1,current_ctx))
                $$.list = malloc(1*sizeof(int));
                $$.list[0] = $1;
                $$.size = 1;
            }
    ;

block:
    OP_BRA push var_decls statements M pop CL_BRA
            {
                complete_liste(code_inter,$4.l_next,$4.size_next,$5);
                $$ = $4;
                $$.l_next = creer_liste((*next_quad),&($$.size_next));
                gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);
            }
    ;

push:
    %empty
            {
                current_ctx = push_ctx(current_ctx, CTX_SIMP);
                gencode(code_inter,next_quad,Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);
            }
    ;

pop:
    %empty
            {
                current_ctx = current_ctx->prec;
                gencode(code_inter,next_quad,Q_POP_CTX,qo_vide,qo_vide,qo_vide);
            }
    ;

var_decls:
    var_decls var_decl
    | %empty
    ;

var_decl:
    type var_ids SM
    ;

var_ids:
    var_ids VIRG ID
            {
                CHECK_NOT_REDEF(newname_var($3,$<int_val>0,current_ctx))
            }
    | ID
            {
                CHECK_NOT_REDEF(newname_var($1,$<int_val>0,current_ctx))
            }
    ;

type: 
    TYPE_INT 
            {
                $$ = T_INT;
            }
    | TYPE_BOOL  
            {
                $$ = T_BOOL;
            }                  
    ;

statements:
    statements M statement
            {
                complete_liste(code_inter,$1.l_next,$1.size_next,$2);
                $$.l_next = $3.l_next;
                $$.size_next = $3.size_next;
                $$.l_break = concat_listes($1.l_break,$3.l_break,$1.size_break,$3.size_break,&($$.size_break));
                $$.l_continue = concat_listes($1.l_continue,$3.l_continue,$1.size_continue,$3.size_continue,&($$.size_continue));
                $$.l_return = concat_listes($1.l_return,$3.l_return,$1.size_return,$3.size_return,&($$.size_return));
                
                if( $1.type_return==T_VOID){
                    $$.type_return=$3.type_return;
                } else if( $3.type_return==T_VOID){
                    $$.type_return=$1.type_return;
                } else if( $3.type_return!=$1.type_return ){
                    ERROR("Types de retour incohérents");
                    YYABORT;
                } else {
                    $$.type_return=$3.type_return;
                }
            }
    | %empty
            {
                $$.l_break = creer_liste_vide(&($$.size_break));
                $$.l_continue = creer_liste_vide(&($$.size_continue));
                $$.l_return = creer_liste_vide(&($$.size_return));
                $$.l_next = creer_liste_vide(&($$.size_next));
                $$.type_return = T_VOID;
            }
    ;

statement:
    WS OP_PAR literal CL_PAR SM
            {
                if($3.type!=T_STRING){
                    ERROR("WriteString n'accepte que des Strings en argument");
                    YYABORT;
                }             
                gencode(code_inter,next_quad,Q_PRINT,qo_vide,qo_vide,$3.result.qo);
                write_empty_stat(&$$);
            } 
    | location assign_op expr SM
            {
                // entier
                // Q_COPY : loc : _ : result
                // tab
                // Q_COPY : loc : dplc : result
                // loc ou result sont des tableaux, on le verifie apres                
                
                if($2==AFF_INC){    
                    if($1.type!=T_INT || $3.type!=T_INT){
                        ERROR("Incrémentation entre entiers uniquement");
                        YYABORT;
                    } else {
                        write_inc_dec(code_inter, next_quad, current_ctx, &num_temp, $1, $3, Q_ADD);
                    }
                }

                if($2==AFF_DEC){
                    if($1.type!=T_INT || $3.type!=T_INT){
                        ERROR("Décrémentation entre entiers uniquement");
                        YYABORT;   
                    } else {
                        write_inc_dec(code_inter, next_quad, current_ctx, &num_temp, $1, $3, Q_SUB);
                    }                                                
                }

                if($2==Q_COPY){
                    if($1.type==T_INT && $3.type==T_INT){
                        gencode(code_inter,next_quad,Q_COPY,$3.result.qo,$1.dplc,$1.result.qo);
                    } else if ($1.type==T_BOOL && $3.type==T_BOOL) {
                        write_assign_bool(code_inter, next_quad, current_ctx, $1, $3);
                    } else {
                        ERROR("Assignation entre types différents interdite");
                        YYABORT;
                    }
                }

                $$.l_next = creer_liste_vide(&$$.size_next);
                $$.l_continue = creer_liste_vide(&$$.size_continue);
                $$.l_break = creer_liste_vide(&$$.size_break);
                $$.l_return = creer_liste_vide(&$$.size_return);
                $$.type_return = T_VOID;

            }
    | method_call SM
            {
                write_empty_stat(&$$);
            }
    | IF OP_PAR expr CL_PAR M block
            {
                if( $3.type != T_BOOL ){
                    ERROR("L'expression évaluée dans le if doit être booléenne");
                    YYABORT;
                } else {
                    write_if_stat(code_inter, next_quad, current_ctx, &num_temp, $3, $5, $6, &$$);
                }
            }
    | IF OP_PAR expr CL_PAR M block ELSE N M block
            {
                if( $3.type != T_BOOL ){
                    ERROR("L'expression évaluée dans le if doit être booléenne");
                    YYABORT;
                } else {
                    write_if_else_stat(code_inter, next_quad, current_ctx, &num_temp, $3, $5, $6, $8, $9, $10, &$$);

                    if( $6.type_return==T_VOID){
                        $$.type_return=$10.type_return;
                    } else if( $10.type_return==T_VOID){
                        $$.type_return=$6.type_return;
                    } else if( $10.type_return!=$6.type_return ){
                        ERROR("Types de retour incohérents");
                        YYABORT;
                    } else {
                        $$.type_return=$6.type_return;
                    }            
                }
            
            }
    | FOR ID AFF_EQ expr VIRG expr
            {
                if( $4.type!=T_INT || $6.type!=T_INT ){
                    ERROR("Les bornes de la boucle for doivent être des entiers");
                    YYABORT;
                }

                current_ctx = push_ctx(current_ctx, CTX_FOR);
                gencode(code_inter,next_quad,Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);
                
                //protection des variables de controle de la boucle for
                symbole* s_ite;
                s_ite=newname_var($2,T_INT,current_ctx);

                quad_op qo_ite;
                new_qo_name(s_ite->name,&(qo_ite));
                
                //ite = borne_inf
                gencode(code_inter,next_quad,Q_COPY,$4.result.qo,qo_vide,qo_ite);
            }
    M  
            {
                //vérification que ite < borne_sup
                quad_op qo_ite;
                new_qo_name(look_up($2,current_ctx)->name,&(qo_ite));
                gencode(code_inter,next_quad,Q_GREAT,qo_ite,$6.result.qo,qo_vide); 
            }
    block
            {

                write_end_loop_for_stat(code_inter, next_quad, &current_ctx, &num_temp, $2, $8, $10);

                //on part de la boucle
                $$.l_next = creer_liste((*next_quad),&($$.size_next));
                $$.l_continue = creer_liste_vide(&($$.size_continue));
                $$.l_break = creer_liste_vide(&($$.size_break));
                $$.l_return = $10.l_return;
                $$.size_return = $10.size_return;
                $$.type_return = $10.type_return;

                gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);
            }
    | RETURN return_res SM
            {
                write_empty_stat(&$$);   
                write_return_stat(code_inter, next_quad, current_ctx, &num_temp, $2, &$$);
            }
    | BREAK SM
            {
                if( dans_ctx_for(current_ctx)==0 ){
                    ERROR("Instruction break en-dehors d'une boucle for");
                    YYABORT;
                }
                write_empty_stat(&$$);
                $$.l_break = creer_liste((*next_quad),&($$.size_break));
                gencode(code_inter,next_quad,Q_BREAK,qo_vide,qo_vide,qo_vide);
            }
    | CONTINUE SM
            {
                if( dans_ctx_for(current_ctx)==0 ){
                    ERROR("Instruction continue en-dehors d'une boucle for");
                    YYABORT;
                }
                write_empty_stat(&$$);
                $$.l_continue = creer_liste((*next_quad),&($$.size_continue));
                gencode(code_inter,next_quad,Q_CONTINUE,qo_vide,qo_vide,qo_vide);
            }
    | block
            {
                $$ = $1;
            }
    ;

return_res:
    expr
            {
                $$ = $1;
            }
    | %empty
            {
                $$.type = T_VOID;
                new_qo_vide(&$$.dplc);
                new_qo_vide(&$$.result.qo);
            }
    ;

N:  
    %empty    
            {
                $$.l_next = creer_liste((*next_quad),&($$.size_next));
                gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);
            } 
   ;


assign_op:
    AFF_EQ
            {   
                $$ = Q_COPY;    
            }
    | AFF_INC
            {
                $$ = AFF_INC;
            }
    | AFF_DEC
            {
                $$ = AFF_DEC;
            }
    ;



method_call:
    ID OP_PAR method_call_args CL_PAR
            {
               
                
                symbole* s_meth = look_up($1,TAB_SYMBOLES);

                //vérification de l'existence de la methode
                if(s_meth==NULL || s_meth->fonction!=F_METH){
                    ERROR("Appel à une méthode non définie");
                    YYABORT;
                }
                //vérification du nombre d'arguments
                if(s_meth->type.proc.nb_arg!=$3.size){
                    ERROR("Nombre d'arguments incohérent");
                    YYABORT;
                }
                //vérification du type
                for(int i = 0; i<$3.size; i++){
                    if( s_meth->type.proc.arg[i]!=$3.list[i] ){
                        ERROR("Le type des arguments de l'appel ne correspond pas à la définition de la méthode");
                        YYABORT;
                    }
                }

                write_method_call(code_inter, next_quad, current_ctx, &num_temp, s_meth, $3, &$$);
            }
    ;

method_call_args:
    method_call_arg
            {
                $$ = $1;
                for(int i = 0; i<$1.size; i++){
                    quad_op qo_depl;
                    new_qo_cst(i+1,&(qo_depl));
                    gencode(code_inter,next_quad,Q_PARAM,qo_depl,qo_vide,($$.list_arg)[i]);
                }
            }
    | %empty
            {
                $$.list_arg = NULL;
                $$.list = NULL;
                $$.size = 0;
            }
    ;

method_call_arg:
    method_call_arg VIRG expr
            {
                $$.list = concat_liste_int((int*)$1.list,$3.type,$1.size,&($$.size));
                $$.list_arg = realloc($1.list_arg,($1.size +1)*sizeof(quad_op));

                quad_op qo_arg, qo_depl;
                //réification
                if($3.type==T_BOOL){
                    complete_liste(code_inter,$3.result.liste_bool.liste_true,$3.result.liste_bool.size_true,(*next_quad));
                    complete_liste(code_inter,$3.result.liste_bool.liste_false,$3.result.liste_bool.size_false,(*next_quad)+2);
                    
                    symbole* s_temp = newname_temp(T_BOOL,current_ctx,&(num_temp));
                    quad_op qo_next;
                    new_qo_name(s_temp->name,&(qo_arg));
                    new_qo_cst((*next_quad)+3,&qo_next);

                    gencode(code_inter,next_quad,Q_COPY,qo_un,qo_vide,qo_arg);
                    gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_next);
                    gencode(code_inter,next_quad,Q_COPY,qo_zero,qo_vide,qo_arg); 
                } else if ($3.type==T_INT){
                    new_qo_name($3.result.qo.qo_valeur.name,&(qo_arg));
                }

                new_qo_name(qo_arg.qo_valeur.name,&($$.list_arg[$1.size]));

            }
    | expr
            {
                $$.list = malloc(1*sizeof(int));
                $$.list[0] = $1.type;
                $$.size = 1;
                $$.list_arg = malloc(1*sizeof(quad_op));

                quad_op qo_arg, qo_depl;
                //réification
                if($1.type==T_BOOL){
                    complete_liste(code_inter,$1.result.liste_bool.liste_true,$1.result.liste_bool.size_true,(*next_quad));
                    complete_liste(code_inter,$1.result.liste_bool.liste_false,$1.result.liste_bool.size_false,(*next_quad)+2);
                    
                    symbole* s_temp = newname_temp(T_BOOL,current_ctx,&(num_temp));
                    quad_op qo_next;
                    new_qo_name(s_temp->name,&(qo_arg));
                    new_qo_cst((*next_quad)+3,&qo_next);


                    gencode(code_inter,next_quad,Q_COPY,qo_un,qo_vide,qo_arg);
                    gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_next);
                    gencode(code_inter,next_quad,Q_COPY,qo_zero,qo_vide,qo_arg); 
                } else if ($1.type==T_INT){
                    new_qo_name($1.result.qo.qo_valeur.name,&(qo_arg));
                }
                
                new_qo_name(qo_arg.qo_valeur.name,&($$.list_arg[0]));

            }
    ;

location:
    ID
        //[name]  => [name,type_name]
            {
                symbole* s_id = look_up($1,current_ctx);
                if( s_id==NULL ){
                    ERROR("Symbole non défini");
                    YYABORT;
                }
                if( s_id->fonction!=F_METH
                 && s_id->fonction!=F_TAB
                 && s_id->fonction!=F_TEMP)
                {
                    $$.type = s_id->type.simple;
                    new_qo_vide(&($$.dplc));
                    new_qo_name(s_id->name,&($$.result.qo));
                } else {
                    ERROR("Utilisation impossible de la variable");
                    YYABORT;
                }
            }
    | ID OP_CRO expr CL_CRO
        //[name,index]  => [name,index,type_tab]
            {
                symbole* s_tab = look_up($1,current_ctx);
                
                if(s_tab==NULL){
                    ERROR("Tableau non défini");
                    YYABORT;
                }
                if($3.type!=T_INT){
                    ERROR("Index du tableau non entier");
                    YYABORT;
                }

                if( s_tab->fonction==F_TAB ){
                    $$.type = s_tab->type.tab.simple;
                    $$.dplc = $3.result.qo;
                    new_qo_name(s_tab->name,&($$.result.qo));
                } else {
                    ERROR("La variable ne correspond pas à un tableau");
                    YYABORT;
                }
            }
    ;


//expr contient uniquement des temporaires int ou des listes booleans
expr:
    location
        //[tab,index,int]   => [temp,int]
        //[var,int]         => [temp,int]
        //[tab,index,bool]  => [list,bool]
        //[var,bool]        => [list,bool]
            {   
                if( $1.type==T_BOOL ){
                    write_location_bool_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, &$$);
                } else if ( $1.type==T_INT ){
                    write_location_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, &$$);
                } else {
                    ERROR("Type de l'identificateur non reconnu");
                    YYABORT;
                }
            }
    | method_call
        //[temp,int] => [temp,int]
        //[temp,bool] => [list,bool]
            {
                $$.type = $1.type;
                new_qo_vide(&($$.dplc));
                if( $1.type == T_INT ){
                    $$ = $1;
                } else if ( $1.type == T_BOOL ) {
                    //return renvoie un boolean réifié, on deréifie
                    $$.result.liste_bool.liste_true = creer_liste((*next_quad),&($$.result.liste_bool.size_true));
                    $$.result.liste_bool.liste_false = creer_liste((*next_quad)+1,&($$.result.liste_bool.size_false));
                    gencode(code_inter,next_quad,Q_IF,$1.result.qo,qo_vide,qo_vide);
                    gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);                     
                } else {
                    ERROR("Retour de méthode incompatible avec les calculs");
                    YYABORT;
                }
            }
    | literal
        //[cst,bool]   => [list,bool]
        //[cst,int]    => [temp,int]
            {
                if( $1.type == T_BOOL ){
                    write_bool_to_expr(code_inter,next_quad,$1,&$$);
                } else if( $1.type == T_INT ){
                    write_int_to_expr(code_inter,next_quad,current_ctx,&num_temp,$1,&$$);
                } else {
                    ERROR("Littéral non reconnu");
                    YYABORT;                    
                }
            }
    | expr OP_PLUS expr
        //[temp,int] => [temp,int]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),$1,$3,&$$,Q_ADD);  
                }   
            }
    | expr OP_SUB expr
        //[temp,int] => [temp,int]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),$1,$3,&$$,Q_SUB); 
                }
            }
    | expr OP_MULT expr
        //[temp,int] => [temp,int]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),$1,$3,&$$,Q_MULT);
                }
            }
    | expr OP_DIV expr
        //[temp,int] => [temp,int]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),$1,$3,&$$,Q_DIV);
                }
            }
    | expr OP_RES expr
        //[temp,int] => [temp,int]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),$1,$3,&$$,Q_RES);
                }
            }
    | expr OP_GREAT expr
        //[temp,int] => [list,bool]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, &$$, Q_GREAT);
                }
            }
    | expr OP_GREAT_EQ expr
        //[temp,int] => [list,bool]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, &$$, Q_GREAT_EQ);
                }
            }
    | expr OP_LESS expr
        //[temp,int] => [list,bool]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, &$$, Q_LESS);
                }
            }
    | expr OP_LESS_EQ expr
        //[temp,int] => [list,bool]
            {
                if( $1.type!=T_INT || $3.type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, &$$, Q_LESS_EQ);
                }
            }
    | expr OP_EQ M expr
        //[temp,int]    => [list,bool]
        //[list,bool]   => [list,bool]
            {
                if( $1.type!=$4.type ){
                    ERROR("Comparaison d'égalité seulement entre mêmes types");
                    YYABORT;
                } else {
                    if( $1.type==T_INT ){
                        write_op_eq_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $4, &$$, Q_EQ);                 
                    }
                    if( $1.type==T_BOOL ){
                        write_op_eq_bool_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, $4, &$$, Q_EQ);
                    }
                }
            }
    | expr OP_NOT_EQ M expr
        //[temp,int]    => [list,bool]
        //[list,bool]   => [list,bool]
            {
                if( $1.type!=$4.type ){
                    ERROR("Comparaison d'égalité seulement entre mêmes types");
                    YYABORT;
                } else {
                    if( $1.type==T_INT ){
                        write_op_eq_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $4, &$$, Q_NOT_EQ);                      
                    }
                    if( $1.type==T_BOOL ){
                        write_op_eq_bool_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, $4, &$$, Q_NOT_EQ);                       
                    }
                }
            }
    | expr OP_OR M expr
        //[list,bool]   => [list,bool]
            {
                if( $1.type!=T_BOOL 
                 || $4.type!=T_BOOL )
                {
                    ERROR("Opération OR entre booléens seulement");
                    YYABORT;
                } else {
                    write_or_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, $4, &$$);
                }                   
            }
    | expr OP_AND M expr
        //[list,bool]   => [list,bool]
            {
                if( $1.type!=T_BOOL 
                    || $4.type!=T_BOOL )
                {
                    ERROR("Opération AND entre booléens seulement");
                    YYABORT;
                } else {
                    write_and_to_expr(code_inter, next_quad, current_ctx, &num_temp, $1, $3, $4, &$$);
                }                       
            }

    | OP_SUB expr %prec U_MOINS 
        //[temp,int]   => [temp,int]
            {
                if( $2.type!=T_INT ){
                    ERROR("L'opération unaire - ne s'applique qu'aux entiers");
                    YYABORT;
                } else {
                    write_neg_to_expr(code_inter, next_quad, current_ctx, &num_temp, $2, &$$);
                }                
            }
    | OP_NOT expr
        //[list,bool]   => [list,bool]
            {
                if( $2.type!=T_BOOL ){
                    ERROR("L'opérateur ! ne s'applique qu'aux booléens");
                    YYABORT;
                } else {
                    write_not_to_expr(code_inter, next_quad, current_ctx, &num_temp, $2, &$$);
                }
            }
    | OP_PAR expr CL_PAR
            {
                $$ = $2;
            }
    ;

M:
    %empty              
            {   
                $$ = (*next_quad); 
            }
    ;



literal: 
    int_literal   
        //[cst,int] => [cst,int]  
            {
                $$ = $1;
            }
    | bool_literal    
        //[cst,bool] => [cst,bool]    
            {
                $$ = $1;
            }
    | CHAR_LIT
            {
                $$.type = T_INT;
                new_qo_vide(&($$.dplc));
                new_qo_cst($1,&($$.result.qo));                
            }
    | STRING_LIT
            {
                $$.type = T_STRING;
                symbole* str = newname_string($1,TAB_SYMBOLES,&num_temp);
                new_qo_name(str->name,&($$.result.qo));                 
            }
    ;

int_literal: 
    DEC_LIT
            {
                $$.type = T_INT;
                if(-2147483648>$1 || $1>2147483648){
                    ERROR("Décimal hors limites");
                    YYABORT;
                }
                new_qo_vide(&($$.dplc));
                new_qo_cst($1,&($$.result.qo));
            }
    | HEX_LIT   
            {
                $$.type = T_INT;
                printf("%li",$1);
                if(-2147483648>$1 || $1>2147483648){
                    ERROR("Décimal hors limites");
                    YYABORT;
                }
                new_qo_vide(&($$.dplc));
                new_qo_cst($1,&($$.result.qo));
            }         
    ;

bool_literal: 
    BOOL_FALSE
            {
                $$.type = T_BOOL;
                new_qo_vide(&($$.dplc));
                new_qo_cst(0,&($$.result.qo));
            }
    | BOOL_TRUE 
            {
                $$.type = T_BOOL;
                new_qo_vide(&($$.dplc));
                new_qo_cst(1,&($$.result.qo));
            }
    ;


%%

void yyerror (void** tab_symbole, void** code_inter, int* next_quad, const char* msg){
    fprintf(stderr,"%s\n",msg);
}

void new_qo_cst(int cst, quad_op* res){
    res->qo_type = QO_CST;
    res->qo_valeur.cst = cst;
}
void new_qo_name(char* name, quad_op* res){
    res->qo_type = QO_NAME;
    res->qo_valeur.name = name;
}
void new_qo_vide(quad_op* res){
    res->qo_type = QO_VIDE;
    res->qo_valeur.cst = -1;
}