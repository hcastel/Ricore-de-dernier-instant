#ifndef QUAD_H
#define QUAD_H

//Ensemble des opérations possibles pour les quadruplets
enum q_type {
    Q_ADD,
    Q_SUB,
    Q_MULT,
    Q_DIV,
    Q_RES,
    Q_EQ,
    Q_NOT_EQ,
    Q_LESS,
    Q_GREAT,
    Q_LESS_EQ,
    Q_GREAT_EQ,
    Q_COPY,
    Q_GOTO,
    Q_IF,
    Q_PUSH_CTX,
    Q_POP_CTX,
    Q_AFF_INT,
    Q_NEG,
    Q_FOR,
    Q_BREAK,
    Q_CONTINUE,
    Q_DEF_METH,
    Q_RETURN,
    Q_END_METH,
    Q_CALL_METH,
    Q_PARAM,
    Q_PRINT,
};
typedef enum q_type q_type;

//Types de base
enum type_simple {
    T_INT,
    T_BOOL,
    T_VOID,
    T_STRING,
    T_CHAR,
};
typedef enum type_simple type_simple;


//Opérateur d'un quadruplet quad
struct quad_op {
    
    enum qo_type {
        QO_VIDE,
        QO_CST,
        QO_NAME,
    } qo_type;

    union qo_valeur {
        int cst;
        char* name;
    } qo_valeur;
};
typedef struct quad_op quad_op;


//quadruplet : instruction , op1, op2, op3
struct quad {

    q_type q_type;

    quad_op q1, q2, q3;

};
typedef struct quad quad;

//nouveau quad_op constant
void new_qo_cst(int cst, quad_op* res);
//nouveau quad_op qui a pour nom name
void new_qo_name(char* name, quad_op* res);
//nouveau quad_op vide
void new_qo_vide(quad_op* res);

#endif